#ifndef Agates_hh_
# define Agates_hh_

# include <string>
# include <vector>
# include "Igates.hh"
# include "IComponent.hh"

namespace nts
{
  class Agates : public nts::Igates
  {
  public:
    virtual ~Agates();
    Agates(size_t nbInputs, std::vector<nts::Tristate> stateIn);
    Agates();

    virtual nts::Tristate		compute() = 0;

    // GETTER

    virtual nts::Tristate		getOutState() const;
    virtual nts::Tristate		getInState(int nb) const;
    virtual size_t			getNbInputs() const;
    virtual std::vector<nts::Tristate>	getVecInputs() const;

    // SETTER

    virtual void			setOutState(nts::Tristate state);
    virtual void			editEntrie(size_t numEntrie,
						   nts::Tristate state = nts::UNDEFINED);
    virtual void			setNewInput(nts::Tristate state);

  protected:
    nts::Tristate			_outState;
    std::vector<nts::Tristate>		_inState;
  };
}

#endif //Agates_hh_
