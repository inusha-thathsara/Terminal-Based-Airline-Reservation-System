
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "gates.h"

struct GateList gateList;

void initGateList() {
    gateList.head = NULL;
}

struct GateNode* createGateNode() {
    struct GateNode* newNode = (struct GateNode*)malloc(sizeof(struct GateNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    return newNode;
}

int gateExists(int gateNum) {
    if (!gateList.head) return 0;
    struct GateNode* temp = gateList.head;
    do {
        if (temp->gateNumber == gateNum) return 1;
        temp = temp->next;
    } while (temp != gateList.head);
    return 0;
}

void addGate() {
    struct GateNode* newNode, *tail;
    char msg[60];

    newNode = createGateNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("ADD GATE");
    boxSep();
    printf("  | Gate Number     : "); scanf("%d", &newNode->gateNumber);
    if (gateExists(newNode->gateNumber)) {
        msgERR("Gate already exists!"); free(newNode); return;
    }
    printf("  | Terminal (A/B/C): "); scanf(" %s", newNode->terminal);
    manualStrCpy(newNode->status, "Available");
    manualStrCpy(newNode->assignedFlight, "------");
    manualStrCpy(newNode->lastFlight, "------");
    boxLine();

    if (!gateList.head) {
        newNode->next = newNode;
        gateList.head = newNode;
    } else {
        tail = gateList.head;
        while (tail->next != gateList.head) tail = tail->next;
        tail->next = newNode;
        newNode->next = gateList.head;
    }
    sprintf(msg, "Gate %d added (Terminal %s).", newNode->gateNumber, newNode->terminal);
    msgOK(msg);
}

void assignGate() {
    char fn[10];
    struct GateNode* temp;

    if (!gateList.head) { msgERR("No gates available."); return; }

    printf("\n");
    boxLine();
    boxTitle("ASSIGN GATE");
    boxSep();
    printf("  | Flight Number   : "); scanf(" %s", fn);
    boxLine();

    temp = gateList.head;
    do {
        if (manualStrCmp(temp->status, "Available") == 0) {
            manualStrCpy(temp->status, "Occupied");
            manualStrCpy(temp->assignedFlight, fn);
            manualStrCpy(temp->lastFlight, fn);
            msgOK("Gate assigned successfully.");
            return;
        }
        temp = temp->next;
    } while (temp != gateList.head);
    msgERR("No available gates.");
}

void releaseGate() {
    int gnum;
    struct GateNode* temp;

    if (!gateList.head) { msgERR("No gates."); return; }

    printf("\n");
    boxLine();
    boxTitle("RELEASE GATE");
    boxSep();
    printf("  | Gate Number     : "); scanf("%d", &gnum);
    boxLine();

    temp = gateList.head;
    do {
        if (temp->gateNumber == gnum) {
            if (manualStrCmp(temp->status, "Occupied") == 0) {
                manualStrCpy(temp->status, "Available");
                manualStrCpy(temp->assignedFlight, "------");
                msgOK("Gate released.");
            } else {
                msgINFO("Gate was already available.");
            }
            return;
        }
        temp = temp->next;
    } while (temp != gateList.head);
    msgERR("Gate not found.");
}

void displayAllGates() {
    struct GateNode* temp;

    if (!gateList.head) { msgERR("No gates."); return; }

    printf("\n");
    boxLine();
    boxTitle("GATE STATUS BOARD");
    boxSep();
    printf("  | %-6s | %-8s | %-13s | %-10s |\n",
           "GATE", "TERMINAL", "STATUS", "FLIGHT");
    boxSep();

    temp = gateList.head;
    do {
        printf("  | %-6d | %-8s | %-13s | %-10s |\n",
            temp->gateNumber, temp->terminal, temp->status, temp->assignedFlight);
        temp = temp->next;
    } while (temp != gateList.head);
    boxLine();
}

void gateStatistics() {
    struct GateNode* temp;
    int total = 0, available = 0, occupied = 0;

    if (!gateList.head) { msgERR("No gates."); return; }

    temp = gateList.head;
    do {
        total++;
        if (manualStrCmp(temp->status, "Available") == 0) available++;
        else occupied++;
        temp = temp->next;
    } while (temp != gateList.head);

    printf("\n");
    boxLine();
    boxTitle("GATE STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Gates", total);
    printf("  | %-30s : %-30d |\n", "Available Gates", available);
    printf("  | %-30s : %-30d |\n", "Occupied Gates", occupied);
    printf("  | %-30s : %-30.1f%% |\n", "Utilization", (float)occupied / total * 100);
    boxLine();
}

void gateMenu() {
    int c;
    do {
        printHeader("GATE CONTROL");
        boxDbl();
        boxEmpty();
        boxTitle("GATE CONTROL");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Gate");
        boxRow("  2.  Assign Gate to Flight");
        boxRow("  3.  Release Gate");
        boxRow("  4.  View All Gates");
        boxRow("  5.  Gate Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  GATE > "); scanf("%d", &c);
        switch(c) {
            case 1: addGate(); break;
            case 2: assignGate(); break;
            case 3: releaseGate(); break;
            case 4: displayAllGates(); break;
            case 5: gateStatistics(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
