#include "fortnite_replay/crypto.hpp"

#include <algorithm>
#include <cstring>
#include <filesystem>

// OpenSSL for AES decryption
#include <openssl/evp.h>
#include <openssl/err.h>

// zlib for fallback decompression (keeping include for potential future use)
// #include <zlib.h>

// Platform-specific dynamic library loading
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace fortnite_replay
{

    // ============================================================================
    // Error Strings
    // ============================================================================

    const char *crypto_error_string(CryptoError error)
    {
        switch (error)
        {
        case CryptoError::Success:
            return "Success";
        case CryptoError::InvalidKeySize:
            return "Invalid key size (expected 32 bytes for AES-256)";
        case CryptoError::InvalidDataSize:
            return "Invalid data size (must be multiple of block size)";
        case CryptoError::DecryptionFailed:
            return "Decryption failed";
        case CryptoError::KeyNotSet:
            return "Encryption key not set";
        case CryptoError::InvalidCompressedData:
            return "Invalid compressed data";
        case CryptoError::DecompressionFailed:
            return "Decompression failed";
        case CryptoError::OutputBufferTooSmall:
            return "Output buffer too small";
        case CryptoError::DecompressorNotAvailable:
            return "Decompressor not available";
        case CryptoError::InvalidInput:
            return "Invalid input";
        case CryptoError::InternalError:
            return "Internal error";
        }
        return "Unknown error";
    }

    // ============================================================================
    // AesDecryptor Implementation
    // ============================================================================

    struct AesDecryptor::Impl
    {
        EVP_CIPHER_CTX *ctx = nullptr;
        std::vector<uint8_t> key;
        bool key_set = false;

        Impl()
        {
            ctx = EVP_CIPHER_CTX_new();
        }

        ~Impl()
        {
            if (ctx)
            {
                EVP_CIPHER_CTX_free(ctx);
            }
        }

        Impl(Impl &&other) noexcept
            : ctx(other.ctx), key(std::move(other.key)), key_set(other.key_set)
        {
            other.ctx = nullptr;
            other.key_set = false;
        }

        Impl &operator=(Impl &&other) noexcept
        {
            if (this != &other)
            {
                if (ctx)
                {
                    EVP_CIPHER_CTX_free(ctx);
                }
                ctx = other.ctx;
                key = std::move(other.key);
                key_set = other.key_set;
                other.ctx = nullptr;
                other.key_set = false;
            }
            return *this;
        }
    };

    AesDecryptor::AesDecryptor() : m_impl(std::make_unique<Impl>()) {}

    AesDecryptor::~AesDecryptor() = default;

    AesDecryptor::AesDecryptor(AesDecryptor &&) noexcept = default;
    AesDecryptor &AesDecryptor::operator=(AesDecryptor &&) noexcept = default;

    CryptoResult<void> AesDecryptor::set_key(std::span<const uint8_t> key)
    {
        if (key.size() != KEY_SIZE)
        {
            return std::unexpected(CryptoError::InvalidKeySize);
        }

        m_impl->key.assign(key.begin(), key.end());
        m_impl->key_set = true;
        return {};
    }

    CryptoResult<void> AesDecryptor::set_key(const std::vector<uint8_t> &key)
    {
        return set_key(std::span<const uint8_t>(key));
    }

    bool AesDecryptor::has_key() const
    {
        return m_impl->key_set;
    }

    CryptoResult<void> AesDecryptor::decrypt_inplace(std::span<uint8_t> data)
    {
        if (!m_impl->key_set)
        {
            return std::unexpected(CryptoError::KeyNotSet);
        }

        if (data.empty())
        {
            return {};
        }

        if (data.size() % BLOCK_SIZE != 0)
        {
            return std::unexpected(CryptoError::InvalidDataSize);
        }

        // Initialize decryption context for AES-256-ECB
        if (!EVP_DecryptInit_ex(m_impl->ctx, EVP_aes_256_ecb(), nullptr,
                                m_impl->key.data(), nullptr))
        {
            return std::unexpected(CryptoError::DecryptionFailed);
        }

        // Disable padding (Fortnite data is already aligned)
        EVP_CIPHER_CTX_set_padding(m_impl->ctx, 0);

        int out_len = 0;
        int total_len = 0;

        // Decrypt the data
        if (!EVP_DecryptUpdate(m_impl->ctx, data.data(), &out_len,
                               data.data(), static_cast<int>(data.size())))
        {
            return std::unexpected(CryptoError::DecryptionFailed);
        }
        total_len = out_len;

        // Finalize (should be a no-op with padding disabled)
        if (!EVP_DecryptFinal_ex(m_impl->ctx, data.data() + total_len, &out_len))
        {
            return std::unexpected(CryptoError::DecryptionFailed);
        }

        return {};
    }

    CryptoResult<std::vector<uint8_t>> AesDecryptor::decrypt(std::span<const uint8_t> encrypted_data)
    {
        std::vector<uint8_t> result(encrypted_data.begin(), encrypted_data.end());
        auto status = decrypt_inplace(result);
        if (!status)
        {
            return std::unexpected(status.error());
        }
        return result;
    }

    CryptoResult<std::vector<uint8_t>> AesDecryptor::decrypt(
        std::span<const uint8_t> key,
        std::span<const uint8_t> encrypted_data)
    {
        AesDecryptor decryptor;
        auto key_result = decryptor.set_key(key);
        if (!key_result)
        {
            return std::unexpected(key_result.error());
        }
        return decryptor.decrypt(encrypted_data);
    }

    // ============================================================================
    // OodleDecompressor Implementation
    // ============================================================================

    // Oodle function signature
    using OodleLZ_Decompress_Func = int64_t (*)(
        const uint8_t *src_buf, int64_t src_len,
        uint8_t *dst_buf, int64_t dst_len,
        int fuzz, int crc, int verbose,
        uint8_t *dst_base, int64_t e, void *cb, void *cb_ctx,
        void *scratch, int64_t scratch_size, int threadPhase);

    struct OodleDecompressor::Impl
    {
#ifdef _WIN32
        HMODULE library = nullptr;
#else
        void *library = nullptr;
#endif
        OodleLZ_Decompress_Func decompress_func = nullptr;
        std::string loaded_path;

        ~Impl()
        {
            if (library)
            {
#ifdef _WIN32
                FreeLibrary(library);
#else
                dlclose(library);
#endif
            }
        }

        bool load_library(const std::string &path)
        {
#ifdef _WIN32
            HMODULE lib = LoadLibraryA(path.c_str());
            if (!lib)
            {
                return false;
            }
            auto func = reinterpret_cast<OodleLZ_Decompress_Func>(
                GetProcAddress(lib, "OodleLZ_Decompress"));
            if (!func)
            {
                FreeLibrary(lib);
                return false;
            }
            library = lib;
            decompress_func = func;
#else
            void *lib = dlopen(path.c_str(), RTLD_NOW);
            if (!lib)
            {
                return false;
            }
            auto func = reinterpret_cast<OodleLZ_Decompress_Func>(
                dlsym(lib, "OodleLZ_Decompress"));
            if (!func)
            {
                dlclose(lib);
                return false;
            }
            library = lib;
            decompress_func = func;
#endif
            loaded_path = path;
            return true;
        }

        std::vector<std::string> get_search_paths() const
        {
            std::vector<std::string> paths;

#ifdef _WIN32
            // Common Fortnite installation paths on Windows
            paths.push_back("oo2core_9_win64.dll");
            paths.push_back("C:\\Program Files\\Epic Games\\Fortnite\\FortniteGame\\Binaries\\Win64\\oo2core_9_win64.dll");
            paths.push_back("C:\\Program Files (x86)\\Epic Games\\Fortnite\\FortniteGame\\Binaries\\Win64\\oo2core_9_win64.dll");
#elif __APPLE__
            // macOS paths
            // paths.push_back("liboo2coredarwin64.dylib");
            // paths.push_back("./liboo2coredarwin64.dylib");
            paths.push_back("/usr/local/lib/liboo2coredarwin64.dylib");
            // paths.push_back("/opt/homebrew/lib/liboo2coredarwin64.dylib");
#else
            // Linux paths
            paths.push_back("liboo2corelinux64.so");
            paths.push_back("./liboo2corelinux64.so");
#endif

            return paths;
        }
    };

    OodleDecompressor::OodleDecompressor(const std::string &library_path)
        : m_impl(std::make_unique<Impl>())
    {
        if (!library_path.empty())
        {
            m_impl->load_library(library_path);
        }
        else
        {
            // Try common paths
            for (const auto &path : m_impl->get_search_paths())
            {
                if (m_impl->load_library(path))
                {
                    break;
                }
            }
        }
    }

    OodleDecompressor::~OodleDecompressor() = default;

    OodleDecompressor::OodleDecompressor(OodleDecompressor &&) noexcept = default;
    OodleDecompressor &OodleDecompressor::operator=(OodleDecompressor &&) noexcept = default;

    bool OodleDecompressor::is_available() const
    {
        return m_impl->decompress_func != nullptr;
    }

    std::string OodleDecompressor::library_path() const
    {
        return m_impl->loaded_path;
    }

    CryptoResult<std::vector<uint8_t>> OodleDecompressor::decompress(
        std::span<const uint8_t> compressed_data,
        size_t decompressed_size)
    {
        std::vector<uint8_t> output(decompressed_size);
        auto result = decompress_to(compressed_data, output, decompressed_size);
        if (!result)
        {
            return std::unexpected(result.error());
        }
        output.resize(*result);
        return output;
    }

    CryptoResult<size_t> OodleDecompressor::decompress_to(
        std::span<const uint8_t> compressed_data,
        std::span<uint8_t> output,
        size_t decompressed_size)
    {
        if (!is_available())
        {
            return std::unexpected(CryptoError::DecompressorNotAvailable);
        }

        if (output.size() < decompressed_size)
        {
            return std::unexpected(CryptoError::OutputBufferTooSmall);
        }

        if (compressed_data.empty())
        {
            return std::unexpected(CryptoError::InvalidCompressedData);
        }

        // Debug: Print first bytes of compressed data to understand format
        fprintf(stderr, "Oodle decompress: compressed_size=%zu, decompressed_size=%zu\n",
                compressed_data.size(), decompressed_size);
        fprintf(stderr, "First 16 bytes: ");
        for (size_t i = 0; i < std::min(compressed_data.size(), size_t(16)); i++)
        {
            fprintf(stderr, "%02x ", compressed_data[i]);
        }
        fprintf(stderr, "\n");

        int64_t result = m_impl->decompress_func(
            compressed_data.data(),
            static_cast<int64_t>(compressed_data.size()),
            output.data(),
            static_cast<int64_t>(decompressed_size),
            0,       // fuzz
            0,       // crc
            0,       // verbose
            nullptr, // dst_base
            0,       // e
            nullptr, // cb
            nullptr, // cb_ctx
            nullptr, // scratch
            0,       // scratch_size
            0        // threadPhase
        );

        fprintf(stderr, "Oodle result: %lld\n", result);

        if (result <= 0)
        {
            return std::unexpected(CryptoError::DecompressionFailed);
        }

        return static_cast<size_t>(result);
    }

    // ============================================================================
    // ReplayDataProcessor Implementation
    // ============================================================================

    struct ReplayDataProcessor::Impl
    {
        AesDecryptor decryptor;
        std::unique_ptr<Decompressor> decompressor;

        Impl()
        {
            // Only use Oodle - it's required for UE replay decompression
            decompressor = std::make_unique<OodleDecompressor>();
        }
    };

    ReplayDataProcessor::ReplayDataProcessor()
        : m_impl(std::make_unique<Impl>()) {}

    ReplayDataProcessor::~ReplayDataProcessor() = default;

    ReplayDataProcessor::ReplayDataProcessor(ReplayDataProcessor &&) noexcept = default;
    ReplayDataProcessor &ReplayDataProcessor::operator=(ReplayDataProcessor &&) noexcept = default;

    CryptoResult<void> ReplayDataProcessor::set_encryption_key(std::span<const uint8_t> key)
    {
        return m_impl->decryptor.set_key(key);
    }

    CryptoResult<void> ReplayDataProcessor::set_encryption_key(const std::vector<uint8_t> &key)
    {
        return set_encryption_key(std::span<const uint8_t>(key));
    }

    void ReplayDataProcessor::set_decompressor(std::unique_ptr<Decompressor> decompressor)
    {
        m_impl->decompressor = std::move(decompressor);
    }

    bool ReplayDataProcessor::has_encryption_key() const
    {
        return m_impl->decryptor.has_key();
    }

    bool ReplayDataProcessor::has_decompressor() const
    {
        return m_impl->decompressor && m_impl->decompressor->is_available();
    }

    const char *ReplayDataProcessor::decompressor_name() const
    {
        if (m_impl->decompressor)
        {
            return m_impl->decompressor->name();
        }
        return "none";
    }

    CryptoResult<std::vector<uint8_t>> ReplayDataProcessor::process(
        std::span<const uint8_t> data,
        bool is_encrypted,
        bool is_compressed,
        size_t decompressed_size)
    {
        if (data.empty())
        {
            return std::vector<uint8_t>{};
        }

        fprintf(stderr, "ReplayDataProcessor::process: data_size=%zu, is_encrypted=%d, is_compressed=%d, decompressed_size=%zu\n",
                data.size(), is_encrypted, is_compressed, decompressed_size);

        std::vector<uint8_t> working_data(data.begin(), data.end());

        // Step 1: Decrypt if needed
        if (is_encrypted)
        {
            fprintf(stderr, "Decrypting data...\n");
            fprintf(stderr, "Has key: %d\n", m_impl->decryptor.has_key());
            
            // Print key for debugging (first few bytes only)
            fprintf(stderr, "Input data first 16 bytes: ");
            for (size_t i = 0; i < std::min(working_data.size(), size_t(16)); i++)
            {
                fprintf(stderr, "%02x ", working_data[i]);
            }
            fprintf(stderr, "\n");
            
            auto decrypt_result = m_impl->decryptor.decrypt_inplace(working_data);
            if (!decrypt_result)
            {
                fprintf(stderr, "Decryption failed with error!\n");
                return std::unexpected(decrypt_result.error());
            }
            fprintf(stderr, "After decryption, first 16 bytes: ");
            for (size_t i = 0; i < std::min(working_data.size(), size_t(16)); i++)
            {
                fprintf(stderr, "%02x ", working_data[i]);
            }
            fprintf(stderr, "\n");
        }

        // Step 2: Decompress if needed
        if (is_compressed)
        {
            if (!m_impl->decompressor || !m_impl->decompressor->is_available())
            {
                return std::unexpected(CryptoError::DecompressorNotAvailable);
            }

            if (decompressed_size == 0)
            {
                // Try to read size from header
                auto header_result = parse_compressed_chunk_header(working_data);
                if (!header_result)
                {
                    return std::unexpected(header_result.error());
                }

                auto [decomp_size, comp_size, offset] = *header_result;
                decompressed_size = decomp_size;

                fprintf(stderr, "Parsed header: decomp_size=%u, comp_size=%u, offset=%zu\n",
                        decomp_size, comp_size, offset);

                // Extract just the compressed data
                std::span<const uint8_t> compressed_portion(
                    working_data.data() + offset,
                    comp_size);

                return m_impl->decompressor->decompress(compressed_portion, decompressed_size);
            }

            return m_impl->decompressor->decompress(working_data, decompressed_size);
        }

        return working_data;
    }

    // ============================================================================
    // Utility Functions
    // ============================================================================

    CryptoResult<std::tuple<uint32_t, uint32_t, size_t>>
    parse_compressed_chunk_header(std::span<const uint8_t> data)
    {
        constexpr size_t HEADER_SIZE = 8; // 2 x uint32_t

        if (data.size() < HEADER_SIZE)
        {
            return std::unexpected(CryptoError::InvalidInput);
        }

        // Read decompressed size (little-endian)
        uint32_t decompressed_size =
            static_cast<uint32_t>(data[0]) |
            (static_cast<uint32_t>(data[1]) << 8) |
            (static_cast<uint32_t>(data[2]) << 16) |
            (static_cast<uint32_t>(data[3]) << 24);

        // Read compressed size (little-endian)
        uint32_t compressed_size =
            static_cast<uint32_t>(data[4]) |
            (static_cast<uint32_t>(data[5]) << 8) |
            (static_cast<uint32_t>(data[6]) << 16) |
            (static_cast<uint32_t>(data[7]) << 24);

        return std::make_tuple(decompressed_size, compressed_size, HEADER_SIZE);
    }

    CryptoResult<std::span<const uint8_t>>
    extract_compressed_data(std::span<const uint8_t> data)
    {
        auto header_result = parse_compressed_chunk_header(data);
        if (!header_result)
        {
            return std::unexpected(header_result.error());
        }

        auto [decomp_size, comp_size, offset] = *header_result;

        if (data.size() < offset + comp_size)
        {
            return std::unexpected(CryptoError::InvalidInput);
        }

        return data.subspan(offset, comp_size);
    }

} // namespace fortnite_replay
