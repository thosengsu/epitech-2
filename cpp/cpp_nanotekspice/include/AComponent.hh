#ifndef ACOMPONENT_HH_
# define ACOMPONENT_HH_

# include <vector>
# include <list>
# include <string>
# include "enum.hh"
# include "IComponent.hh"

namespace nts
{
  struct	Pin
  {
    nts::Tristate	state;
    nts::InOut		inOut;
  };

  struct	target
  {
    size_t		pinThis;
    nts::IComponent	*theTarget;
    size_t		pinTarget;
  };

  class AComponent : public nts::IComponent
  {
  public :
    AComponent(std::vector<nts::InOut> inOut, const std::string& name);
    AComponent(const AComponent& component);
    virtual ~AComponent();

    // pure methods
    virtual nts::Tristate	Compute(size_t pin_num_this = 1) = 0;
    virtual void		linkGates() = 0;

    // getter
    nts::Tristate		getState(size_t pin) const;
    nts::InOut			getPinType(size_t pin) const;
    nts::Tristate		getInLinkState(size_t pin);
    const std::string&		getName(void) const;
    size_t			getMaxPin(void) const;
    int				isLinked(void) const;

    //member functions
    virtual void		Dump(void) const;
    virtual void		SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target);

    virtual void		setPin(size_t numPin, nts::Tristate state);


    //operators
    AComponent&					operator=(const AComponent& component);

  protected :
    std::string					_name;
    std::vector<nts::Pin>			_pins;
    std::vector<nts::target>			_inLinks;
  };
}

#endif // ACOMPONENT_HH_
