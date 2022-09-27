/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include "circular-list.h" 

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if (l->elems == l->size) {
    return -1;
  }

  if (l->start == -1) {
    l->start = l->end = 0;
    l->buffer[l->start] = i;
  }

  else if (l->end == l->size - 1 && l->start != 0) {
    l->end = 0;
    l->buffer[l->end] = i;
  }

  else {
    l->end++;
    l->buffer[l->end] = i;
  }
  
  l->elems++;

  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  if (l->elems == 0) {
    return -1;
  }

  *i = l->buffer[l->start];
  l->buffer[l->start] = 0;
  l->elems--;

  if (l->start == l->end) {
    l->start = -1;
    l->end = -1;
  }

  else if (l->start == l->size-1) {
    l->start = 0;
  }

  else {
    l->start++;
  }

  return 0;
}
