#include "File.hpp"
#include <iostream>
#include <stdexcept>

File::File(const fs::path& path) : filePath(path) {
    if (!fs::is_regular_file(path)) {
        throw std::invalid_argument("Invalid file path: not a regular file");
    }

    extension = path.extension().string();
    if (extension.size() > 1)
        extension = extension.substr(1);
    else
        extension = "unknown";
}

const std::string& File::getExtension() const { return extension; }
const fs::path& File::getPath() const { return filePath; }

fs::path File::safeDestination(const fs::path& destFolder, const fs::path& filename) {
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

void File::moveToFolder(const fs::path& folder) {
    fs::path finalDest = safeDestination(folder, filePath.filename());

    try {
        fs::copy_file(filePath, finalDest);
        fs::remove(filePath);
        std::cout << "[Moved] " << filePath << " -> " << finalDest << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[Error] Could not move " << filePath << ": " << e.what() << "\n";
    }
}
