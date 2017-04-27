#ifndef Pacman_HPP_
# define Pacman_HPP_

# include <chrono>
# include <random>
# include <functional>
# include <string>
# include <stdint.h>
# include <iostream>
# include <fstream>
# include <sys/types.h>
# include <unistd.h>
# include "arcade_protocoll.hpp"
# include "IGame.hpp"
# include "ILib.hpp"
# include "IDlGfxLoader.hpp"

/*                   */
/* ALIAS FOR SPRITES */
/*                   */						\


static const char		*BACKGROUND	= "ressources/background.png";
static const char		*FONT		= "ressources/calibrib.ttf";

static const char		*PACMAN_LEFT	= "ressources/PacmanLeft.png";
static const char		*PACMAN_RIGHT	= "ressources/Pacman.png";
static const char		*PACMAN_UP	= "ressources/PacmanUp.png";
static const char		*PACMAN_DOWN	= "ressources/PacmanDown.png";
static const char		*PACGUM		= "ressources/LittlePacgum.png";
static const char		*MPACGUM	= "ressources/bigPacgum.png";
static const char		*WALL		= "ressources/SnakeWallSprite.png";
static const char		*EMPTY		= "ressources/SnakeEmptyMap.png";
static const char		*AKABEI		= "ressources/akabei.png";
static const char		*PINKY		= "ressources/Pinky.png";
static const char		*GUZUTA		= "ressources/guzuta.png";
static const char		*AOSUKE		= "ressources/aosuke.png";
static const char		*DEAD		= "ressources/deadGhost.png";
static const char		*DEADSTATE	= "ressources/DeadState.png";
static const char		*WIN		= "ressources/YOUWIN.png";

static const std::string	mapInit =
"111111111111111111111111111111111\
160606061606060606060606160606061\
101111101011111111111110101111101\
161606060606060606060606060606161\
101010101110111111111011101010101\
160616160606060606060606061616061\
111010101111101111101111101010111\
160616060606160606061606060616061\
101010111110101000101011111010101\
161606060616161030161616060606161\
101011111010101333101010111110101\
161606060616161111161616060606161\
101110101010101111101010101011101\
160606161606060606060606161606061\
101111101010111111111010101111101\
160606060616060606060616060606061\
101111111010111111111010111111101\
160616060606060606060606060616061\
111010111010111111111010111010111\
160616060616060606060616060616061\
101111111010111111111010111111101\
160606060616060606060616060606061\
111111111111111111111111111111111";

# include "IGame.hpp"

namespace arcade
{
  class Pacman : public IGame
  {
  public :
    //////////
    // CTOR
    //////////
    Pacman(arcade::IDlGfxLoader *loader)
    {
      _key.push_back(std::bind(&Pacman::prevGfx, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::nextGfx, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::prevGame, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::nextGame, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::restartGame, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::backToMenu, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::quit, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::PMoveLeft, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::PMoveRight, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::PMoveUp, this, std::placeholders::_1));
      _key.push_back(std::bind(&Pacman::PMoveDown, this, std::placeholders::_1));

      this->_rand.seed(time(NULL));
      this->InitGame();
      this->_loader = loader;
      this->_highScore = 0;
      this->getScore();
      this->_gfx = this->_loader->getCurrentGfxLib();
      this->_gfx->loadFont(FONT);
      this->_gfxTmp = NULL;
      this->_quit = false;
      this->_nextGame = arcade::GameExitState::NOTHING;
      this->_direction = arcade::Dir::LEFT;
      this->_nextDir = arcade::Dir::NOTHING;
      this->_score = 0;
      this->InitCmd();
      this->loadSprites();
      this->_pacmanSpeed = 8;
    }

    Pacman(void)
    {
      this->InitGame();
      this->_quit = false;
      this->_nextGame = arcade::GameExitState::NOTHING;
      this->_direction = arcade::Dir::LEFT;
      this->_nextDir = arcade::Dir::NOTHING;
      this->_score = 0;
    }

    //////////
    // ~DTOR
    //////////
    ~Pacman()
    {
      delete[] this->_map;
      delete[] this->_me.me;
    }

    ////////////////////
    //****
    //***
    //**  Members functions
    //***
    //****
    ////////////////////

    //////////
    // init commands for the checks
    //////////
    void			InitCmd(void)
    {

      this->_gfx->defCommand(_key, arcade::CmdMode::GAME);
    }

    /////////////
    //	Self made Event Handler
    /////////////
    void		CheckEvent(void)
    {
      this->_gfx->checkEvent();

      if (this->_gfxTmp != NULL)
	{
	  this->_gfx->close();
	  delete this->_gfx;
	  this->_loader->closeOldGfx();
	  this->_gfx = this->_gfxTmp;
	  this->_gfxTmp = NULL;
	  this->_gfx->init("pacman");
	  this->InitCmd();
	  this->loadSprites();
	  this->_gfx->loadFont(FONT);
	}
    }

    //////////
    // Load the default Map of Pacman in the _map
    //////////
    void			InitGame(void)
    {
      char			*c = new char[sizeof(arcade::GetMap) + (PACWIDTH * PACHEIGHT *
									sizeof(arcade::TileType))];

      this->_map = new(c) arcade::GetMap;
      this->_map->width = static_cast<uint16_t>(PACWIDTH);
      this->_map->height = static_cast<uint16_t>(PACHEIGHT);
      this->_map->type = arcade::CommandType::GET_MAP;
      for (int y = 0; y < PACHEIGHT; y++)
	{
	  for (int x = 0; x < PACWIDTH; x++)
	    {
	      if (mapInit[x + (y * PACWIDTH)] - 48 == 1)
		this->_map->tile[x + (y * PACWIDTH)] = arcade::TileType::BLOCK;
	      else if (mapInit[x + (y * PACWIDTH)] - 48 == 0)
		this->_map->tile[x + (y * PACWIDTH)] = arcade::TileType::EMPTY;
	      else if (mapInit[x + (y * PACWIDTH)] - 48 == 6)
		this->_map->tile[x + (y * PACWIDTH)] = arcade::TileType::POWERUP;
	      else if (mapInit[x + (y * PACWIDTH)] - 48 == 3)
		{
		  this->_map->tile[x + (y * PACWIDTH)] = arcade::TileType::EVIL_DUDE;
		  InitGhost(x, y);
		}
	    }
	}
      this->_pacgums[0].x = 1;
      this->_pacgums[0].y = 1;
      this->_pacgums[0].eaten = false;
      this->_pacgums[1].x = 31;
      this->_pacgums[1].y = 1;
      this->_pacgums[1].eaten = false;
      this->_pacgums[2].x = 1;
      this->_pacgums[2].y = 21;
      this->_pacgums[2].eaten = false;
      this->_pacgums[3].x = 31;
      this->_pacgums[3].y = 21;
      this->_pacgums[3].eaten = false;
      this->InitPacman();
    }

    //////////
    // init a ghost depending of the position
    //////////
    void			InitGhost(int x, int y)
    {
      if (x == 15 && y == 10)
	{
	  this->_aosuke.x = x;
	  this->_aosuke.gfx_x = x * PACTILE_WIDTH;
	  this->_aosuke.y = y;
	  this->_aosuke.gfx_y = y * PACTILE_HEIGHT;
	  this->_aosuke.speed = 8;
	  this->_aosuke.alive = true;
	  this->_aosuke.chased = false;
	  this->_aosuke.waiting = true;
	  this->_aosuke.direction = arcade::Dir::UP;
	  this->_aosuke.timeDead = std::chrono::milliseconds(8000);
	  this->_aosuke.timeChased = std::chrono::milliseconds(10000);
	  this->_aosuke.refWaiting = std::chrono::high_resolution_clock::now();
	}
      else if (y == 9 && x == 16)
	{
	  this->_akabei.gfx_x = x * PACTILE_WIDTH;
	  this->_akabei.x = x;
	  this->_akabei.gfx_y = y * PACTILE_HEIGHT;
	  this->_akabei.y = y;
	  this->_akabei.alive = true;
	  this->_akabei.chased = false;
	  this->_akabei.waiting = true;
	  this->_akabei.speed = 8;
	  this->_akabei.direction = arcade::Dir::UP;
	  this->_akabei.timeDead = std::chrono::milliseconds(8000);
	  this->_akabei.timeChased = std::chrono::milliseconds(10000);
	  this->_akabei.refWaiting = std::chrono::high_resolution_clock::now();
	}
      else if (x == 16 && y == 10)
	{
	  this->_pinky.gfx_x = x * PACTILE_WIDTH;
	  this->_pinky.x = x;
	  this->_pinky.gfx_y = y * PACTILE_HEIGHT;
	  this->_pinky.y = y;
	  this->_pinky.speed = 8;
	  this->_pinky.alive = true;
	  this->_pinky.chased = false;
	  this->_pinky.waiting = true;
	  this->_pinky.direction = arcade::Dir::UP;
	  this->_pinky.timeDead = std::chrono::milliseconds(8000);
	  this->_pinky.timeChased = std::chrono::milliseconds(10000);
	  this->_pinky.refWaiting = std::chrono::high_resolution_clock::now();
	}
      else if (x == 17 && y == 10)
	{
	  this->_guzuta.gfx_x = x * PACTILE_WIDTH;
	  this->_guzuta.x = x;
	  this->_guzuta.gfx_y = y * PACTILE_HEIGHT;
	  this->_guzuta.y = y;
	  this->_guzuta.speed = 8;
	  this->_guzuta.alive = true;
	  this->_guzuta.chased = false;
	  this->_guzuta.waiting = true;
	  this->_guzuta.direction = arcade::Dir::UP;
	  this->_guzuta.timeDead = std::chrono::milliseconds(8000);
	  this->_guzuta.timeChased = std::chrono::milliseconds(10000);
	  this->_guzuta.refWaiting = std::chrono::high_resolution_clock::now();
	}
    }

