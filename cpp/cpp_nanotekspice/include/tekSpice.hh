#ifndef TEKSPICE_HH_
# define TEKSPICE_HH_

# include <string>
# include <vector>
# include <functional>
# include "IComponent.hh"

namespace nts
{
  class tekSpice
  {
  public:
    tekSpice();
    ~tekSpice();

    nts::IComponent			*createComponent(const std::string& type, const std::string& value);

  private:
    nts::IComponent			*create4001(const std::string& value);
    nts::IComponent			*create4011(const std::string& value);
    nts::IComponent			*create4030(const std::string& value);
    nts::IComponent			*create4069(const std::string& value);
    nts::IComponent			*create4071(const std::string& value);
    nts::IComponent			*create4081(const std::string& value);
    nts::IComponent			*createIn(const std::string& value);
    nts::IComponent			*createOut(const std::string& value);
    nts::IComponent			*createClock(const std::string& value);
    nts::IComponent			*createTrue(const std::string& value);
    nts::IComponent			*createFalse(const std::string& value);

    std::vector<std::string>						_names;
    std::vector<std::function<nts::IComponent *(const std::string&)>>	_fct;
  };
}

#endif // TEKSPICE_HH_
