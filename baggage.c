
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "baggage.h"

struct BaggageList baggageList;

void initBaggageList() {
    baggageList.head = NULL;
    baggageList.tail = NULL;
}

struct BaggageNode* createBaggageNode() {
    struct BaggageNode* newNode = (struct BaggageNode*)malloc(sizeof(struct BaggageNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int baggageExists(int id) {
    struct BaggageNode* temp = baggageList.head;
    while (temp) {
        if (temp->baggageID == id) return 1;
        temp = temp->next;
    }
    return 0;
}

void addBaggage() {
    struct BaggageNode* newNode;
    int position, i, total;

    total = 0;
    struct BaggageNode* temp = baggageList.head;
    while (temp) { total++; temp = temp->next; }

    printf("\n");
    boxLine();
    boxTitle("BAGGAGE CHECK-IN");
    boxSep();
    printf("  Total bags: %d\n", total);
    printf("  \n");
    printf("  Check-in position:\n");
    printf("    1 = Priority / Fragile Baggage\n");
    printf("    %d = Normal Check-in\n", total + 1);
    printf("    Any number between = Insert at that position\n");
    boxLine();
    printf("  Select position: ");
    scanf("%d", &position);

    if (position < 1 || position > total + 1) {
        msgERR("Invalid position!"); return;
    }

    newNode = createBaggageNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("BAGGAGE DETAILS");
    boxSep();
    printf("  | Baggage ID      : "); scanf("%d", &newNode->baggageID);
    if (baggageExists(newNode->baggageID)) {
        msgERR("Baggage ID exists!"); free(newNode); return;
    }
    printf("  | Passenger ID    : "); scanf("%d", &newNode->passengerID);
    printf("  | Owner Name      : "); scanf(" %[^\n]", newNode->ownerName);
    printf("  | Weight (kg)     : "); scanf("%f", &newNode->weight);
    sprintf(newNode->tag, "TAG-%04d", newNode->baggageID);
    manualStrCpy(newNode->status, "Checked-In");
    boxLine();

    if (newNode->weight > 30.0) msgWARN("Baggage over 30kg! Extra charges apply.");

    if (position == 1) {
        if (!baggageList.head) {
            baggageList.head = newNode;
            baggageList.tail = newNode;
        } else {
            newNode->next = baggageList.head;
            baggageList.head->prev = newNode;
            baggageList.head = newNode;
        }
        msgOK("Priority baggage checked-in.");
    } else if (position == total + 1) {
        if (!baggageList.head) {
            baggageList.head = newNode;
            baggageList.tail = newNode;
        } else {
            baggageList.tail->next = newNode;
            newNode->prev = baggageList.tail;
            baggageList.tail = newNode;
        }
        msgOK("Baggage checked-in normally.");
    } else {
        struct BaggageNode* tempNode = baggageList.head;
        for (i = 1; i < position - 1; i++) tempNode = tempNode->next;
        newNode->next = tempNode->next;
        newNode->prev = tempNode;
        if (tempNode->next) tempNode->next->prev = newNode;
        tempNode->next = newNode;
        if (!newNode->next) baggageList.tail = newNode;
        msgOK("Baggage inserted at specified position.");
    }
}

void removeBaggage() {
    int id;
    struct BaggageNode* temp;

    if (!baggageList.head) { msgERR("No baggage."); return; }

    printf("\n");
    boxLine();
    boxTitle("REMOVE BAGGAGE");
    boxSep();
    printf("  Enter Baggage ID to remove: ");
    scanf("%d", &id);
    boxLine();

    temp = baggageList.head;
    while (temp) {
        if (temp->baggageID == id) {
            if (temp->prev) temp->prev->next = temp->next;
            else baggageList.head = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            else baggageList.tail = temp->prev;
            free(temp);
            msgOK("Baggage removed.");
            return;
        }
        temp = temp->next;
    }
    msgERR("Baggage ID not found.");
}

void displayBaggageForward() {
    struct BaggageNode* temp;
    int count = 0;

    if (!baggageList.head) { msgERR("No baggage."); return; }

    printf("\n");
    boxLine();
    boxTitle("BAGGAGE - CHECK-IN ORDER");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-7s |\n",
           "TAG", "PAX ID", "OWNER", "WEIGHT");
    boxSep();

    temp = baggageList.head;
    while (temp) {
        printf("  | %-10s | %-6d | %-18s | %-7.1f |\n",
            temp->tag, temp->passengerID, temp->ownerName, temp->weight);
        temp = temp->next;
        count++;
    }
    boxSep();
    char msg[50];
    sprintf(msg, "TOTAL BAGS: %d", count);
    boxTitle(msg);
    boxLine();
}

void displayBaggageBackward() {
    struct BaggageNode* temp;
    int count = 0;

    if (!baggageList.tail) { msgERR("No baggage."); return; }

    printf("\n");
    boxLine();
    boxTitle("BAGGAGE - LOADING ORDER");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-7s |\n",
           "TAG", "PAX ID", "OWNER", "WEIGHT");
    boxSep();

    temp = baggageList.tail;
    while (temp) {
        printf("  | %-10s | %-6d | %-18s | %-7.1f |\n",
            temp->tag, temp->passengerID, temp->ownerName, temp->weight);
        temp = temp->prev;
        count++;
    }
    boxSep();
    char msg[50];
    sprintf(msg, "TOTAL BAGS: %d", count);
    boxTitle(msg);
    boxLine();
}

void baggageStatistics() {
    struct BaggageNode* temp;
    int count = 0;
    float total = 0, heaviest = 0;

    temp = baggageList.head;
    while (temp) {
        count++;
        total += temp->weight;
        if (temp->weight > heaviest) heaviest = temp->weight;
        temp = temp->next;
    }

    printf("\n");
    boxLine();
    boxTitle("BAGGAGE STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Bags", count);
    printf("  | %-30s : %-29.1f  |\n","Total Weight (kg)", total);
    if (count > 0) printf("  | %-30s : %-29.1f  |\n","Average Weight (kg)", total / count);
    printf("  | %-30s : %-29.1f  |\n","Heaviest Bag (kg)", heaviest);
    boxLine();
}

void baggageMenu() {
    int c;
    do {
        printHeader("BAGGAGE SERVICES");
        boxDbl();
        boxEmpty();
        boxTitle("BAGGAGE SERVICES");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Baggage");
        boxRow("  2.  Remove Baggage");
        boxRow("  3.  View Baggage (Check-in Order)");
        boxRow("  4.  View Baggage (Loading Order)");
        boxRow("  5.  Baggage Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  BAGGAGE > "); scanf("%d", &c);
        switch(c) {
            case 1: addBaggage(); break;
            case 2: removeBaggage(); break;
            case 3: displayBaggageForward(); break;
            case 4: displayBaggageBackward(); break;
            case 5: baggageStatistics(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
