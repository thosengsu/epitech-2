#ifndef OUT_HH_
# define OUT_HH_

# include <string>
# include "enum.hh"
# include "AInOut.hh"

namespace nts
{
  class Out : public AInOut
  {
  public:
    Out(std::string const& name);
    virtual ~Out();

    virtual nts::Tristate	Compute(size_t pin_num_this = 1);
  };
}

#endif /* !OUT_HH_ */
