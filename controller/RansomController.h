#ifndef AIDS_TROJAN_RANSOMCONTROLLER_H
#define AIDS_TROJAN_RANSOMCONTROLLER_H


#include "../service/EncryptorService.h"

class RansomController {
private:
    EncryptorService* encryptorService;

public:
    explicit RansomController();
};


#endif //AIDS_TROJAN_RANSOMCONTROLLER_H
