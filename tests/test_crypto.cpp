#include "fortnite_replay/crypto.hpp"
#include "test_utils.cpp"

#include <gtest/gtest.h>

#include <array>
#include <cstdlib>

using namespace fortnite_replay;
using namespace test_utils;

// ============================================================================
// CryptoError Tests
// ============================================================================

TEST(CryptoErrorTest, ErrorStrings) {
  EXPECT_STREQ(crypto_error_string(CryptoError::Success), "Success");
  EXPECT_STREQ(crypto_error_string(CryptoError::InvalidKeySize),
               "Invalid key size (expected 32 bytes for AES-256)");
  EXPECT_STREQ(crypto_error_string(CryptoError::InvalidDataSize),
               "Invalid data size (must be multiple of block size)");
  EXPECT_STREQ(crypto_error_string(CryptoError::DecryptionFailed),
               "Decryption failed");
  EXPECT_STREQ(crypto_error_string(CryptoError::KeyNotSet),
               "Encryption key not set");
  EXPECT_STREQ(crypto_error_string(CryptoError::DecompressorNotAvailable),
               "Decompressor not available");
}

// ============================================================================
// AesDecryptor Tests
// ============================================================================

class AesDecryptorTest : public ::testing::Test {
protected:
  // Known test vector for AES-256-ECB
  // Key: 32 bytes of zeros
  // Plaintext: 16 bytes of zeros
  // Ciphertext is the result of encrypting zeros with zero key
  std::array<uint8_t, 32> zero_key{};
  std::array<uint8_t, 16> zero_block{};

  void SetUp() override {
    zero_key.fill(0);
    zero_block.fill(0);
  }
};

TEST_F(AesDecryptorTest, DefaultConstruction) {
  AesDecryptor decryptor;
  EXPECT_FALSE(decryptor.has_key());
}

TEST_F(AesDecryptorTest, SetValidKey) {
  AesDecryptor decryptor;
  auto result = decryptor.set_key(zero_key);
  EXPECT_TRUE(result.has_value());
  EXPECT_TRUE(decryptor.has_key());
}

TEST_F(AesDecryptorTest, SetInvalidKeySize) {
  AesDecryptor decryptor;

  // Too short
  std::array<uint8_t, 16> short_key{};
  auto result = decryptor.set_key(short_key);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidKeySize);
  EXPECT_FALSE(decryptor.has_key());

  // Too long
  std::array<uint8_t, 64> long_key{};
  result = decryptor.set_key(long_key);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidKeySize);
}

TEST_F(AesDecryptorTest, DecryptWithoutKey) {
  AesDecryptor decryptor;
  std::vector<uint8_t> data(16, 0);

  auto result = decryptor.decrypt_inplace(data);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::KeyNotSet);
}

TEST_F(AesDecryptorTest, DecryptInvalidDataSize) {
  AesDecryptor decryptor;
  ASSERT_TRUE(decryptor.set_key(zero_key).has_value());

  // Data not aligned to block size
  std::vector<uint8_t> data(17, 0);
  auto result = decryptor.decrypt_inplace(data);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidDataSize);
}

TEST_F(AesDecryptorTest, DecryptEmptyData) {
  AesDecryptor decryptor;
  ASSERT_TRUE(decryptor.set_key(zero_key).has_value());

  std::vector<uint8_t> data;
  auto result = decryptor.decrypt_inplace(data);
  EXPECT_TRUE(result.has_value());
}

TEST_F(AesDecryptorTest, DecryptSingleBlock) {
  AesDecryptor decryptor;
  ASSERT_TRUE(decryptor.set_key(zero_key).has_value());

  // AES-256-ECB encryption of 16 zero bytes with 32-byte zero key
  // This is a known test vector
  std::vector<uint8_t> ciphertext = {0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40,
                                     0x89, 0x89, 0xad, 0x48, 0xa2, 0x14,
                                     0x92, 0x84, 0x20, 0x87};

  auto result = decryptor.decrypt(ciphertext);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 16u);

  // Should decrypt to zeros
  for (size_t i = 0; i < result->size(); ++i) {
    EXPECT_EQ((*result)[i], 0) << "Mismatch at index " << i;
  }
}

TEST_F(AesDecryptorTest, DecryptMultipleBlocks) {
  AesDecryptor decryptor;
  ASSERT_TRUE(decryptor.set_key(zero_key).has_value());

  // Two blocks of ciphertext (same block repeated)
  std::vector<uint8_t> ciphertext = {
      0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40, 0x89, 0x89, 0xad, 0x48, 0xa2,
      0x14, 0x92, 0x84, 0x20, 0x87, 0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40,
      0x89, 0x89, 0xad, 0x48, 0xa2, 0x14, 0x92, 0x84, 0x20, 0x87};

  auto result = decryptor.decrypt(ciphertext);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 32u);

  // Should decrypt to zeros
  for (size_t i = 0; i < result->size(); ++i) {
    EXPECT_EQ((*result)[i], 0) << "Mismatch at index " << i;
  }
}

