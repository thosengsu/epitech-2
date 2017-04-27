#ifndef PARSER_HH_
# define PARSER_HH_

# include <fstream>
# include <list>
# include <regex>
# include "IComponent.hh"
# include "graph.hh"
# include "cpp_nanotekspice_parser.hh"
# include "tekSpice.hh"

namespace nts
{
  class Parser : public IParser
  {
  public:
    Parser();
    virtual ~Parser();

    virtual void		feed(std::string const& input);
    virtual void		parseTree(t_ast_node& root);
    virtual nts::t_ast_node	*createTree(void);

    nts::s_ast_node		*sectionNode(std::string const& str, nts::t_ast_node *root,
					     nts::t_ast_node *currentSectionPtr);
    nts::s_ast_node		*componentNode(std::string const& str, nts::t_ast_node *root,
					       nts::t_ast_node *currentSectionPtr);
    nts::s_ast_node		*linkNode(std::string const& str, nts::t_ast_node *root,
					  nts::t_ast_node *currentSectionPtr);
    nts::graph			*getGraph(void) const;

  private:
    std::string			epurString(std::string const& str) const;
    nts::ASTNodeType		getNodeType(std::string const& str) const;
    int				isComponent(std::string const& str) const;
    void			checkChipsetsSection(t_ast_node const& section);
    void			checkLink(std::string const& chipsetLinkName,
					  size_t chipsetLinkPin, nts::InOut pinType) const;
    void			checkLinksSection(t_ast_node const& section);

    std::vector<std::string>	_input;
    std::vector<std::regex>	_regexTab;
    nts::graph			*_graph;
    nts::tekSpice		tekSpice;
  };
}
#endif /* !PARSER_HH_ */
