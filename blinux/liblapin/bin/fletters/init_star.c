/*
**
**
**
**
**
*/

#include		"fletters.h"

void			init_star(t_fletters			*f)
{
  int			len;
  int			j;
  int			i;

  len = sizeof(f->star) / sizeof(f->star[0]);
  for (i = 0; i < len; ++i)
    for (j = 0; j < 3; ++j)
      {
	f->star[i].pos[j] = (rand() % (int)(f->win->buffer.width * 1.2));
	if (j == 0)
	  f->star[i].spe[j] = -(rand() % 1000) / 100;
	else
	  f->star[i].spe[j] = 0;
      }
}

