/*
**
**
**
**
**
*/

#include		"joystick.h"

void			square(t_bunny_clipable	*clip,
			       int		_x,
			       int		_y,
			       int		_w,
			       int		_h,
			       unsigned int	color)
{
  int			x;
  int			y;
  int			w;
  int			h;

  x = clip->clip_x_position;
  y = clip->clip_y_position;
  w = clip->clip_width;
  h = clip->clip_height;

  clip->clip_x_position = _x;
  clip->clip_y_position = _y;
  clip->clip_width = _w;
  clip->clip_height = _h;

  bunny_fill(&clip->buffer, color);

  clip->clip_x_position = x;
  clip->clip_y_position = y;
  clip->clip_width = w;
  clip->clip_height = h;
}