TEST_F(AesDecryptorTest, DecryptInplace) {
  AesDecryptor decryptor;
  ASSERT_TRUE(decryptor.set_key(zero_key).has_value());

  std::vector<uint8_t> data = {0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40, 0x89, 0x89,
                               0xad, 0x48, 0xa2, 0x14, 0x92, 0x84, 0x20, 0x87};

  auto result = decryptor.decrypt_inplace(data);
  ASSERT_TRUE(result.has_value());

  // Data should be decrypted in place
  for (size_t i = 0; i < data.size(); ++i) {
    EXPECT_EQ(data[i], 0) << "Mismatch at index " << i;
  }
}

TEST_F(AesDecryptorTest, StaticDecrypt) {
  std::vector<uint8_t> key(32, 0);
  std::vector<uint8_t> ciphertext = {0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40,
                                     0x89, 0x89, 0xad, 0x48, 0xa2, 0x14,
                                     0x92, 0x84, 0x20, 0x87};

  auto result = AesDecryptor::decrypt(key, ciphertext);
  ASSERT_TRUE(result.has_value());

  for (size_t i = 0; i < result->size(); ++i) {
    EXPECT_EQ((*result)[i], 0) << "Mismatch at index " << i;
  }
}

TEST_F(AesDecryptorTest, MoveConstruction) {
  AesDecryptor decryptor1;
  ASSERT_TRUE(decryptor1.set_key(zero_key).has_value());
  EXPECT_TRUE(decryptor1.has_key());

  AesDecryptor decryptor2(std::move(decryptor1));
  EXPECT_TRUE(decryptor2.has_key());
}

TEST_F(AesDecryptorTest, MoveAssignment) {
  AesDecryptor decryptor1;
  ASSERT_TRUE(decryptor1.set_key(zero_key).has_value());

  AesDecryptor decryptor2;
  decryptor2 = std::move(decryptor1);
  EXPECT_TRUE(decryptor2.has_key());
}

// ============================================================================
// OodleDecompressor Tests
// ============================================================================

class OodleDecompressorTest : public ::testing::Test {
protected:
  OodleDecompressor decompressor;
};

TEST_F(OodleDecompressorTest, Name) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  EXPECT_STREQ(decompressor.name(), "Oodle");
}

TEST_F(OodleDecompressorTest, AvailabilityCheck) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  // Oodle may or may not be available depending on the system
  // Just ensure the check doesn't crash
  bool available = decompressor.is_available();
  if (available) {
    EXPECT_FALSE(decompressor.library_path().empty());
  } else {
    EXPECT_TRUE(decompressor.library_path().empty());
  }
}

TEST_F(OodleDecompressorTest, DecompressWithoutLibrary) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  // Create a decompressor with an invalid path
  OodleDecompressor invalid_decompressor("/nonexistent/path/to/oodle.dll");
  EXPECT_FALSE(invalid_decompressor.is_available());

  std::vector<uint8_t> data = {0x01, 0x02, 0x03};
  auto result = invalid_decompressor.decompress(data, 100);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::DecompressorNotAvailable);
}

TEST_F(OodleDecompressorTest, MoveConstruction) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  OodleDecompressor d1;
  bool was_available = d1.is_available();

  OodleDecompressor d2(std::move(d1));
  EXPECT_EQ(d2.is_available(), was_available);
}

// ============================================================================
// ReplayDataProcessor Tests
// ============================================================================

class ReplayDataProcessorTest : public ::testing::Test {
protected:
  ReplayDataProcessor processor;
  std::vector<uint8_t> test_key{32, 0}; // 32 zero bytes

  void SetUp() override { test_key.assign(32, 0); }
};

TEST_F(ReplayDataProcessorTest, DefaultConstruction) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  EXPECT_FALSE(processor.has_encryption_key());
  EXPECT_TRUE(processor.has_decompressor());
}

TEST_F(ReplayDataProcessorTest, SetEncryptionKey) {
  auto result = processor.set_encryption_key(test_key);
  EXPECT_TRUE(result.has_value());
  EXPECT_TRUE(processor.has_encryption_key());
}

TEST_F(ReplayDataProcessorTest, SetInvalidEncryptionKey) {
  std::vector<uint8_t> short_key(16, 0);
  auto result = processor.set_encryption_key(short_key);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidKeySize);
  EXPECT_FALSE(processor.has_encryption_key());
}

TEST_F(ReplayDataProcessorTest, DecompressorName) {
  // Should have either Oodle or zlib
  const char *name = processor.decompressor_name();
  EXPECT_TRUE(std::string(name) == "Oodle" || std::string(name) == "zlib");
}

TEST_F(ReplayDataProcessorTest, ProcessUnencryptedUncompressed) {
  std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};

  auto result = processor.process(data, false, false);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, data);
}

TEST_F(ReplayDataProcessorTest, ProcessEmptyData) {
  std::vector<uint8_t> empty;

  auto result = processor.process(empty, false, false);
  ASSERT_TRUE(result.has_value());
  EXPECT_TRUE(result->empty());
}

TEST_F(ReplayDataProcessorTest, ProcessEncryptedWithoutKey) {
  std::vector<uint8_t> data(16, 0);

  auto result = processor.process(data, true, false);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::KeyNotSet);
}

