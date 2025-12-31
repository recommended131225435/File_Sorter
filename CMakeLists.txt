cmake_minimum_required(VERSION 3.12)

project(FileSorter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(FileSorter
    src/main.cpp
    src/File.cpp
    src/DirectoryManager.cpp
)

target_include_directories(FileSorter
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Link filesystem for older GCC versions (Linux only)
if(UNIX AND NOT APPLE)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
       CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
        target_link_libraries(FileSorter stdc++fs)
    endif()
endif()
