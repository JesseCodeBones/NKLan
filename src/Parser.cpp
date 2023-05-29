#include "Parser.hpp"

using namespace nk;

void Parser::parse() {
    // init tree node to file tree node
    ASTTreeNode node {this->source, ASTTreeNodeKind::FILE_NODE};
    
}

