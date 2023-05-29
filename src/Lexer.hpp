#ifndef __NK_LEXER_HPP__
#define __NK_LEXER_HPP__

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
namespace nk {
/// @brief token type
enum TokenType {
  Class = 1U,
  OpenBrace,  // {
  CloseBrace, // }
  StringLiteral,
  DecIntegerLiteral,
  OpenParentheses,  // (
  CloseParentheses, // )
  Colon,            // :
  BreakLine,        //\n
  Plus,             // +
  PlusPlus,         // ++
  Val,
  Equal,
  NEqual, // !=
  EndOfFile,
  Identifier,
  InValid
};
///< token strings, can print its meaning
const static std::array tokenStrings = {"Class",
                                        "OpenBrace",
                                        "CloseBrace",
                                        "StringLiteral",
                                        "DecIntegerLiteral",
                                        "OpenParentheses",
                                        "CloseParentheses",
                                        "Colon",
                                        "BreakLine",
                                        "Plus",
                                        "PlusPlus",
                                        "Val",
                                        "Equal",
                                        "NEqual",
                                        "EndOfFile",
                                        "Identifier",
                                        "InValid"};
/// @brief token with range
struct Token {

  TokenType type;                  ///< type
  std::pair<size_t, size_t> range; ///< range
  /// @brief print token content
  friend std::ostream &operator<<(std::ostream &out, const Token &instance) noexcept {
    out << tokenStrings[instance.type - 1U] << "{" << instance.range.first << ":"
        << instance.range.second << "}\n";
    return out;
  }
};

/// @brief Lexer for NK language
class Lexer {
public:
  /// @brief constructor for Lexer
  ///
  /// @param _source script source of NK
  /// @param _path path of source code
  Lexer(std::string _source, std::filesystem::path _path)
      : source(_source), path(_path), sourceView(source), pos(0U) {
  }

  /// @brief parse and generate token list
  /// @throw runtime_exception
  void tokenizer();

  /// @brief retrieve next token
  ///
  /// @return token with range
  /// @throw runtime_exception with there is unrecognized character
  Token next();

  /// @brief get tokens
  ///
  /// @return token vector
  const std::vector<Token> &getTokens() const noexcept {
    return tokens;
  }

private:
  const std::string source;          ///< original text source code
  const std::filesystem::path path;  ///< path of source code
  const std::string_view sourceView; ///< string view of source code string
  size_t pos;                        ///< position
  std::vector<Token> tokens;         ///< result tokens

  // private function
private:
  /// @brief if this is a identifier start
  bool isIdentifierStart(uint8_t c) const noexcept;
  /// @brief if this is a part of identifier body
  bool isIdentifierBody(uint8_t c) const noexcept;
  /// a-z A-Z
  bool isAlphabet(uint8_t c) const noexcept;
  /// 0-9
  bool isDecNumber(const uint8_t c) const noexcept;
  ///@brief string to TokenType
  TokenType toTokenType(const std::string_view str) const noexcept;
};
} // namespace nk

#endif