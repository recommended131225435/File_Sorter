#include <iostream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

// file class 
class File {
private:
    fs::path filePath;
    std::string extension;

public:
    File(const fs::path& path) : filePath(path) {
        if (!fs::is_regular_file(path)) {
            throw std::invalid_argument("Invalid file path: not a regular file");
        }

        extension = path.extension().string();
        if (extension.size() > 1)
            extension = extension.substr(1);
        else
            extension = "unknown";
    }

    const std::string& getExtension() const { return extension; }
    const fs::path& getPath() const { return filePath; }

    static fs::path safeDestination(const fs::path& destFolder, const fs::path& filename) {
        fs::path newPath = destFolder / filename;
        int counter = 1;

        while (fs::exists(newPath)) {
            std::string base = filename.stem().string();
            std::string ext  = filename.extension().string();
            newPath = destFolder / (base + "_" + std::to_string(counter) + ext);
            counter++;
        }

        return newPath;
    }

    void moveToFolder(const fs::path& folder) {
        fs::path finalDest = safeDestination(folder, filePath.filename());

        try {
            fs::copy_file(filePath, finalDest);
            fs::remove(filePath);
            std::cout << "[Moved] " << filePath << " -> " << finalDest << "\n";
        } catch (const fs::filesystem_error& e) {
            std::cerr << "[Error] Could not move " << filePath << ": " << e.what() << "\n";
        }
    }
};

// classifying  file types 
class FileTypeClassifier {
public:
    std::string getFolderForExtension(const std::string& ext) const {
        if (ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "gif") return "images";
        if (ext == "pdf") return "pdfs";
        if (ext == "zip" || ext == "rar" || ext == "7z") return "archives";
        if (ext == "mp4" || ext == "mkv" || ext == "mov") return "videos";
        if (ext == "mp3" || ext == "wav") return "audio";
        return "others";
    }
};

// class to manage directory 
class DirectoryManager {
private:
    fs::path directoryPath;
    FileTypeClassifier classifier;

public:
    DirectoryManager(const std::string& path) : directoryPath(path) {}

    fs::path getDirectoryPath() const { return directoryPath; }
    bool exists() const { return fs::exists(directoryPath); }

    void ensureFolder(const std::string& folderName) const {
        fs::path folderPath = directoryPath / folderName;
        if (!fs::exists(folderPath)) {
            fs::create_directory(folderPath);
            std::cout << "[Created Folder] " << folderPath << "\n";
        }
    }

    void sortFilesByType() {
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
};

// -sorting files
class FileSorter {
private:
    DirectoryManager dirManager;

public:
    FileSorter(const std::string& path) : dirManager(path) {}
    void sortFiles() { 
        std::cout << "\n[Sorting] " << dirManager.getDirectoryPath() << "\n";
        dirManager.sortFilesByType(); 
    }
};

// -watches the files
class FileWatcher {
private:
    FileSorter sorter;

public:
    FileWatcher(const std::string& path) : sorter(path) {}

    void startOnce() {
        // run only once 
        sorter.sortFiles();
    }
};

// function for the download folder
std::string getUserDownloadsPath() {
    const char* home = std::getenv("HOME");
    if (!home) {
        home = std::getenv("USERPROFILE"); // for the indows fallback
    }
    
    if (!home) {
        std::cerr << "[Error] HOME/USERPROFILE environment variable missing.\n";
        return "";
    }
    return std::string(home) + "/Downloads";
}


int main() {
    std::string path = getUserDownloadsPath();
    if (path.empty()) return 1;

    try {
        FileWatcher watcher(path);
        watcher.startOnce(); // runs only one time and exits
    } catch (const std::exception& e) {
        std::cerr << "[Fatal] " << e.what() << "\n";
        return 1;
    }
    return 0;
}
