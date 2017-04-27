#ifndef ERROR_HH_
# define ERROR_H_

# include <stdexcept>

namespace nts
{
  namespace error
  {
    class file_error : public std::logic_error
    {
    public:
      file_error(std::string what) : logic_error(what) {};
      virtual ~file_error() {};
    };
  }
}

#endif /* !ERROR_H_ */
