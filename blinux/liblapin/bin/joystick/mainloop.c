/*
**
**
**
**
**
*/

#include		"joystick.h"

t_bunny_response	mainloop(void		*data)
{
  t_joystick		*joy = data;
  t_bunny_position	pos;
  int			nb;
  int			i;

  bunny_clear(&joy->pic->buffer, BLACK);

  pos.y = (WINH - FONTH * joy->bigfont->scale.y) / 2;
  pos.x = (WINW - gl_program_name_size * (FONTW + 1) * joy->bigfont->scale.x) / 2;
  say(joy->bigfont, joy->pic, &pos, gl_program_name);

  for (i = 0, nb = joy->nb_joy; i < LAST_BUNNY_JOYSTICK && nb > 0; ++i)
    if (joy->info[i].connected)
      {
	display_joy(joy, joy->pic, &joy->info[i], joy->nb_joy - nb);
	nb -= 1;
      }
  bunny_draw(joy->pic);
  bunny_blit(&joy->win->buffer, joy->pic, NULL);
  bunny_display(joy->win);
  return (GO_ON);
}

