# C++ File Sorter

### Overview
This project is a C++ program that automatically sorts files in a directory based on their file types using object-oriented programming principles. It organizes files such as images, documents, archives, videos, and audio into corresponding folders, keeping directories clean and structured.

### Features
- Classifies files by type:
  - Images (`png`, `jpg`, `jpeg`, `gif`)
  - PDFs (`pdf`)
  - Archives (`zip`, `rar`, `7z`)
  - Videos (`mp4`, `mkv`, `mov`)
  - Audio (`mp3`, `wav`)
  - Others (`any unrecognized file type`)
- Automatically creates folders if they do not exist.
- Safely moves files without overwriting existing files.
- Designed for the user's Downloads directory by default.
- Runs once and sorts all files in the target directory.

### Project Structure

```
FileSorter/
├── fileSorter.cpp # Main source code
├── LICENSE # MIT License
├── README.md # Project documentation
└── .gitignore # Git ignore file
```
### Requirements
- Minimum C++17 compatible compiler (for `<filesystem>` support)
- Linux environment (tested on Zorin OS)
- Standard C++ library
### Usage
1. Compile the program:
```
g++ -std=c++17 ./src/fileSorter.cpp -o FileSorter
```
Run the program
```
./FileSorter
```

How it Works

- `File` class handles individual files and moves them safely.
- `FileTypeClassifier` maps file extensions to target folders.
- `DirectoryManager` ensures folders exist and iterates through files in the directory.
- `FileSorter` integrates the directory manager to perform sorting.
- `FileWatcher` triggers the sorting process (runs once).



License

This project is licensed under the MIT License.
You can view the full license [here](./LICENSE)


