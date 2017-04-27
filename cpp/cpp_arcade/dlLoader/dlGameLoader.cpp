#include <string>
#include <vector>
#include <stdexcept>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include "dlGameLoader.hpp"
#include "IGame.hpp"

static bool     isLibDyna(const char *name)
{
  size_t        idx = 0;

  while (name[idx] != 0)
    ++idx;

  return (name[idx - 3] == '.' && name[idx - 2] == 's' && name[idx - 1] == 'o');
}

/* ------------ */
/* CTOR && DTOR */
/* ------------ */
arcade::dlGameLoader::dlGameLoader()
  : _handler(NULL)
 {
   DIR			*dir;
   struct dirent	*file;
   std::string		fileName;

   if ((dir = opendir("games")) == NULL)
     throw (std::runtime_error("Opendir failed, check if the directory \"games\" exist"));

   file = readdir(dir);
   while (file != NULL)
     {
       if (file->d_type == DT_REG && isLibDyna(file->d_name))
	 {
	   fileName = "games/";
	   fileName += file->d_name;
	   this->_gameLibNames.push_back(fileName);
	 }
       file = readdir(dir);
     }
   closedir(dir);

   this->_currentGame = this->_gameLibNames.begin();
 }

arcade::dlGameLoader::~dlGameLoader()
{
  if (this->_handler != NULL)
    dlclose(this->_handler);
}

/* ------ */
/* GETTER */
/* ------ */
std::vector<std::string>		arcade::dlGameLoader::getGameLibNames(void) const
{
  return (this->_gameLibNames);
}

std::vector<std::string>::iterator	arcade::dlGameLoader::getCurrentGameLibIt(void) const
{
  return (this->_currentGame);
}

/* ------------------ */
/* PRIVATES FUNCTIONS */
/* ------------------ */
void			arcade::dlGameLoader::setHandler(void)
{
  void			*handler = NULL;
  std::string		libName;

  libName = *(this->_currentGame);
  handler = dlopen(libName.c_str(), RTLD_LAZY);
  if (handler == NULL)
    throw (std::runtime_error(dlerror()));

  if (this->_handler != NULL)
    dlclose(this->_handler);
  this->_handler = handler;
}

arcade::launcher	arcade::dlGameLoader::getLauncher(void)
{
  arcade::launcher	fct;

  fct = (launcher)dlsym(this->_handler, "launchGame");
  if (fct == NULL)
    {
      dlclose(this->_handler);
      throw (std::runtime_error(dlerror()));
    }
  return (fct);
}

/* ----------------- */
/* MEMBERS FUNCTIONS */
/* ----------------- */
arcade::launcher	arcade::dlGameLoader::getCurrentGameLauncher(void)
{
  if (this->_handler == NULL)
    this->setHandler();
  return (getLauncher());
}

arcade::launcher	arcade::dlGameLoader::getNextGameLauncher(void)
{
  this->_currentGame++;

  if (this->_currentGame == this->_gameLibNames.end())
    this->_currentGame = this->_gameLibNames.begin();

  this->setHandler();
  return (getLauncher());
}

arcade::launcher	arcade::dlGameLoader::getPreviousGameLauncher(void)
{
  if (this->_currentGame == this->_gameLibNames.begin())
    this->_currentGame = this->_gameLibNames.end();

  this->_currentGame--;

  this->setHandler();
  return (getLauncher());
}

void	arcade::dlGameLoader::setToNextGame(void)
{
  this->_currentGame++;

  if (this->_currentGame == this->_gameLibNames.end())
    this->_currentGame = this->_gameLibNames.begin();

  this->setHandler();
}

#include <iostream>

void	arcade::dlGameLoader::setToPreviousGame(void)
{
  if (this->_currentGame == this->_gameLibNames.begin())
    this->_currentGame = this->_gameLibNames.end();

  this->_currentGame--;

  this->setHandler();
}
