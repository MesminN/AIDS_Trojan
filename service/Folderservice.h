#ifndef AIDS_TROJAN_FOLDERSERVICE_H
#define AIDS_TROJAN_FOLDERSERVICE_H

#include <vector>
#include <filesystem>
#include <string>

class FolderService {
protected:
    std::filesystem::path rootPath;
    std::vector<std::string> m_exclude_paths;

public:
    const std::filesystem::path DEFAULT_ROOT_FOLDER = "\\";
    FolderService();
    FolderService(std::filesystem::path rootFolder);
    void initializeExcludedFilesAndFolders();
    void getFiles(const std::filesystem::path rootPath, std::vector<std::filesystem::path>* fileList, bool isEncryption);
    void getFiles(std::vector<std::filesystem::path>* fileList, bool isEncryption);
    void renameFileName(std::filesystem::path filePath, std::string newFileName);
    bool is_excluded(std::string path, bool isEncryption);
    std::filesystem::path getRootPath() const;
    virtual ~FolderService();
};

#endif //AIDS_TROJAN_FOLDERSERVICE_H
