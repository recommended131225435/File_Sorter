#ifndef DIRECTORYMANAGER_HPP
#define DIRECTORYMANAGER_HPP

#include <filesystem>
#include <string>
#include "FileTypeClassifier.hpp"

namespace fs = std::filesystem;

class DirectoryManager {
private:
    fs::path directoryPath;
    FileTypeClassifier classifier;

public:
    DirectoryManager(const std::string& path);

    fs::path getDirectoryPath() const;
    bool exists() const;

    void ensureFolder(const std::string& folderName) const;
    void sortFilesByType();
};

#endif
