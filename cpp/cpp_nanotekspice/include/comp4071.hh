#ifndef COMP4071_HH_
# define COMP4071_HH_

# include <map>
# include <string>
# include "AComponent.hh"
# include "IComponent.hh"
# include "Agates.hh"

namespace nts
{
  class comp4071 : public nts::AComponent
  {
  public :
    comp4071(const std::string& name);
    virtual ~comp4071();

    virtual nts::Tristate		Compute(size_t pin_num_this = 1);
    virtual void			linkGates();
  private :
    std::map<size_t, nts::Agates *>	_gates;
  };
}

#endif // !COMP4071_HH_
