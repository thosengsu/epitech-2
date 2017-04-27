#ifndef IGATES_HH_
# define IGATES_HH_

# include <string>
# include "IComponent.hh"

namespace nts
{
  class Igates
  {
  public:
    virtual nts::Tristate		compute() = 0;
    virtual void			editEntrie(size_t numEntrie,
						   nts::Tristate state = nts::UNDEFINED) = 0;
    virtual nts::Tristate		getOutState() const = 0;
    virtual nts::Tristate		getInState(int nb) const = 0;
    virtual size_t			getNbInputs() const = 0;
    virtual std::vector<nts::Tristate>	getVecInputs() const = 0;
    virtual void		setOutState(nts::Tristate state) = 0;

    virtual ~Igates() {}
  };
}

#endif // !IGATES_HH_
