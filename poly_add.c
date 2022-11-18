#include <stdio.h>
#include <stdlib.h>

struct term {
  int coef;
  int pow;
  struct term *next;
};

void free_poly(struct term *poly) {
  if (!poly) {
    return;
  } else {
    while (!poly -> next) {
      free(poly -> next);
    }
    free(poly);
  }
}

void create_polynomial(struct term **poly, int coef, int pow) {
  struct term *temp1, *temp2;
  temp1 = *poly;

  if (temp1 == NULL) {
    temp2 = (struct term *) malloc(
        sizeof(struct term));
    temp2 -> coef = coef;
    temp2 -> pow = pow;
    *poly = temp2;
    temp2 -> next = NULL;
  } else {
    temp2 -> next = (struct term *) malloc(
        sizeof(struct term));
    temp2 = temp2 -> next;
    temp2 -> coef = coef;
    temp2 -> pow = pow;
    temp2 -> next = NULL;
  }
}

void poly_add(struct term **pol, struct term *poly1, struct term *poly2) {
  struct term *temp = (struct term *)malloc(sizeof(struct term));
  temp -> next = NULL;
  *pol = temp;

  while (poly1 && poly2) {
    if (poly1 -> pow > poly2 -> pow) {
      temp -> coef = poly1 -> coef;
      temp -> pow = poly1 -> pow;
      poly1 = poly1 -> next;
    } else if (poly1 -> pow < poly2 -> pow) {
      temp -> coef = poly2 -> coef;
      temp -> pow = poly2 -> pow;
      poly2 = poly2 -> next;
    } else {
      temp -> coef = poly1 -> coef + poly2 -> coef;
      temp -> pow = poly1 -> pow;
      poly1 = poly1 -> next;
      poly2 = poly2 -> next;
    }

    if (poly1 && poly2) {
      temp -> next = (struct term *)malloc(sizeof(struct term));
      temp = temp -> next;
      temp -> next = NULL;
    }
  }
  
  while (poly1 || poly2) {
    temp -> next = (struct term *)malloc(sizeof(struct term));
    temp = temp -> next;
    temp -> next = NULL;

    if (poly1) {
      temp -> coef = poly1 -> coef;
      temp -> pow = poly1 -> pow;
      poly1 = poly1 -> next;
    } else if (poly2) {
      temp -> coef = poly2 -> coef;
      temp -> pow = poly2 -> pow;
      poly2 = poly2 -> next;
    }
  }
}

void display_polynomial(struct term *poly) {
  while (poly != NULL) {
    printf("%d x^%d", poly -> coef, poly->pow);
    poly = poly->next;
    if (poly != NULL) {
      printf(" + ");
    }
  }
}

static void test(struct term *poly1, struct term *poly2, struct term *poly3) {
  printf("polynomial");
  create_polynomial(&poly1, 5, 2);
  create_polynomial(&poly1, 3, 1);
  create_polynomial(&poly1, 2, 0);
  display_polynomial(poly1);

  poly_add(&poly2, poly1, poly2);
  printf("\n");
  
  free_poly(poly1);
}

int main(void) {
  struct term *poly1 = NULL, *poly2=NULL, *poly3=NULL;
  test(poly1, poly2, poly3);
  return 0;
}
