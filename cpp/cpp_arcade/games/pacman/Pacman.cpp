#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include "arcade_protocoll.hpp"
#include "IGame.hpp"
#include "Pacman.hpp"
#include "IDlGfxLoader.hpp"

//////////////////////////////////
//     GFX RUN FOR PITCH        //
//////////////////////////////////
extern "C" arcade::GameExitState	launchGame(arcade::IDlGfxLoader *loader,
						   const std::string& playerName)
{
  arcade::Pacman			pacman(loader);
  std::chrono::high_resolution_clock::time_point	refPac;
  std::chrono::milliseconds		turnPac = std::chrono::milliseconds(25);
  arcade::GameExitState			gameState;

  refPac = std::chrono::high_resolution_clock::now();
  while (1)
    {
      pacman.CheckEvent();
      if (pacman.checkQuit() == true)
	return (arcade::GameExitState::EXIT);
      else if ((gameState = pacman.checkNextGame()) != arcade::GameExitState::NOTHING)
	return (gameState);
      if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - refPac) >= turnPac)
	{
	  pacman.loadMapGraph(playerName);
	  if (pacman.goForwardPx() == false)
	    pacman.gameOver(playerName);
	  pacman.loadMapGraph(playerName);
	  if (pacman.GhostsMovesPx() == false)
	    pacman.gameOver(playerName);
	  pacman.loadMapGraph(playerName);
	  if ((gameState = pacman.checkWin()) != arcade::GameExitState::NOTHING)
	    return (gameState);
	  refPac = std::chrono::high_resolution_clock::now();
	}
    }
}


//////////////////////////////////
//     RUN FOR KOALINETTE       //
//////////////////////////////////
extern "C" void		Play(void)
{
  uint16_t		cmd;
  arcade::Pacman	pacman;

  cmd = 0;
  while (read(0, &cmd, sizeof(uint16_t)))
    {
      switch (cmd)
	{
	case (static_cast<uint16_t>(arcade::CommandType::GET_MAP)):
	  pacman.getMap();
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::WHERE_AM_I)):
	  pacman.getWhereAmI();
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_UP)):
	  pacman.PMoveUp(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_DOWN)):
	  pacman.PMoveDown(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_LEFT)):
	  pacman.PMoveLeft(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_RIGHT)):
	  pacman.PMoveRight(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_FORWARD)):
	  if (pacman.goForward() == false)
	    return ;
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::PLAY)):
	  if (pacman.goForward() == false)
	    return ;
	  break;
	}
      cmd = 0;
    }
}
