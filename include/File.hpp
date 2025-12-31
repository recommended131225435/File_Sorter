#ifndef FILE_HPP
#define FILE_HPP

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class File {
private:
    fs::path filePath;
    std::string extension;

public:
    File(const fs::path& path);

    const std::string& getExtension() const;
    const fs::path& getPath() const;

    static fs::path safeDestination(const fs::path& destFolder, const fs::path& filename);
    void moveToFolder(const fs::path& folder);
};

#endif
