/*
**
**
**
**
**
**
**
*/

#ifndef				__JOYSTICK_H___
# define			__JOYSTICK_H__
# include			<setjmp.h>
# include			"lapin.h"

# define			WINW					1200
# define			WINH					50
# define			FONTW					5
# define			FONTH					7

extern const char * const	gl_program_name;
extern const int		gl_program_name_size;

typedef enum			e_errcode
  {
    CANNOT_OPEN_WINDOW,
    CANNOT_CREATE_PICTURE,
    NO_MORE_MEMORY,
    CANNOT_LOAD_FONT,
    LAST_ERRCODE
  }				t_errcode;

typedef struct			s_info
{
  bool				connected;
  char				*name;
  int				button;
  unsigned char			axis;
}				t_info;

typedef struct			s_joystick
{
  t_bunny_window		*win;
  t_bunny_picture		*pic;
  t_bunny_picture		*bigfont;
  t_bunny_picture		*littlefont;
  jmp_buf			env;
  int				nb_joy;
  t_info			info[LAST_BUNNY_JOYSTICK];
}				t_joystick;

void				resize_win(t_joystick			*joy);

t_bunny_response		mainloop(void				*data);
t_bunny_response		key(t_bunny_event_state			state,
				    t_bunny_keysym			sym,
				    void				*data);
t_bunny_response		joyconnect(t_bunny_event_state		state,
					   int				joyid,
					   const t_bunny_joystick	*info,
					   void				*data);
t_bunny_response		joyaxis(int				joyid,
					t_bunny_axis			axis,
					float				value,
					void				*data);
t_bunny_response		joybutton(t_bunny_event_state		state,
					  int				joyid,
					  int				button,
					  void				*data);

void				display_joy(t_joystick			*joy,
					    t_bunny_picture		*pic,
					    t_info			*info,
					    int				n);
void				say(t_bunny_picture			*font,
				    t_bunny_picture			*pic,
				    const t_bunny_position		*pos,
				    const char				*string);
void				square(t_bunny_clipable			*clip,
				       int				x,
				       int				y,
				       int				w,
				       int				h,
				       unsigned int			color);

#endif	/*		__JOYSTICK_H__			*/
