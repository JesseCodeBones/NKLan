#ifndef __NK_PARSER_HPP__
#define __NK_PARSER_HPP__
#include <string>
#include <vector>
#include "Lexer.hpp"
namespace nk {

/// @brief Parser class translate tokens to AST (Abstract Syntax Tree)
class Parser {

public:
  ///
  /// @brief public construct of Parser
  ///
  /// @param _source source file
  /// @param _tokens tokens from Lexer
  Parser(std::string const &_source, std::vector<Token> const &_tokens) noexcept
      : source(_source), tokens(_tokens) {
  }

  ///
  /// @brief common parse public interface
  ///
  void parse();

private:
  const std::string &source;
  const std::vector<Token> &tokens;
};

} // namespace nk
#endif