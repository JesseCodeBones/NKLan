
#include "Lexer.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>
#include "EnvironmentConfig.hpp"
using namespace nk;

void Lexer::parse() {
  while (true) {
    Token token = next();
    if (token.type == TokenType::EndOfFile) {
      break; // end
    }
    NK_TRACE(token)
    this->tokens.push_back(std::move(token));
  }
}

Token Lexer::next() {
  // skip space
  while (pos < sourceView.size() && '\n' != sourceView[pos] && static_cast<bool>(std::isspace(sourceView[pos]))) {
    ++pos;
  }
  // to the end
  if (pos == sourceView.size()) {
    return {TokenType::EndOfFile, {sourceView.size(), sourceView.size()}};
  }

  if (sourceView[pos] == '\n') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::BreakLine, {posBefore, pos}};
  }

  if (sourceView[pos] == '{') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::OpenBrace, {posBefore, pos}};
  }

  if (sourceView[pos] == '}') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::CloseBrace, {posBefore, pos}};
  }

  if (sourceView[pos] == '(') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::OpenParentheses, {posBefore, pos}};
  }

  if (sourceView[pos] == ')') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::CloseParentheses, {posBefore, pos}};
  }

  if (sourceView[pos] == ':') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::Colon, {posBefore, pos}};
  }

  if (sourceView[pos] == '+') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::Plus, {posBefore, pos}};
  }

  if (sourceView.substr(pos, 2) == "++") {
    size_t posBefore = pos;
    pos += 2;
    return {TokenType::PlusPlus, {posBefore, pos}};
  }

  if (sourceView.substr(pos, 2) == "!=") {
    size_t posBefore = pos;
    pos += 2;
    return {TokenType::NEqual, {posBefore, pos}};
  }

  if (sourceView[pos] == '=') {
    size_t posBefore = pos;
    pos++;
    return {TokenType::Equal, {posBefore, pos}};
  }

  if (isDecNumber(sourceView[pos])) {
    size_t posBefore = pos;
    while (isDecNumber(sourceView[pos])) {
      pos++;
    }
    if (static_cast<bool>(std::isspace(sourceView[pos + 1]))) {
      return {TokenType::DecIntegerLiteral, {posBefore, pos}};
    } else {
      // turn back and continue to below check
      pos = posBefore;
    }
  }

  if (isIdentifierStart(sourceView[pos])) {
    size_t posBefore = pos;
    while (isIdentifierBody(sourceView[pos]) && pos < sourceView.size()) {
      pos++;
    }
    std::string_view identifier = sourceView.substr(posBefore, pos - posBefore);
    TokenType type = toTokenType(identifier);
    if (type != TokenType::InValid) {
      return {type, {posBefore, pos}};
    } else {
      return {TokenType::Identifier, {posBefore, pos}};
    }
  }
  std::cerr << "find unrecognized character " << sourceView[pos] << ", @" << path << ":" << pos
            << std::endl;
  throw std::runtime_error("Illegal input");
}

bool Lexer::isIdentifierStart(uint8_t c) const noexcept {
  return isAlphabet(c) || c == '_';
}

bool Lexer::isIdentifierBody(uint8_t c) const noexcept {
  return isAlphabet(c) || isDecNumber(c) || c == '_';
}

bool Lexer::isAlphabet(uint8_t c) const noexcept {
  c = c | static_cast<uint8_t>(0x20);
  return c >= 'a' && c <= 'z';
}

bool Lexer::isDecNumber(const uint8_t c) const noexcept {
  return c >= '0' && c <= '9';
}

TokenType Lexer::toTokenType(const std::string_view str) const noexcept {
  if (str == "class") {
    return TokenType::Class;
  }

  if (str == "val") {
    return TokenType::Val;
  }
  return TokenType::InValid;
}
