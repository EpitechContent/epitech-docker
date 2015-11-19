/*
**
**
**
**
**
*/

#include			<string.h>
#include			<unistd.h>
#include			"joystick.h"

const char * const		gl_program_name = "Joystick Monitor";
const int			gl_program_name_size = 16;

static const char * const	gl_errcode[LAST_ERRCODE] =
  {
    "The Lapins Noirs failed at opening a window.",
    "The Lapins Noirs failed at creating a cpu side picture.",
    "The Lapins Noirs hit the memory wall.",
    "The Lapins Noirs failed at loading the font."
  };

static void			goto_bindir(char	*file)
{
  unsigned int		i;

  for (i = 0; file[i] != '\0'; ++i);
  while (i > 0 && file[i] != '/')
    i = i - 1;
  file[++i] = '\0';
  chdir(file);
}

static void			initall(t_joystick		*j)
{
  int				i;

  if ((j->win = bunny_start(WINW, WINH, false, gl_program_name)) == NULL)
    longjmp(j->env, CANNOT_OPEN_WINDOW);
  if ((j->pic = bunny_new_picture(j->win->buffer.width, j->win->buffer.height)) == NULL)
    longjmp(j->env, CANNOT_CREATE_PICTURE);
  if ((j->bigfont = bunny_load_picture("font.png")) == NULL)
    longjmp(j->env, CANNOT_LOAD_FONT);
  if ((j->littlefont = bunny_load_picture("font.png")) == NULL)
    longjmp(j->env, CANNOT_LOAD_FONT);
  j->bigfont->scale.x = 3;
  j->bigfont->scale.y = 3;
  j->littlefont->scale.x = 2;
  j->littlefont->scale.y = 2;
  bunny_set_loop_main_function(mainloop);
  bunny_set_key_response(key);
  bunny_set_joy_connect_response(joyconnect);
  bunny_set_joy_button_response(joybutton);
  bunny_set_joy_axis_response(joyaxis);
  for (i = 0; i < LAST_BUNNY_JOYSTICK; ++i)
    if (bunny_get_joy_info(i)->connected)
      joyconnect(CONNECTED, i, bunny_get_joy_info(i), j);
}

static int			cleanall(t_joystick		*j,
					 t_errcode		errcode)
{
  int				i;

  for (i = 0; i < LAST_BUNNY_JOYSTICK; ++i)
    if (j->info[i].name != NULL)
      free(j->info[i].name);
  if (j->bigfont)
    bunny_delete_clipable(j->littlefont);
  if (j->littlefont)
    bunny_delete_clipable(j->bigfont);
  if (j->pic)
    bunny_delete_clipable(j->pic);
  if (j->win)
    bunny_stop(j->win);
  write(STDERR_FILENO, gl_errcode[errcode], strlen(gl_errcode[errcode]));
  return (EXIT_FAILURE);
}

int				main(int		argc,
				     char		**argv)
{
  static t_joystick		joystick;
  t_errcode			errcode;

  (void)argc;
  goto_bindir(*argv);
  if ((errcode = setjmp(joystick.env)) != 0)
    return (cleanall(&joystick, errcode));
  initall(&joystick);
  return (bunny_loop(joystick.win, 25, &joystick) == EXIT_ON_ERROR ? EXIT_FAILURE : EXIT_SUCCESS);
}
