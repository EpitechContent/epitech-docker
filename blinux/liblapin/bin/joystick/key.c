/*
**
**
**
**
**
**
*/

#include		"joystick.h"

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*data)
{
  (void)state;
  (void)data;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

