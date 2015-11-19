
#include		<stdio.h>
#include		<lapin.h>
#include		<assert.h>

extern int		memory_check;
void			set_max_heap_size(size_t	data);

int			main(void)
{
  char			*buf[5000];
  int			i;

  memory_check = 1;
  set_max_heap_size(10);

  puts("Allocating 5000 and then freeing 5000.");
  for (i = 0; i < 5000; ++i)
    if ((buf[i] = bunny_malloc(i / 10 + 1)) == NULL)
      {
	puts("Memory exhausted");
	return (EXIT_FAILURE);
      }
  for (i = 0; i < 5000; ++i)
    bunny_free(buf[i]);

  puts("Allocating 1 and freeing 1 5000 time.");
  for (i = 0; i < 5000; ++i)
    bunny_free(bunny_malloc(200 + i / 10));

  puts("Allocating 2500, freeing 2000, allocating 2500, freeing 3000.");
  for (i = 0; i < 2500; ++i)
    if ((buf[i] = bunny_malloc(rand() % 1024 + 32)) == NULL)
      {
	puts("Memory exhausted");
	return (EXIT_FAILURE);
      }
  for (i = 0; i < 2000; ++i)
    bunny_free(buf[i]);
  for (i = 2500; i < 5000; ++i)
    if ((buf[i] = bunny_malloc(rand() % 1024 + 32)) == NULL)
      {
	puts("Memory exhausted");
	return (EXIT_FAILURE);
      }
  for (i = 2000; i < 5000; ++i)
    bunny_free(buf[i]);

  puts("Calloc");
  for (i = 0; i < 5000; ++i)
    if ((buf[i] = bunny_calloc(rand() % 63 + 1, rand() % 15 + 1)) == NULL)
      {
	puts("Memory exhausted");
	return (EXIT_FAILURE);
      }
  puts("Realloc");
  for (i = 0; i < 5000; ++i)
    if ((buf[i] = bunny_realloc(buf[i], rand() % 63 + 1)) == NULL)
      {
	puts("Memory exhausted");
	return (EXIT_FAILURE);
      }
  for (i = 0; i < 5000; ++i)
    bunny_free(buf[i]);

  puts("Allocating 1 and altering 1.");
  if ((buf[0] = bunny_malloc(64)) == NULL)
    {
      puts("Memory exhausted");
      return (EXIT_FAILURE);
    }
  buf[0][-1] = 0;

  puts("Try to allocate a too wide chunk.");
  assert((buf[1] = bunny_malloc(1024 * 1024 * 1024)) == NULL);

  puts("Try to exhaust the memory with a lot a medium chunk.");
  for (i = 0; i < 1024 * 1024; ++i)
    if (bunny_malloc(1024) == NULL)
      {
	puts("Memory exhausted.");
	return (0);
      }

  return (0);
}

