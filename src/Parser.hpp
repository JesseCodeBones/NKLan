#ifndef __NK_PARSER_HPP__
#define __NK_PARSER_HPP__
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include "Lexer.hpp"
namespace nk {
/// @brief AST node kind class
enum class ASTTreeNodeKind : uint32_t { FILE_NODE, CLASS_NODE, INVALID_NODE };
/// @brief AST node class
class ASTTreeNode {
public:
  std::string_view code;
  ASTTreeNodeKind kind = ASTTreeNodeKind::INVALID_NODE;
  std::vector<ASTTreeNode> nodes;
};

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

  ///
  /// @brief get ast tree
  ///
  const ASTTreeNode &getASTTree() const noexcept {
    return ast;
  }

private:
  const std::string &source;        ///< source code
  const std::vector<Token> &tokens; ///< tokens from Lexer
  ASTTreeNode ast;                  ///< ast tree
};

} // namespace nk
#endif