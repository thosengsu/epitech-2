#ifndef AINOUT_HH_
# define AINOUT_HH_

# include "AComponent.hh"

namespace nts
{
  class AInOut : public nts::AComponent
  {
  public:
    AInOut(std::vector<nts::InOut> type, std::string const& name) : AComponent(type, name) {};
    virtual ~AInOut() {};

    virtual void		linkGates(void) {};
    virtual nts::Tristate	Compute(size_t pin_num_this = 1) = 0;
  };
}

#endif /* !AINOUT_HH_ */
