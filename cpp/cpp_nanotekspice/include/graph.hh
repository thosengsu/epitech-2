#ifndef GRAPH_HH_
# define GRAPH_HH_

# include <string>
# include <vector>
# include "IComponent.hh"
# include "AComponent.hh"

namespace nts
{
  struct graph
  {
    std::vector<nts::IComponent *>	inputs;
    std::vector<nts::IComponent *>	outputs;
    std::vector<nts::IComponent *>	components;

    IComponent	*getComponent(std::string const& name)
    {
      for (auto i : this->components)
	if (static_cast<AComponent *>(i)->getName() == name)
	  return (i);
      return (NULL);
    }

    IComponent	*getInput(std::string const& name)
    {
      for (auto i : this->inputs)
	if (static_cast<AComponent *>(i)->getName() == name)
	  return (i);
      return (NULL);
    }
  };
}

#endif /* !GRAPH_HH_ */
