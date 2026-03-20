// ============================================================
//  MEMBER 5 — BOARDING CONTROL
//  Data Structure: STACK
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "boarding.h"

// ─── Initialize Stack ─────────────────────────────────────────
void initStack(struct Stack* stack) {
    stack->top = NULL;
}

// ─── Create New Stack Node ────────────────────────────────────
struct StackNode* createStackNode(int passengerID, char* passengerName,
                                   char* seatNumber) {
    struct StackNode* newNode;
    newNode = (struct StackNode*)malloc(sizeof(struct StackNode));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->passengerID = passengerID;
    strcpy(newNode->passengerName, passengerName);
    strcpy(newNode->seatNumber,    seatNumber);
    sprintf(newNode->boardingPass, "BP-%04d", passengerID);
    newNode->next = NULL;

    return newNode;
}

// ─── Check Duplicate Boarding ─────────────────────────────────
int isDuplicateBoarding(struct Stack* stack, int id) {
    struct StackNode* temp = stack->top;
    while (temp != NULL) {
        if (temp->passengerID == id) return 1;
        temp = temp->next;
    }
    return 0;
}

// ─── 1. Push — Board Passenger ───────────────────────────────
void pushBoarding(struct Stack* stack) {
    int passengerID;
    char passengerName[MAX_NAME], seatNumber[10];
    struct StackNode* newNode;
    char msg[100];

    printf("\n");
    boxTop();
    boxTitle("PASSENGER BOARDING");
    boxSep();
    boxEmpty();
    printf("  | Passenger ID    : "); scanf("%d", &passengerID);

    if (isDuplicateBoarding(stack, passengerID)) {
        msgERR("Passenger already on board!"); return;
    }

    printf("  | Passenger Name  : "); scanf(" %[^\n]", passengerName);
    printf("  | Seat Number     : "); scanf(" %s", seatNumber);
    boxEmpty();
    boxBottom();

    newNode = createStackNode(passengerID, passengerName, seatNumber);
    if (newNode == NULL) return;

    // Push to top of stack
    if (stack->top == NULL) {
        stack->top = newNode;
    } else {
        newNode->next = stack->top;
        stack->top    = newNode;
    }

    sprintf(msg, "Boarding confirmed. Seat: %s | Pass: %s",
            seatNumber, newNode->boardingPass);
    msgOK(msg);
}

// ─── 2. Pop — Deboard Passenger ──────────────────────────────
void popBoarding(struct Stack* stack) {
    struct StackNode* temp;
    char msg[80];

    if (stack->top == NULL) { msgERR("No passengers on board."); return; }

    temp       = stack->top;
    stack->top = stack->top->next;

    sprintf(msg, "%s (Seat %s) deboarded.", temp->passengerName, temp->seatNumber);
    free(temp);
    msgOK(msg);
}

// ─── 3. Peek — View Last Boarded ─────────────────────────────
void peekBoarding(struct Stack* stack) {
    if (stack->top == NULL) { msgERR("No passengers on board."); return; }

    printf("\n");
    boxTop();
    boxTitle("LAST BOARDED PASSENGER");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Name",          stack->top->passengerName);
    printf("  | %-20s : %-40d |\n", "Passenger ID",  stack->top->passengerID);
    printf("  | %-20s : %-40s |\n", "Seat Number",   stack->top->seatNumber);
    printf("  | %-20s : %-40s |\n", "Boarding Pass", stack->top->boardingPass);
    boxBottom();
}

// ─── 4. Display All Boarded ───────────────────────────────────
void displayBoardingList(struct Stack* stack) {
    struct StackNode* temp;
    int pos = 1;

    if (stack->top == NULL) { msgERR("No passengers boarded yet."); return; }

    printf("\n");
    boxTop();
    boxTitle("BOARDING LIST");
    boxSep();
    printf("  | %-4s | %-5s | %-20s | %-8s | %-12s |\n",
           "NO","ID","NAME","SEAT","BOARDING PASS");
    boxSep();

    temp = stack->top;
    while (temp != NULL) {
        printf("  | %-4d | %-5d | %-20s | %-8s | %-12s |\n",
            pos++, temp->passengerID, temp->passengerName,
            temp->seatNumber, temp->boardingPass);
        temp = temp->next;
    }
    boxBottom();
}

// ─── 5. Undo Last Boarding ───────────────────────────────────
void undoBoarding(struct Stack* stack) {
    if (stack->top == NULL) { msgERR("Nothing to undo."); return; }
    msgINFO("Reversing last boarding action...");
    popBoarding(stack);
}

// ─── Menu ─────────────────────────────────────────────────────
void boardingMenu(struct Stack* stack) {
    int c;
    do {
        printHeader("BOARDING CONTROL");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("BOARDING CONTROL");
        boxEmpty();
        boxSep();
        boxRow("  1.  Board Passenger");
        boxRow("  2.  Deboard Passenger");
        boxRow("  3.  View Last Boarded Passenger");
        boxRow("  4.  View Full Boarding List");
        boxRow("  5.  Undo Last Boarding");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  BOARDING CONTROL > "); scanf("%d", &c);

        switch(c) {
            case 1: pushBoarding(stack);       break;
            case 2: popBoarding(stack);        break;
            case 3: peekBoarding(stack);       break;
            case 4: displayBoardingList(stack);break;
            case 5: undoBoarding(stack);       break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
