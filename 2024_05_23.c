#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Term {
    int coeff;
    int exp;
    struct Term *next;
} Term;

typedef struct {
    Term *head;
} Polynomial;

Polynomial inputPolynomial() {
    Polynomial poly;
    poly.head = NULL;
    Term *last = NULL;
    char input[256];

    printf("다항식을 입력하세요 (예: 2x3+2x1+3x0): ");
    scanf("%s", input);

    char *term = strtok(input, "+");
    while (term != NULL) {
        Term *newTerm = (Term *)malloc(sizeof(Term));
        sscanf(term, "%dx%d", &newTerm->coeff, &newTerm->exp);
        newTerm->next = NULL;

        if (poly.head == NULL) {
            poly.head = newTerm;
        } else {
            last->next = newTerm;
        }
        last = newTerm;

        term = strtok(NULL, "+");
    }

    return poly;
}

Polynomial addPolynomials(Polynomial p1, Polynomial p2) {
    Polynomial result;
    result.head = NULL;
    Term *last = NULL;
    Term *t1 = p1.head;
    Term *t2 = p2.head;

    while (t1 != NULL || t2 != NULL) {
        Term *newTerm = (Term *)malloc(sizeof(Term));
        newTerm->next = NULL;

        if (t1 == NULL) {
            newTerm->coeff = t2->coeff;
            newTerm->exp = t2->exp;
            t2 = t2->next;
        } else if (t2 == NULL) {
            newTerm->coeff = t1->coeff;
            newTerm->exp = t1->exp;
            t1 = t1->next;
        } else if (t1->exp > t2->exp) {
            newTerm->coeff = t1->coeff;
            newTerm->exp = t1->exp;
            t1 = t1->next;
        } else if (t1->exp < t2->exp) {
            newTerm->coeff = t2->coeff;
            newTerm->exp = t2->exp;
            t2 = t2->next;
        } else {
            newTerm->coeff = t1->coeff + t2->coeff;
            newTerm->exp = t1->exp;
            t1 = t1->next;
            t2 = t2->next;
        }

        if (result.head == NULL) {
            result.head = newTerm;
        } else {
            last->next = newTerm;
        }
        last = newTerm;
    }

    return result;
}

void printPolynomial(Polynomial poly) {
    Term *current = poly.head;
    while (current != NULL) {
        printf("%dx^%d", current->coeff, current->exp);
        if (current->next != NULL) {
            printf(" + ");
        }
        current = current->next;
    }
    printf("\n");
}

void freePolynomial(Polynomial poly) {
    Term *current = poly.head;
    while (current != NULL) {
        Term *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Polynomial p1, p2, sum;

    printf("첫 번째 다항식을 입력하세요:\n");
    p1 = inputPolynomial();

    printf("두 번째 다항식을 입력하세요:\n");
    p2 = inputPolynomial();

    sum = addPolynomials(p1, p2);

    printf("두 다항식의 합은:\n");
    printPolynomial(sum);

    freePolynomial(p1);
    freePolynomial(p2);
    freePolynomial(sum);

    return 0;
}