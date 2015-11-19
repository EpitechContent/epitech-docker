/*
**
**
**
**
*/

#include		"joystick.h"

t_bunny_response	joybutton(t_bunny_event_state		state,
				  int				joyid,
				  int				button,
				  void				*data)
{
  (void)state;
  (void)joyid;
  (void)button;
  (void)data;
  return (GO_ON);
}
