/* Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2015
**
*/ 

#include		<stdio.h>
#include		<lapin.h>

void			*malloc(size_t	s)
{
  puts(__PRETTY_FUNCTION__);
  return (bunny_malloc(s));
}

void			*calloc(size_t	a,
				size_t	b)
{
  puts(__PRETTY_FUNCTION__);
  return (bunny_calloc(a, b));
}

void			*realloc(void	*a,
				 size_t	b)
{
  puts(__PRETTY_FUNCTION__);
  return (bunny_realloc(a, b));
}

void			free(void	*a)
{
  puts(__PRETTY_FUNCTION__);
  bunny_free(a);
}

