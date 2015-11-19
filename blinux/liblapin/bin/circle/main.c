

#include		<math.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_window	*win;
  t_bunny_position	pos;
  double		a;

  win = bunny_start(800, 600, false, "");
  for (a = 0; a < 2 * M_PI; a += 1 / 200.0)
    {
      pos.x = 200 * cos(a) + 400;
      pos.y = 200 * sin(a) + 300;
      bunny_set_pixel(&win->buffer, pos, WHITE);
    }
  while (1)
    bunny_display(win);
  return (0);
}
