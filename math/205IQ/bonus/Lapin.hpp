//
// Lapin.hpp for 205 in /home/erwan/Tek2/Math/205IQ/bonus
//
// Made by Erwan
// Login   <erwan.guiomar@epitech.eu>
//
// Started on  Fri Apr 14 13:33:43 2017 Erwan
// Last update Tue Apr 18 17:06:36 2017 Erwan
//

#ifndef LAPIN_HPP_
# define LAPIN_HPP_

# include <lapin.h>
# include <string>
# include <vector>
# include <exception>
# include "my.hpp"

static bool		s_compute;

static const int	SC_WIDTH = 1920;
static const int	SC_HEIGHT = 1080;
static const int	FONT_S = 30;

static const int	GRAPH_MIN_X_PX = 200;
static const int	GRAPH_MAX_X_PX = SC_WIDTH - 200;

static const int	GRAPH_MIN_Y_PX = SC_HEIGHT - 200;
static const int	GRAPH_MAX_Y_PX = 200;

# define X_PX(x)	((((GRAPH_MAX_X_PX - GRAPH_MIN_X_PX) / 200) * (x)) + GRAPH_MIN_X_PX)
# define Y_PX(y, max)	((((GRAPH_MAX_Y_PX - GRAPH_MIN_Y_PX) / (max)) * (y)) + GRAPH_MIN_Y_PX)

static t_bunny_response	loop(void *data);
static t_bunny_response	key(t_bunny_event_state state, t_bunny_keysym key, void *data);

class Lapin
{
public:
  /* CTOR && DTOR */
  Lapin(IQ *iq) : _iq(iq)
  {
    if ((this->_win = bunny_start(SC_WIDTH, SC_HEIGHT, false, "205IQ with libLapin")) == NULL)
      throw (std::runtime_error("Bunny_start failed."));

    this->loadFont("./arial.ttf");
    bunny_set_mouse_visibility(this->_win, true);
    bunny_set_key_repeat(this->_win, true);
    bunny_set_loop_main_function(&loop);
    bunny_set_key_response(key);
    s_compute = true;
    this->refresh();
  };

  ~Lapin(void) {};

  /* MEMBERS FUNCTIONS */
  void	startLoop(void)
  {
    bunny_loop(this->_win, 60, this);
  }

  void	aff_interface(void)
  {
    t_bunny_position	pos[2];
    unsigned int	color[2];
    std::string		str;

    this->setMax();

    color[0] = BLACK;
    color[1] = BLACK;

    pos[0].x = GRAPH_MIN_X_PX;
    pos[0].y = GRAPH_MIN_Y_PX;
    pos[1].x = GRAPH_MIN_X_PX;
    pos[1].y = GRAPH_MAX_Y_PX;
    bunny_set_line(&(this->_win->buffer), pos, color);

    pos[1].x = GRAPH_MAX_X_PX;
    pos[1].y = GRAPH_MIN_Y_PX;
    bunny_set_line(&(this->_win->buffer), pos, color);

    blitText("0", X_PX(0) - FONT_S, Y_PX(0, this->_max), 0);
    blitText("50", X_PX(50) - FONT_S, Y_PX(0, this->_max), 0);
    blitText("100", X_PX(100) - FONT_S, Y_PX(0, this->_max), 0);
    blitText("150", X_PX(150) - FONT_S, Y_PX(0, this->_max), 0);
    blitText("200", X_PX(200) - FONT_S, GRAPH_MIN_Y_PX, 0);

    str = std::to_string(this->_max / 4);
    blitText(str.c_str(), X_PX(0) - FONT_S, Y_PX(this->_max / 4, this->_max), 0);

    str = std::to_string(this->_max / 2);
    blitText(str.c_str(), X_PX(0) - FONT_S, Y_PX(this->_max / 2, this->_max), 0);

    str = std::to_string(this->_max * 3 / 4);
    blitText(str.c_str(), X_PX(0) - FONT_S, Y_PX(this->_max * 3 / 4, this->_max), 0);

    str = std::to_string(this->_max);
    blitText(str.c_str(), X_PX(0) - FONT_S, Y_PX(this->_max, this->_max), 0);

    str = "Mean : ";
    str += std::to_string(this->_iq->getMean());
    blitText(str.c_str(), SC_WIDTH - 300, 50, 0);

    str = "Deviation :";
    str += std::to_string(this->_iq->getDeviation());
    blitText(str.c_str(), SC_WIDTH - 300, 50 + FONT_S + 20, 0);
  }

