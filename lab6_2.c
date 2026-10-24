
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff, exp;
    struct Node *prev, *next;
} Node;

Node *createNode(int coeff, int exp) {
    Node *newNode = malloc(sizeof(Node));

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertEnd(Node **head, int coeff, int exp) {
    if (coeff == 0)
        return;

    Node *newNode = createNode(coeff, exp);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

Node *readPolynomial() {
    Node *head = NULL;
    int n, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    printf("Enter coefficient and exponent in descending order:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertEnd(&head, coeff, exp);
    }

    return head;
}

Node *addPolynomials(Node *p1, Node *p2) {
    Node *result = NULL;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            int sum = p1->coeff + p2->coeff;

            if (sum != 0)
                insertEnd(&result, sum, p1->exp);

            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp > p2->exp) {
            insertEnd(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else {
            insertEnd(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertEnd(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertEnd(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

void display(Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node *temp = head;

    while (temp != NULL) {
        if (temp != head)
            printf(temp->coeff >= 0 ? " + " : " - ");
        else if (temp->coeff < 0)
            printf("-");

        int coeff = abs(temp->coeff);

        if (temp->exp == 0)
            printf("%d", coeff);
        else if (temp->exp == 1)
            printf("%dx", coeff);
        else
            printf("%dx^%d", coeff, temp->exp);

        temp = temp->next;
    }

    printf("\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    printf("First Polynomial:\n");
    Node *p1 = readPolynomial();

    printf("\nSecond Polynomial:\n");
    Node *p2 = readPolynomial();

    Node *sum = addPolynomials(p1, p2);

    printf("\nPolynomial 1: ");
    display(p1);

    printf("Polynomial 2: ");
    display(p2);

    printf("Sum: ");
    display(sum);

    freeList(p1);
    freeList(p2);
    freeList(sum);

    return 0;
}
