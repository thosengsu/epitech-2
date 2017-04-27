#ifndef COMP4081_HH_
# define COMP4081_HH_

# include <map>
# include <string>
# include "Agates.hh"
# include "IComponent.hh"
# include "AComponent.hh"

namespace nts
{
  class comp4081 : public AComponent
  {
  public :
    comp4081(const std::string& name);
    ~comp4081();

    virtual nts::Tristate		Compute(size_t pin_num_this = 1);
    virtual void			linkGates();

  private :
    std::map<size_t, nts::Agates *>	_gates;
  };
}

#endif // !COMP4081_HH_
