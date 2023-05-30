#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "EnvironmentConfig.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace nk;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Please provide nk scripts\n";
    return 1;
  }
  EnvironmentConfiguration::getInstance().init();
  NK_TRACE(argv[1])
  NK_TRACE('\n')
  std::filesystem::path inputPath = std::filesystem::path(argv[1]);
  if (std::filesystem::exists(inputPath)) {
    std::ifstream inputStream{inputPath};
    std::string source((std::istreambuf_iterator<char>(inputStream)),
                       std::istreambuf_iterator<char>());
    inputStream.close();
    Lexer lexer(source, std::move(inputPath));
    lexer.tokenizer();
    Parser parser(source, lexer.getTokens());
    parser.parse();
  } else {
    std::cerr << "file not exists\n";
    return 1;
  }
}
