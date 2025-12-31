#include "DirectoryManager.hpp"
#include "File.hpp"
#include <iostream>

DirectoryManager::DirectoryManager(const std::string& path) : directoryPath(path) {}

fs::path DirectoryManager::getDirectoryPath() const { return directoryPath; }
bool DirectoryManager::exists() const { return fs::exists(directoryPath); }

void DirectoryManager::ensureFolder(const std::string& folderName) const {
    fs::path folderPath = directoryPath / folderName;
    if (!fs::exists(folderPath)) {
        fs::create_directory(folderPath);
        std::cout << "[Created Folder] " << folderPath << "\n";
    }
}

void DirectoryManager::sortFilesByType() {
    if (!exists()) {
        std::cerr << "[Error] Directory not found: " << directoryPath << "\n";
        return;
    }

    for (auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_directory()) continue;

        try {
            File file(entry.path());
            std::string folder = classifier.getFolderForExtension(file.getExtension());
            ensureFolder(folder);
            file.moveToFolder(directoryPath / folder);
        } catch (...) {
            std::cerr << "[Warning] Skipping invalid entry: " << entry.path() << "\n";
        }
    }
}
