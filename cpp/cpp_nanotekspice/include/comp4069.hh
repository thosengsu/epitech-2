#ifndef COMP4069_HH_
# define COMP4069_HH_

# include <map>
# include <vector>
# include <string>
# include "Agates.hh"
# include "AComponent.hh"
# include "IComponent.hh"

namespace nts
{
  class comp4069 : public nts::AComponent
  {
  public :
    comp4069(const std::string& name);
    virtual ~comp4069();

    virtual void			linkGates();
    virtual nts::Tristate		Compute(size_t pin_num_this = 1);
  private:
    std::map<size_t, nts::Agates *>	_gates;
  };
}

#endif // !COMP4069_HH_
