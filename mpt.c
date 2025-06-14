#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 118

struct Element {
    int atomicNumber;
    char name[30];
    char symbol[5];
    char configuration[100];
    char discoveredBy[100];
    char charge[10];
};

typedef struct Element Element;

void displayElement(const Element *e) {
    printf("\nName: %s\nSymbol: %s\nAtomic Number: %d\nElectronic Configuration: %s\nDiscovered By: %s\nCharge: %s\n",
           e->name, e->symbol, e->atomicNumber, e->configuration, e->discoveredBy, e->charge);
}

int loadElements(Element elements[]) {
    FILE *fp = fopen("periodic_table.txt", "r");
    if (!fp) {
        printf("\nError: periodic_table.txt not found.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &elements[count].atomicNumber,
                  elements[count].name,
                  elements[count].symbol,
                  elements[count].configuration,
                  elements[count].discoveredBy,
                  elements[count].charge) == 6 && count < MAX_ELEMENTS) {
        count++;
    }
    fclose(fp);
    return count;
}

void searchByAtomicNumber(Element elements[], int total) {
    int num;
    printf("\nEnter atomic number (1-118): ");
    scanf("%d", &num);
    if (num >= 1 && num <= total) {
        displayElement(&elements[num - 1]);
    } else {
        printf("\nInvalid atomic number.\n");
    }
}

void listAllElements(Element elements[], int total, int index) {
    if (index >= total) return;
    displayElement(&elements[index]);
    listAllElements(elements, total, index + 1);
}

int main() {
    Element elements[MAX_ELEMENTS];
    int totalElements = loadElements(elements);

    if (totalElements == 0) return 1;

    int choice;
    do {
        printf("\n--- Modern Periodic Table ---\n");
        printf("1. Search by Atomic Number\n");
        printf("2. Display All Elements\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchByAtomicNumber(elements, totalElements);
                break;
            case 2:
                listAllElements(elements, totalElements, 0);
                break;
            case 3:
                printf("\nExiting Periodic Table...\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
