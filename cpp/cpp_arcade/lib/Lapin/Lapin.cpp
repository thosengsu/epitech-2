//
// Lapin.cpp for arcade in /home/erwan/Tek2/C++/cpp_arcade/lib
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Thu Mar 23 16:10:12 2017 Erwan
// Last update Sun Apr  9 13:44:37 2017 Erwan
//

#include <iostream>
#include <string>
#include "Lapin.hpp"
#include "ILib.hpp"

extern "C" arcade::ILib	*create_GFX(void)
{
  return (new arcade::Lapin);
}
