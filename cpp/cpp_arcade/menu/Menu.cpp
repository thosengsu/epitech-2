#include <string>
#include <vector>
#include "ILib.hpp"
#include "IGame.hpp"
#include "IDlGfxLoader.hpp"
#include "dlGfxLoader.hpp"
#include "dlGameLoader.hpp"
#include "Menu.hpp"

static const char	*FONT = "ressources/calibrib.ttf";
static const char	*BACKGROUND = "ressources/background.png";
static const int	fontSize = 40;

arcade::Menu::Menu(const std::string &gfxLibName)
  : _gfxTmp(NULL), _start(false), _leave(false)
{
  this->_dlGfxLoader = new arcade::dlGfxLoader(gfxLibName);
  this->_gfx = this->_dlGfxLoader->getCurrentGfxLib();

  this->_gfx->init();
  this->_gfx->loadFont(FONT);
  this->_gfx->loadSprite("Background", BACKGROUND);
  this->defCmd();
}

arcade::Menu::~Menu()
{
  if (this->_gfxTmp != NULL)
    delete this->_gfxTmp;
  delete this->_dlGfxLoader;
}

/* ----------------- */
/* MEMBERS FUNCTIONS */
/* ----------------- */
void			arcade::Menu::loop(void)
{
  arcade::GameExitState	gameReturn = arcade::GameExitState::NOTHING;
  bool			reLaunchGame = false;

  while (!this->_leave)
    {
      this->checkEvent();
      this->affMenu();
      while (this->_start == true || reLaunchGame == true)
	{
	  gameReturn = ((this->_dlGameLoader.getCurrentGameLauncher())(this->_dlGfxLoader,
								       this->_playerName));
	  this->_gfx = this->_dlGfxLoader->getCurrentGfxLib();
	  this->_gfx->loadFont(FONT);
	  this->_gfx->loadSprite("Background", BACKGROUND);
	  this->defCmd();
	  this->_start = false;

	  switch (gameReturn)
	    {
	    case (arcade::GameExitState::PREVIOUS):
	      {
		this->previousGame(NULL);
		reLaunchGame = true;
		break;
	      }
	    case (arcade::GameExitState::NEXT):
	      {
		this->nextGame(NULL);
		reLaunchGame = true;
		break;
	      }
	    case (arcade::GameExitState::MENU):
	      {
		reLaunchGame = false;
		break;
	      }
	    case (arcade::GameExitState::EXIT):
	      {
		reLaunchGame = false;
		this->_leave = true;
		break;
	      }
	    default:
	      {
		reLaunchGame = false;
		this->_leave = true;
		break;
	      }
	    }
	}
    }
}

void		arcade::Menu::checkEvent(void)
{
  this->_gfx->checkEvent();

  if (this->_gfxTmp != NULL)
    {
      this->_gfx->close();
      delete this->_gfx;
      this->_dlGfxLoader->closeOldGfx();

      this->_gfx = this->_gfxTmp;
      this->_gfxTmp = NULL;

      this->_gfx->init("Arcade");
      this->defCmd();
      this->_gfx->loadSprite("Background", BACKGROUND);
      this->_gfx->loadFont(FONT);
    }
}

void		arcade::Menu::affMenu(void) const
{
  int		y;
  std::string	str;

  this->_gfx->blitSprite(0, 0, "Background", SC_WIDTH, SC_HEIGHT);
  this->_gfx->blitText("Arcade :", (SC_WIDTH / 2) - 40, SC_HEIGHT / 5, fontSize);

  y = SC_HEIGHT / 3;
  this->_gfx->blitText("Lib Graphiques :", (SC_WIDTH / 4) - 80, y, fontSize);
  for (auto i : this->_dlGfxLoader->getGfxLibNames())
    {
      y += 100;
      str = i;
      if (i == *(this->_dlGfxLoader->getCurrentGfxLibIt()))
	str += " <";
      this->_gfx->blitText(str, (SC_WIDTH / 4) - (str.size() / 2), y, fontSize);
    }

  y = SC_HEIGHT / 3;
  this->_gfx->blitText("Jeux disponibles :", ((3 * SC_WIDTH / 4) - 40) - 8, y, fontSize);
  for (auto i : this->_dlGameLoader.getGameLibNames())
    {
      y += 100;
      str = i;
      if (i == *(this->_dlGameLoader.getCurrentGameLibIt()))
	str += " <";
      this->_gfx->blitText(str, ((SC_WIDTH / 4) * 3) - (str.size() / 2), y, fontSize);
    }

  this->_gfx->blitText(this->_playerName, (SC_WIDTH / 2) - (this->_playerName.size() / 2),
		       4 * SC_HEIGHT / 5, fontSize);
  this->_gfx->refresh();
}

void		arcade::Menu::defCmd(void)
{
  std::vector<std::function<void (void *)>>	fctTab;

  fctTab.push_back(std::bind(&arcade::Menu::previousGfx, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::nextGfx, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::previousGame, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::nextGame, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::writeName, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::launchGame, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::delCaraInName, this, std::placeholders::_1));
  fctTab.push_back(std::bind(&arcade::Menu::quit, this, std::placeholders::_1));

  this->_gfx->defCommand(fctTab, arcade::CmdMode::MENU);
}

/* ----------------- */
/* COMMAND FUNCTIONS */
/* ----------------- */
void	arcade::Menu::nextGfx(void *)
{
  this->_gfxTmp = this->_dlGfxLoader->getNextGfxLib();
}

void	arcade::Menu::previousGfx(void *)
{
  this->_gfxTmp = this->_dlGfxLoader->getPreviousGfxLib();
}

void	arcade::Menu::nextGame(void *)
{
  this->_dlGameLoader.setToNextGame();
}

void	arcade::Menu::previousGame(void *)
{
  this->_dlGameLoader.setToPreviousGame();
}

void	arcade::Menu::writeName(void *data)
{
  char	*c = static_cast<char *>(data);

  this->_playerName += *c;
}

void	arcade::Menu::launchGame(void *)
{
  this->_start = true;
}

void	arcade::Menu::delCaraInName(void *)
{
  if (!this->_playerName.empty())
    this->_playerName.pop_back();
}

void	arcade::Menu::quit(void *)
{
  this->_leave = true;
}
