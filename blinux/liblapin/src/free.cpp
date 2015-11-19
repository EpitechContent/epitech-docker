// Jason Brillante "Damdoshi"
// Epitech 1999-2042
//
// LibLapin

#include		<stddef.h>
#include		<signal.h>
#include		<unistd.h>
#include		"lapin_private.h"

void			check_memory_state(void);
struct memhead		*memory_head(void);
extern size_t		border0;
extern size_t		border1;

void			bunny_free(void		*data)
{
  if (data == NULL)
    return ;
  struct memchunk	*chunk;

  /// Get the chunk from the data pointer
  chunk = (struct memchunk*)&((char*)data)[-sizeof(struct memchunk)];
  if (chunk->border0 != border0 || chunk->border1 != border1)
    {
      fprintf(stderr, "Bad pointer or altered memory detected while freeing 0x%p.\n", data);
      check_memory_state();
      kill(getpid(), SIGSEGV); /* die Die DIE! */
      while (1);
    }
  struct memtree	*tree;

  tree = chunk->tree;
  /// Remove from the allocated list
  if (chunk->prev == chunk->next)
    tree->allocated = NULL;
  else
    {
      chunk->prev->next = chunk->next;
      chunk->next->prev = chunk->prev;
      if (tree->allocated == chunk)
	tree->allocated = chunk->next;
    }

  /// Add inside the freed list
  if (tree->freed == NULL)
    {
      chunk->next = chunk;
      chunk->prev = chunk;
    }
  else
    {
      chunk->next = tree->freed;
      chunk->prev = tree->freed->prev;
      chunk->prev->next = chunk;
      chunk->next->prev = chunk;
    }
  tree->freed = chunk;

  /// Stats
  struct memhead	*head;

  head = memory_head();
  head->alloc -= 1;
  head->total -= tree->chunk_size;
}

// avec un prev, l'action de retirer serait plus rapide
