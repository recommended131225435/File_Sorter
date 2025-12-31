#include <iostream>
#include <cstdlib>
#include "FileWatcher.hpp"
#include "utils.hpp"

std::string getUserDownloadsPath() {
    const char* home = std::getenv("HOME");
    if (!home) {
        home = std::getenv("USERPROFILE");
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
        watcher.startOnce();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal] " << e.what() << "\n";
        return 1;
    }
    return 0;
}
