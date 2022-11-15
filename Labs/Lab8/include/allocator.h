#ifndef _ALLOC_H_
#define _ALLOC_H_
 
/**
 * Initializes two doubly-linked lists, one for free memory and one for allocated memory.
 *
 * @param size bytes of total memory system
 * @return 0, -1 upon failure.
 */
int allocator_init(size_t size);

/**
 * Equivalent to malloc. Finds chunk of memory in free list to use for a process that needs
 * size bytes. 
 *
 * @param type of allocation policy to use for allocation 
 * @param size bytes needed for allocation for a process
 */
void *allocate(int type, size_t size);

/**
 * Equivalent to free. Finds a process in the allocated list and puts that memory back in the
 * free list.
 *
 * @param ptr pointer to the address of the process
 * @return 0, -1 upon failure.
 */
int deallocate(void *ptr);

/**
 * Prints both free_list and allocated_list for testing.
 */

void print_lists(void);

/**
 * Computes the average fragmentation created in memory
 */
double average_frag(void);

#endif /* _ALLOC_H_ */
