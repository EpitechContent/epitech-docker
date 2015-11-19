
#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		"../../include/lapin.h"

int			main(int		argc,
			     char		**argv)
{
  t_bunny_ini		*ini;
  t_bunny_ini_scope	*scope;
  char			buffer[64];
  int			i;

  for (i = 1; i < argc; ++i)
    {
      if ((ini = bunny_load_ini(argv[1])) == NULL)
	{
	  fprintf(stderr, "%s: Error while loading INI file.\n", *argv);
	  continue;
	}

      for (scope = bunny_ini_first(ini); scope != last_scope; scope = bunny_ini_next(ini, scope))
	{
	  printf("[%s]\n", bunny_ini_scope_name(ini, scope));
	  printf("type exist ? = %s\n", bunny_ini_scope_get_field(scope, "type", 0));
	}

      if (bunny_save_ini(ini, "dump") == false)
	{
	  fprintf(stderr, "%s: Error while saving INI file.\n", *argv);
	  continue;
	}

      snprintf(&buffer[0], 64, "cat %s", argv[i]);
      printf("Original file:\n");
      system(&buffer[0]);

      printf("Regenerated file with edited field:\n");
      system("cat dump");

      bunny_delete_ini(ini);
    }
  system("rm -f dump");
  return (EXIT_SUCCESS);
}

