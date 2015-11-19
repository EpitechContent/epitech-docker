/*
**
**
**
**
**
*/

#include		<stdio.h>
#include		<math.h>
#include		"fletters.h"

static t_bunny_response	loop(void		*dat)
{
  t_fletters		*f = dat;
  int			tmp;
  int			i;

  f->rot[0] = f->r[0] * (2.0 * M_PI) / 360.0;
  f->rot[1] = f->r[1] * (2.0 * M_PI) / 360.0;
  f->rot[2] = f->r[2] * (2.0 * M_PI) / 360.0;

  move(f);

  for (i = 0; i < 3; ++i)
    f->rot[i] = 0;

  for (i = 0; i < 4; ++i)
    {
      if ((tmp = f->col.argb[i] + f->cols.mod[i]) > 255 || tmp < 0)
	f->cols.argb[i] *= -1;
      f->col.mod[i] += f->cols.argb[i];
    }
  f->col.argb[ALPHA_CMP] = 255;

  display(f);
  bunny_draw(f->before);
  bunny_blit(&f->win->buffer, f->before, NULL);
  bunny_display(f->win);
  return (GO_ON);
}

static t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	sym,
			    void		*data)
{
  t_fletters		*f = data;

  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (state == GO_DOWN)
    {
      if (bunny_get_keyboard()[BKS_UP])
	f->r[0] += -2.5;
      if (bunny_get_keyboard()[BKS_DOWN])
	f->r[0] += +2.5;
  
      if (bunny_get_keyboard()[BKS_LEFT])
	f->r[1] += -2.5;
      if (bunny_get_keyboard()[BKS_RIGHT])
	f->r[1] += +2.5;

      if (bunny_get_keyboard()[BKS_ADD])
	f->r[2] += -2.5;
      if (bunny_get_keyboard()[BKS_SUBTRACT])
	f->r[2] += +2.5;
    }
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  t_fletters		fletters;
  const char		*str;
  int			i;

  if (argc == 1)
    str = "lapins noirs";
  else if (argc == 2)
    str = argv[1];

  fletters.rot[0] = 0;
  fletters.rot[1] = 0;
  fletters.rot[2] = 0;
  fletters.r[0] = 2.5;
  fletters.r[1] = 2.5;
  fletters.r[2] = 2.5;
  
  for (i = 0; i < 4; ++i)
    {
      fletters.col.argb[i] = rand() % 255;
      while ((fletters.cols.mod[i] = rand() % 10 - 5) == 0);
    }

  if ((fletters.win = bunny_start(WINW, WINH, true, "Floatings Letters")) == NULL)
    return (1);
  if ((fletters.before = bunny_new_picture(fletters.win->buffer.width,
					   fletters.win->buffer.height)) == NULL)
    return (1);
  if ((fletters.pic = bunny_load_picture("bigbunny.png")) == NULL)
    return (1);
  load_string(&fletters, str);
  init_star(&fletters);

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(fletters.win, 30, &fletters);
  return (EXIT_SUCCESS);
}

