#include "Parser.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/types.h>
#include "Lexer.hpp"

using namespace nk;

void Parser::parse() {
  // init tree node to file tree node
  static_cast<void>(source);
  SourceFileTreeNode root{this->source, ASTTreeNodeKind::FILE_NODE};
  skipBreakLines();
  const Token &token = tokens.front();
  if (token.type == TokenType::Class) { // parse class
    currPos++;
    root.children.push_back(parseClass(token));
  }
}

ClassTreeNode Parser::parseClass(const Token &token) {
  // class \n \n className is valid
  skipBreakLines();
  const Token &identifierToken = tokens[currPos];
  uint32_t braceCount = 0U;
  if (identifierToken.type != TokenType::Identifier) {
    throw std::runtime_error("Class does not follow a class name @" +
                             std::to_string(token.range.first) + ":" +
                             std::to_string(token.range.second));
  }

  const std::string_view className = source.substr(
      identifierToken.range.first, identifierToken.range.second - identifierToken.range.first);
  std::cout << "className:" << className << std::endl;
  ClassTreeNode classTreeNode(source.substr(token.range.first, token.range.second -token.range.first), className);
  currPos++; // after consume one class identifier token
  skipBreakLines();
  // open brace check {
  if (tokens[currPos].type != TokenType::OpenBrace) {
    throw std::runtime_error("No open brace following class name @" +
                             std::to_string(tokens[currPos].range.first) + ":" +
                             std::to_string(tokens[currPos].range.second));
  }
  currPos++; // after {
  braceCount++;
  skipBreakLines();
  if (tokens[currPos].type != TokenType::CloseBrace) {
    do {
      // parse all class member
      const ASTTreeNode memberTreeNode = parseClassMember();
      if (memberTreeNode.kind == ASTTreeNodeKind::FUNCTION_NODE) {
        // it is a member function
        
      }
      skipBreakLines();
    } while (tokens[currPos].type != TokenType::CloseBrace);
  }

  return classTreeNode;
}

ASTTreeNode Parser::parseClassMember() {
  const Token &identifierToken = tokens[currPos];
  uint32_t braceCount = 0U;
  if (identifierToken.type != TokenType::Identifier) {
    throw std::runtime_error("Class member does not follow a member name @" +
                             std::to_string(tokens[currPos].range.first) + ":" +
                             std::to_string(tokens[currPos].range.second));
  }

  const uint32_t prevPos = currPos;
  currPos++;
  if (tokens[currPos].type == TokenType::OpenParentheses) { // main() function

  } else if (tokens[currPos].type == TokenType::BreakLine ||
             tokens[currPos].type == TokenType::Colon||
             tokens[currPos].type == TokenType::Equal) { // a \n | a:int | a = 
  }
}
