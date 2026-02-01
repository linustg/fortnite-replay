#ifndef FORTNITE_REPLAY_CRYPTO_HPP
#define FORTNITE_REPLAY_CRYPTO_HPP

#include <cstdint>
#include <expected>
#include <memory>
#include <span>
#include <string>
#include <vector>

namespace fortnite_replay
{

    // ============================================================================
    // Error Types
    // ============================================================================

    /**
     * Error codes for crypto operations
     */
    enum class CryptoError
    {
        Success = 0,

        // Decryption errors
        InvalidKeySize,
        InvalidDataSize,
        DecryptionFailed,
        KeyNotSet,

        // Decompression errors
        InvalidCompressedData,
        DecompressionFailed,
        OutputBufferTooSmall,
        DecompressorNotAvailable,

        // General errors
        InvalidInput,
        InternalError
    };

    /**
     * Get human-readable description of a crypto error
     */
    const char *crypto_error_string(CryptoError error);

    // ============================================================================
    // Result Type
    // ============================================================================

    /**
     * Result type for crypto operations
     */
    template <typename T>
    using CryptoResult = std::expected<T, CryptoError>;

    // ============================================================================
    // Decryption Interface
    // ============================================================================

    /**
     * AES-256-ECB decryptor for Fortnite replay data
     *
     * Fortnite uses AES-256 in ECB mode for encrypting replay chunks.
     * The encryption key is stored in the replay header.
     */
    class AesDecryptor
    {
    public:
        static constexpr size_t KEY_SIZE = 32;   // 256 bits
        static constexpr size_t BLOCK_SIZE = 16; // 128 bits

        AesDecryptor();
        ~AesDecryptor();

        // Non-copyable but movable
        AesDecryptor(const AesDecryptor &) = delete;
        AesDecryptor &operator=(const AesDecryptor &) = delete;
        AesDecryptor(AesDecryptor &&) noexcept;
        AesDecryptor &operator=(AesDecryptor &&) noexcept;

        /**
         * Set the decryption key
         * @param key 32-byte (256-bit) key
         * @return Success or InvalidKeySize error
         */
        CryptoResult<void> set_key(std::span<const uint8_t> key);

        /**
         * Set the decryption key from a vector
         */
        CryptoResult<void> set_key(const std::vector<uint8_t> &key);

        /**
         * Check if a key has been set
         */
        bool has_key() const;

        /**
         * Decrypt data in place
         * @param data Data to decrypt (must be aligned to BLOCK_SIZE)
         * @return Success or error
         */
        CryptoResult<void> decrypt_inplace(std::span<uint8_t> data);

        /**
         * Decrypt data to a new buffer
         * @param encrypted_data Encrypted data (must be aligned to BLOCK_SIZE)
         * @return Decrypted data or error
         */
        CryptoResult<std::vector<uint8_t>> decrypt(std::span<const uint8_t> encrypted_data);

        /**
         * Static convenience function for one-shot decryption
         */
        static CryptoResult<std::vector<uint8_t>> decrypt(
            std::span<const uint8_t> key,
            std::span<const uint8_t> encrypted_data);

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };

    // ============================================================================
    // Decompression Interface
    // ============================================================================

    /**
     * Abstract base class for decompressors
     *
     * Fortnite uses Oodle compression for replay data. Since Oodle is proprietary,
     * this provides an abstraction layer that supports multiple implementations:
     * - OodleDecompressor: Uses the Oodle DLL from Fortnite installation
     * - ZlibDecompressor: Fallback for testing or older replay formats
     */
    class Decompressor
    {
    public:
        virtual ~Decompressor() = default;

        /**
         * Get the name of this decompressor
         */
        virtual const char *name() const = 0;

        /**
         * Check if this decompressor is available/functional
         */
        virtual bool is_available() const = 0;

        /**
         * Decompress data
         * @param compressed_data Compressed input data
         * @param decompressed_size Expected size of decompressed output
         * @return Decompressed data or error
         */
        virtual CryptoResult<std::vector<uint8_t>> decompress(
            std::span<const uint8_t> compressed_data,
            size_t decompressed_size) = 0;

        /**
         * Decompress data to a pre-allocated buffer
         * @param compressed_data Compressed input data
         * @param output Output buffer (must be at least decompressed_size bytes)
         * @param decompressed_size Expected size of decompressed output
         * @return Number of bytes written or error
         */
        virtual CryptoResult<size_t> decompress_to(
            std::span<const uint8_t> compressed_data,
            std::span<uint8_t> output,
            size_t decompressed_size) = 0;
    };

