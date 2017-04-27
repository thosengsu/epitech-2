#ifndef NANDGATE_HH_
# define NANDGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class nandGate : public Agates
  {
  public :
    virtual ~nandGate();
    nandGate();
    nandGate(size_t nbInputs, std::vector<nts::Tristate> states);

    virtual nts::Tristate	compute();
  };
}

#endif // NANDGATE_HH_
