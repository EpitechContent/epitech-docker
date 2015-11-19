/*
**
**
**
**
**
**
**
*/

#include		"joystick.h"

void			say(t_bunny_picture		*font,
			    t_bunny_picture		*pic,
			    const t_bunny_position	*p,
			    const char			*str)
{
  t_bunny_position	pos;
  t_bunny_position	siz;
  int			i;

  siz.x = (FONTW + 1) * font->scale.x;
  siz.y = FONTH * font->scale.y;
  font->clip_y_position = 0;
  font->clip_width = FONTW;
  font->clip_height = FONTH;
  pos.x = p->x;
  pos.y = p->y;
  for (i = 0; str[i]; ++i)
    if (str[i] == '\n')
      {
	pos.y += siz.x;
	pos.x = p->x;
      }
    else if (str[i] == ' ')
      pos.x += siz.x;
    else if (str[i] == '\t')
      pos.x = i % 8 ? (p->x + (i % 8) * siz.x) : pos.x + siz.x * 8;
    else
      {
	font->clip_x_position = str[i] * FONTW;
	bunny_blit(&pic->buffer, font, &pos);
	pos.x += siz.x;
      }
}