    //////////
    // Init Pacmam (_me) var
    //////////
    void			InitPacman(void)
    {
      char			*c = new char[sizeof(arcade::WhereAmI) + 1 * sizeof(arcade::Position)];

      this->_me.me = new(c) arcade::WhereAmI;
      this->_me.me->type = arcade::CommandType::WHERE_AM_I;
      this->_me.me->lenght = 1;
      this->_me.me->position[0].x = 16;
      this->_me.me->position[0].y = 13;
      this->_me.gfx_x = 16 * PACTILE_WIDTH;
      this->_me.gfx_y = 13 * PACTILE_HEIGHT;
      this->_direction = arcade::Dir::LEFT;
    }

    //////////
    // load the sprites in the gfx lib
    //////////
    void			loadSprites(void)
    {
      this->_gfx->loadSprite("PacmanLeft", PACMAN_LEFT);
      this->_gfx->loadSprite("PacmanRight", PACMAN_RIGHT);
      this->_gfx->loadSprite("PacmanUp", PACMAN_UP);
      this->_gfx->loadSprite("PacmanDown", PACMAN_DOWN);
      this->_gfx->loadSprite("Wall", WALL);
      this->_gfx->loadSprite("Empty", EMPTY);
      this->_gfx->loadSprite("PowerUp", MPACGUM);
      this->_gfx->loadSprite("Pacgum", PACGUM);
      this->_gfx->loadSprite("pinky", PINKY);
      this->_gfx->loadSprite("akabei", AKABEI);
      this->_gfx->loadSprite("aosuke", AOSUKE);
      this->_gfx->loadSprite("guzuta", GUZUTA);
      this->_gfx->loadSprite("affraid", DEAD);
      this->_gfx->loadSprite("background", BACKGROUND);
      this->_gfx->loadSprite("DeadState", DEADSTATE);
      this->_gfx->loadSprite("Win", WIN);
    }

