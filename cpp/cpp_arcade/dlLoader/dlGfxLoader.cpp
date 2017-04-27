#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include "dlGfxLoader.hpp"
#include "../lib/ILib.hpp"

static bool	isLibDyna(const char *name)
{
  size_t	idx = 0;

  while (name[idx] != 0)
    ++idx;

  return (name[idx - 3] == '.' && name[idx - 2] == 's' && name[idx - 1] == 'o');
}

/* ------------ */
/* CTOR && DTOR */
/* ------------ */
arcade::dlGfxLoader::dlGfxLoader(std::string const& gfxLibName)
  :  current(NULL), _handler(NULL), _handlerTmp(NULL)
 {
   DIR			*dir;
   struct dirent	*file;
   std::string		fileName;

   if ((dir = opendir("lib")) == NULL)
     throw (std::runtime_error("Opendir failed, check if the directory \"lib\" exist"));

   file = readdir(dir);
   while (file != NULL)
     {
       if (file->d_type == DT_REG && isLibDyna(file->d_name))
	 {
	   fileName = "lib/";
	   fileName += file->d_name;
	   this->_gfxLibNames.push_back(fileName);
	 }
       file = readdir(dir);
     }
   closedir(dir);

   if (this->_gfxLibNames.empty())
     throw (std::invalid_argument("No gfx lib found."));
   this->_currentGfx = this->_gfxLibNames.begin();
   while ((*this->_currentGfx).find(gfxLibName) == (*this->_currentGfx).npos)
     {
       this->_currentGfx++;
       if (this->_currentGfx == this->_gfxLibNames.end())
	 throw (std::invalid_argument("Invalid gfx lib passed as argument."));
     }
 };

arcade::dlGfxLoader::~dlGfxLoader()
{
  if (this->current != NULL)
    delete this->current;

  if (this->_handler != NULL)
    dlclose(this->_handler);

  if (this->_handlerTmp != NULL)
    dlclose(this->_handlerTmp);
}

/* ------ */
/* GETTER */
/* ------ */

std::vector<std::string>	arcade::dlGfxLoader::getGfxLibNames(void) const
{
  return (this->_gfxLibNames);
}

std::vector<std::string>::iterator	arcade::dlGfxLoader::getCurrentGfxLibIt(void) const
{
  return (this->_currentGfx);
}

/* ----------------- */
/* MEMBERS FUNCTIONS */
/* ----------------- */
void			arcade::dlGfxLoader::closeOldGfx(void)
{
  if (this->_handlerTmp != NULL)
    dlclose(this->_handlerTmp);
}

arcade::ILib		*arcade::dlGfxLoader::getCurrentGfxLib(void)
{
  if (this->_handler == NULL)
    this->setHandler();

  if (this->current == NULL)
    this->current = this->getILib();
  return (this->current);
}

arcade::ILib		*arcade::dlGfxLoader::getNextGfxLib(void)
{
  if (this->_gfxLibNames.size() > 1)
    {
      this->_currentGfx++;
      if (this->_currentGfx == this->_gfxLibNames.end())
	this->_currentGfx = this->_gfxLibNames.begin();
      this->setHandler();

      this->current = this->getILib();
    }
  return (this->current);
}

arcade::ILib		*arcade::dlGfxLoader::getPreviousGfxLib(void)
{
  if (this->_gfxLibNames.size() > 1)
    {
      if (this->_currentGfx == this->_gfxLibNames.begin())
	this->_currentGfx = this->_gfxLibNames.end();
      this->_currentGfx--;
      this->setHandler();

      this->current = this->getILib();
    }
  return (this->current);
}

/* ------------------ */
/* PRIVATES FUNCTIONS */
/* ------------------ */
void			arcade::dlGfxLoader::setHandler(void)
{
  void			*handler = NULL;
  std::string		libName;

  libName = (*(this->_currentGfx)).c_str();
  handler = dlopen(libName.c_str(), RTLD_LAZY);
  if (handler == NULL)
    throw (std::runtime_error(dlerror()));

  this->_handlerTmp = this->_handler;
  this->_handler = handler;
}

arcade::ILib		*arcade::dlGfxLoader::getILib(void)
{
  arcade::create_gfx	*fct;
  ILib			*ptr;

  fct = (arcade::create_gfx *)(dlsym(this->_handler, "create_GFX"));
  if (fct == NULL)
    {
      if (this->_handler != NULL)
	dlclose(this->_handler);
      throw (std::runtime_error(dlerror()));
    }
  ptr = fct();
  return (ptr);
}
