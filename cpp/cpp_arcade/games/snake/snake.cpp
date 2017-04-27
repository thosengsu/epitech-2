#include <chrono>
#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include "arcade_protocoll.hpp"
#include "IGame.hpp"
#include "snake.hpp"
#include "IDlGfxLoader.hpp"

///////////////////////
// Var for game Loop //
///////////////////////
static int	turnTime = 200;

//////////////////////////////////
//	Run For Gfx             //
//////////////////////////////////

extern "C" arcade::GameExitState	launchGame(arcade::IDlGfxLoader *loader,
						   const std::string& playerName)
{
  std::chrono::high_resolution_clock::time_point	ref;
  std::chrono::milliseconds		turn = std::chrono::milliseconds(turnTime);
  arcade::GameExitState			gameState;
  arcade::snake				snake(loader);

  ref = std::chrono::high_resolution_clock::now();
  snake.LoadMapGraph();
  while (1)
    {
      snake.CheckEvent();
      if (snake.checkQuit() == true)
	{
	  snake.WriteScores(playerName);
	  return (arcade::GameExitState::EXIT);
	}
      else if ((gameState = snake.checkNextGame()) != arcade::GameExitState::NOTHING)
	{
	  snake.WriteScores(playerName);
	  return (gameState);
	}
      if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - ref)) >= turn)
	{
	  if (snake.goForward() == false)
	    {
	      snake.LoadMapGraph();
	      usleep(5000);
	      if ((gameState = snake.gameOver(playerName)) != arcade::GameExitState::NOTHING)
		return (gameState);
	      snake.restartGame(NULL);
	    }
	  snake.LoadMapGraph();
	  ref = std::chrono::high_resolution_clock::now();
	}
    }
  snake.WriteScores(playerName);
  return (arcade::GameExitState::EXIT);
}

//////////////////////////////////
//	Run For Koalinette      //
//////////////////////////////////
extern "C" void		Play(void)
{
  uint16_t		cmd;
  arcade::snake		snake;

  cmd = 0;
  while (read(0, &cmd, sizeof(uint16_t)))
    {
      switch (cmd)
	{
	case (static_cast<uint16_t>(arcade::CommandType::GET_MAP)):
	  snake.getMap();
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::WHERE_AM_I)):
	  snake.getWhereAmI();
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_UP)):
	  snake.PMoveUp(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_DOWN)):
	  snake.PMoveDown(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_LEFT)):
	  snake.PMoveLeft(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_RIGHT)):
	  snake.PMoveRight(NULL);
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::GO_FORWARD)):
	  if (snake.checkMove(snake.getDirection()) == true)
	    {
	      if (snake.goForward() == false)
		return ;
	    }
	  break;
	case (static_cast<uint16_t>(arcade::CommandType::PLAY)):
	  if (snake.checkMove(snake.getDirection()) == true)
	    {
	      if (snake.goForward() == false)
		return ;
	    }
	  break;
	}
      cmd = 0;
    }
}