    /**
     * Oodle decompressor using dynamic library loading
     *
     * Attempts to load oo2core_*.dll (Windows) or liboo2core*.so (Linux/macOS)
     * from the specified path or common Fortnite installation locations.
     */
    class OodleDecompressor : public Decompressor
    {
    public:
        /**
         * Create an Oodle decompressor
         * @param library_path Optional path to Oodle library. If empty, searches
         *                     common Fortnite installation paths.
         */
        explicit OodleDecompressor(const std::string &library_path = "");
        ~OodleDecompressor() override;

        // Non-copyable but movable
        OodleDecompressor(const OodleDecompressor &) = delete;
        OodleDecompressor &operator=(const OodleDecompressor &) = delete;
        OodleDecompressor(OodleDecompressor &&) noexcept;
        OodleDecompressor &operator=(OodleDecompressor &&) noexcept;

        const char *name() const override { return "Oodle"; }
        bool is_available() const override;

        CryptoResult<std::vector<uint8_t>> decompress(
            std::span<const uint8_t> compressed_data,
            size_t decompressed_size) override;

        CryptoResult<size_t> decompress_to(
            std::span<const uint8_t> compressed_data,
            std::span<uint8_t> output,
            size_t decompressed_size) override;

        /**
         * Get the path to the loaded library, or empty if not loaded
         */
        std::string library_path() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };

    /**
     * Zlib decompressor for testing or older replay formats
     */
    class ZlibDecompressor : public Decompressor
    {
    public:
        ZlibDecompressor() = default;
        ~ZlibDecompressor() override = default;

        const char *name() const override { return "zlib"; }
        bool is_available() const override;

        CryptoResult<std::vector<uint8_t>> decompress(
            std::span<const uint8_t> compressed_data,
            size_t decompressed_size) override;

        CryptoResult<size_t> decompress_to(
            std::span<const uint8_t> compressed_data,
            std::span<uint8_t> output,
            size_t decompressed_size) override;
    };

    // ============================================================================
    // High-Level Replay Data Processing
    // ============================================================================

    /**
     * Combined decryption and decompression for replay chunk data
     *
     * This class handles the common pattern of decrypting then decompressing
     * replay data chunks.
     */
    class ReplayDataProcessor
    {
    public:
        /**
         * Create a processor with optional encryption key and decompressor
         */
        ReplayDataProcessor();
        ~ReplayDataProcessor();

        // Non-copyable but movable
        ReplayDataProcessor(const ReplayDataProcessor &) = delete;
        ReplayDataProcessor &operator=(const ReplayDataProcessor &) = delete;
        ReplayDataProcessor(ReplayDataProcessor &&) noexcept;
        ReplayDataProcessor &operator=(ReplayDataProcessor &&) noexcept;

        /**
         * Set the encryption key for decryption
         */
        CryptoResult<void> set_encryption_key(std::span<const uint8_t> key);
        CryptoResult<void> set_encryption_key(const std::vector<uint8_t> &key);

        /**
         * Set a custom decompressor
         * If not set, attempts to use Oodle, falling back to zlib
         */
        void set_decompressor(std::unique_ptr<Decompressor> decompressor);

        /**
         * Check if encryption is configured
         */
        bool has_encryption_key() const;

        /**
         * Check if a decompressor is available
         */
        bool has_decompressor() const;

        /**
         * Get the name of the active decompressor
         */
        const char *decompressor_name() const;

        /**
         * Process replay data (decrypt if needed, decompress if needed)
         *
         * @param data Raw chunk data
         * @param is_encrypted Whether the data is encrypted
         * @param is_compressed Whether the data is compressed
         * @param decompressed_size Expected decompressed size (required if compressed)
         * @return Processed data or error
         */
        CryptoResult<std::vector<uint8_t>> process(
            std::span<const uint8_t> data,
            bool is_encrypted,
            bool is_compressed,
            size_t decompressed_size = 0);

    private:
        struct Impl;
        std::unique_ptr<Impl> m_impl;
    };

    // ============================================================================
    // Utility Functions
    // ============================================================================

    /**
     * Parse compressed chunk header
     *
     * Compressed chunks in Fortnite replays start with:
     * - decompressed_size: uint32_t
     * - compressed_size: uint32_t
     * - compressed_data: bytes[compressed_size]
     *
     * @param data Raw chunk data
     * @return Tuple of (decompressed_size, compressed_size, compressed_data_offset)
     */
    CryptoResult<std::tuple<uint32_t, uint32_t, size_t>>
    parse_compressed_chunk_header(std::span<const uint8_t> data);

    /**
     * Extract compressed data from a chunk
     * @param data Raw chunk data with header
     * @return Compressed data portion (without header)
     */
    CryptoResult<std::span<const uint8_t>>
    extract_compressed_data(std::span<const uint8_t> data);

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_CRYPTO_HPP
