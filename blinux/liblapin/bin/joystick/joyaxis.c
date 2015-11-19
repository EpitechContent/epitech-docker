/*
**
**
**
**
*/

#include		"joystick.h"

t_bunny_response	joyaxis(int				joyid,
				t_bunny_axis			axis,
				float				value,
				void				*data)
{
  (void)joyid;
  (void)axis;
  (void)value;
  (void)data;
  return (GO_ON);
}
