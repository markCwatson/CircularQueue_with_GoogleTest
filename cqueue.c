#include "cqueue.h"

void cqueue_init(cqueue_s *s, size_t init_size, size_t elem_size, void(*free_callback)(void *))
{
	assert(elem_size > 0);
	
	s->elem_size = elem_size;
	s->count = 0;
	s->size = init_size;
	s->elems = malloc((init_size + 1) * elem_size);
	s->pos_tail = 0;
	s->pos_head = s->pos_tail;
	s->free_callback = free_callback;
	
	assert(s->elems != NULL);
}

void cqueue_close(cqueue_s *s)
{
	if (s == NULL)
	{
		return;	
	}
	
	if (s->free_callback != NULL)
	{
		for (int i = 0; i < s->count; i++)
		{
			s->free_callback((int *)s->elems + i * s->elem_size);
		}
	}
	
	free(s->elems);
}

void cqueue_enque(cqueue_s *s, void *source)
{	
	if ((s == NULL) || (source == NULL))
	{
		return;	
	}
	
	// copy element to the tail and increment the counter
	void *target = (void *)s->elems + s->pos_tail * s->elem_size;
	
	memcpy(target, source, s->elem_size);	
	
	if (++(s->count) >= s->size)
	{
		s->count = s->size;
	}
	
	// increment tail and wrap around if the end is reached (via modulo operation)
	s->pos_tail = (s->pos_tail + 1) % (s->size + 1);
	
	// check if the head and tail have collided
	if (s->pos_head == s->pos_tail)
	{
		// If so, move head up one to make room for tail.
		// This discards the oldest entery which was previously at the head.
		// This makes it a circular queue :)
		s->pos_head = (s->pos_head + 1) % (s->size + 1);
	}
}

void cqueue_deque(cqueue_s *s, void *target)
{
	if ((s == NULL) || (target == NULL))
	{
		return;	
	}
	
	// check if queue is empty
	if (s->pos_head == s->pos_tail)
	{
		// queue empty: nothing to do
		return;
	}
	
	// copy item from head of queue
	void *source = (void *)s->elems + s->pos_head * s->elem_size;
	
	memcpy(target, source, s->elem_size);
	
	// move head up one, wrap around if necessary (via modulo), decrement count
	s->pos_head = (s->pos_head + 1) % (s->size + 1);
	
	// check if the queue is now empty
	if (s->pos_head == s->pos_tail)
	{
		s->count = 0;
	}
	else
	{
		s->count--;
	}
}

void cqueue_reset(cqueue_s *s)
{	
    if (s == NULL)
    {
        return;	
    }
	
    s->count = 0;
    s->pos_tail = 0;
    s->pos_head = s->pos_tail;
}

void cqueue_peek(cqueue_s *s, void *elem_addr)
{
	if ((s == NULL) || (elem_addr == NULL))
	{
		return;	
	}
	
	if (s->pos_head == s->pos_tail)
	{
		// queue empty: nothing to do
		return;
	}
	
	void *source = (void *)s->elems + s->pos_head * s->elem_size;
	
	memcpy(elem_addr, source, s->elem_size);
}

uint8_t cqueue_is_empty(cqueue_s *s)
{
	return (s->pos_head == s->pos_tail) ? 1 : 0;
}

uint8_t cqueue_is_full(cqueue_s *s)
{
	return (s->count == s->size) ? 1 : 0;
}

size_t cqueue_get_size(cqueue_s *s)
{
	return s->count;
}
