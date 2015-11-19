/*
**
**
**
**
**
*/

#ifndef			__FLETTERS_H__
# define		__FLETTERS_H__
# include		<lapin.h>

# define		WINW				1920
# define		WINH				1080

typedef struct		s_coord
{
  double		a[3];
  double		b[3];
}			t_coord;

typedef struct		s_star
{
  double		pos[3];
  double		spe[3];
}			t_star;

typedef struct		s_letter
{
  int			cnt;
  t_coord		coord[8];
}			t_letter;

typedef struct		s_fletters
{
  t_bunny_window	*win;
  t_bunny_picture	*before;
  t_bunny_picture	*pic;
  t_letter		*letters;
  int			len;
  double		rot[3];
  t_star		star[256];
  double		r[3];
  t_color		col;
  t_color		cols;
}			t_fletters;

void			init_star(t_fletters		*f);
void			load_string(t_fletters		*f,
				    const char		*str);
void			display(t_fletters		*r);
void			move(t_fletters			*r);

#endif	/*		__FLETTERS_H__			*/
