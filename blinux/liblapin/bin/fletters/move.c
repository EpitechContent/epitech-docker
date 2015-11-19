/*
**
**
**
**
**
**
*/

#include		<math.h>
#include		"fletters.h"

static void		x_rot(double			*c,
			      double			*cos_,
			      double			*sin_)
{
  double		d[3];
  int			i;

  d[0] = 1 * c[0] +		0 * c[1]	+ 0 * c[2];
  d[1] = 0 * c[0] +		*cos_ * c[1]	- *sin_ * c[2];
  d[2] = 0 * c[0] +		*sin_ * c[1]	+ *cos_ * c[2];
  for (i = 0; i < 3; ++i)
    c[i] = d[i];
}

static void		y_rot(double			*c,
			      double			*cos_,
			      double			*sin_)
{
  double		d[3];
  int			i;

  d[0] = *cos_ * c[0] +		0 * c[1]	+ *sin_ * c[2];
  d[1] = 0 * c[0] +		1 * c[1]	+ 0 * c[2];
  d[2] = -*sin_ * c[0] +	0 * c[1]	+ *cos_ * c[2];
  for (i = 0; i < 3; ++i)
    c[i] = d[i];
}

static void		z_rot(double			*c,
			      double			*cos_,
			      double			*sin_)
{
  double		d[3];
  int			i;

  d[0] = *cos_ * c[0] -		*sin_ * c[1]	+ 0 * c[2];
  d[1] = *sin_ * c[0] +		*cos_ * c[1]	+ 0 * c[2];
  d[2] = 0 * c[0] +		0 * c[1]	+ 1 * c[2];
  for (i = 0; i < 3; ++i)
    c[i] = d[i];
}

void			move(t_fletters			*f)
{
  double		cos_[3];
  double		sin_[3];
  int			len;
  int			i;
  int			j;

  for (i = 0; i < 3; ++i)
    {
      cos_[i] = cos(f->rot[i]);
      sin_[i] = sin(f->rot[i]);
    }
  for (i = 0; i < f->len; ++i)
    for (j = 0; j < f->letters[i].cnt; ++j)
      {
	x_rot(&f->letters[i].coord[j].a[0], &cos_[0], &sin_[0]);
	x_rot(&f->letters[i].coord[j].b[0], &cos_[0], &sin_[0]);
	y_rot(&f->letters[i].coord[j].a[0], &cos_[1], &sin_[1]);
	y_rot(&f->letters[i].coord[j].b[0], &cos_[1], &sin_[1]);
	z_rot(&f->letters[i].coord[j].a[0], &cos_[2], &sin_[2]);
	z_rot(&f->letters[i].coord[j].b[0], &cos_[2], &sin_[2]);
      }
  len = sizeof(f->star) / sizeof(f->star[0]);
  for (i = 0; i < len; ++i)
    for (j = 0; j < 3; ++j)
      {
	/*
	  x_rot(&f->star[i].pos[0], &cos_[0], &sin_[0]);
	  x_rot(&f->star[i].spe[0], &cos_[0], &sin_[0]);
	  y_rot(&f->star[i].pos[0], &cos_[1], &sin_[1]);
	  y_rot(&f->star[i].spe[0], &cos_[1], &sin_[1]);
	  z_rot(&f->star[i].pos[0], &cos_[2], &sin_[2]);
	  z_rot(&f->star[i].spe[0], &cos_[2], &sin_[2]);
	*/
	if ((f->star[i].pos[j] += f->star[i].spe[j]) < 0)
	  f->star[i].pos[j] = f->win->buffer.width * 1.2;
      }
}

