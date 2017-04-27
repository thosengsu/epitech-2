#ifndef SNAKE_HPP_
# define SNAKE_HPP_

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

static const std::string	mapInit =
"111111111111111111111111111111\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
100000000000000000000000000001\
111111111111111111111111111111";

//////////////////////////////
// Var for Sprites and Font //
//////////////////////////////
static const char	*BACKGROUND = "ressources/background.png";
static const char	*FONT = "ressources/calibrib.ttf";

////////////////////////////
// Sprites for Snake game //
////////////////////////////
static const char	*SNAKE_HEAD_UP = "ressources/SnakeHeadUp.png";
static const char	*SNAKE_HEAD_DOWN = "ressources/SnakeHeadDown.png";
static const char	*SNAKE_HEAD_LEFT = "ressources/SnakeHeadLeft.png";
static const char	*SNAKE_HEAD_RIGHT = "ressources/SnakeHeadRight.png";
static const char	*SNAKE_TAIL_UP = "ressources/SnakeTailUp.png";
static const char	*SNAKE_TAIL_DOWN = "ressources/SnakeTailDown.png";
static const char	*SNAKE_TAIL_LEFT = "ressources/SnakeTailLeft.png";
static const char	*SNAKE_TAIL_RIGHT = "ressources/SnakeTailRight.png";
static const char	*SNAKE_BODY_LEFT = "ressources/SnakeBodyLeft.png";
static const char	*SNAKE_BODY_UP = "ressources/SnakeBodyUp.png";
static const char	*SNAKE_BODY_TURN_UP = "ressources/SnakeBodyTurnUp.png";
static const char	*SNAKE_BODY_TURN_DOWN = "ressources/SnakeBodyTurnDown.png";
static const char	*SNAKE_BODY_TURN_RIGHT = "ressources/SnakeBodyTurnRight.png";
static const char	*SNAKE_BODY_TURN_LEFT = "ressources/SnakeBodyTurnLeft.png";
static const char	*SNAKE_EMPTY_MAP = "ressources/SnakeEmptyMap.png";
static const char	*SNAKE_WALL_MAP = "ressources/SnakeWallSprite.png";
static const char	*SNAKE_FRUIT = "ressources/fruit.png";

namespace arcade
{
  class snake : public IGame
  {
  public :
    snake(arcade::IDlGfxLoader *loader)
    {
      srandom(time(NULL));
      this->initChar();
      this->loadMap();
      this->_highScore = 0;
      this->getScore();
      this->_nbPowers = 0;
      this->_addTail = false;
      this->_quit = false;
      this->_posSave.x = 0;
      this->_posSave.y = 0;
      this->_score = 0;
      this->_moveDone = false;
      this->_loader = loader;
      this->_gfx = loader->getCurrentGfxLib();
      //      this->_gfx->init("snake");
      this->_gfxTmp = NULL;
      this->LoadSprites();
      this->_gfx->loadFont(FONT);
      this->_nextGame = arcade::GameExitState::NOTHING;
      this->InitCmd();
    }

    snake(void)
    {
      this->initChar();
      this->loadMap();
      this->_nbPowers = 0;
      this->_addTail = false;
      this->_quit = false;
      this->_posSave.x = 0;
      this->_posSave.y = 0;
      this->_nextGame = arcade::GameExitState::NOTHING;
    }

    ~snake()
    {
      delete[] this->_map;
      delete[] this->_me;
    }

    /////////////
    //****
    //***
    //**  Members Functions
    //***
    //****
    /////////////

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

