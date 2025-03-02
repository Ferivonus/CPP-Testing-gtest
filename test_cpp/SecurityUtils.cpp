#include "SecurityUtils.h"
#include <vector>

std::string CryptoUtils::generateSalt(size_t length) {
    std::vector<unsigned char> buffer(length);
    if (RAND_bytes(buffer.data(), length) != 1) {
        throw SecurityException("Salt generation failed");
    }
    return bytesToHex(buffer.data(), length);
}

std::string CryptoUtils::hashPassword(const std::string& password, const std::string& salt) {
    const EVP_MD* digest = EVP_sha512();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, digest, nullptr);
    EVP_DigestUpdate(context, salt.c_str(), salt.size());
    EVP_DigestUpdate(context, password.c_str(), password.size());
    EVP_DigestFinal_ex(context, hash, &length);
    EVP_MD_CTX_free(context);

    return bytesToHex(hash, length);
}

std::string CryptoUtils::bytesToHex(const unsigned char* data, size_t length) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}
