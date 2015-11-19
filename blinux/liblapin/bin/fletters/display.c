/*
**
**
**
**
**
*/

#include		"fletters.h"

void			display(t_fletters		*f)
{
  t_bunny_position	pos[2];
  t_color		col[2];
  int			len;
  int			i;
  int			j;

  bunny_fill(&f->before->buffer, ALPHA(16, BLACK));

  pos[0].x = f->before->buffer.width - f->pic->buffer.width - 10;
  pos[0].y = f->before->buffer.height - f->pic->buffer.height - 10;
  bunny_blit(&f->before->buffer, f->pic, &pos[0]);

  len = sizeof(f->star) / sizeof(f->star[0]);
  for (i = 0; i < len; ++i)
    {
      pos[0].x = f->star[i].pos[0];/* + f->before->buffer.width / 2;*/
      pos[0].y = f->star[i].pos[1];/* + f->before->buffer.height / 2;*/
      bunny_set_pixel(&f->before->buffer, pos[0], ALPHA(128, WHITE));
    }

  col[0].full = f->col.full;
  col[1].full = f->col.full;
  for (i = 0; i < f->len; ++i)
    for (j = 0; j < f->letters[i].cnt; ++j)
      {
	pos[0].x = f->letters[i].coord[j].a[0] + f->before->buffer.width / 2;
	pos[0].y = f->letters[i].coord[j].a[1] + f->before->buffer.height / 2 - 10;
	pos[1].x = f->letters[i].coord[j].b[0] + f->before->buffer.width / 2;
	pos[1].y = f->letters[i].coord[j].b[1] + f->before->buffer.height / 2 - 10;
	bunny_set_line(&f->before->buffer, &pos[0], &col[0].full);
      }
}

