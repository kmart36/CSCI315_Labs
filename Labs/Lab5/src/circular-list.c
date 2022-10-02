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
#include <stdio.h>
#include "circular-list.h" 

#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t access;
sem_t full;
sem_t empty;

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;

  pthread_mutex_init(&access, NULL);
  sem_init(&empty, 0, size);
  sem_init(&full, 0, 0);
  
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if (l->elems == l->size) {
    return -1;
  }

  sem_wait(&empty);
  pthread_mutex_lock(&access);
  
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

  pthread_mutex_unlock(&access);
  sem_post(&full);
  
  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  if (l->elems == 0) {
    return -1;
  }

  sem_wait(&full);
  pthread_mutex_lock(&access);
  
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

  pthread_mutex_unlock(&access);
  sem_post(&empty);
  
  return 0;
}
