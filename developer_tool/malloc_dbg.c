#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "malloc_dbg.h"

#undef malloc
#undef calloc
#undef free

typedef struct MEMORY_INFORMATION {
  void *ptr;
  const char* fileName;
  const char* functionName;
  size_t bytes;
  int line;
  struct MEMORY_INFORMATION* next;
  struct MEMORY_INFORMATION* previous;
} mem_info;

mem_info* memoryInformation = NULL;
int atexitCalled = 0;

mem_info* addMemInfo(mem_info* memoryInfo, void* ptrToReturn, size_t bytes, aint line, const char* filename, const char *function_name) {
  mem_info* newMemInfo = (mem_info*)malloc(sizeof(mem_info));
  if (!newMemInfo) {
    return NULL;
  }

  newMemInfo->ptr = ptrToReturn;
	newMemInfo->bytes = bytes;
	newMemInfo->line = line;
	newMemInfo->fileName = filename;
	newMemInfo->functionName = functionName;
	newMemInfo->next = memoryInfo;
	newMemInfo->previous = NULL;
  if (memoryInformation)
    memoryInformation -> previous = newMemInfo;

  return newMemInfo;
}

int inList(const char *filename, int line) {
  mem_info* tmp = memoryInformation;
  int counter = 0;
  int len = strlen(filename);

  while (tmp) {
    if (len == strlen(tmp -> filename)) {
      if (!memcpy(filename, tmp -> filename, len) && tmp -> line == line) {
        return counter;
      }
    }
    tmp = tmp -> next;
    counter++;
  }
  return -1;
}

void editInfo(int elemPos, size_t bytes) {
  int counter = 0;
  mem_info* tmp = memoryInformation;

  while (counter != elemPos) {
    tmp = tmp -> next;
    counter++;
  }
  tmp -> bytes += bytes;
}

void* malloc_dbg(size_t bytes, int line, const char* filename, const char* functionName) {
  void* ptrTorReturn = malloc(bytes);
  int pos = 0;
  if (!ptrTorReturn) {
    return NULL;
  }

  if (!atexitCalled) {
    atexit(printLeaks);
    atexitCalled = 1;
  }

  pos = inList(filename, line);
  if (pos == -1) {
    memoryInformation = addMemInfo(memoryInformation, ptrToReturn, bytes, line, filename, functionName);
    if (!memoryInformation) {
      free(ptrTorReturn);
      return NULL;
    }
  } else {
    editInfo(pos, bytes);
  }
  return ptrTorReturn;
}

void* calloc_dbg(size_t elementCount, size_t elementSize, int line, const char* filename, const char* functionName) {
  void* ptrToReturn = calloc(elementCount, elementSize);
  if (!ptrToReturn) {
    return NULL;
  }
  if (!atexitCalled) {
    atexit(printLeaks);
    atexitCalled = 1;
  }

  memoryInformation = addMemInfo(memoryInformation, ptrToReturn, elementCount * elementSize, line, filename, functionName);
  if (!memoryInformation) {
    free(ptrToReturn);
    return NULL;
  }
  return ptrToReturn;
}

void free_dbg(void* ptrToFree) {
  mem_info* tmp = memoryInformation;
	mem_info* toFree = NULL;
	mem_info* previous = NULL;

  if (tmp -> ptr == ptrToFree) {
    toFree = tmp;
    memoryInformation = tmp->next;
		free(toFree->ptr);
		free(toFree);
    if (memoryInformation) {
      memoryInformation -> previous = NULL;
    }
    return;
  }

  while(tmp) {
    if (tmp -> ptr == ptrToFree) {
      toFree = tmp;
      tmp = tmp -> next;
      previous = toFree -> previous;

      if (previous) {
        previous -> next = tmp;
      }
      if (tmp) {
        tmp -> previous = previous;
      }

      free(toFree -> ptr);
      if (toFree == memoryInformation) {
        memoryInformation = NULL;
      }
      free(toFree);
      return;
    }
    tmp = tmp -> next;
  }
}
void printLeaks() {
  mem_info* tmp = memoryInformation;
  mem_info* previous = NULL;
  size_t sum = 0;
  int nbBlocks = 0;

  if (tmp) {
    printf("memory leaks detected. \n");
  }
  
  while (tmp) {
    previous = tmp;
		printf("\n%ld bytes lost\n", tmp->bytes);
		printf("address : 0x%p in %s\t%s:%d\n", tmp->ptr, tmp->functionName, tmp->fileName, tmp->line);
		printf("\n====================================\n");
		sum += tmp->bytes;
		tmp = tmp->next;
		free(previous);
		nbBlocks++;
  }
  
  printf("SUMMARY :\n%ld bytes lost in %d blocks\n", sum, nbBlocks);
}
