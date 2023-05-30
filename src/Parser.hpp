#ifndef __NK_PARSER_HPP__
#define __NK_PARSER_HPP__
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include "Lexer.hpp"
namespace nk {
/// @brief AST node kind class
enum class ASTTreeNodeKind : uint32_t {
  FILE_NODE,
  CLASS_NODE,
  FUNCTION_NODE,
  VARIABLE_DECLARATION_NODE,
  INVALID_NODE
};
/// @brief AST node class
class ASTTreeNode {
public:
  std::string_view code;
  ASTTreeNodeKind kind = ASTTreeNodeKind::INVALID_NODE;
};

class SourceFileTreeNode : public ASTTreeNode {
public:
  std::vector<ASTTreeNode> children;
};

class TypeTreeNode : public ASTTreeNode {
public:
  std::string_view name;
};

class FunctionTreeNode : public ASTTreeNode {
public:
  FunctionTreeNode() noexcept {
    ASTTreeNode::kind = ASTTreeNodeKind::FUNCTION_NODE;
  }
  FunctionTreeNode(const FunctionTreeNode &src) = default;
  std::string_view name;
  std::vector<TypeTreeNode> signature; // return type, param1, param2...
  std::vector<std::string_view> paramNames;
  std::vector<ASTTreeNode> body;
};

class VariableDeclarationTreeNode : public ASTTreeNode {
public:
  VariableDeclarationTreeNode() noexcept {
    ASTTreeNode::kind = ASTTreeNodeKind::VARIABLE_DECLARATION_NODE;
  }
};

class ClassTreeNode : public ASTTreeNode {
public:
  ClassTreeNode(std::string_view _code, std::string_view _className) : className(_className) {
    ASTTreeNode::code = _code;
  }
  std::string_view className;
  std::vector<FunctionTreeNode> constructors;
  std::vector<VariableDeclarationTreeNode> variableMembers;
  std::vector<FunctionTreeNode> functionMembers;
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
  const std::string_view source;    ///< source code
  const std::vector<Token> &tokens; ///< tokens from Lexer
  ASTTreeNode ast;                  ///< ast tree

private:
  uint32_t currPos = 0U;
  ///@brief parse class ast
  /// like class A{a:int=1}
  /// like class B{a():int{return 1}}
  ClassTreeNode parseClass(const Token &token);
  ASTTreeNode parseClassMember();
  ///@brief parse function ast
  FunctionTreeNode parseFunction();
  VariableDeclarationTreeNode parseVariableDeclaration();

  ///@brief skip break line, for example
  /// class
  /// A{}
  /// is valid
  void skipBreakLines() {
    while (tokens[currPos].type == TokenType::BreakLine) {
      currPos++;
    }
  }
};

} // namespace nk
#endif