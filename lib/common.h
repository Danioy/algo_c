/**
 * common.h for general purpose.
 * I am trying to implement a small garbage collect stack.
 * Maybe replace it with a hash table latter.
 */

#ifndef TIGER_COMMON_H
#define TIGER_COMMON_H

/**
 * Error Message stat.
 *
 */
enum cc_stat {
   CC_OK             = 0,
   CC_ERR_ALLOC      = 1,
   CC_ERR_OUTRANGE   = 2,
   CC_ERR_OVERFLOW   = 3,
   CC_ERR_NOTIN      = 4
};

#define BUF_SIZE 4096

/**
 * Implemention of a tiny gabage collector.
 *
 */

void *
malloc_s(size_t bytes);

void *
calloc_s(size_t num, size_t size);

enum cc_stat
free_s(void *ptr);

void free_all();

#endif   /* TIGER_COMMON_H*/
