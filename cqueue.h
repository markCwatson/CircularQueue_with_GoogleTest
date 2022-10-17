#ifndef __CQUEUE_H__
#define __CQUEUE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/*
 * Note:	This is a FIFO circular queue.
 *			Items are being added to the "tail",
 *			and items are being taken off of the "head".
 */

typedef struct {
	void *elems;
	size_t elem_size;
	volatile size_t count;
	size_t size;
	size_t pos_head;
	size_t pos_tail;
	void(*free_callback)(void *);
} cqueue_s;

void cqueue_init(cqueue_s *s, size_t init_size, size_t elem_size, void(*free_callback)(void *));
void cqueue_close(cqueue_s *s);
void cqueue_enque(cqueue_s *s, void *elem_addr);
void cqueue_deque(cqueue_s *s, void *elem_addr);
void cqueue_reset(cqueue_s *s);
void cqueue_peek(cqueue_s *s, void *elem_addr);
void cqueue_remove(cqueue_s *s, void *elem_addr);
uint8_t cqueue_is_empty(cqueue_s *s);
uint8_t cqueue_is_full(cqueue_s *s);
size_t cqueue_get_size(cqueue_s *s);

#endif
