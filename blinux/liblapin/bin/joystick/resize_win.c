/*
**
**
**
**
**
*/

#include		"joystick.h"

void			resize_win(t_joystick		*joy)
{
  bunny_delete_clipable(joy->pic);
  bunny_stop(joy->win);
  if (bunny_start(WINW, WINH + joy->nb_joy * 100, false, gl_program_name) == false)
    longjmp(joy->env, CANNOT_OPEN_WINDOW);
  if ((joy->pic = bunny_new_picture(joy->win->buffer.width, joy->win->buffer.height)) == NULL)
    longjmp(joy->env, CANNOT_CREATE_PICTURE);
}
