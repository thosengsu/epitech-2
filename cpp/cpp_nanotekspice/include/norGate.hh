#ifndef NORGATE_HH_
# define NORGATE_HH_

# include <vector>
# include "Agates.hh"
# include "IComponent.hh"

namespace nts
{
  class norGate : public Agates
  {
  public:
    virtual ~norGate();
    norGate();
    norGate(size_t nbInputs, std::vector<nts::Tristate> states);

    virtual nts::Tristate	compute();

    // operator

    nts::norGate&		operator=(const norGate& gate);
  };
}

#endif // !NORGATE_HH_
