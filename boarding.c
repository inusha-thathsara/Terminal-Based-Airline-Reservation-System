/* boarding.c - Boarding Control (Stack) */
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "boarding.h"

struct Stack boardingStack;

void initStack() {
    boardingStack.top = NULL;
}

struct StackNode* createStackNode() {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    return newNode;
}

int isStackEmpty() { return boardingStack.top == NULL; }

int isStackFull() {
    int count = 0;
    struct StackNode* temp = boardingStack.top;
    while (temp) { count++; temp = temp->next; }
    return count >= 100;
}

int alreadyBoarded(int id) {
    struct StackNode* temp = boardingStack.top;
    while (temp) {
        if (temp->passengerID == id) return 1;
        temp = temp->next;
    }
    return 0;
}

void boardPassenger() {
    struct StackNode* newNode;

    if (isStackFull()) {
        msgERR("Boarding is full!"); return;
    }

    newNode = createStackNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("BOARD PASSENGER");
    boxSep();
    printf("  | Passenger ID    : "); scanf("%d", &newNode->passengerID);
    if (alreadyBoarded(newNode->passengerID)) {
        msgERR("Already boarded!"); free(newNode); return;
    }
    printf("  | Passenger Name  : "); scanf(" %[^\n]", newNode->passengerName);
    printf("  | Seat Number     : "); scanf(" %s", newNode->seatNumber);
    sprintf(newNode->boardingPass, "BP-%04d", newNode->passengerID);
    boxLine();

    newNode->next = boardingStack.top;
    boardingStack.top = newNode;

    msgOK("Passenger boarded.");
}

void deboardPassenger() {
    struct StackNode* temp;

    if (isStackEmpty()) { msgERR("No passengers on board."); return; }

    temp = boardingStack.top;
    boardingStack.top = boardingStack.top->next;
    free(temp);
    msgOK("Passenger deboarded.");
}

void viewLastBoarded() {
    if (isStackEmpty()) { msgERR("No passengers."); return; }

    printf("\n");
    boxLine();
    boxTitle("LAST BOARDED");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Name", boardingStack.top->passengerName);
    printf("  | %-20s : %-40d |\n", "ID", boardingStack.top->passengerID);
    printf("  | %-20s : %-40s |\n", "Seat", boardingStack.top->seatNumber);
    printf("  | %-20s : %-40s |\n", "Pass", boardingStack.top->boardingPass);
    boxLine();
}

void displayBoardingList() {
    struct StackNode* temp;
    int pos = 1;

    if (isStackEmpty()) { msgERR("No passengers."); return; }

    printf("\n");
    boxLine();
    boxTitle("BOARDING LIST");
    boxSep();
    printf("  | %-4s | %-5s | %-20s | %-8s |\n",
           "NO", "ID", "NAME", "SEAT");
    boxSep();

    temp = boardingStack.top;
    while (temp) {
        printf("  | %-4d | %-5d | %-20s | %-8s |\n",
            pos++, temp->passengerID, temp->passengerName, temp->seatNumber);
        temp = temp->next;
    }
    boxLine();
}

void boardingMenu() {
    int c;
    do {
        printHeader("BOARDING CONTROL");
        boxDbl();
        boxEmpty();
        boxTitle("BOARDING CONTROL");
        boxEmpty();
        boxSep();
        boxRow("  1.  Board Passenger");
        boxRow("  2.  Deboard Passenger");
        boxRow("  3.  View Last Boarded");
        boxRow("  4.  View Boarding List");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  BOARDING > "); scanf("%d", &c);
        switch(c) {
            case 1: boardPassenger(); break;
            case 2: deboardPassenger(); break;
            case 3: viewLastBoarded(); break;
            case 4: displayBoardingList(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
