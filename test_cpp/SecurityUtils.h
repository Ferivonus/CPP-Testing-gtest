#ifndef SECURITY_UTILS_H
#define SECURITY_UTILS_H

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class SecurityException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class CryptoUtils {
public:
    static std::string generateSalt(size_t length = 32);
    static std::string hashPassword(const std::string& password, const std::string& salt);

private:
    static std::string bytesToHex(const unsigned char* data, size_t length);
};

#endif // SECURITY_UTILS_H
