/*
**
**
**
**
**
**
*/

#include		<stdio.h>
#include		"joystick.h"

void			display_joy(t_joystick		*joy,
				    t_bunny_picture	*pic,
				    t_info		*info,
				    int			n)
{
  char			buf[2];
  unsigned int		col;
  t_bunny_position	pos;
  t_bunny_position	stick;
  int			wb;
  int			i;

  /* Title */
  pos.x = 10;
  pos.y = n * 100 + WINH;
  say(joy->littlefont, pic, &pos, info->name);
  pos.y += 20;

  /* X / Y */
  col = (info->axis & BA_X) | (info->axis & BA_Y) ? ALPHA(255, WHITE) : ALPHA(32, WHITE);
  square(pic, pos.x, pos.y, 70, 70, col);
  stick.x = pos.x + 30 + 30.0 * bunny_get_joy_axis()[n][0] / 100.0;
  stick.y = pos.y + 30 + 30.0 * bunny_get_joy_axis()[n][1] / 100.0;
  square(pic, stick.x, stick.y, 10, 10, RED);

  pos.x += 80;

  /* Z */
  col = (info->axis & BA_Z) ? ALPHA(255, WHITE) : ALPHA(32, WHITE);
  square(pic, pos.x, pos.y, 70, 70, col);
  stick.x = pos.x + 30 + 30.0 * bunny_get_joy_axis()[n][2] / 100.0;
  stick.y = pos.y;
  square(pic, stick.x, stick.y, 10, 70, RED);

  pos.x += 80;

  /* R / U */
  col = (info->axis & BA_R) | (info->axis & BA_U) ? ALPHA(255, WHITE) : ALPHA(32, WHITE);
  square(pic, pos.x, pos.y, 70, 70, col);
  stick.x = pos.x + 30 + 30.0 * bunny_get_joy_axis()[n][3] / 100.0;
  stick.y = pos.y + 30 + 30.0 * bunny_get_joy_axis()[n][4] / 100.0;
  square(pic, stick.x, stick.y, 10, 10, RED);

  pos.x += 80;

  /* V */
  col = (info->axis & BA_V) ? ALPHA(255, WHITE) : ALPHA(32, WHITE);
  square(pic, pos.x, pos.y, 70, 70, col);
  stick.x = pos.x + 30 + 30.0 * bunny_get_joy_axis()[n][5] / 100.0;
  stick.y = pos.y;
  square(pic, stick.x, stick.y, 10, 70, RED);

  pos.x += 80;

  /* POVX / POVY */
  col = (info->axis & BA_POVX) | (info->axis & BA_POVY) ? ALPHA(255, WHITE) : ALPHA(32, WHITE);
  square(pic, pos.x, pos.y, 70, 70, col);
  stick.x = pos.x + 30 + 30.0 * bunny_get_joy_axis()[n][6] / 100.0;
  stick.y = pos.y + 30 + 30.0 * bunny_get_joy_axis()[n][7] / 100.0;
  square(pic, stick.x, stick.y, 10, 10, RED);

  pos.x += 80;

  /* Buttons */
  buf[1] = '\0';
  wb = ((WINW - 10) - pos.x) / LAST_BUNNY_BUTTON;
  for (i = 0; i < LAST_BUNNY_BUTTON; ++i, pos.x += wb)
    {
      if (i < 10)
	buf[0] = '0' + i;
      else
	buf[0] = 'a' + i - 10;
      say(joy->littlefont, joy->pic, &pos, &buf[0]);

      if (bunny_get_joy_button()[n][i])
	square(pic, pos.x, pos.y + (70 - wb * 0.8) / 2, wb * 0.8, wb * 0.8, RED);
      else if (i < info->button)
	square(pic, pos.x, pos.y + (70 - wb * 0.8) / 2, wb * 0.8, wb * 0.8, ALPHA(255, WHITE));
      else
	square(pic, pos.x, pos.y + (70 - wb * 0.8) / 2, wb * 0.8, wb * 0.8, ALPHA(32, WHITE));
    }
}

