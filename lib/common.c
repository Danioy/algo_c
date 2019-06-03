#include <stdlib.h>
#include <string.h>
#include "common.h"

struct gc_chunk {
    void **buff;
    size_t capacity;
    size_t count;
};

struct gc_chunk *gc;

/* flage to ensure gc only initialized once. */
size_t GC_INITED = 0;

enum cc_stat
gc_init() {
    gc = malloc(sizeof *gc);
    if (!gc) return CC_ERR_ALLOC;

    void *buf = calloc(BUF_SIZE, sizeof(void *));
    if( !buf ) return CC_ERR_ALLOC;

    memset(buf, 0xaa, BUF_SIZE * sizeof(void *));

    gc->buff = buf;
    gc->count = 0;
    gc->capacity = BUF_SIZE;

    GC_INITED = 1;

    return CC_OK;
}

void *
malloc_s(size_t bytes) {

    void *out;
    if ( !GC_INITED ) {
        enum cc_stat ok = gc_init();
        if ( ok != CC_OK ) return NULL;
    }

    if (gc->count >= gc->capacity - 1) return NULL;

    out = malloc(bytes);
    if ( out == NULL ) return NULL;

    gc->buff[gc->count] = out;
    gc->count++;

    return out;
}

void *
calloc_s(size_t num, size_t size){

    void *out;

    if( !GC_INITED ) {
        enum cc_stat ok = gc_init();
        if (ok != CC_OK ) return NULL;
    }

    if (gc->count >= gc->capacity - 1) return NULL;

    out = calloc(num, size);
    if ( out == NULL ) return NULL;

    gc->buff[gc->count] = out;
    gc->count++;

    return out;
}

enum cc_stat
free_s( void *ptr ) {

    size_t sp;
    for (sp = 0; sp < gc->count; sp++) {
        if (gc->buff[sp] == ptr) break;
    }
    if (sp >= gc->capacity) return CC_ERR_NOTIN;

    free(ptr);

    memmove(gc->buff+sp, gc->buff+sp+1, (gc->count-sp)*sizeof(void *));
    gc->count--;

    return CC_OK;
}

void free_all() {
    for (size_t i = 0; i < gc->count; i++)
        free(gc->buff[i]);
    gc->count = 0;
    free(gc->buff);
    free(gc);
    GC_INITED = 0;
}
