#ifndef __NK_LEXER_HPP__
#define __NK_LEXER_HPP__

#include <filesystem>
#include <string>
namespace nk {
/// @brief Lexer for NK language
class Lexer {
public:
  ///@brief constructor for Lexer
  ///
  ///@param _source script source of NK
  ///@param _path path of source code
  Lexer(std::string _source, std::filesystem::path _path) : source(_source), path(_path) {
  }

private:
  std::string source;         ///< original text source code
  std::filesystem::path path; ///< path of source code
};
} // namespace nk

#endif