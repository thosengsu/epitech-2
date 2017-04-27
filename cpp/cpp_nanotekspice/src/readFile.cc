#include <fstream>
#include <string>
#include "Parser.hh"

nts::Parser	*readFile(const char *file_name)
{
  std::string	fileName;
  std::ifstream	file;
  std::string	buff;
  nts::Parser	*parser = new nts::Parser;
  nts::t_ast_node *root;

  fileName = file_name;
  file.open(fileName);

  while (getline(file, buff, '\n'))
      parser->feed(buff);

  root = parser->createTree();
  parser->parseTree(*root);
  return (parser);
}