TEST_F(ReplayDataProcessorTest, ProcessEncryptedWithKey) {
  ASSERT_TRUE(processor.set_encryption_key(test_key).has_value());

  // Ciphertext that decrypts to zeros with zero key
  std::vector<uint8_t> ciphertext = {0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40,
                                     0x89, 0x89, 0xad, 0x48, 0xa2, 0x14,
                                     0x92, 0x84, 0x20, 0x87};

  auto result = processor.process(ciphertext, true, false);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 16u);

  for (uint8_t byte : *result) {
    EXPECT_EQ(byte, 0);
  }
}

TEST_F(ReplayDataProcessorTest, SetCustomDecompressor) {
  if (is_ci_environment()) {
    GTEST_SKIP() << "Skipping Oodle test - oo2core library not available in CI";
  }
  auto oodle = std::make_unique<OodleDecompressor>();
  processor.set_decompressor(std::move(oodle));

  EXPECT_STREQ(processor.decompressor_name(), "Oodle");
}

TEST_F(ReplayDataProcessorTest, MoveConstruction) {
  ASSERT_TRUE(processor.set_encryption_key(test_key).has_value());
  EXPECT_TRUE(processor.has_encryption_key());

  ReplayDataProcessor processor2(std::move(processor));
  EXPECT_TRUE(processor2.has_encryption_key());
}

// ============================================================================
// Utility Function Tests
// ============================================================================

TEST(UtilityFunctionsTest, ParseCompressedChunkHeader) {
  // Header: decompressed_size=1000 (0x000003E8), compressed_size=500
  // (0x000001F4)
  std::vector<uint8_t> data = {
      0xE8, 0x03, 0x00, 0x00, // decompressed_size (little-endian)
      0xF4, 0x01, 0x00, 0x00, // compressed_size (little-endian)
      0x00, 0x01, 0x02, 0x03  // some data
  };

  auto result = parse_compressed_chunk_header(data);
  ASSERT_TRUE(result.has_value());

  auto [decompressed_size, compressed_size, offset] = *result;
  EXPECT_EQ(decompressed_size, 1000u);
  EXPECT_EQ(compressed_size, 500u);
  EXPECT_EQ(offset, 8u);
}

TEST(UtilityFunctionsTest, ParseCompressedChunkHeaderTooShort) {
  std::vector<uint8_t> data = {0x01, 0x02, 0x03}; // Only 3 bytes

  auto result = parse_compressed_chunk_header(data);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidInput);
}

TEST(UtilityFunctionsTest, ExtractCompressedData) {
  std::vector<uint8_t> data = {
      0x10, 0x00, 0x00, 0x00, // decompressed_size = 16
      0x04, 0x00, 0x00, 0x00, // compressed_size = 4
      0xAA, 0xBB, 0xCC, 0xDD  // compressed data
  };

  auto result = extract_compressed_data(data);
  ASSERT_TRUE(result.has_value());

  auto span = *result;
  EXPECT_EQ(span.size(), 4u);
  EXPECT_EQ(span[0], 0xAA);
  EXPECT_EQ(span[1], 0xBB);
  EXPECT_EQ(span[2], 0xCC);
  EXPECT_EQ(span[3], 0xDD);
}

TEST(UtilityFunctionsTest, ExtractCompressedDataTruncated) {
  std::vector<uint8_t> data = {
      0x10, 0x00, 0x00, 0x00, // decompressed_size = 16
      0x10, 0x00, 0x00, 0x00, // compressed_size = 16 (but only 4 bytes follow)
      0xAA, 0xBB, 0xCC, 0xDD  // only 4 bytes
  };

  auto result = extract_compressed_data(data);
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), CryptoError::InvalidInput);
}

// ============================================================================
// Integration Tests
// ============================================================================

TEST(CryptoIntegrationTest, DecryptThenPassthrough) {
  // Simulate decrypting data that is encrypted but not compressed
  ReplayDataProcessor processor;

  std::vector<uint8_t> key(32, 0);
  ASSERT_TRUE(processor.set_encryption_key(key).has_value());

  // This is ciphertext that decrypts to zeros
  std::vector<uint8_t> encrypted_data = {0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40,
                                         0x89, 0x89, 0xad, 0x48, 0xa2, 0x14,
                                         0x92, 0x84, 0x20, 0x87};

  auto result = processor.process(encrypted_data, true, false);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->size(), 16u);

  // Verify decryption produced zeros
  for (uint8_t byte : *result) {
    EXPECT_EQ(byte, 0);
  }
}

TEST(CryptoIntegrationTest, RoundtripConsistency) {
  // Test that processing the same data twice gives consistent results
  ReplayDataProcessor processor1;
  ReplayDataProcessor processor2;

  std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05};

  auto result1 = processor1.process(data, false, false);
  auto result2 = processor2.process(data, false, false);

  ASSERT_TRUE(result1.has_value());
  ASSERT_TRUE(result2.has_value());
  EXPECT_EQ(*result1, *result2);
}
