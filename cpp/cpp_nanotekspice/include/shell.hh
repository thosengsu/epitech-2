#ifndef SHELL_HH_
# define SHELL_HH_

# include <vector>
# include <string>
# include "IComponent.hh"

namespace nts
{
  namespace sh
  {
    class shell
    {
    public:
      shell(std::vector<nts::IComponent *> components,
	    std::vector<nts::IComponent *> in,
	    std::vector<nts::IComponent *> out);
      ~shell();

      void				Compare();
      void				affHelp() const;
      void				sh();
      void				Dump() const;
      void				changeInput();
      void				Simulate();
      void				Display();
      void				loop();

    private:
      std::string			epurString(std::string const& str) const;

    private:
      bool				_running;
      std::string			_cmd;
      std::vector<nts::IComponent *>	_components;
      std::vector<nts::IComponent *>	_in;
      std::vector<nts::IComponent *>	_out;
    };
  }
}

#endif // !SHELL_HH_
