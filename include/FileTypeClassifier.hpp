#ifndef FILETYPECLASSIFIER_HPP
#define FILETYPECLASSIFIER_HPP

#include <string>

class FileTypeClassifier {
public:
    std::string getFolderForExtension(const std::string& ext) const;
};

#endif
