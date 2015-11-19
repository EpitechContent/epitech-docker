
#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		"../../include/lapin.h"

// Frequency:

# define		MINUTE		(60.0 * 1000.0)
# define		TEMPO		120.0

# define		RONDE		(BLANCHE * 2)
# define		BLANCHE		(NOIRE * 2)
# define		NOIRE		(MINUTE / TEMPO)
# define		CROCHE		(NOIRE / 2)
# define		DCROCHE		(CROCHE / 2)

# define		SI_4		493.88
# define		LA_3		440.00
# define		SOL_3		392.00
# define		FA_3		349.23
# define		MI_3		329.63
# define		RE_3		293.66
# define		DO_3		261.63
# define		SI_2		246.94
// Sound base
# define		LA_2		220.00
# define		SOL_2		196.00
# define		FA_2		174.61
# define		MI_2		164.81
# define		RE_2		146.83
# define		DO_2		130.81
# define		SI_1		123.47
# define		LA_1		110.00

# define		NOTE(n)		((n) / LA_2)

typedef struct		s_midi_like
{
  double		pitch;		// ratio
  unsigned int		length;		// ms
}			t_midi_like;

t_midi_like		song[200] =
  {
    ///
    {NOTE(SI_2), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(DO_3), NOIRE},
    {NOTE(RE_3), NOIRE},
    {NOTE(RE_3), NOIRE},
    {NOTE(DO_3), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(LA_2), NOIRE},
    {NOTE(SOL_2), NOIRE},
    {NOTE(SOL_2), NOIRE},
    {NOTE(LA_2), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(SI_2), BLANCHE},
    {NOTE(LA_2), CROCHE},
    {NOTE(LA_2), BLANCHE},
    ///
    {0, CROCHE},
    ///
    {NOTE(SI_2), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(DO_3), NOIRE},
    {NOTE(RE_3), NOIRE},
    {NOTE(RE_3), NOIRE},
    {NOTE(DO_3), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(LA_2), NOIRE},
    {NOTE(SOL_2), NOIRE},
    {NOTE(SOL_2), NOIRE},
    {NOTE(LA_2), NOIRE},
    {NOTE(SI_2), NOIRE},
    {NOTE(LA_2), BLANCHE},
    {NOTE(SOL_2), CROCHE},
    {NOTE(SOL_2), BLANCHE},

    {-1, 0}
  };

static void		play_midi_like(t_bunny_effect	*m)
{
  int			current;

  for (current = 0; song[current].pitch >= 0; ++current)
    {
      bunny_sound_stop(m);
      bunny_sound_pitch(m, song[current].pitch);
      bunny_sound_play(m);
      usleep(song[current].length * 1000);
    }
}

int			main(void)
{
  t_bunny_effect	*music;

  if ((music = bunny_load_effect("guitar.ogg")) == NULL)
    return (EXIT_FAILURE);
  puts("Syntax is: play | stop | exit | pitch=float | vol=float | loop=0|1");
  bunny_sound_loop(music, false);
  bunny_sound_volume(music, 33);
  play_midi_like(music);
  bunny_delete_sound(music);
  return (EXIT_SUCCESS);
}