	  this->_gfx->init("snake");
	  this->InitCmd();
	  this->LoadSprites();
	  this->_gfx->loadFont(FONT);
	}
    }

    /////////////
    //	Init the command for the event Test of the gfx
    /////////////
    void		InitCmd(void)
    {
      std::vector<std::function<void (void *)>> key;

      key.push_back(std::bind(&snake::prevGfx, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::nextGfx, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::prevGame, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::nextGame, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::restartGame, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::backToMenu, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::quit, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::PMoveLeft, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::PMoveRight, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::PMoveUp, this, std::placeholders::_1));
      key.push_back(std::bind(&snake::PMoveDown, this, std::placeholders::_1));
      this->_gfx->defCommand(key, arcade::CmdMode::GAME);
    }

    /////////////
    //	Load Sprites in memory
    /////////////
    void		LoadSprites(void)
    {
      this->_gfx->loadSprite("SnakeHeadUp", SNAKE_HEAD_UP);
      this->_gfx->loadSprite("SnakeHeadDown", SNAKE_HEAD_DOWN);
      this->_gfx->loadSprite("SnakeHeadLeft", SNAKE_HEAD_LEFT);
      this->_gfx->loadSprite("SnakeHeadRight", SNAKE_HEAD_RIGHT);
      this->_gfx->loadSprite("SnakeTailUp", SNAKE_TAIL_UP);
      this->_gfx->loadSprite("SnakeTailDown", SNAKE_TAIL_DOWN);
      this->_gfx->loadSprite("SnakeTailLeft", SNAKE_TAIL_LEFT);
      this->_gfx->loadSprite("SnakeTailRight", SNAKE_TAIL_RIGHT);
      this->_gfx->loadSprite("SnakeBodyUp", SNAKE_BODY_UP);
      this->_gfx->loadSprite("SnakeBodyLeft", SNAKE_BODY_LEFT);
      this->_gfx->loadSprite("SnakeBodyTurnLeft", SNAKE_BODY_TURN_LEFT);
      this->_gfx->loadSprite("SnakeBodyTurnRight", SNAKE_BODY_TURN_RIGHT);
      this->_gfx->loadSprite("SnakeBodyTurnUp", SNAKE_BODY_TURN_UP);
      this->_gfx->loadSprite("SnakeBodyTurnDown", SNAKE_BODY_TURN_DOWN);
      this->_gfx->loadSprite("Wall", SNAKE_WALL_MAP);
      this->_gfx->loadSprite("Empty", SNAKE_EMPTY_MAP);
      this->_gfx->loadSprite("Fruit", SNAKE_FRUIT);
    }

    /////////////
    //	Load a map graphicaly
    /////////////
    void		LoadMapGraph(void)
    {
      std::string	score = std::to_string(this->_score);
      std::string	highscore = std::to_string(this->_highScore);
      int		gfx_x;
      int		gfx_y = 0;

      for (int y = 0; y < MAP_HEIGHT; y++)
	{
	  gfx_x = 0;
	  for (int x = 0; x < MAP_WIDTH; x++)
	    {
	      if (this->_map->tile[x + (y * MAP_WIDTH)] == arcade::TileType::EMPTY)
		this->_gfx->blitSprite(gfx_x, gfx_y, "Empty", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_map->tile[x + (y * MAP_WIDTH)] == arcade::TileType::BLOCK)
		this->_gfx->blitSprite(gfx_x, gfx_y, "Wall", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_map->tile[x + (y * MAP_WIDTH)] == arcade::TileType::POWERUP)
		this->_gfx->blitSprite(gfx_x, gfx_y, "Fruit", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      gfx_x += TILE_SIZE_WIDTH;
	    }
	  gfx_y += TILE_SIZE_HEIGHT;
	}
      this->_gfx->blitText("score = ", static_cast<int>((SC_WIDTH / 2) - (TILE_SIZE_WIDTH * (8 + score.size()))), 0, 35);
      this->_gfx->blitText(score, static_cast<int>((SC_WIDTH / 2) - (TILE_SIZE_WIDTH * score.size())), 0, 35);
      this->_gfx->blitText("highscore = ", 0, (MAP_HEIGHT - 1) * TILE_SIZE_HEIGHT, 40);
      this->_gfx->blitText(highscore, 13 * 40, (MAP_HEIGHT - 1) * TILE_SIZE_HEIGHT, 40);
      this->blitSnake();
      this->_gfx->refresh();
    }

    /////////////
    //	Handle the blit of the snake
    /////////////
    void		blitSnake(void)
    {
      int		gfx_x;
      int		gfx_y;

      for (uint16_t idx = 0; idx < this->_me->lenght; idx++)
	{
	  gfx_x = this->_me->position[idx].x * TILE_SIZE_WIDTH;
	  gfx_y = this->_me->position[idx].y * TILE_SIZE_HEIGHT;
	  if (idx == 0)
	    {
	      if (this->_me->position[idx].x == this->_me->position[idx + 1].x - 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeHeadLeft", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].x == this->_me->position[idx + 1].x + 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeHeadRight", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].y == this->_me->position[idx + 1].y - 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeHeadUp", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].y == this->_me->position[idx + 1].y + 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeHeadDown", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	    }
	  else if (idx == this->_me->lenght - 1)
	    {
	      if (this->_me->position[idx].x == this->_me->position[idx - 1].x - 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeTailLeft", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].x == this->_me->position[idx - 1].x + 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeTailRight", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].y == this->_me->position[idx - 1].y - 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeTailDown", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (this->_me->position[idx].y == this->_me->position[idx - 1].y + 1)
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeTailUp", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	    }
	  else
	    {
	      if (((this->_me->position[idx].x == this->_me->position[idx - 1].x - 1) && (this->_me->position[idx].x == this->_me->position[idx + 1].x + 1)) ||
		  ((this->_me->position[idx].x == this->_me->position[idx + 1].x - 1) && (this->_me->position[idx].x == this->_me->position[idx - 1].x + 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyLeft", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (((this->_me->position[idx].y == this->_me->position[idx - 1].y - 1) && (this->_me->position[idx].y == this->_me->position[idx + 1].y + 1)) ||
		       ((this->_me->position[idx].y == this->_me->position[idx + 1].y - 1) && (this->_me->position[idx].y == this->_me->position[idx - 1].y + 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyUp", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (((this->_me->position[idx].x == this->_me->position[idx + 1].x - 1) && (this->_me->position[idx].y == this->_me->position[idx - 1].y - 1)) ||
		       ((this->_me->position[idx].x == this->_me->position[idx - 1].x - 1) && (this->_me->position[idx].y == this->_me->position[idx + 1].y - 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyTurnDown", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (((this->_me->position[idx].x == this->_me->position[idx + 1].x + 1) && (this->_me->position[idx].y == this->_me->position[idx - 1].y + 1)) ||
		       ((this->_me->position[idx].x == this->_me->position[idx - 1].x + 1) && (this->_me->position[idx].y == this->_me->position[idx + 1].y + 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyTurnUp", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (((this->_me->position[idx].x == this->_me->position[idx + 1].x + 1) && (this->_me->position[idx].y == this->_me->position[idx - 1].y - 1)) ||
		       ((this->_me->position[idx].x == this->_me->position[idx - 1].x + 1) && (this->_me->position[idx].y == this->_me->position[idx + 1].y - 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyTurnLeft", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	      else if (((this->_me->position[idx].x == this->_me->position[idx + 1].x - 1) && (this->_me->position[idx].y == this->_me->position[idx - 1].y + 1)) ||
		       ((this->_me->position[idx].x == this->_me->position[idx - 1].x - 1) && (this->_me->position[idx].y == this->_me->position[idx + 1].y + 1)))
		this->_gfx->blitSprite(gfx_x, gfx_y, "SnakeBodyTurnRight", TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
	    }
	}
    }

    /////////////
    //	Load the default Map of Snake and Init _map
    /////////////
    void		loadMap(void)
    {
      char *c = new char[sizeof(arcade::GetMap) + (MAP_WIDTH * MAP_HEIGHT
						   * sizeof(arcade::TileType))];
      this->_map = new(c) arcade::GetMap;
      this->_map->width = static_cast<uint16_t>(MAP_WIDTH);
      this->_map->height = static_cast<uint16_t>(MAP_HEIGHT);
      this->_map->type = arcade::CommandType::GET_MAP;
      for (int y = 0; y < MAP_HEIGHT; y++)
	{
	  for (int x = 0; x < MAP_WIDTH; x++)
	    {
	      if (mapInit[x + (y * MAP_WIDTH)] - 48 == 1)
		this->_map->tile[x + (y * MAP_WIDTH)] = arcade::TileType::BLOCK;
	      else if (mapInit[x + (y * MAP_WIDTH)] - 48 == 0)
		this->_map->tile[x + (y * MAP_WIDTH)] = arcade::TileType::EMPTY;
	    }
	}
      this->randomFruit();
    }

    ///////////
    //	generate a random fruit
    ///////////
    void		randomFruit(void)
    {
      arcade::Position	pos;

      pos.x = random() % MAP_WIDTH;
      pos.y = random() % MAP_HEIGHT;
      while (this->_map->tile[pos.x + (pos.y * MAP_WIDTH)] == arcade::TileType::BLOCK
	     || this->checkChar(pos.x, pos.y) == -1)
	{
	  pos.x = random() % MAP_WIDTH;
	  pos.y = random() % MAP_HEIGHT;
	}
      this->_map->tile[pos.x + (pos.y * MAP_WIDTH)] = arcade::TileType::POWERUP;
    }

    ///////////
    //	init the character's position
    ///////////
    void		initChar(void)
    {
      char		*c = new char[sizeof(arcade::WhereAmI) + 4 * sizeof(arcade::Position)];
      this->_me = new(c) arcade::WhereAmI;
      this->_me->type = arcade::CommandType::WHERE_AM_I;
      this->_me->lenght = 4;
      for (uint16_t idx = 0; idx < this->_me->lenght; idx++)
	{
	  this->_me->position[idx].x = (MAP_WIDTH / 2) + idx;
	  this->_me->position[idx].y = (MAP_HEIGHT / 2);
	}
      this->_direction = arcade::Dir::LEFT;
    }

    ///////////
    //	Check if snake eat himself
    ///////////
    int			checkChar(const uint16_t& x, const uint16_t& y) const
    {
      for (uint16_t idx = 0; idx < this->_me->lenght - 1; idx++)
	{
	  if (this->_me->position[idx].x == x &&
	      this->_me->position[idx].y == y)
	    return (-1);
	}
      return (0);
    }

    ///////////
    //	Prepare to move UP
    ///////////
    void			PMoveUp(void *)
    {
      if (this->_direction != arcade::Dir::DOWN && this->_moveDone == false)
	{
	  this->_direction = arcade::Dir::UP;
	  this->_moveDone = true;
	}
    }

    ///////////
    //	Move your character UP
    ///////////
    bool			moveUp(void)
    {
      this->_posSave = this->_me->position[_me->lenght - 1];
      if (_map->tile[_me->position[0].x + ((_me->position[0].y - 1) * MAP_WIDTH)] == arcade::TileType::BLOCK)
	return (false);
      else if (this->checkChar(_me->position[0].x, _me->position[0].y - 1) == -1)
	return (false);
      else
	{
	  arcade::Position tmp = this->_me->position[0];
	  arcade::Position tmp2 = this->_me->position[0];

	  this->_me->position[0].y -= 1;
	  for (uint16_t idx = 1; idx < _me->lenght; idx++)
	    {
	      tmp2 = this->_me->position[idx];
	      this->_me->position[idx] = tmp;
	      tmp = tmp2;
	    }
	  if (_map->tile[_me->position[0].x + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::POWERUP)
	    this->_addTail = true;
	  this->_direction = arcade::Dir::UP;
	  this->_moveDone = false;
	}
      return (true);
    }

    ///////////
    //	Prepare to move DOWN
    ///////////
    void			PMoveDown(void *)
    {
      if (this->_direction != arcade::Dir::UP && this->_moveDone == false)
	{
	  this->_direction = arcade::Dir::DOWN;
	  this->_moveDone = true;
	}
    }

    ///////////
    // Move your character DOWN
    ///////////
    bool			moveDown(void)
    {
      this->_posSave = this->_me->position[_me->lenght - 1];
      if (_map->tile[_me->position[0].x + ((_me->position[0].y + 1) * MAP_WIDTH)] == arcade::TileType::BLOCK)
	return (false);
      else if (this->checkChar(_me->position[0].x, _me->position[0].y + 1) == -1)
	return (false);
      else
	{
	  arcade::Position tmp = this->_me->position[0];
	  arcade::Position tmp2 = this->_me->position[0];

	  this->_me->position[0].y += 1;
	  for (uint16_t idx = 1; idx < _me->lenght; idx++)
	    {
	      tmp2 = this->_me->position[idx];
	      this->_me->position[idx] = tmp;
	      tmp = tmp2;
	    }
	  if (_map->tile[_me->position[0].x + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::POWERUP)
	    this->_addTail = true;
	  this->_posSave = this->_me->position[_me->lenght -1];
	  this->_direction = arcade::Dir::DOWN;
	  this->_moveDone = false;
	}
      return (true);
    }

    ////////////
    //	Prepare to move RIGHT
    ////////////
    void			PMoveRight(void *)
    {
      if (this->_direction != arcade::Dir::LEFT && this->_moveDone == false)
	{
	  this->_direction = arcade::Dir::RIGHT;
	  this->_moveDone = true;
	}
    }

    ////////////
    //	Move your character on the RIGTH
    ////////////
    bool			moveRight(void)
    {
      this->_posSave = this->_me->position[_me->lenght - 1];
      if (_map->tile[(_me->position[0].x + 1) + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::BLOCK)
	return (false);
      else if (this->checkChar(_me->position[0].x + 1, _me->position[0].y) == -1)
	return (false);
      else
	{
	  arcade::Position tmp = this->_me->position[0];
	  arcade::Position tmp2 = this->_me->position[0];

	  this->_me->position[0].x += 1;
	  for (uint16_t idx = 1; idx < _me->lenght; idx++)
	    {
	      tmp2 = this->_me->position[idx];
	      this->_me->position[idx] = tmp;
	      tmp = tmp2;
	    }
	  if (_map->tile[_me->position[0].x + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::POWERUP)
	    this->_addTail = true;
	  this->_posSave = this->_me->position[_me->lenght - 1];
	  this->_direction = arcade::Dir::RIGHT;
	  this->_moveDone = false;
	}
      return (true);
    }

    ////////////
    //	Prepare to move LEFT
    ////////////
    void			PMoveLeft(void *)
    {
      if (this->_direction != arcade::Dir::RIGHT && this->_moveDone == false)
	{
	  this->_direction = arcade::Dir::LEFT;
	  this->_moveDone = true;
	}
    }

    ////////////
    // Move your character on the LEFT
    ////////////
    bool			moveLeft(void)
    {
      this->_posSave = this->_me->position[_me->lenght - 1];
      if (_map->tile[(_me->position[0].x - 1) + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::BLOCK)
	return (false);
      else if (this->checkChar(_me->position[0].x - 1, _me->position[0].y) == -1)
	return (false);
      else
	{
	  arcade::Position tmp = this->_me->position[0];
	  arcade::Position tmp2 = this->_me->position[0];

	  this->_me->position[0].x -= 1;
	  for (uint16_t idx = 1; idx < _me->lenght; idx++)
	    {
	      tmp2 = this->_me->position[idx];
	      this->_me->position[idx] = tmp;
	      tmp = tmp2;
	    }
	  if (_map->tile[_me->position[0].x + (_me->position[0].y * MAP_WIDTH)] == arcade::TileType::POWERUP)
	    this->_addTail = true;
	  this->_direction = arcade::Dir::LEFT;
	  this->_moveDone = false;
	}
      return (true);
    }

    ////////////
    //	litteraly pass a round
    ////////////
    bool			goForward(void)
    {
      if (this->_addTail == true)
	this->eatFruit();
      if (this->_direction == arcade::Dir::UP)
	return (this->moveUp());
      else if (this->_direction == arcade::Dir::DOWN)
	return (this->moveDown());
      else if (this->_direction == arcade::Dir::LEFT)
	return (this->moveLeft());
      else if (this->_direction == arcade::Dir::RIGHT)
	return (this->moveRight());
      return (true);
    }

    ////////////
    //	Snake Eat a fruit and grow
    ////////////
    bool		eatFruit(void)
    {
      if (_map->tile[(_me->position[_me->lenght - 1].x + 1) + (_me->position[_me->lenght - 1].y * MAP_WIDTH)] != arcade::TileType::EMPTY)
	return (false);
      else
	{
	  this->addTail(this->_posSave.x, this->_posSave.y);
	  this->_map->tile[_me->position[0].x + (_me->position[0].y * MAP_WIDTH)] = arcade::TileType::EMPTY;
	  this->_addTail = false;
	  this->randomFruit();
	  this->_score += 100;
	}
      return (true);
    }

    ////////////
    //	The Snake grow
    ////////////
    void		addTail(uint16_t x, uint16_t y)
    {
      arcade::WhereAmI	*tmp;

      char		*c = new char[sizeof(arcade::WhereAmI) + ((this->_me->lenght + 1) * sizeof(arcade::Position))];
      tmp = new(c) arcade::WhereAmI;

      for (uint16_t idx = 0; idx < this->_me->lenght; idx++)
	tmp->position[idx] = this->_me->position[idx];
      tmp->lenght = this->_me->lenght + 1;
      tmp->position[tmp->lenght - 1].x = x;
      tmp->position[tmp->lenght - 1].y = y;
      delete this->_me;
      this->_me = tmp;
    }

    ////////////
    //	check if snake can move this direction
    ////////////
    bool		checkMove(arcade::Dir dir)
    {
      if (dir == arcade::Dir::UP && (this->_me->position[0].y - 1) == this->_me->position[1].y)
	return (false);
      else if (dir == arcade::Dir::DOWN && (this->_me->position[0].y + 1) == this->_me->position[1].y)
	return (false);
      else if (dir == arcade::Dir::LEFT && (this->_me->position[0].x - 1) == this->_me->position[1].x)
	return (false);
      else if (dir == arcade::Dir::RIGHT && (this->_me->position[0].x + 1) == this->_me->position[1].x)
	return (false);
      return (true);
    }

    ////////////
    //	check If must quit the game
    ////////////
    bool		checkQuit(void) const
    {
      return (this->_quit);
    }

    ////////////
    //  check If must change of game
    ////////////
    arcade::GameExitState	checkNextGame(void) const
    {
      return (this->_nextGame);
    }
    
    ////////////
    // get highscore
    ////////////
    void				getScore(void)
    {
      std::size_t		pos;
      std::size_t		save;
      std::fstream		file;
      std::string		playerName;
      std::string		scores;
      std::string		line;
      int			scorePlayer;
      bool			correct = true;

      file.open(".snake.highscore", std::ios::in);
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
    
    ////////////
    //	GAMEOVER
    ////////////
    arcade::GameExitState		gameOver(const std::string& playerName)
    {
      std::chrono::high_resolution_clock::time_point	ref;
      std::chrono::milliseconds		turn = std::chrono::milliseconds(5000);
      std::string			nb = std::to_string(this->_score);
      std::string			highscore = std::to_string(this->_highScore);
      arcade::GameExitState		state;

      ref = std::chrono::high_resolution_clock::now();
      this->_gfx->loadSprite("Background", BACKGROUND);
      this->_gfx->blitSprite(0, 0, "Background", SC_WIDTH, SC_HEIGHT);
      this->_gfx->blitText("GAMEOVER", static_cast<int>(SC_WIDTH / 2) - (4 * TILE_SIZE_WIDTH), static_cast<int>(SC_HEIGHT / 2), 50);
      this->WriteScores(playerName);
      this->_gfx->blitText("score = ", static_cast<int>((SC_WIDTH / 2) - ((4 + nb.size()) * TILE_SIZE_WIDTH)), static_cast<int>(SC_HEIGHT / 2) + TILE_SIZE_HEIGHT, 40);
      this->_gfx->blitText(nb, static_cast<int>((SC_WIDTH / 2) - (nb.size() * TILE_SIZE_WIDTH) + (8 * TILE_SIZE_WIDTH)), static_cast<int>(SC_HEIGHT / 2) + TILE_SIZE_HEIGHT, 40);
      this->_gfx->blitText("highscore = ", 0, 0, 40);
      this->_gfx->blitText(highscore, 13 * 40, 0, 40);
      this->_gfx->refresh();
      while ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - ref)) < turn)
	{
	  this->CheckEvent();
	  if (this->checkQuit() == true)
	    return (arcade::GameExitState::EXIT);
	  else if ((state = this->checkNextGame()) != arcade::GameExitState::NOTHING)
	    return (state);
	}
      return (arcade::GameExitState::NOTHING);
    }

    ////////////
    // Save Score in file if HighScore
    ////////////
    void			WriteScores(const std::string& playerName)
    {
      std::string			nb = std::to_string(this->_score);
      std::string			line;
      std::string			scores;
      std::size_t			pos;
      std::size_t			save;
      int				scorePlayer = -1;
      bool				correct = true;
      std::fstream			file;

      file.open(".snake.highscore", std::ios::in);
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
	  file.open(".snake.highscore", std::ios::out | std::ios::trunc);
	  if (file.is_open() == true)
	    {
	      file << playerName;
	      file << ":";
	      file << nb;
	    }
	}
      file.close();
    }

    ////////////
    //****
    //***
    //**   Getters
    //***
    //****
    ////////////
    void		getMap(void) const
    {
      int		size = sizeof(arcade::GetMap) + ((MAP_WIDTH * MAP_HEIGHT)
							 * sizeof(arcade::TileType));
      write(1, this->_map, size);
    }

    void		getWhereAmI(void) const
    {
      int		size = sizeof(arcade::WhereAmI) + (this->_me->lenght * sizeof(arcade::Position));

      write(1, this->_me, size);
    }

    arcade::Dir		getDirection(void) const
    {
      return (this->_direction);
    }

    /////////////
    //****
    //***
    //**   Key's Functions
    //***
    //****
    /////////////

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
      delete this->_me;
      this->initChar();
      this->loadMap();
      this->_nbPowers = 0;
      this->_addTail = false;
      this->_quit = false;
      this->_posSave.x = 0;
      this->_posSave.y = 0;
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
      this->_gfx->close();
    }

  private :
    arcade::GetMap		*_map;
    arcade::WhereAmI		*_me;
    arcade::Dir			_direction;
    arcade::ILib		*_gfx;
    arcade::ILib		*_gfxTmp;
    arcade::Position		_posSave;
    arcade::IDlGfxLoader	*_loader;
    uint16_t			_nbPowers;
    int				_score;
    int				_highScore;
    bool			_addTail;
    bool			_quit;
    bool			_moveDone;
    arcade::GameExitState	_nextGame;
  };
}

#endif // !SNAKE_HPP_
