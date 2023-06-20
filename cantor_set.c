#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cantor_set {
    double start;
    double end;
    struct _cantor_set *next;
} CantorSet;

void propagate(CantorSet *head) {
  CantorSet* temp = head;

  while (temp != NULL) {
    double diff = (temp -> end - temp -> start) / 3;
    CantorSet* newNode = (CantorSet*)malloc(sizeof(CantorSet));
    newNode -> end = temp -> end;
    temp -> end = temp -> start + diff;
    newNode -> start = newNode -> end - diff;
    newNode -> next = temp -> next;
    temp -> next = newNode;
    temp = temp -> next -> next;
  }
}

void print(CantorSet *head) {
  const CantorSet* temp = head;
  while (temp != NULL) {
    printf("\t[%lf] -- [%lf] --", temp -> start, temp -> end);
    temp = temp -> next;
  }
  printf("\n");
}

void free_memmory(CantorSet *head) {
  CantorSet* temp = head;
  while (temp != NULL) {
    CantorSet* nextNode = temp -> next;
    free(temp);
    temp = nextNode;
  }
}

int main(int argc, char const* argv[]) {
  int start_num, end_num, levels;
  if (argc < 4) {
    printf("enter 3 argument: start_num \t end_num \t levels\n");
    scanf("%d %d %d", &start_num, &end_num, &levels);
  } else {
    start_num = atoi(argv[1]);
    end_num = atoi(argv[2]);
    levels = atoi(argv[3]);
  }

  if (start_num < 0 || end_num < 0 || levels < 0) {
    fprintf(stderr, "all numbers must be positive\n");
    return -1;
  }

  CantorSet* head = (CantorSet*)malloc(sizeof(CantorSet));
  head -> start = start_num;
  head -> end = end_num;
  head -> next = NULL;

  for (int i = 0; i <= levels; i++) {
    printf("level %d\t", i);
    print(head);
    propagate(head);
    printf("\n");
  }
  free_memmory(head);
  return 0;
}
