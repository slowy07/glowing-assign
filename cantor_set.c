#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cantor_set {
    double start;
    double end;
    struct _cantor_set *next;
} CantorSet;

void propagate(CantorSet *head) {
    if (head == NULL)
        return;
    CantorSet *temp = head;
    CantorSet *newNode = (CantorSet *)malloc(sizeof(CantorSet));

    double diff = (((temp -> end) - (temp -> start)) / 3);
    newNode -> end = temp -> end;
    temp -> end = ((temp -> strt) + diff);
    newNode -> start = (newNode -> end) - diff;
    newNode -> next = temp -> next;
    temp ->  next = newNode;

    propagate(temp -> next -> next);
}

void print(CantorSet *head) {
    CantorSet *temp = head;
    while (temp != NULL) {
        printf("\t");
        printf("[%lf] --", temp -> start);
        printf("[%lf] --", temp -> end);
        temp = temp -> next;
    }
    printf("\n");
}

void free_memmory(CantorSet *head) {
    if (!head)
        return;
    if (head -> next)
        free_memmory(head -> next);
    
    free(head);
}

int main(int argc, char const *argv[]) {
    int start_num, end_num, levels;

    if (argc < 2) {
        printf("enter 3 argument: start_num \t end_num \t leves\n");
        scanf("%d %d %d", &start_num, &end_num, &levels);
    } else {
        start_num = atoi(argv[1]);
        end_num = atoi(argv[2]);
        levels = atoi(argv[3]);
    }
    
    if (start_num < 0 || end_num < 0 || levels < 0) {
        fprintf(stderr, "all number must be positive\n")
        return -1;
    }

    CantorSet head = {.head = start_num, .end = end_num, .next = NULL};

    for (int i = 0; i < levels; i++) {
        printf("level %d\t", i);
        print(&head);
        propagate(&hed);
        printf("\n");
    }
    printf("level %d\t", levels);
    printf(&head);
    free_memmory(head.next);

    return 0;
}
