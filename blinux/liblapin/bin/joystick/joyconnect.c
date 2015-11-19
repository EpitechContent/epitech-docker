/*
**
**
**
**
**
*/

#include		<stdio.h>
#include		<string.h>
#include		"joystick.h"

char			*bunny_strdup(const char		*str)
{
  size_t		i;
  char			*n;

  for (i = 0; str[i]; ++i);
  if ((n = bunny_malloc((i + 1) * sizeof(str[i]))) == NULL)
    return (NULL);
  for (i = 0; str[i]; ++i)
    n[i] = str[i];
  n[i] = str[i];
  return (n);
}

t_bunny_response	joyconnect(t_bunny_event_state		state,
				   int				joyid,
				   const t_bunny_joystick	*info,
				   void				*data)
{
  t_joystick		*joy = data;

  if (state == CONNECTED)
    {
      joy->nb_joy += 1;
      joy->info[joyid].connected = true;
      if ((joy->info[joyid].name = bunny_strdup(info->name)) == NULL)
	longjmp(joy->env, NO_MORE_MEMORY);
      joy->info[joyid].button = info->nb_button;
      joy->info[joyid].axis = info->axis;
      resize_win(joy);
      return (GO_ON);
    }
  joy->nb_joy -= 1;
  joy->info[joyid].connected = false;
  bunny_free(joy->info[joyid].name);
  resize_win(joy);
  return (GO_ON);
}

