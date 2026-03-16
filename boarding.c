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

StackNode* boardingTop = NULL;

int isDuplicateBoarding(int id) {
    StackNode* curr = boardingTop;
    while (curr) { if (curr->passengerID == id) return 1; curr = curr->next; }
    return 0;
}

void pushBoarding() {
    StackNode* n = (StackNode*)malloc(sizeof(StackNode));
    if (!n) { msgERR("Memory allocation failed."); return; }
    printf("\n");
    boxTop();
    boxTitle("PASSENGER BOARDING");
    boxSep();
    boxEmpty();
    printf("  | Passenger ID    : "); scanf("%d", &n->passengerID);
    if (isDuplicateBoarding(n->passengerID)) {
        msgERR("Passenger already on board!"); free(n); return;
    }
    printf("  | Passenger Name  : "); scanf(" %[^\n]", n->passengerName);
    printf("  | Seat Number     : "); scanf(" %s", n->seatNumber);
    sprintf(n->boardingPass, "BP-%04d", n->passengerID);
    boxEmpty();
    boxBottom();
    n->next     = boardingTop;
    boardingTop = n;
    char msg[100];
    sprintf(msg, "Boarding confirmed. Seat: %s | Pass: %s",
            n->seatNumber, n->boardingPass);
    msgOK(msg);
}

void popBoarding() {
    if (!boardingTop) { msgERR("No passengers on board."); return; }
    StackNode* temp = boardingTop;
    boardingTop = boardingTop->next;
    char msg[80];
    sprintf(msg, "%s (Seat %s) deboarded.", temp->passengerName, temp->seatNumber);
    free(temp); msgOK(msg);
}

void peekBoarding() {
    if (!boardingTop) { msgERR("No passengers on board."); return; }
    printf("\n");
    boxTop();
    boxTitle("LAST BOARDED PASSENGER");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Name",         boardingTop->passengerName);
    printf("  | %-20s : %-40d |\n", "Passenger ID", boardingTop->passengerID);
    printf("  | %-20s : %-40s |\n", "Seat Number",  boardingTop->seatNumber);
    printf("  | %-20s : %-40s |\n", "Boarding Pass",boardingTop->boardingPass);
    boxBottom();
}

void displayBoardingList() {
    if (!boardingTop) { msgERR("No passengers boarded yet."); return; }
    printf("\n");
    boxTop();
    boxTitle("BOARDING LIST");
    boxSep();
    printf("  | %-4s | %-5s | %-20s | %-8s | %-12s |\n",
           "NO","ID","NAME","SEAT","BOARDING PASS");
    boxSep();
    StackNode* curr = boardingTop; int pos = 1;
    while (curr) {
        printf("  | %-4d | %-5d | %-20s | %-8s | %-12s |\n",
            pos++, curr->passengerID, curr->passengerName,
            curr->seatNumber, curr->boardingPass);
        curr = curr->next;
    }
    boxBottom();
}

void undoBoarding() {
    if (!boardingTop) { msgERR("Nothing to undo."); return; }
    msgINFO("Reversing last boarding action...");
    popBoarding();
}

void boardingMenu() {
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
            case 1: pushBoarding();       break;
            case 2: popBoarding();        break;
            case 3: peekBoarding();       break;
            case 4: displayBoardingList();break;
            case 5: undoBoarding();       break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