    //////////
    // Load map in Graphic mode
    //////////
    void			loadMapGraph(const std::string& playerName)
    {
      bool			ishere = false;
      int			gfx_x;
      int			gfx_y = 0;

      for (int y = 0; y < PACHEIGHT; y++)
	{
	  gfx_x = 0;
	  for (int x = 0; x < PACWIDTH; x++)
	    {
	      if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::EMPTY)
		_gfx->blitSprite(gfx_x, gfx_y, "Empty", PACTILE_WIDTH, PACTILE_HEIGHT);
	      else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
		_gfx->blitSprite(gfx_x, gfx_y, "Wall", PACTILE_WIDTH, PACTILE_HEIGHT);
	      else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
		{
		  ishere = false;
		  for (int idx = 0; idx < 4; idx++)
		    {
		      if (this->_pacgums[idx].x == x && this->_pacgums[idx].y == y)
			{
			  ishere = true;
			  _gfx->blitSprite(gfx_x, gfx_y, "PowerUp", PACTILE_WIDTH, PACTILE_HEIGHT);
			}
		    }
		  if (ishere == false)
		    _gfx->blitSprite(gfx_x, gfx_y, "Pacgum", PACTILE_WIDTH, PACTILE_HEIGHT);
		}
	      else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::EVIL_DUDE)
		_gfx->blitSprite(gfx_x, gfx_y, "Empty", PACTILE_WIDTH, PACTILE_HEIGHT);
	      gfx_x += PACTILE_WIDTH;
	    }
	  gfx_y += PACTILE_HEIGHT;
	}
      this->printEvil();
      this->printStat(playerName);
      this->printPacman();
      this->_gfx->refresh();
    }

    //////////
    // PRINT STAT
    //////////
    void			printStat(const std::string& playerName)
    {
      std::string		score = std::to_string(this->_score);
      std::string		highScore = std::to_string(this->_highScore);

      this->_gfx->blitText(playerName, (PACTILE_WIDTH * PACWIDTH) + 10, 0, 35);
      this->_gfx->blitText("score = ", (PACTILE_WIDTH * PACWIDTH) + 10, PACTILE_HEIGHT * (PACHEIGHT / 2), 35);
      this->_gfx->blitText(score, (PACTILE_WIDTH * PACWIDTH) + (PACTILE_WIDTH * 8) + 10, PACTILE_HEIGHT * (PACHEIGHT / 2), 35);
      this->_gfx->blitText("highscore = ", 0, 0, 35);
      this->_gfx->blitText(highScore, 13 * PACTILE_WIDTH, 0, 35);
    }

    //////////
    // PRINT PACMAN
    //////////
    void			printPacman(void)
    {
      if (this->_direction == arcade::Dir::LEFT)
	_gfx->blitSprite(_me.gfx_x, _me.gfx_y, "PacmanLeft", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_direction == arcade::Dir::RIGHT)
	_gfx->blitSprite(_me.gfx_x, _me.gfx_y, "PacmanRight", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_direction == arcade::Dir::UP)
	_gfx->blitSprite(_me.gfx_x, _me.gfx_y, "PacmanUp", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_direction == arcade::Dir::DOWN)
	_gfx->blitSprite(_me.gfx_x, _me.gfx_y, "PacmanDown", PACTILE_WIDTH, PACTILE_HEIGHT);
    }

    //////////
    // print a ghost
    //////////
    void			printEvil(void)
    {
      if (this->_pinky.chased == true)
	_gfx->blitSprite(_pinky.gfx_x,_pinky.gfx_y, "affraid", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_pinky.alive == false)
	_gfx->blitSprite(_pinky.gfx_x,_pinky.gfx_y, "DeadState", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_pinky.alive == true)
	_gfx->blitSprite(_pinky.gfx_x,_pinky.gfx_y, "pinky", PACTILE_WIDTH, PACTILE_HEIGHT);

      if (this->_aosuke.chased == true)
	_gfx->blitSprite(_aosuke.gfx_x,_aosuke.gfx_y, "affraid", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_aosuke.alive == false)
	_gfx->blitSprite(_aosuke.gfx_x,_aosuke.gfx_y, "DeadState", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_aosuke.alive == true)
	_gfx->blitSprite(_aosuke.gfx_x,_aosuke.gfx_y, "aosuke", PACTILE_WIDTH, PACTILE_HEIGHT);

      if (this->_guzuta.chased == true)
	_gfx->blitSprite(_guzuta.gfx_x,_guzuta.gfx_y, "affraid", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_guzuta.alive == false)
	_gfx->blitSprite(_guzuta.gfx_x,_guzuta.gfx_y, "DeadState", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_guzuta.alive == true)
	_gfx->blitSprite(_guzuta.gfx_x,_guzuta.gfx_y, "guzuta", PACTILE_WIDTH, PACTILE_HEIGHT);

      if (this->_akabei.chased == true)
	_gfx->blitSprite(_akabei.gfx_x,_akabei.gfx_y, "affraid", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_akabei.alive == false)
	_gfx->blitSprite(_akabei.gfx_x,_akabei.gfx_y, "DeadState", PACTILE_WIDTH, PACTILE_HEIGHT);
      else if (this->_akabei.alive == true)
	_gfx->blitSprite(_akabei.gfx_x,_akabei.gfx_y, "akabei", PACTILE_WIDTH, PACTILE_HEIGHT);
    }

    //////////
    // change Direction of next dir
    //////////
    void			PMoveLeft(void *)
    {
      this->_nextDir = arcade::Dir::LEFT;
    }

    //////////
    // Move to the left
    //////////
    bool			MoveLeftPx(void)
    {
      uint16_t			y = _me.gfx_y / PACTILE_HEIGHT;
      uint16_t			x = (_me.gfx_x - this->_pacmanSpeed) / PACTILE_WIDTH;

      if (this->_map->tile[x + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  if (checkIfGhost(x, y) == false)
	    return (false);
	  this->_me.gfx_x -= this->_pacmanSpeed;
	  this->_me.me->position[0].x = x;
	  if (this->_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y);
	}
      else
	this->_me.gfx_x = (x + 1) * PACTILE_WIDTH;
      return (true);
    }

    //////////
    // change Direction of next dir
    //////////
    void			PMoveRight(void *)
    {
      this->_nextDir = arcade::Dir::RIGHT;
    }

    //////////
    // Move to the Right
    //////////
    bool			MoveRightPx(void)
    {
      uint16_t			y = ((_me.gfx_y) / PACTILE_HEIGHT);
      uint16_t			x = ((_me.gfx_x + this->_pacmanSpeed) / PACTILE_WIDTH);
      x += 1;

      if (this->_map->tile[x + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  if (checkIfGhost(x, y) == false)
	    return (false);
	  this->_me.gfx_x += this->_pacmanSpeed;
	  this->_me.me->position[0].x = x;
	  if (this->_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y);
	}
      else
	this->_me.gfx_x = (x - 1) * PACTILE_WIDTH;
      return (true);
    }

    //////////
    // change Direction of next dir (moul v)
    //////////
    void			PMoveUp(void *)
    {
      this->_nextDir = arcade::Dir::UP;
    }

    //////////
    // Move UP
    //////////
    bool			MoveUpPx(void)
    {
      uint16_t			y = ((_me.gfx_y - this->_pacmanSpeed) / PACTILE_HEIGHT);
      uint16_t			x = ((_me.gfx_x) / PACTILE_WIDTH);

      if (this->_map->tile[x + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  if (checkIfGhost(x, y) == false)
	    return (false);
	  this->_me.gfx_y -= this->_pacmanSpeed;
	  this->_me.me->position[0].y = y;
	  if (this->_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y);
	}
      else
	this->_me.gfx_y = (y + 1) * PACTILE_HEIGHT;
      return (true);
    }

    //////////
    // change Direction of next dir
    //////////
    void			PMoveDown(void *)
    {
      this->_nextDir = arcade::Dir::DOWN;
    }

    bool			MoveDownPx(void)
    {
      uint16_t			y = ((_me.gfx_y + this->_pacmanSpeed) / PACTILE_HEIGHT);
      y += 1;
      uint16_t			x = ((_me.gfx_x) / PACTILE_WIDTH);

      if (this->_map->tile[x + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  if (checkIfGhost(x, y) == false)
	    return (false);
	  this->_me.gfx_y += this->_pacmanSpeed;
	  this->_me.me->position[0].y = y;
	  if (this->_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y);
	}
      else
	this->_me.gfx_y = (y - 1) * PACTILE_HEIGHT;
      return (true);
    }

    //////////
    // check if have eaten all the pacgums
    //////////
    arcade::GameExitState	checkWin(void)
    {
      bool			gotPac = false;

      for (uint16_t y = 0; y < PACHEIGHT; y++)
	{
	  for (uint16_t x = 0; x < PACWIDTH; x++)
	    {
	      if (this->_map->tile[x + (y * PACWIDTH)] == arcade::TileType::POWERUP)
		gotPac = true;
	    }
	}
      if (gotPac == false)
	return (this->win());
      return (arcade::GameExitState::NOTHING);
    }

    //////////
    // Check if must end and restart the game
    //////////
    arcade::GameExitState	win(void)
    {
      std::chrono::high_resolution_clock::time_point	ref;
      std::chrono::milliseconds		turn = std::chrono::milliseconds(5000);
      arcade::GameExitState		state;

      ref = std::chrono::high_resolution_clock::now();
      this->_gfx->blitSprite(0, 0, "Win", SC_WIDTH,SC_HEIGHT - 100);
      this->_gfx->refresh();
      while ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - ref)) < turn)
	{
	  this->CheckEvent();
	  if (this->checkQuit() == true)
	    return (arcade::GameExitState::EXIT);
	  else if ((state = this->checkNextGame()) != arcade::GameExitState::NOTHING)
	    return (state);
	}
      this->restart();
      return (arcade::GameExitState::NOTHING);
    }

    //////////
    // go forward gfx version
    //////////
    bool			goForwardPx(void)
    {
      if (this->_nextDir == arcade::Dir::UP)
	{
	  if (this->canMove() == true)
	    {
	      this->_direction = arcade::Dir::UP;
	      return (this->MoveUpPx());
	    }
	  else
	    return (moveForwardDir());
	}
      else if (this->_nextDir == arcade::Dir::DOWN)
	{
	  if (this->canMove() == true)
	    {
	      this->_direction = arcade::Dir::DOWN;
	      return (this->MoveDownPx());
	    }
	  else
	    return (moveForwardDir());
	}
      else if (this->_nextDir == arcade::Dir::LEFT)
	{
	  if (this->canMove() == true)
	    {
	      this->_direction = arcade::Dir::LEFT;
	      return (this->MoveLeftPx());
	    }
	  else
	    return (moveForwardDir());
	}
      else if (this->_nextDir == arcade::Dir::RIGHT)
	{
	  if (this->canMove() == true)
	    {
	      this->_direction = arcade::Dir::RIGHT;
	      return (this->MoveRightPx());
	    }
	  else
	    return (moveForwardDir());
	}
      return (true);
    }

    //////////
    // check if pacman can move
    /////////
    bool			canMove(void)
    {
      if (this->_nextDir == arcade::Dir::UP)
	{
	  if (this->_map->tile[this->_me.me->position[0].x +
			       ((this->_me.me->position[0].y - 1) * PACWIDTH)] != arcade::TileType::BLOCK)
	    {
	      if (this->_me.gfx_x >= (PACTILE_WIDTH * this->_me.me->position[0].x) - 10 &&
		  this->_me.gfx_x <= (PACTILE_WIDTH * this->_me.me->position[0].x) + 10)
		{
		  this->_me.gfx_x = PACTILE_WIDTH * this->_me.me->position[0].x;
		  return (true);
		}
	    }
	  else
	    return (false);
	}
      else if (this->_nextDir == arcade::Dir::DOWN)
	{
	  if (this->_map->tile[this->_me.me->position[0].x +
			       ((this->_me.me->position[0].y + 1) * PACWIDTH)] != arcade::TileType::BLOCK)
	    {
	      if (this->_me.gfx_x >= (PACTILE_WIDTH * this->_me.me->position[0].x) - 10 &&
		  this->_me.gfx_x <= (PACTILE_WIDTH * this->_me.me->position[0].x) + 10)
		{
		  this->_me.gfx_x = PACTILE_WIDTH * this->_me.me->position[0].x;
		  return (true);
		}
	    }
	  else
	    return (false);
	}
      else if (this->_nextDir == arcade::Dir::LEFT)
	{
	  if (this->_map->tile[(this->_me.me->position[0].x - 1)
			       + (_me.me->position[0].y * PACWIDTH)] != arcade::TileType::BLOCK)
	    {
	      if (this->_me.gfx_y >= (PACTILE_HEIGHT * this->_me.me->position[0].y) - 10 &&
		  this->_me.gfx_y <= (PACTILE_HEIGHT * this->_me.me->position[0].y) + 10)
		{
		  this->_me.gfx_y = PACTILE_HEIGHT * this->_me.me->position[0].y;
		  return (true);
		}
	    }
	  else
	    return (false);
	}
      else if (this->_nextDir == arcade::Dir::RIGHT)
	{

	  if (this->_map->tile[(this->_me.me->position[0].x + 1) + (_me.me->position[0].y * PACWIDTH)] != arcade::TileType::BLOCK)
	    {
	      if (this->_me.gfx_y >= (PACTILE_HEIGHT * this->_me.me->position[0].y) - 10 &&
		  this->_me.gfx_y <= (PACTILE_HEIGHT * this->_me.me->position[0].y) + 10)
		{
		  this->_me.gfx_y = PACTILE_HEIGHT * this->_me.me->position[0].y;
		  return (true);
		}
	    }
	  else
	    return (false);
	}
      return (false);
    }

    //////////
    // move forward gfx
    //////////
    bool			moveForwardDir(void)
    {
      if (this->_direction == arcade::Dir::UP)
	return (this->MoveUpPx());
      else if (this->_direction == arcade::Dir::DOWN)
	return (this->MoveDownPx());
      else if (this->_direction == arcade::Dir::LEFT)
	return (this->MoveLeftPx());
      else if (this->_direction == arcade::Dir::RIGHT)
	return (this->MoveRightPx());
      return (true);
    }

    //////////
    // MOVE FOR EACH GHOST INDEPANDENTLY
    //////////
    bool			GhostsMovesPx(void)
    {
      if (this->_pinky.alive == false && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_pinky.refDead))
	  >= this->_pinky.timeDead)
	{
	  this->_pinky.speed = 8;
	  this->_pinky.alive = true;
	  this->_pinky.chased = false;
	  this->_pinky.refDead = std::chrono::high_resolution_clock::now();
	}
      else
	{
	  if (this->_pinky.chased == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_pinky.refChase))
	      >= this->_pinky.timeChased)
	    {
	      this->_pinky.speed = 8;
	      this->_pinky.chased = false;
	      this->_pinky.refChase = std::chrono::high_resolution_clock::now();
	    }
	  else if (this->_pinky.waiting == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_pinky.refWaiting))
		   >= this->_pinky.timeChased)
	    {
	      this->_pinky.speed = 8;
	      this->_pinky.waiting = false;
	      this->_pinky.refWaiting = std::chrono::high_resolution_clock::now();
	    }
	  if ((this->_pinky.chased == true || this->_pinky.alive == true)
	      && this->_pinky.waiting != true)
	    {
	      if (this->pinkyMove() == false)
		return (false);
	    }
	}
      if (this->_akabei.alive == false && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_akabei.refDead))
	      >= _akabei.timeDead)
	{
	  this->_akabei.alive = true;
	  this->_akabei.chased = false;
	  this->_akabei.refDead = std::chrono::high_resolution_clock::now();
	  this->_akabei.speed = 8;
	}
      else
	{
	  if (this->_akabei.chased == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_akabei.refChase))
	      >= _akabei.timeChased)
	    {
	      this->_akabei.speed = 8;
	      this->_akabei.chased = false;
	      this->_akabei.refChase = std::chrono::high_resolution_clock::now();
	      return (true);
	    }
	  else if (this->_akabei.waiting == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_akabei.refWaiting))
		   >= _akabei.timeChased)
	    {
	      this->_akabei.speed = 8;
	      this->_akabei.waiting = false;
	      this->_akabei.refWaiting = std::chrono::high_resolution_clock::now();
	      return (true);
	    }
	  if ((this->_akabei.chased == true || this->_akabei.alive == true)
	      && this->_akabei.waiting != true)
	    {
	      if (this->akabeiMove() == false)
		return (false);
	    }
	}
      if (this->_aosuke.alive == false && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_aosuke.refDead))
	  >= this->_aosuke.timeDead)
	{
	  this->_aosuke.speed = 8;
	  this->_aosuke.alive = true;
	  this->_aosuke.chased = false;
	  this->_aosuke.refDead = std::chrono::high_resolution_clock::now();
	}
      else
	{
	  if (this->_aosuke.chased == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_aosuke.refChase))
	      >= this->_aosuke.timeChased)
	      {
		this->_aosuke.speed = 8;
		this->_aosuke.chased = false;
		this->_aosuke.refChase = std::chrono::high_resolution_clock::now();
		return (true);
	      }
	  else if (this->_aosuke.waiting == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_aosuke.refWaiting))
	      >= this->_aosuke.timeChased)
	    {
	      this->_aosuke.speed = 8;
	      this->_aosuke.waiting = false;
	      this->_aosuke.refWaiting = std::chrono::high_resolution_clock::now();
	      return (true);
	    }
	  if ((this->_aosuke.chased == true || this->_aosuke.alive == true)
	      && this->_aosuke.waiting != true)
	    {
	      if (this->aosukeMove() == false)
		return (false);
	    }
	}
      if (this->_guzuta.alive == false && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_guzuta.refDead))
	  >= this->_guzuta.timeDead)
	  {
	    this->_guzuta.speed = 8;
	    this->_guzuta.alive = true;
	    this->_guzuta.chased = false;
	    this->_guzuta.refDead = std::chrono::high_resolution_clock::now();
	  }
      else
	{
	  if (this->_guzuta.chased == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_guzuta.refChase))
	      >= this->_guzuta.timeChased)
	    {
	      this->_guzuta.speed = 8;
	      this->_guzuta.chased = false;
	      this->_guzuta.refChase = std::chrono::high_resolution_clock::now();
	      return (true);
	    }
	  else if (this->_guzuta.waiting == true && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_guzuta.refWaiting))
		   >= this->_guzuta.timeChased)
	    {
	      this->_guzuta.speed = 8;
	      this->_guzuta.waiting = false;
	      this->_guzuta.refWaiting = std::chrono::high_resolution_clock::now();
	      return (true);
	    }
	  if ((this->_guzuta.alive == true || this->_guzuta.chased == true)
	      && this->_guzuta.waiting != true)
	    {
	      if (this->guzutaMove() == false)
		return (false);
	    }
	}
    return (true);
  }

    //////////
    // pinkyDeath
    //////////
    void			pinkyDeath(void)
    {
      this->_pinky.alive = false;
      this->_pinky.chased = false;
      this->_pinky.x = 16;
      this->_pinky.y = 10;
      this->_pinky.gfx_x = this->_pinky.x * PACTILE_WIDTH;
      this->_pinky.gfx_y = this->_pinky.y * PACTILE_HEIGHT;
      this->_pinky.ocur = 0;
      this->_pinky.refDead = std::chrono::high_resolution_clock::now();
    }

    //////////
    // Check if pinky Is surrounded
    //////////
    bool			checkIfPinkySurrounded(void)
    {
      bool			left = false;
      bool			right = false;
      bool			up = false;
      bool			down = false;

      if (this->_map->tile[(_pinky.x - 1) + (_pinky.y * PACWIDTH)] == arcade::TileType::BLOCK)
	left = true;
      if (this->_map->tile[(_pinky.x + 1) + (_pinky.y * PACWIDTH)] == arcade::TileType::BLOCK)
	right = true;
      if (this->_map->tile[_pinky.x + ((_pinky.y - 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	up = true;
      if (this->_map->tile[_pinky.x + ((_pinky.y + 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	down = true;

      if ((this->_pinky.x + 1 == this->_aosuke.x && this->_pinky.y == this->_aosuke.y) ||
	  (this->_pinky.x + 1 == this->_akabei.x && this->_pinky.y == this->_akabei.y) ||
	  (this->_pinky.x + 1 == this->_guzuta.x && this->_pinky.y == this->_guzuta.y))
	right = true;
      if ((this->_pinky.x - 1 == this->_aosuke.x && this->_pinky.y == this->_aosuke.y) ||
	  (this->_pinky.x - 1 == this->_akabei.x && this->_pinky.y == this->_akabei.y) ||
	  (this->_pinky.x - 1 == this->_guzuta.x && this->_pinky.y == this->_guzuta.y))
	left = true;
      if ((this->_pinky.x == this->_aosuke.x && this->_pinky.y + 1 == this->_aosuke.y) ||
	  (this->_pinky.x == this->_akabei.x && this->_pinky.y + 1 == this->_akabei.y) ||
	  (this->_pinky.x == this->_guzuta.x && this->_pinky.y + 1 == this->_guzuta.y))
	down = true;
      if ((this->_pinky.x == this->_aosuke.x && this->_pinky.y - 1 == this->_aosuke.y) ||
	  (this->_pinky.x == this->_akabei.x && this->_pinky.y - 1 == this->_akabei.y) ||
	  (this->_pinky.x == this->_guzuta.x && this->_pinky.y - 1 == this->_guzuta.y))
	up = true;
      if (up == true && down == true && left == true && right == true)
	return (true);
      return (false);
    }

    //////////
    // pinky check move
    //////////
    bool			pinkyCheckMove(void)
    {
      uint16_t			y;
      uint16_t			x;

      if (this->_pinky.direction == arcade::Dir::UP)
	{
	  x = this->_pinky.gfx_x / PACTILE_WIDTH;
	  y = (this->_pinky.gfx_y - this->_pinky.speed) / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_pinky.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_pinky.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_pinky.direction == arcade::Dir::DOWN)
	{
	  x = this->_pinky.gfx_x / PACTILE_WIDTH;
	  y = (this->_pinky.gfx_y + this->_pinky.speed) / PACTILE_HEIGHT;
	  y += 1;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y))
	    {
	      this->_pinky.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_pinky.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_pinky.direction == arcade::Dir::LEFT)
	{
	  x = (this->_pinky.gfx_x - this->_pinky.speed) / PACTILE_WIDTH;
	  y = this->_pinky.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y))
	    {
	      this->_pinky.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_pinky.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      else if (this->_pinky.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_pinky.gfx_x + this->_pinky.speed) / PACTILE_WIDTH;
	  x += 1;
	  y = this->_pinky.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y))
	    {
	      this->_pinky.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_pinky.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      return (true);
    }

    //////////
    // Movement algorithm of pinky ghost
    //////////
    bool			pinkyMove(void)
    {
      bool			isGood = false;
      int			nb = 0;
      uint16_t			x;
      uint16_t			y;

      while (isGood == false)
	{
	  if (this->pinkyCheckMove() == true)
	    isGood = true;
	  else if (checkIfPinkySurrounded() == true)
	    return (true);
	  else
	    {
	      nb += 1;
	      _pinky.direction = static_cast<arcade::Dir>(static_cast<uint16_t>(this->_rand()) % 4);
	      if (nb > 4086)
		return (true);
	    }
	}
      if (this->_pinky.direction == arcade::Dir::UP)
	{
	  x = this->_pinky.gfx_x / PACTILE_WIDTH;
	  y = (this->_pinky.gfx_y - this->_pinky.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_pinky.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_pinky.chased == true)
	    {
	      pinkyDeath();
	      return (true);
	    }
	  _pinky.gfx_y -= _pinky.speed;
	  _pinky.y = y;
	}
      else if (this->_pinky.direction == arcade::Dir::DOWN)
	{
	  x = this->_pinky.gfx_x / PACTILE_WIDTH;
	  y = (this->_pinky.gfx_y + this->_pinky.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_pinky.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_pinky.chased == true)
	    {
	      pinkyDeath();
	      return (true);
	    }
	  _pinky.gfx_y += _pinky.speed;
	  _pinky.y = y;
	}
      else if (this->_pinky.direction == arcade::Dir::LEFT)
	{
	  x = (this->_pinky.gfx_x - this->_pinky.speed) / PACTILE_WIDTH;
	  y = this->_pinky.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_pinky.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_pinky.chased == true)
	    {
	      pinkyDeath();
	      return (true);
	    }
	  _pinky.gfx_x -= _pinky.speed;
	  _pinky.x = x;
	}
      else if (this->_pinky.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_pinky.gfx_x + this->_pinky.speed) / PACTILE_WIDTH;
	  y = this->_pinky.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_pinky.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_pinky.chased == true)
	    {
	      pinkyDeath();
	      return (true);
	    }
	  _pinky.gfx_x += _pinky.speed;
	  _pinky.x = x;
	}
      return (true);
    }

    //////////
    // Akabei Death
    //////////
    void			akabeiDeath(void)
    {
      this->_akabei.alive = false;
      this->_akabei.chased = false;
      this->_akabei.x = 16;
      this->_akabei.y = 9;
      this->_akabei.gfx_x = this->_akabei.x * PACTILE_WIDTH;
      this->_akabei.gfx_y = this->_akabei.y * PACTILE_HEIGHT;
      this->_akabei.ocur = 0;
      this->_akabei.refDead = std::chrono::high_resolution_clock::now();
    }

    //////////
    // Check if akabei Is surrounded
    //////////
    bool			checkIfAkabeiSurrounded(void)
    {
      bool			left = false;
      bool			right = false;
      bool			up = false;
      bool			down = false;

      if (this->_map->tile[(_akabei.x - 1) + (_akabei.y * PACWIDTH)] == arcade::TileType::BLOCK)
	left = true;
      if (this->_map->tile[(_akabei.x + 1) + (_akabei.y * PACWIDTH)] == arcade::TileType::BLOCK)
	right = true;
      if (this->_map->tile[_akabei.x + ((_akabei.y - 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	up = true;
      if (this->_map->tile[_akabei.x + ((_akabei.y + 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	down = true;

      if ((this->_akabei.x + 1 == this->_aosuke.x && this->_akabei.y == this->_aosuke.y) ||
	  (this->_akabei.x + 1 == this->_pinky.x && this->_akabei.y == this->_pinky.y) ||
	  (this->_akabei.x + 1 == this->_guzuta.x && this->_akabei.y == this->_guzuta.y))
	right = true;
      if ((this->_akabei.x - 1 == this->_aosuke.x && this->_akabei.y == this->_aosuke.y) ||
	  (this->_akabei.x - 1 == this->_pinky.x && this->_akabei.y == this->_pinky.y) ||
	  (this->_akabei.x - 1 == this->_guzuta.x && this->_akabei.y == this->_guzuta.y))
	left = true;
      if ((this->_akabei.x == this->_aosuke.x && this->_akabei.y + 1 == this->_aosuke.y) ||
	  (this->_akabei.x == this->_pinky.x && this->_akabei.y + 1 == this->_pinky.y) ||
	  (this->_akabei.x == this->_guzuta.x && this->_akabei.y + 1 == this->_guzuta.y))
	down = true;
      if ((this->_akabei.x == this->_aosuke.x && this->_akabei.y - 1 == this->_aosuke.y) ||
	  (this->_akabei.x == this->_pinky.x && this->_akabei.y - 1 == this->_pinky.y) ||
	  (this->_akabei.x == this->_guzuta.x && this->_akabei.y - 1 == this->_guzuta.y))
	up = true;
      if (up == true && down == true && left == true && right == true)
	return (true);
      return (false);
    }

    //////////
    // akabei check move
    //////////
    bool			akabeiCheckMove(void)
    {
      uint16_t			y;
      uint16_t			x;

      if (this->_akabei.direction == arcade::Dir::UP)
	{
	  x = this->_akabei.gfx_x / PACTILE_WIDTH;
	  y = (this->_akabei.gfx_y - this->_akabei.speed) / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_akabei.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_akabei.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_akabei.direction == arcade::Dir::DOWN)
	{
	  x = this->_akabei.gfx_x / PACTILE_WIDTH;
	  y = (this->_akabei.gfx_y + this->_akabei.speed) / PACTILE_HEIGHT;
	  y += 1;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_akabei.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_akabei.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_akabei.direction == arcade::Dir::LEFT)
	{
	  x = (this->_akabei.gfx_x - this->_akabei.speed) / PACTILE_WIDTH;
	  y = this->_akabei.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_akabei.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_akabei.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      else if (this->_akabei.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_akabei.gfx_x + this->_akabei.speed) / PACTILE_WIDTH;
	  x += 1;
	  y = this->_akabei.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _aosuke.x && y == _aosuke.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_akabei.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_akabei.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      return (true);
    }

    //////////
    // Akabei Move algorithm
    //////////
    bool			akabeiMove(void)
    {
      bool			isGood = false;
      int			nb = 0;
      uint16_t			x;
      uint16_t			y;

      while (isGood == false)
	{
	  if (this->akabeiCheckMove() == true)
	    isGood = true;
	  else if (checkIfAkabeiSurrounded() == true)
	    return (true);
	  else
	    {
	      nb += 1;
	      _akabei.direction = static_cast<arcade::Dir>(static_cast<uint16_t>(this->_rand()) % 4);
	      if (nb > 4086)
		return (true);
	    }
	}
      if (this->_akabei.direction == arcade::Dir::UP)
	{
	  x = this->_akabei.gfx_x / PACTILE_WIDTH;
	  y = (this->_akabei.gfx_y - this->_akabei.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_akabei.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_akabei.chased == true)
	    {
	      akabeiDeath();
	      return (true);
	    }
	  _akabei.gfx_y -= _akabei.speed;
	  _akabei.y = y;
	}
      else if (this->_akabei.direction == arcade::Dir::DOWN)
	{
	  x = this->_akabei.gfx_x / PACTILE_WIDTH;
	  y = (this->_akabei.gfx_y + this->_akabei.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_akabei.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_akabei.chased == true)
	    {
	      akabeiDeath();
	      return (true);
	    }
	  _akabei.gfx_y += _akabei.speed;
	  _akabei.y = y;
	}
      else if (this->_akabei.direction == arcade::Dir::LEFT)
	{
	  x = (this->_akabei.gfx_x - this->_akabei.speed) / PACTILE_WIDTH;
	  y = this->_akabei.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_akabei.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_akabei.chased == true)
	    {
	      akabeiDeath();
	      return (true);
	    }
	  _akabei.gfx_x -= _akabei.speed;
	  _akabei.x = x;
	}
      else if (this->_akabei.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_akabei.gfx_x + this->_akabei.speed) / PACTILE_WIDTH;
	  y = this->_akabei.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_akabei.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_akabei.chased == true)
	    {
	      akabeiDeath();
	      return (true);
	    }
	  _akabei.gfx_x += _akabei.speed;
	  _akabei.x = x;
	}
      return (true);
    }

    //////////
    // Aosuke Death
    //////////
    void			aosukeDeath(void)
    {
      this->_aosuke.alive = false;
      this->_aosuke.chased = false;
      this->_aosuke.x = 15;
      this->_aosuke.y = 10;
      this->_aosuke.gfx_x = this->_aosuke.x * PACTILE_WIDTH;
      this->_aosuke.gfx_y = this->_aosuke.y * PACTILE_HEIGHT;
      this->_aosuke.ocur = 0;
      this->_aosuke.refDead = std::chrono::high_resolution_clock::now();
    }

    //////////
    // Check if aosuke Is surrounded
    //////////
    bool			checkIfAosukeSurrounded(void)
    {
      bool			left = false;
      bool			right = false;
      bool			up = false;
      bool			down = false;

      if (this->_map->tile[(_aosuke.x - 1) + (_aosuke.y * PACWIDTH)] == arcade::TileType::BLOCK)
	left = true;
      if (this->_map->tile[(_aosuke.x + 1) + (_aosuke.y * PACWIDTH)] == arcade::TileType::BLOCK)
	right = true;
      if (this->_map->tile[_aosuke.x + ((_aosuke.y - 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	up = true;
      if (this->_map->tile[_aosuke.x + ((_aosuke.y + 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	down = true;

      if ((this->_aosuke.x + 1 == this->_akabei.x && this->_aosuke.y == this->_akabei.y) ||
	  (this->_aosuke.x + 1 == this->_pinky.x && this->_aosuke.y == this->_pinky.y) ||
	  (this->_aosuke.x + 1 == this->_guzuta.x && this->_aosuke.y == this->_guzuta.y))
	right = true;
      if ((this->_aosuke.x - 1 == this->_akabei.x && this->_aosuke.y == this->_akabei.y) ||
	  (this->_aosuke.x - 1 == this->_pinky.x && this->_aosuke.y == this->_pinky.y) ||
	  (this->_aosuke.x - 1 == this->_guzuta.x && this->_aosuke.y == this->_guzuta.y))
	left = true;
      if ((this->_aosuke.x == this->_akabei.x && this->_aosuke.y + 1 == this->_akabei.y) ||
	  (this->_aosuke.x == this->_pinky.x && this->_aosuke.y + 1 == this->_pinky.y) ||
	  (this->_aosuke.x == this->_guzuta.x && this->_aosuke.y + 1 == this->_guzuta.y))
	down = true;
      if ((this->_aosuke.x == this->_akabei.x && this->_aosuke.y - 1 == this->_akabei.y) ||
	  (this->_aosuke.x == this->_pinky.x && this->_aosuke.y - 1 == this->_pinky.y) ||
	  (this->_aosuke.x == this->_guzuta.x && this->_aosuke.y - 1 == this->_guzuta.y))
	up = true;
      if (up == true && down == true && left == true && right == true)
	return (true);
      return (false);
    }

    //////////
    // Aosuke checkMove
    /////////
    bool			aosukeCheckMove(void)
    {
      uint16_t			y;
      uint16_t			x;

      if (this->_aosuke.direction == arcade::Dir::UP)
	{
	  x = this->_aosuke.gfx_x / PACTILE_WIDTH;
	  y = (this->_aosuke.gfx_y - this->_aosuke.speed) / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_aosuke.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_aosuke.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_aosuke.direction == arcade::Dir::DOWN)
	{
	  x = this->_aosuke.gfx_x / PACTILE_WIDTH;
	  y = (this->_aosuke.gfx_y + this->_aosuke.speed) / PACTILE_HEIGHT;
	  y += 1;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_aosuke.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_aosuke.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_aosuke.direction == arcade::Dir::LEFT)
	{
	  x = (this->_aosuke.gfx_x - this->_aosuke.speed) / PACTILE_WIDTH;
	  y = this->_aosuke.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_aosuke.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_aosuke.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      else if (this->_aosuke.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_aosuke.gfx_x + this->_aosuke.speed) / PACTILE_WIDTH;
	  x += 1;
	  y = this->_aosuke.gfx_y / PACTILE_HEIGHT;
	  if ((x == _guzuta.x && y == _guzuta.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_aosuke.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_aosuke.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      return (true);
    }

    //////////
    // Aosuke Move algorithm
    //////////
    bool			aosukeMove(void)
    {
      bool			isGood = false;
      int			nb = 0;
      uint16_t			x;
      uint16_t			y;

      while (isGood == false)
	{
	  if (this->aosukeCheckMove() == true)
	    isGood = true;
	  else if (checkIfAosukeSurrounded() == true)
	    return (true);
	  else
	    {
	      if (nb > 4086)
		return (true);
	      _aosuke.direction = static_cast<arcade::Dir>(static_cast<uint16_t>(this->_rand()) % 4);
	      nb += 1;
	    }
	}
      if (this->_aosuke.direction == arcade::Dir::UP)
	{
	  x = this->_aosuke.gfx_x / PACTILE_WIDTH;
	  y = (this->_aosuke.gfx_y - this->_aosuke.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_aosuke.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_aosuke.chased == true)
	    {
	      aosukeDeath();
	      return (true);
	    }
	  _aosuke.gfx_y -= _aosuke.speed;
	  _aosuke.y = y;
	}
      else if (this->_aosuke.direction == arcade::Dir::DOWN)
	{
	  x = this->_aosuke.gfx_x / PACTILE_WIDTH;
	  y = (this->_aosuke.gfx_y + this->_aosuke.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_aosuke.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_aosuke.chased == true)
	    {
	      aosukeDeath();
	      return (true);
	    }
	  _aosuke.gfx_y += _aosuke.speed;
	  _aosuke.y = y;
	}
      else if (this->_aosuke.direction == arcade::Dir::LEFT)
	{
	  x = (this->_aosuke.gfx_x - this->_aosuke.speed) / PACTILE_WIDTH;
	  y = this->_aosuke.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_aosuke.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_aosuke.chased == true)
	    {
	      aosukeDeath();
	      return (true);
	    }
	  _aosuke.gfx_x -= _aosuke.speed;
	  _aosuke.x = x;
	}
      else if (this->_aosuke.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_aosuke.gfx_x + this->_aosuke.speed) / PACTILE_WIDTH;
	  y = this->_aosuke.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_aosuke.chased == false)
	    return (false);
	  _aosuke.gfx_x += _aosuke.speed;
	  _aosuke.x = x;
	}
      return (true);
    }

    //////////
    // Guzuta Death
    //////////
    void			guzutaDeath(void)
    {
      this->_guzuta.alive = false;
      this->_guzuta.chased = false;
      this->_guzuta.x = 17;
      this->_guzuta.y = 10;
      this->_guzuta.gfx_x = this->_guzuta.x * PACTILE_WIDTH;
      this->_guzuta.gfx_y = this->_guzuta.y * PACTILE_HEIGHT;
      this->_guzuta.ocur = 0;
      this->_guzuta.refDead = std::chrono::high_resolution_clock::now();
    }

    //////////
    // Check if guzuta Is surrounded
    //////////
    bool			checkIfGuzutaSurrounded(void)
    {
      bool			left = false;
      bool			right = false;
      bool			up = false;
      bool			down = false;

      if (this->_map->tile[(_guzuta.x - 1) + (_guzuta.y * PACWIDTH)] == arcade::TileType::BLOCK)
	left = true;
      if (this->_map->tile[(_guzuta.x + 1) + (_guzuta.y * PACWIDTH)] == arcade::TileType::BLOCK)
	right = true;
      if (this->_map->tile[_guzuta.x + ((_guzuta.y - 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	up = true;
      if (this->_map->tile[_guzuta.x + ((_guzuta.y + 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	down = true;

      if ((this->_guzuta.x + 1 == this->_akabei.x && this->_guzuta.y == this->_akabei.y) ||
	  (this->_guzuta.x + 1 == this->_pinky.x && this->_guzuta.y == this->_pinky.y) ||
	  (this->_guzuta.x + 1 == this->_aosuke.x && this->_guzuta.y == this->_aosuke.y))
	right = true;
      if ((this->_guzuta.x - 1 == this->_akabei.x && this->_guzuta.y == this->_akabei.y) ||
	  (this->_guzuta.x - 1 == this->_pinky.x && this->_guzuta.y == this->_pinky.y) ||
	  (this->_guzuta.x - 1 == this->_aosuke.x && this->_guzuta.y == this->_aosuke.y))
	left = true;
      if ((this->_guzuta.x == this->_akabei.x && this->_guzuta.y + 1 == this->_akabei.y) ||
	  (this->_guzuta.x == this->_pinky.x && this->_guzuta.y + 1 == this->_pinky.y) ||
	  (this->_guzuta.x == this->_aosuke.x && this->_guzuta.y + 1 == this->_aosuke.y))
	down = true;
      if ((this->_guzuta.x == this->_akabei.x && this->_guzuta.y - 1 == this->_akabei.y) ||
	  (this->_guzuta.x == this->_pinky.x && this->_guzuta.y - 1 == this->_pinky.y) ||
	  (this->_guzuta.x == this->_aosuke.x && this->_guzuta.y - 1 == this->_aosuke.y))
	up = true;
      if (up == true && down == true && left == true && right == true)
	return (true);
      return (false);
    }

    //////////
    // guzutaCheckMove
    //////////
    bool			guzutaCheckMove(void)
    {
      uint16_t			y;
      uint16_t			x;

      if (this->_guzuta.direction == arcade::Dir::UP)
	{
	  x = this->_guzuta.gfx_x / PACTILE_WIDTH;
	  y = (this->_guzuta.gfx_y - this->_guzuta.speed) / PACTILE_HEIGHT;
	  if ((x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_guzuta.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_guzuta.gfx_y = (y + 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_guzuta.direction == arcade::Dir::DOWN)
	{
	  x = this->_guzuta.gfx_x / PACTILE_WIDTH;
	  y = (this->_guzuta.gfx_y + this->_guzuta.speed) / PACTILE_HEIGHT;
	  y += 1;
	  if ((x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_guzuta.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_guzuta.gfx_y = (y - 1) * PACTILE_HEIGHT;
	      return (false);
	    }
	}
      else if (this->_guzuta.direction == arcade::Dir::LEFT)
	{
	  x = (this->_guzuta.gfx_x - this->_guzuta.speed) / PACTILE_WIDTH;
	  y = this->_guzuta.gfx_y / PACTILE_HEIGHT;
	  if ((x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_guzuta.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_guzuta.gfx_x = (x + 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      else if (this->_guzuta.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_guzuta.gfx_x + this->_guzuta.speed) / PACTILE_WIDTH;
	  x += 1;
	  y = this->_guzuta.gfx_y / PACTILE_HEIGHT;
	  if ((x == _aosuke.x && y == _aosuke.y) || (x == _akabei.x && y == _akabei.y) || (x == _pinky.x && y == _pinky.y))
	    {
	      this->_guzuta.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	  else if (_map->tile[x + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      this->_guzuta.gfx_x = (x - 1) * PACTILE_WIDTH;
	      return (false);
	    }
	}
      return (true);
    }

    //////////
    // Guzuta Move algorithm
    //////////
    bool			guzutaMove(void)
    {
      bool			isGood = false;
      int			nb = 0;
      uint16_t			x;
      uint16_t			y;

      while (isGood == false)
	{
	  if (this->guzutaCheckMove() == true)
	    isGood = true;
	  else if (checkIfGuzutaSurrounded() == true)
	    return (true);
	  else
	    {
	      nb += 1;
	      _guzuta.direction = static_cast<arcade::Dir>(static_cast<uint16_t>(this->_rand()) % 4);
	      if (nb > 5086)
		return (true);
	    }
	}
      if (this->_guzuta.direction == arcade::Dir::UP)
	{
	  x = this->_guzuta.gfx_x / PACTILE_WIDTH;
	  y = (this->_guzuta.gfx_y - this->_guzuta.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_guzuta.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_guzuta.chased == true)
	    {
	      guzutaDeath();
	      return (true);
	    }
	  _guzuta.gfx_y -= _guzuta.speed;
	  _guzuta.y = y;
	}
      else if (this->_guzuta.direction == arcade::Dir::DOWN)
	{
	  x = this->_guzuta.gfx_x / PACTILE_WIDTH;
	  y = (this->_guzuta.gfx_y + this->_guzuta.speed) / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_guzuta.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_guzuta.chased == true)
	    {
	      guzutaDeath();
	      return (true);
	    }
	  _guzuta.gfx_y += _guzuta.speed;
	  _guzuta.y = y;
	}
      else if (this->_guzuta.direction == arcade::Dir::LEFT)
	{
	  x = (this->_guzuta.gfx_x - this->_guzuta.speed) / PACTILE_WIDTH;
	  y = this->_guzuta.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_guzuta.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_guzuta.chased == true)
	    {
	      guzutaDeath();
	      return (true);
	    }
	  _guzuta.gfx_x -= _guzuta.speed;
	  _guzuta.x = x;
	}
      else if (this->_guzuta.direction == arcade::Dir::RIGHT)
	{
	  x = (this->_guzuta.gfx_x + this->_guzuta.speed) / PACTILE_WIDTH;
	  y = this->_guzuta.gfx_y / PACTILE_HEIGHT;
	  if (x == _me.me->position[0].x && y == _me.me->position[0].y
	      && this->_guzuta.chased == false)
	    return (false);
	  else if (x == _me.me->position[0].x && y == _me.me->position[0].y
		   && this->_guzuta.chased == true)
	    {
	      guzutaDeath();
	      return (true);
	    }
	  _guzuta.gfx_x += _guzuta.speed;
	  _guzuta.x = x;
	}
      return (true);
    }


    //////////
    // GAMEOVER
    //////////
    arcade::GameExitState		gameOver(const std::string& playerName)
    {
      std::chrono::high_resolution_clock::time_point	ref;
      std::chrono::milliseconds		turn = std::chrono::milliseconds(5000);
      std::string			nb = std::to_string(this->_score);
      std::string			highscore = std::to_string(this->_highScore);
      arcade::GameExitState		state;

      ref = std::chrono::high_resolution_clock::now();
      this->_gfx->loadSprite("Background", BACKGROUND);
      this->_gfx->blitSprite(0, 0, "Background", SC_WIDTH, SC_HEIGHT - 100);
      this->_gfx->blitText("GAMEOVER", static_cast<int>(SC_WIDTH / 2) - (4 * TILE_SIZE_WIDTH), static_cast<int>(SC_HEIGHT / 2), 50);
      this->WriteScores(playerName);
      this->_gfx->blitText("score = ", static_cast<int>((SC_WIDTH / 2) - ((4 + nb.size()) * TILE_SIZE_WIDTH)), static_cast<int>(SC_HEIGHT / 2) + TILE_SIZE_HEIGHT, 40);
      this->_gfx->blitText(nb, static_cast<int>((SC_WIDTH / 2) - (nb.size() * TILE_SIZE_WIDTH) + (8 * TILE_SIZE_WIDTH)), static_cast<int>(SC_HEIGHT / 2) + TILE_SIZE_HEIGHT, 40);
      this->_gfx->blitText("highscore = ", 0, 0, 35);
      this->_gfx->blitText(highscore, 13 * PACTILE_WIDTH, 0, 32);
      this->_gfx->refresh();
      while ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - ref)) < turn)
	{
	  this->CheckEvent();
	  if (this->checkQuit() == true)
	    return (arcade::GameExitState::EXIT);
	  else if ((state = this->checkNextGame()) != arcade::GameExitState::NOTHING)
	    return (state);
	}
      this->restart();
      return (arcade::GameExitState::NOTHING);
    }

    /////////
    // write stats
    /////////
    void			WriteScores(const std::string& playerName)
    {
      std::string		nb = std::to_string(this->_score);
      std::string		line;
      std::string		scores;
      std::size_t		pos;
      std::size_t		save;
      int			scorePlayer = -1;
      bool			correct = true;
      std::fstream		file;

      file.open(".pacman.highscore", std::ios::in);
      if (file.is_open() == true)
	{
	  std::getline(file, line);
	  if (line.size() >= 3)
	    {
	      if ((pos = line.find(":")) != std::string::npos)
		{
		  save = pos;
		  while (playerName[++save] != '\0')
		    {
		      if (playerName[save] < '0' || playerName[save] > '9')
			correct = false;
		    }
		  if (correct == true)
		    {
		      scores = line.substr(pos + 1);
		      scorePlayer = std::stoi(scores);
		    }
		}
	    }
	}
      if (scorePlayer < this->_score)
	{
	  file.close();
	  file.open(".pacman.highscore", std::ios::out | std::ios::trunc);
	  if (file.is_open() == true)
	    {
	      file << playerName;
	      file << ":";
	      file << nb;
	    }
	}
      file.close();
    }

    ///////////
    //
    ///////////
    void			getScore(void)
    {
      std::size_t		pos;
      std::size_t		save;
      std::fstream		file;
      std::string		playerName;
      std::string		scores;
      std::string		line;
      int			scorePlayer;
      bool			correct = true;

      file.open(".pacman.highscore", std::ios::in);
      if (file.is_open() == true)
	{
	  std::getline(file, line);
	  if (line.size() >= 3)
	    {
	      if ((pos = line.find(":")) != std::string::npos)
		{
		  save = pos;
		  while (playerName[++save] != '\0' && playerName[save] != '\n')
		    {
		      if (playerName[save] < '0' || playerName[save] > '9')
			correct = false;
		    }
		  if (correct == true)
		    {
		      scores = line.substr(pos + 1);
		      scorePlayer = std::stoi(scores);
		      this->_highScore = scorePlayer;
		    }
		}
	    }
	}
      file.close();
    }

    /////////
    // RESTART THE GAME
    /////////
    void			restart(void)
    {
      delete[] this->_map;
      delete[] this->_me.me;
      this->InitGame();
      this->_nextGame = arcade::GameExitState::NOTHING;
      this->_direction = arcade::Dir::LEFT;
      this->_nextDir = arcade::Dir::LEFT;
      this->_quit = false;
      this->_pacmanSpeed = 8;
      this->_score = 0;
    }

    //////////////
    //****
    //***
    //**  GETTERS
    //***
    //****
    //////////////
    arcade::GameExitState	checkNextGame(void) const
    {
      return (_nextGame);
    }

    int				getPacmanSpeed(void) const
    {
      return (this->_pacmanSpeed);
    }

    ////////////
    //	check If must quit the game
    ////////////
    bool		checkQuit(void) const
    {
      return (this->_quit);
    }

    void		getMap(void) const
    {
      int		size = sizeof(arcade::GetMap) + ((PACWIDTH * PACHEIGHT)
							 * sizeof(arcade::TileType));
      write(1, this->_map, size);
    }

    void		getWhereAmI(void) const
    {
      int		size = sizeof(arcade::WhereAmI) + (this->_me.me->lenght * sizeof(arcade::Position));

      write(1, this->_me.me, size);
    }

    arcade::Dir		getDirection(void) const
    {
      return (this->_direction);
    }

    //////////////
    //****
    //***
    //**  FOR MOUL
    //***
    //****
    ///////////////

    //////////
    // Move to the left if not blocked by walls (moul v)
    //////////
    bool			MoveLeft(uint16_t x, uint16_t y)
    {
      if (this->_map->tile[(x - 1) + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  this->_me.me->position[0].x -= 1;
	  if (checkIfGhost(x - 1, y) == false)
	    return (false);
	  if (this->_map->tile[(x - 1) + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x - 1, y);
	}
      return (true);
    }

    //////////
    // Move to the right if not blocked by walls (moul v)
    //////////
    bool			MoveRight(uint16_t x, uint16_t y)
    {
      if (this->_map->tile[(x + 1) + (y * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  this->_me.me->position[0].x += 1;
	  if (checkIfGhost(x + 1, y) == false)
	    return (false);
	  if (this->_map->tile[(x + 1) + (y * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x + 1, y);
	}
      return (true);
    }

    //////////
    // Move Down  if not blocked by walls
    //////////
    bool			MoveDown(uint16_t x, uint16_t y)
    {
      if (this->_map->tile[x + ((y + 1) * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  this->_me.me->position[0].y += 1;
	  if (checkIfGhost(x, y + 1) == false)
	    return (false);
	  if (this->_map->tile[x + ((y + 1) * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y + 1);
	}
      return (true);
    }

    //////////
    // Move UP if not blocked by walls (moul v)
    //////////
    bool			MoveUp(uint16_t x, uint16_t y)
    {
      if (this->_map->tile[x + ((y - 1) * PACWIDTH)] != arcade::TileType::BLOCK)
	{
	  this->_me.me->position[0].y -= 1;
	  if (checkIfGhost(x, y - 1) == false)
	    return (false);
	  if (this->_map->tile[x + ((y - 1) * PACWIDTH)] == arcade::TileType::POWERUP)
	    eatPacgum(x, y - 1);
	}
      return (true);
    }

    //////////
    // Move depending to the _direction and nextDir
    //////////
    bool			goForward(void)
    {
      uint16_t			x = this->_me.me->position[0].x;
      uint16_t			y = this->_me.me->position[0].y;

      if (this->_nextDir == arcade::Dir::UP)
	{
	  if (this->_map->tile[x + ((y - 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      switch(static_cast<uint16_t>(this->_direction))
		{
		case (static_cast<uint16_t>(arcade::Dir::LEFT)):
		  return (MoveLeft(x, y));
		case (static_cast<uint16_t>(arcade::Dir::RIGHT)):
		  return (MoveRight(x, y));
		case (static_cast<uint16_t>(arcade::Dir::DOWN)):
		  return (MoveDown(x, y));
		case (static_cast<uint16_t>(arcade::Dir::UP)):
		  return (MoveUp(x, y));
		}
	    }
	  else
	    {
	      this->_direction = arcade::Dir::UP;
	      return (MoveUp(x, y));
	    }
	}
      else if (this->_nextDir == arcade::Dir::DOWN)
	{
	  if (this->_map->tile[x + ((y + 1) * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      switch(static_cast<uint16_t>(this->_direction))
		{
		case (static_cast<uint16_t>(arcade::Dir::LEFT)):
		  return (MoveLeft(x, y));
		case (static_cast<uint16_t>(arcade::Dir::RIGHT)):
		  return (MoveRight(x, y));
		case (static_cast<uint16_t>(arcade::Dir::DOWN)):
		  return (MoveDown(x, y));
		case (static_cast<uint16_t>(arcade::Dir::UP)):
		  return (MoveUp(x, y));
		}
	    }
	  else
	    {
	      this->_direction = arcade::Dir::DOWN;
	      return (MoveDown(x, y));
	    }
	}
      else if (this->_nextDir == arcade::Dir::LEFT)
	{
	  if (this->_map->tile[(x - 1) + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      switch(static_cast<uint16_t>(this->_direction))
		{
		case (static_cast<uint16_t>(arcade::Dir::LEFT)):
		  return (MoveLeft(x, y));
		case (static_cast<uint16_t>(arcade::Dir::RIGHT)):
		  return (MoveRight(x, y));
		case (static_cast<uint16_t>(arcade::Dir::DOWN)):
		  return (MoveDown(x, y));
		case (static_cast<uint16_t>(arcade::Dir::UP)):
		  return (MoveUp(x, y));
		}
	    }
	  else
	    {
	      this->_direction = arcade::Dir::LEFT;
	      return (MoveLeft(x, y));
	    }
	}
      else if (this->_nextDir == arcade::Dir::RIGHT)
	{
	  if (this->_map->tile[(x + 1) + (y * PACWIDTH)] == arcade::TileType::BLOCK)
	    {
	      switch(static_cast<uint16_t>(this->_direction))
		{
		case (static_cast<uint16_t>(arcade::Dir::LEFT)):
		  return (MoveLeft(x, y));
		case (static_cast<uint16_t>(arcade::Dir::RIGHT)):
		  return (MoveRight(x, y));
		case (static_cast<uint16_t>(arcade::Dir::DOWN)):
		  return (MoveDown(x, y));
		case (static_cast<uint16_t>(arcade::Dir::UP)):
		  return (MoveUp(x, y));
		}
	    }
	  else
	    {
	      this->_direction = arcade::Dir::RIGHT;
	      return (MoveRight(x, y));
	    }
	}
      return (true);
    }

    //////////
    // check if there is a ghost on Pacman path
    //////////
    bool				checkIfGhost(uint16_t x, uint16_t y)
    {
      if (x == this->_pinky.x && y == this->_pinky.y)
	{
	  if (this->_pinky.chased == false && this->_pinky.alive == true)
	    return (false);
	  else if (this->_pinky.alive == true && this->_pinky.chased == true)
	    pinkyDeath();
	}
      else if (x == this->_akabei.x && y == this->_akabei.y)
	{
	  if (this->_akabei.chased == false && this->_akabei.alive == true)
	    return (false);
	  else if (this->_akabei.alive == true && this->_akabei.chased == true)
	    akabeiDeath();
	}
      else if (x == this->_aosuke.x && y == this->_aosuke.y)
	{
	  if (this->_aosuke.chased == false && this->_aosuke.alive == true)
	    return (false);
	  else if (this->_aosuke.alive == true && this->_aosuke.chased == true)
	    aosukeDeath();
	}
      else if (x == this->_guzuta.x && y == this->_guzuta.y)
	{
	  if (this->_guzuta.chased == false && this->_guzuta.alive == true)
	    return (false);
	  else if (this->_guzuta.alive == true && this->_guzuta.chased == true)
	    guzutaDeath();
	}

      return (true);
    }

    //////////
    // Pacman eat a pacgum
    //////////
    void				eatPacgum(uint16_t x, uint16_t y)
    {
      for (int idx = 0; idx < 4; idx++)
	{
	  if (x == this->_pacgums[idx].x && y == this->_pacgums[idx].y)
	    {
	      this->_pacgums[idx].eaten = true;
	      if (this->_pinky.alive == true)
		{
		  this->_pinky.speed -= 3;
		  this->_pinky.chased = true;
		  this->_pinky.refChase = std::chrono::high_resolution_clock::now();
		  this->_pinky.ocurChase = 0;
		}
	      if (this->_akabei.alive == true)
		{
		  this->_akabei.speed -= 3;
		  this->_akabei.chased = true;
		  this->_akabei.refChase = std::chrono::high_resolution_clock::now();
		  this->_akabei.ocurChase = 0;
		}
	      if (this->_aosuke.alive == true)
		{
		  this->_aosuke.speed -= 3;
		  this->_aosuke.chased = true;
		  this->_aosuke.refChase = std::chrono::high_resolution_clock::now();
		  this->_aosuke.ocurChase = 0;
		}
	      if (this->_guzuta.alive == true)
		{
		  this->_guzuta.speed -= 3;
		  this->_guzuta.chased = true;
		  this->_guzuta.refChase = std::chrono::high_resolution_clock::now();
		  this->_guzuta.ocurChase = 0;
		}
	    }
	}
      this->_map->tile[x + (y * PACWIDTH)] = arcade::TileType::EMPTY;
      this->_score += 100;
    }

    //////////
    // Ghost Moves
    //////////
    void			GhostsMoves(void)
    {
      if (this->_pinky.alive == false)
	{
	  this->_pinky.ocur++;
	  if (this->_pinky.ocur == this->_pinky.maxOcur)
	    this->_pinky.alive = true;
	}
      else
	{
	}
      if (this->_akabei.alive == false)
	{
	  this->_akabei.ocur++;
	  if (this->_akabei.ocur == this->_akabei.maxOcur)
	    this->_akabei.alive = true;
	}
      else
	{
	}
      if (this->_aosuke.alive == false)
	{
	  this->_aosuke.ocur++;
	  if (this->_aosuke.ocur == this->_aosuke.maxOcur)
	    this->_aosuke.alive = true;
	}
      else
	{
	}
      if (this->_guzuta.alive == false)
	{
	  this->_guzuta.ocur++;
	  if (this->_guzuta.ocur == this->_guzuta.maxOcur)
	    this->_guzuta.alive = true;
	}
      else
	{
	}
    }

    ///////////////
    //****
    //***
    //**  KEY'S FUNCTIONS
    //***
    //****
    ///////////////

    /////////////
    // move to next gfx
    /////////////
    void		nextGfx(void *)
    {
      this->_gfxTmp = this->_loader->getNextGfxLib();
    }

    /////////////
    // move to previous gfx
    /////////////
    void		prevGfx(void *)
    {
      this->_gfxTmp = this->_loader->getPreviousGfxLib();
    }

    /////////////
    // Set var to move to next game
    /////////////
    void		nextGame(void *)
    {
      this->_nextGame = arcade::GameExitState::NEXT;
    }

    /////////////
    // Set var to move to prev Game;
    /////////////
    void		prevGame(void *)
    {
      this->_nextGame = arcade::GameExitState::PREVIOUS;
    }

    /////////////
    // Restart the game from the begining
    /////////////
    void		restartGame(void *)
    {
      delete this->_map;
      delete this->_me.me;
      this->InitGame();
      this->_nextGame = arcade::GameExitState::NOTHING;
      this->_direction = arcade::Dir::LEFT;
      this->_nextDir = arcade::Dir::LEFT;
      this->_quit = false;
      this->_score = 0;
    }

    ////////////
    //  back to menu
    ////////////
    void		backToMenu(void *)
    {
      this->_nextGame = arcade::GameExitState::MENU;
    }

    ////////////
    //	SET VAR TO QUIT GAME
    ////////////
    void		quit(void *)
    {
      this->_quit = true;
    }

  private :
    std::minstd_rand0		_rand;
    arcade::ILib		*_gfx;
    arcade::ILib		*_gfxTmp;
    arcade::IDlGfxLoader	*_loader;
    arcade::GetMap		*_map;
    arcade::t_pacman		_me;
    arcade::t_ghostStruct	_pinky;
    arcade::t_ghostStruct	_akabei;
    arcade::t_ghostStruct	_aosuke;
    arcade::t_ghostStruct	_guzuta;
    arcade::GameExitState	_nextGame;
    arcade::Dir			_direction;
    arcade::Dir			_nextDir;
    arcade::t_pacgum		_pacgums[4];
    bool			_quit;
    int				_highScore;
    int				_score;
    int				_pacmanSpeed;
    std::vector<std::function<void (void *)>> _key;
  };
}

#endif // Pacman_HPP_
