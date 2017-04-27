#include <string>
#include <vector>
#include <list>
#include "Error.hh"
#include "cpp_nanotekspice_parser.hh"
#include "Parser.hh"
#include "tekSpice.hh"
#include "IComponent.hh"

#include <iostream>

static const std::string	sectionsNames[] =
  {
    ".chipsets",
    ".links",
  };

static const size_t		NB_COMPONENT = 11;
static const std::string	componentsNames[] =
  {
    "input",
    "output",
    "clock",
    "true",
    "false",
    "4001",
    "4011",
    "4030",
    "4069",
    "4071",
    "4081",
  };

static const nts::ASTNodeType	nodeType[] =
  {
    nts::ASTNodeType::SECTION,
    nts::ASTNodeType::COMPONENT,
    nts::ASTNodeType::LINK,
  };

typedef nts::s_ast_node *(nts::Parser::* nodeTypeFunc)(std::string const&, nts::t_ast_node *root,
						       nts::t_ast_node *currentSectionPtr);

static nodeTypeFunc		typeFunc[] =
  {
    &nts::Parser::sectionNode,
    &nts::Parser::componentNode,
    &nts::Parser::linkNode,
  };

nts::Parser::Parser()
{
  this->_regexTab.push_back(static_cast<std::regex>("^\\.[a-z]+:$"));
  this->_regexTab.push_back(static_cast<std::regex>("^(([a-z]+)|([0-9]+)) [a-zA-Z0-9]+$"));
  this->_regexTab.push_back(static_cast<std::regex>("^[a-zA-Z0-9]+:[0-9]+ [a-zA-Z0-9]+:[0-9]+$"));

  this->_graph = new nts::graph;
}

nts::Parser::~Parser()
{
}

void		nts::Parser::feed(std::string const& input)
{
  size_t	pos;
  std::string	tmp = this->epurString(input);

  if ((pos = tmp.find_first_of('#')) != tmp.npos)
    {
      if (pos != 0)
	this->_input.push_back(this->epurString(tmp.substr(0, pos)));
    }
  else if (!tmp.empty() && tmp != "")
    this->_input.push_back(tmp);
}

std::string	nts::Parser::epurString(std::string const& str) const
{
  std::string	out;

  for (size_t n = 0 ; n < str.size() ; n++)
    {
      if (str[n] != ' ' && str[n] != '\t')
	out += str[n];
      else if (!out.empty() &&(str[n] == ' ' || str[n] == '\t') &&
	       (n + 1 < str.size()&& str[n + 1] != ' ' && str[n + 1] != '\t'))
	out += ' ';
    }
  return (out);
}

void		nts::Parser::checkChipsetsSection(t_ast_node const& section)
{
  nts::IComponent	*newComponent;

  for (auto i : *section.children)
    {
      if (i->type != nts::ASTNodeType::COMPONENT)
	throw(nts::error::file_error("You can only define component in \".chipsets\" section."));
      else if (this->isComponent(i->value) == -1)
	throw(nts::error::file_error(static_cast<std::string>(i->value) +
				     static_cast<std::string>(" isn't a valid component type.")));
      else if (i->children->size() != 1 || i->children->at(0)->type != nts::ASTNodeType::STRING)
	throw(nts::error::file_error("In \".component\" section, component must be defined like this : \"componentType componentName\"."));

      if (this->_graph->getComponent(i->children->at(0)->value) == NULL)
	{
	  newComponent = this->tekSpice.createComponent(i->value, i->children->at(0)->value);
	  this->_graph->components.push_back(newComponent);
	  if (i->value == "input" || i->value == "clock")
	    this->_graph->inputs.push_back(newComponent);
	  else if (i->value == "output")
	    this->_graph->outputs.push_back(newComponent);
	}
      else
	throw(nts::error::file_error(static_cast<std::string>(i->children->at(0)->value) +
				     static_cast<std::string>(" : There is already a chipset with this name.")));
    }
}

void		nts::Parser::checkLink(std::string const& chipsetLinkName, size_t chipsetLinkPin,
				       nts::InOut pinType) const
{
  nts::IComponent	*chipset = this->_graph->getComponent(chipsetLinkName);
  std::ostringstream	stream;

  stream << chipsetLinkName << ":" << chipsetLinkPin;

  if (chipset == NULL)
    throw(nts::error::file_error(stream.str() +
				 static_cast<std::string>( " : Link on undefined chipset.")));
  else if (chipsetLinkPin > static_cast<AComponent *>(chipset)->getMaxPin())
    throw(nts::error::file_error(stream.str() +
				 static_cast<std::string>(" : Out of range pin for this chipset.")));
  else if (pinType != static_cast<AComponent *>(chipset)->getPinType(chipsetLinkPin))
    throw(nts::error::file_error(stream.str() +
				 static_cast<std::string>(" : Targeted pin isn't of the good type.")));
}

void		nts::Parser::checkLinksSection(t_ast_node const& section)
{
  std::string	name1;
  std::string	name2;
  size_t	pin1;
  size_t	pin2;

  for (auto i : *section.children)
    {
      if (i->type != nts::ASTNodeType::LINK)
	throw(nts::error::file_error("You can only define link in \".links\" section."));

      name1 = i->value.substr(0, i->value.find_first_of(':'));
      pin1 = static_cast<size_t>(std::stoi(i->value.substr(i->value.find_first_of(':') + 1)));

      name2 = i->children->at(0)->value.substr(0, i->children->at(0)->value.find_first_of(':'));
      pin2 = static_cast<size_t>(std::stoi(i->children->at(0)->value.substr(i->children->at(0)->value.find_first_of(':')
									    + 1)));
      this->checkLink(name1, pin1, nts::OUTPUT);
      this->checkLink(name2, pin2, nts::INPUT);

      this->_graph->getComponent(name2)->SetLink(pin2, *this->_graph->getComponent(name1), pin1);
    }
}

