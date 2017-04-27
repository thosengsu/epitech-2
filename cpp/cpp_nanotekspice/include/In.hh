#ifndef IN_HH_
# define IN_HH_

#include <string>
#include "enum.hh"
#include "AInOut.hh"

namespace nts
{
  enum class InputType : int
    {
      NORMAL,
      CLOCK,
      TRUE,
      FALSE,
    };

  class In : public AInOut
  {
  public:
    In(std::string const& name, nts::InputType type =  nts::InputType::NORMAL);
    virtual ~In();

    virtual nts::Tristate	Compute(size_t pin_num_this = 1);
    virtual void		setPin(size_t pin, nts::Tristate state);

    nts::InputType		getInType(void) const;

  private:
    nts::InputType		_type;
  };

}

#endif /* !IN_HH_ */
