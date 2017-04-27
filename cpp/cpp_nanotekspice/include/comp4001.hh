#ifndef COMP4001_HH_
# define COMP4001_HH_

# include <map>
# include <vector>
# include <string>
# include "IComponent.hh"
# include "AComponent.hh"
# include "Agates.hh"

namespace nts
{
  class comp4001: public nts::AComponent
  {
  public:
    comp4001(const std::string& name);
    virtual ~comp4001();

    // member functions
    virtual nts::Tristate		Compute(size_t pin_num_this = 1);
    virtual void			linkGates();

  private:
    std::map<size_t, nts::Agates *>	_gates;
  };
}

#endif // !COMP4001_HH_
