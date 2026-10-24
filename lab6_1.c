
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *first = NULL, *last = NULL;

void insertEnd(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;

    if (first == NULL) {
        first = last = newNode;
        newNode->next = first;
    } else {
        newNode->next = first;
        last->next = newNode;
        last = newNode;
    }
}

void deleteBegin() {
    if (first == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = first;

    if (first == last) {
        first = last = NULL;
    } else {
        first = first->next;
        last->next = first;
    }

    free(temp);
}

void deleteEnd() {
    if (first == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = last;

    if (first == last) {
        first = last = NULL;
    } else {
        Node *curr = first;

        while (curr->next != last)
            curr = curr->next;

        last = curr;
        last->next = first;
    }

    free(temp);
}

void display() {
    if (first == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *curr = first;

    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != first);

    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Insert at End");
        printf("\n2. Delete from Beginning");
        printf("\n3. Delete from End");
        printf("\n4. Display");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertEnd(value);
                break;

            case 2:
                deleteBegin();
                break;

            case 3:
                deleteEnd();
                break;

            case 4:
                display();
                continue;

            case 5:
                return 0;

            default:
                printf("Invalid choice\n");
                continue;
        }

        display();
    }
}
