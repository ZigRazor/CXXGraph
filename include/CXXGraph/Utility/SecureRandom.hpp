
#pragma once
#include <array>
#include <stdexcept>

#if defined(_WIN32) || defined(_WIN64)
// clang-format off
#include <windows.h>
#include <bcrypt.h>
// clang-format on
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif
#ifdef _MSC_VER
#pragma comment(lib, "bcrypt.lib")
#endif
#else
#include <fstream>
#endif

namespace CXXGraph {
namespace SecureRandom {

inline void generateBytes(unsigned char* buffer, size_t length) {
  if (!buffer || length == 0)
    throw std::invalid_argument("Invalid buffer or length");

#if defined(_WIN32) || defined(_WIN64)
  if (length > ULONG_MAX)
    throw std::length_error("Requested random length too large");
  NTSTATUS status = BCryptGenRandom(nullptr, buffer, static_cast<ULONG>(length),
                                    BCRYPT_USE_SYSTEM_PREFERRED_RNG);
  if (status != STATUS_SUCCESS)
    throw std::runtime_error("BCryptGenRandom failed");
#else
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (!urandom.is_open())
    throw std::runtime_error("Failed to open /dev/urandom");

  std::streamsize totalRead = 0;
  while (totalRead < static_cast<std::streamsize>(length)) {
    urandom.read(reinterpret_cast<char*>(buffer) + totalRead,
                 static_cast<std::streamsize>(length) - totalRead);
    std::streamsize bytesRead = urandom.gcount();
    if (bytesRead <= 0)
      throw std::runtime_error("Failed to read enough random bytes");
    totalRead += bytesRead;
  }
#endif
}

template <size_t N>
inline std::array<unsigned char, N> randomBytes() {
  std::array<unsigned char, N> arr{};
  generateBytes(arr.data(), N);
  return arr;
}

inline unsigned int randomUInt() {
  unsigned int value;
  generateBytes(reinterpret_cast<unsigned char*>(&value), sizeof(value));
  return value;
}
}  // namespace SecureRandom
}  // namespace CXXGraph
