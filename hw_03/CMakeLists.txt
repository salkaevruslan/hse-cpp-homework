cmake_minimum_required(VERSION 3.1)
project(hw_03)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Werror -stdlib=libc++")

add_library(doctest INTERFACE)

include_directories(include)

add_executable(hw_03 src/main.cpp src/HuffmanArchiver.cpp src/Huffman.cpp src/BitStream.cpp src/CLI.cpp)

add_executable(test_hw_03 test/TestMain.cpp src/HuffmanArchiver.cpp src/Huffman.cpp src/BitStream.cpp src/CLI.cpp
        test/TestCLI.cpp test/TestArchiver.cpp test/TestHuffman.cpp test/TestBitStream.cpp)
target_link_libraries(test_hw_03 doctest)