  void	aff_graph(void)
  {
    std::vector<double>	values = this->_iq->getValues();
    t_bunny_position	pos[2];
    int			idx = 0;
    unsigned int	color[2];

    color[0] = RED;
    color[1] = RED;

    pos[1].x = GRAPH_MIN_X_PX;
    pos[1].y = GRAPH_MIN_Y_PX;
    while (idx <= 200)
      {
	pos[0] = pos[1];
	pos[1].x = X_PX(idx);
	pos[1].y = Y_PX(values[idx], this->_max);
	bunny_set_line(&(this->_win->buffer), pos, color);
	++idx;
      }
  }

  void	refresh(void)
    {
      bunny_display(this->_win);
      bunny_clear(&(this->_win->buffer), WHITE);
    }

  void	blitText(const std::string &text, int x, int y, int)
    {
      t_bunny_position	pos;

      pos.x = x;
      pos.y = y;

      bunny_clear(&(this->_font->clipable.buffer), COLOR(0, 0, 0, 0));
      this->_font->string = text.c_str();
      this->_font->string_len = text.size();
      bunny_draw(&(this->_font->clipable));
      bunny_blit(&(this->_win->buffer), &(this->_font->clipable), &pos);
    }

  void	loadFont(const std::string &fileName)
    {
      t_bunny_position	size;

      size.x = 40;
      size.y = 40;

      this->_font = bunny_load_font(500, 50, fileName.c_str(), &size);
      if (this->_font == NULL)
	throw (std::runtime_error("Bunny load font crashed.\n"));


      this->_font->color = BLACK;
      this->_font->halign = BAL_LEFT;
      this->_font->valign = BAL_TOP;
      this->_font->string_offset = 0;
      this->_font->outline = 1;

      size.x = 0;
      size.y = 0;
      this->_font->offset = size;
    }

  /* GETTER && SETTER */
  IQ	*getIq(void)
  {
    return (this->_iq);
  }

  void	setMax(void)
  {
    this->_max = static_cast<int>((this->_iq->getValues())[this->_iq->getMean()]) + 1;
  }


private:
  IQ			*_iq;
  t_bunny_window	*_win;
  t_bunny_font		*_font;
  int			_max;
};

static t_bunny_response	key(t_bunny_event_state state, t_bunny_keysym key, void *data)
{
  Lapin	*ptr = (Lapin *)data;

  if (state == GO_DOWN)
    {
      if (key == BKS_ESCAPE)
	return (EXIT_ON_CROSS);
      else if (key == BKS_1)
	{
	  ptr->getIq()->setMean(ptr->getIq()->getMean() - 1);
	  s_compute = true;
	}
      else if (key == BKS_2)
	{
	  ptr->getIq()->setMean(ptr->getIq()->getMean() + 1);
	  s_compute = true;
	}
      else if (key == BKS_3)
	{
	  ptr->getIq()->setDeviation(ptr->getIq()->getDeviation() - 1);
	  s_compute = true;
	}
      else if (key == BKS_QUOTE)
	{
	  ptr->getIq()->setDeviation(ptr->getIq()->getDeviation() + 1);
	  s_compute = true;
	}
    }
    return (GO_ON);
}

static t_bunny_response	loop(void *data)
{
  Lapin	*ptr = (Lapin *)data;

  if (s_compute)
    {
      ptr->getIq()->compute();
      ptr->setMax();
      ptr->aff_interface();
      ptr->aff_graph();
      ptr->refresh();

      s_compute = false;
    }
  return (GO_ON);
}

#endif /* !LAPIN_HPP_ */
