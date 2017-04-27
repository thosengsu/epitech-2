#ifndef ANDGATE_HH_
# define ANDGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class andGate : public nts::Agates
  {
  public :
    virtual ~andGate();
    andGate();
    andGate(size_t nbInputs, std::vector<nts::Tristate> states);

    virtual nts::Tristate	compute();
  };
}

#endif // ANDGATE_HH_
