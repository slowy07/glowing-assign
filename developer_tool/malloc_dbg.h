#ifndef MALLOC_DBG_H
#define MALLOC_DBG_H

#define malloc(bytes) malloc_dbg(bytes, __LINE__, __FILE__, __FUNCTION__)

#define calloc(elemCount, elemSize) calloc_dbg(elemCount, elemSize, __LINE__, __FILE__, __FUNCTION__)

#define free(ptr) free_dbg(ptr)
void* malloc_dbg(size_t bytes, int line, const char* filename, const char* functionName);

void* calloc_dbg(size_t elementCount, size_t elementSize, int line, const char* filename, const char* functionName);

void free_dbg(void* ptrToFree);

void printLeaks(void);
#endif
