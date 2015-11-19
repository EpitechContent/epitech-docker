
#include		<lapin.h>
#include		<unistd.h>

size_t			dstrlen(const char	*str)
{
  const char		*s = str;

  while (*str++);
  return (str - s);
}

int			main(void)
{
  const char		*str;
  t_bunny_ini		*ini;
  int			i;

  i = 0;
  if ((ini = bunny_load_ini("blob.ini")) == NULL)
    return (EXIT_FAILURE);
  while ((str = bunny_ini_get_field(ini, "section", "field", i++)) != NULL)
    {
      write(1, str, dstrlen(str));
      write(1, "\n", 1);
    }
  bunny_delete_ini(ini);
  return (EXIT_SUCCESS);
}
