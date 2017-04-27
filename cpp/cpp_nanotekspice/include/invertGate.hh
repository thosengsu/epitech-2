#ifndef INVERTGATE_HH_
# define INVERTGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class invertGate : public nts::Agates
  {
  public :
    virtual ~invertGate();
    invertGate();
    invertGate(size_t nbInputs, std::vector<nts::Tristate> stateIn);

    virtual nts::Tristate	compute();

    // operator
    nts::invertGate&	operator=(const invertGate& gate);
  };
}

#endif // INVERTGARE_HH_
