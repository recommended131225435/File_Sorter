# fSort

### About
fSort is a small project that automatically sorts files in a directory based on their file types using OOP principles. It organizes files based on images, documents, archives, videos, and audio into their designated folders, keeping directories clean and structured.

### Features
- It classifies files by their type:
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

### Usage
1. Compile the program:
```
g++ -std=c++17 ./src/fileSorter.cpp -o FileSorter
```
Run the program
```
./FileSorter
```

License

This project is licensed under the MIT License.
You can view the full license [here](./LICENSE)


