
#include		<math.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<lapin.h>

typedef struct		s_test
{
  int			part;
  t_bunny_window	*window;
  t_bunny_picture	*gen_picture;
  t_bunny_picture	*lod_picture;
  t_bunny_pixelarray	*wrt_picture;
}			t_test;

static t_bunny_response	loop(void		*data)
{
  static int		rot;
  static int		alt;
  t_bunny_position	pos[3];
  unsigned int		col[3];
  t_test		*test = (t_test*)data;
  int			i;
  int			j;

  rot += 1;
  if (test->part != -1)
    alt = 20 * test->part;
  switch ((++alt / 20) % 7)
    {
    case 0:
      bunny_fill(&test->window->buffer, ALPHA(128, rand()));
      break;
    case 1:
      for (i = 0; i < 2000; ++i)
	{
	  pos[0].x = rand() % 800;
	  pos[0].y = rand() % 600;
	  bunny_set_pixel(&test->window->buffer, pos[0], ALPHA(128, rand()));
	}
      break;
    case 2:
      for (i = 0; i < 300; ++i)
	{
	  col[0] = ALPHA(128, rand());
	  pos[0].x = rand() % 800;
	  pos[0].y = rand() % 600;
	  col[1] = ALPHA(128, rand());
	  pos[1].x = rand() % 800;
	  pos[1].y = rand() % 600;
	  bunny_set_line(&test->window->buffer, &pos[0], &col[0]);
	}
      break;
    case 3:
      for (i = 0; i < 100; ++i)
	{
	  col[0] = ALPHA(128, rand());
	  pos[0].x = rand() % 800;
	  pos[0].y = rand() % 600;
	  col[1] = ALPHA(128, rand());
	  pos[1].x = rand() % 800;
	  pos[1].y = rand() % 600;
	  col[2] = ALPHA(128, rand());
	  pos[2].x = rand() % 800;
	  pos[2].y = rand() % 600;
	  bunny_set_polygon(&test->window->buffer, &pos[0], &col[0]);
	}
      break;
    case 4:
      bunny_fill(&test->window->buffer, ALPHA(BLACK, 64));
      for (i = 0; i < 360; i += 90)
	{
	  pos[0].x = cos((i + rot) * M_PI / 180.0) * 100 + 400 - 150;
	  pos[0].y = sin((i + rot) * M_PI / 180.0) * 100 + 300 - 150;
	  bunny_blit(&test->window->buffer, test->gen_picture, &pos[0]);
	}
      break;
    case 5:
      bunny_fill(&test->window->buffer, WHITE);
      pos[0].x = cos(rot * M_PI / 180.0) * 100 + 400;
      pos[0].y = sin(rot * M_PI / 180.0) * 100 + 300;
      for (i = 0; test->window->name[i]; ++i)
	{
	  test->lod_picture->clip_x_position = test->window->name[i] * 5;
	  bunny_blit(&test->window->buffer, test->lod_picture, &pos[0]);
	  pos[0].x += 6;
	}
      break;
    case 6:
      for (j = 0; j < 600; ++j)
	for (i = 0; i < 800; ++i)
	  {
	    t_color	col;

	    col.full = 0;
	    col.argb[ALPHA_CMP] = 255;
	    col.argb[RED_CMP] = ((600 - j) / 600.0) * 255;
	    ((unsigned int*)test->wrt_picture->pixels)[j * 800 + i] = col.full;
	  }
      pos[0].x = 0;
      pos[0].y = 0;
      bunny_blit(&test->window->buffer, &test->wrt_picture->clipable, &pos[0]);
      break;
    }
  bunny_display(test->window);
  return (GO_ON);
}

extern int		memory_check;

int			main(int	argc,
			     char	**argv)
{
  t_test		test;
  int			ret;
  int			i;

  memory_check = 1;

  if (argc < 2)
    test.part = -1;
  else
    test.part = atoi(argv[1]);

  if ((test.window = bunny_start(800, 600, false, "random")) == NULL)
    return (EXIT_FAILURE);

  if ((test.gen_picture = bunny_new_picture(300, 300)) == NULL)
    return (EXIT_FAILURE);
  bunny_clear(&test.gen_picture->buffer, ALPHA(BLACK, 0));
  for (i = 0; i < 800; i += 2)
    {
      t_bunny_position	pos[2];
      unsigned int	color[2];

      pos[0].x = pos[1].x = i;
      pos[0].y = 0;
      pos[0].y = 600;
      if (i % 4)
	{
	  color[0] = RED;
	  color[1] = BLUE;
	}
      else
	{
	  color[1] = RED;
	  color[0] = BLUE;
	}
      bunny_set_line(&test.gen_picture->buffer, &pos[0], &color[0]);
    }
  bunny_draw(test.gen_picture);

  if ((test.lod_picture = bunny_load_picture("./font.png")) == NULL)
    return (EXIT_FAILURE);
  test.lod_picture->clip_y_position = 0;
  test.lod_picture->clip_width = 5;
  test.lod_picture->clip_height = 7;

  if ((test.wrt_picture = bunny_new_pixelarray(800, 600)) == NULL)
    return (EXIT_FAILURE);

  bunny_set_loop_main_function(loop);
  ret = bunny_loop(test.window, 10, &test);
  bunny_stop(test.window);

  bunny_delete_clipable(&test.wrt_picture->clipable);
  return (ret);
}
