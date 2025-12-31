#ifndef FILEWATCHER_HPP
#define FILEWATCHER_HPP

#include "FileSorter.hpp"

class FileWatcher {
private:
    FileSorter sorter;

public:
    FileWatcher(const std::string& path);
    void startOnce();
};

#endif
