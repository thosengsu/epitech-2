#ifndef EXORGATE_HH_
# define EXORGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class exOrGate : public nts::Agates
  {
  public :
    virtual ~exOrGate();
    exOrGate();
    exOrGate(size_t nbInputs, std::vector<nts::Tristate>);

    virtual nts::Tristate	compute();
  };
}

#endif // EXORGATE_HH_