static bool	asciiOrder(nts::IComponent *i, nts::IComponent *j)
{
  return (static_cast<nts::AComponent *>(i)->getName()
	  < static_cast<nts::AComponent *>(j)->getName());
}

void	nts::Parser::parseTree(t_ast_node &root)
{
  nts::AComponent	*tmp;

  if (root.children->size() != 2 ||
      root.children->at(0)->value != ".chipsets" || root.children->at(1)->value != ".links")
    throw(nts::error::file_error("File must content sections \".chipsets\" and \".links\"."));
  this->checkChipsetsSection(*root.children->at(0));
  this->checkLinksSection(*root.children->at(1));

  for (auto i : this->_graph->outputs)
    {
      tmp = static_cast<AComponent *>(i);
      if (tmp->isLinked() == -1)
	throw(nts::error::file_error(static_cast<std::string>(tmp->getName()) +
				     static_cast<std::string>(" output is not linked to anything.")));
    }
  std::sort(this->_graph->outputs.begin(), this->_graph->outputs.end(), asciiOrder);
}

nts::t_ast_node	*nts::Parser::createTree(void)
{
  nts::t_ast_node	*root = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);
  nts::t_ast_node	*currentSectionPtr = root;
  nts::ASTNodeType	currentNodeType = nts::ASTNodeType::DEFAULT;
  std::ostringstream	stream;
  size_t		idx = 0;
  size_t		line = 1;

  root->type = nts::ASTNodeType::DEFAULT;
  for (auto i : this->_input)
    {
      currentNodeType = getNodeType(i);
      idx = 0;
      while (idx < this->_regexTab.size())
	{
	  if (nodeType[idx] == currentNodeType)
	    {
	      currentSectionPtr = ((*this).*typeFunc[idx])(i, root, currentSectionPtr);
	      break;
	    }
	  ++idx;
	}
      if (idx == this->_regexTab.size())
	{
	  stream << static_cast<std::string>("Ligne n°");
	  stream << line << static_cast<std::string>(": \"") <<
	    static_cast<std::string>(i) << static_cast<std::string>("\" : isn's a good line format.");
	  throw(nts::error::file_error(stream.str()));
	  }
      ++line;
    }
  return (root);
}

nts::ASTNodeType	nts::Parser::getNodeType(std::string const& str) const
{
  for (size_t i = 0; i < this->_regexTab.size() ; ++i)
    {
      if (std::regex_match(str, this->_regexTab[i]) == 1)
	return (nodeType[i]);
    }
  return (nts::ASTNodeType::DEFAULT);
}

int			nts::Parser::isComponent(std::string const& str) const
{
  size_t		idx = 0;

  while (idx < NB_COMPONENT)
    {
      if (str.compare(componentsNames[idx]) == 0)
	return (0);
      ++idx;
    }
  return (-1);
}
nts::t_ast_node		*nts::Parser::sectionNode(std::string const& str, nts::t_ast_node *root,
						  nts::t_ast_node *currentSectionPtr)
{
  static_cast<void>(currentSectionPtr);
  nts::t_ast_node	*newNode = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);

  root->children->push_back(newNode);
  newNode->type = nts::ASTNodeType::SECTION;
  newNode->lexeme = str;
  newNode->value = str;
  newNode->value.pop_back();

  return (newNode);
}

nts::t_ast_node		*nts::Parser::componentNode(std::string const& str,
						    __attribute__((unused))nts::t_ast_node *root,
						    nts::t_ast_node *currentSectionPtr)
{
  nts::t_ast_node	*newNode = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);
  nts::t_ast_node	*newNodeC = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);

  currentSectionPtr->children->push_back(newNode);
  newNode->children->push_back(newNodeC);

  newNode->type = nts::ASTNodeType::COMPONENT;
  newNode->lexeme = str;
  newNode->value = str.substr(0, str.find_first_of(' '));

  newNodeC->type = nts::ASTNodeType::STRING;
  newNodeC->lexeme = str;
  newNodeC->value = str.substr(str.find_first_of(' ') + 1);

  return (currentSectionPtr);
}

nts::t_ast_node		*nts::Parser::linkNode(std::string const& str,
					      __attribute__((unused))nts::t_ast_node *root,
					      nts::t_ast_node *currentSectionPtr)
{
  nts::t_ast_node	*newNode = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);
  nts::t_ast_node	*newNodeC = new nts::t_ast_node(new std::vector<nts::t_ast_node *>);

  currentSectionPtr->children->push_back(newNode);
  newNode->children->push_back(newNodeC);

  newNode->type = nts::ASTNodeType::LINK;
  newNode->lexeme = str;
  newNode->value = str.substr(0, str.find_first_of(' '));

  newNodeC->type = nts::ASTNodeType::LINK_END;
  newNodeC->lexeme = str;
  newNodeC->value = str.substr(str.find_first_of(' ') + 1);

  return (currentSectionPtr);
}

nts::graph		*nts::Parser::getGraph(void) const
{
  return (this->_graph);
}
