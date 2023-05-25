#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Lexer.hpp"

using namespace nk;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Please provide nk scripts\n";
    return 1;
  }
  std::cout << argv[1] << std::endl;
  std::filesystem::path inputPath = std::filesystem::path(argv[1]);
  if (std::filesystem::exists(inputPath)) {
    std::ifstream inputStream{inputPath};
    std::string source((std::istreambuf_iterator<char>(inputStream)),
                       std::istreambuf_iterator<char>());
    inputStream.close();
    Lexer lexer(std::move(source), std::move(inputPath));
  } else {
    std::cerr << "file not exists\n";
    return 1;
  }
}
