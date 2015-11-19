
#include		<stdlib.h>
#include		<lapin.h>
#include		<unistd.h>

#define			PUTSERR(s)		(void)write(2, s, sizeof(s));

static size_t		dstrlen(const char	*s)
{
  return (1 + (*s ? dstrlen(s + 1) : 0));
}

static t_bunny_response	loop(void		*data)
{
  int			*i = data;

  if (++(*i) == 10)
    return (EXIT_ON_SUCCESS);
  return (GO_ONE);
}

int			main(int		argc,
			     char		**argv)
{
  t_bunny_music		*music;
  int			delay;
  int			i;

  i = 1;
  bunny_set_loop_main_function(loop);
  while (i < argc)
    {
      if ((music = bunny_load_music(argv[i])) == NULL)
	{
	  PUTSERR("An error happened while trying to read file ");
	  write(2, argv[i], dstrlen(argv[i]));
	  PUTSERR("\n");
	}
      else
	{
	  delay = 0;
	  bunny_sound_play(music);
	  bunny_loop(NULL, 1, &delay);
	  bunny_sound_stop(music);
	  bunny_delete_sound(music);
	}
      i = i + 1;
    }
  return (EXIT_SUCCESS);
}
