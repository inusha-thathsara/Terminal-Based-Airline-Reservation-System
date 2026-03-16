// ============================================================
//  MEMBER 4 — GATE CONTROL
//  Data Structure: CIRCULAR LINKED LIST
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "gates.h"

GateNode* gateHead = NULL;

int gateExists(int gateNum) {
    if (!gateHead) return 0;
    GateNode* curr = gateHead;
    do {
        if (curr->gateNumber == gateNum) return 1;
        curr = curr->next;
    } while (curr != gateHead);
    return 0;
}

void addGate() {
    GateNode* n = (GateNode*)malloc(sizeof(GateNode));
    if (!n) { msgERR("Memory allocation failed."); return; }
    printf("\n  Enter Gate Number     : "); scanf("%d", &n->gateNumber);
    if (gateExists(n->gateNumber)) {
        msgERR("Gate already exists!"); free(n); return;
    }
    printf("  Enter Terminal (A/B/C): "); scanf(" %s", n->terminal);
    strcpy(n->status, "Available");
    strcpy(n->assignedFlight, "------");
    strcpy(n->lastFlight,     "------");
    n->historyCount = 0;
    if (!gateHead) { n->next = n; gateHead = n; }
    else {
        GateNode* tail = gateHead;
        while (tail->next != gateHead) tail = tail->next;
        tail->next = n; n->next = gateHead;
    }
    char msg[60];
    sprintf(msg, "Gate %d (Terminal %s) added.", n->gateNumber, n->terminal);
    msgOK(msg);
}

void assignGate() {
    if (!gateHead) { msgERR("No gates available."); return; }
    char fn[MAX_FLIGHT_NO];
    printf("\n  Enter Flight Number to assign: "); scanf(" %s", fn);
    GateNode* curr = gateHead;
    do {
        if (strcmp(curr->status, "Available") == 0) {
            strcpy(curr->status, "Occupied");
            strcpy(curr->assignedFlight, fn);
            strcpy(curr->lastFlight, fn);
            if (curr->historyCount < 3)
                strcpy(curr->history[curr->historyCount++], fn);
            char msg[80];
            sprintf(msg, "Gate %d (Terminal %s) assigned to Flight %s.",
                    curr->gateNumber, curr->terminal, fn);
            msgOK(msg); return;
        }
        curr = curr->next;
    } while (curr != gateHead);
    msgERR("No available gates at this time.");
}

void releaseGate() {
    if (!gateHead) { msgERR("No gates in system."); return; }
    int gnum;
    printf("\n  Enter Gate Number to release: "); scanf("%d", &gnum);
    GateNode* curr = gateHead;
    do {
        if (curr->gateNumber == gnum) {
            if (strcmp(curr->status, "Available") == 0) {
                msgERR("Gate is already available.");
            } else {
                char msg[80];
                sprintf(msg, "Gate %d released. Flight %s has departed.",
                        curr->gateNumber, curr->assignedFlight);
                strcpy(curr->status, "Available");
                strcpy(curr->assignedFlight, "------");
                msgOK(msg);
            }
            return;
        }
        curr = curr->next;
    } while (curr != gateHead);
    msgERR("Gate not found.");
}

void displayAllGates() {
    if (!gateHead) { msgERR("No gates registered."); return; }
    printf("\n");
    boxTop();
    boxTitle("GATE STATUS BOARD");
    boxSep();
    printf("  | %-6s | %-8s | %-13s | %-10s | %-10s |\n",
           "GATE","TERMINAL","STATUS","FLIGHT","LAST FLIGHT");
    boxSep();
    GateNode* curr = gateHead;
    do {
        printf("  | %-6d | %-8s | %-13s | %-10s | %-10s |\n",
            curr->gateNumber, curr->terminal,
            curr->status, curr->assignedFlight, curr->lastFlight);
        curr = curr->next;
    } while (curr != gateHead);
    boxBottom();
}

void findAvailableGate() {
    if (!gateHead) { msgERR("No gates in system."); return; }
    GateNode* curr = gateHead;
    do {
        if (strcmp(curr->status, "Available") == 0) {
            char msg[60];
            sprintf(msg, "Next available: Gate %d | Terminal %s",
                    curr->gateNumber, curr->terminal);
            msgOK(msg); return;
        }
        curr = curr->next;
    } while (curr != gateHead);
    msgERR("All gates are currently occupied.");
}

void gateStatistics() {
    if (!gateHead) { msgERR("No gates."); return; }
    int total = 0, available = 0, occupied = 0;
    GateNode* curr = gateHead;
    do {
        total++;
        if (strcmp(curr->status, "Available") == 0) available++;
        else occupied++;
        curr = curr->next;
    } while (curr != gateHead);
    printf("\n");
    boxTop();
    boxTitle("GATE CONTROL STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Gates",     total);
    printf("  | %-30s : %-30d |\n", "Available Gates", available);
    printf("  | %-30s : %-30d |\n", "Occupied Gates",  occupied);
    boxBottom();
}

void gateHistory() {
    if (!gateHead) { msgERR("No gates."); return; }
    printf("\n");
    boxTop();
    boxTitle("GATE FLIGHT HISTORY LOG");
    boxSep();
    GateNode* curr = gateHead;
    do {
        printf("  | Gate %-3d | Terminal %-3s | Last: %-8s | History: ",
               curr->gateNumber, curr->terminal, curr->lastFlight);
        if (curr->historyCount == 0) printf("None");
        else for (int i = 0; i < curr->historyCount; i++)
            printf("[%s] ", curr->history[i]);
        printf("\n");
        curr = curr->next;
    } while (curr != gateHead);
    boxBottom();
}

void emergencyReleaseAllGates() {
    if (!gateHead) { msgERR("No gates."); return; }
    msgWARN("EMERGENCY PROTOCOL ACTIVATED — Releasing all gates...");
    printf("\n");
    int count = 0;
    GateNode* curr = gateHead;
    do {
        if (strcmp(curr->status, "Occupied") == 0) {
            printf("  [ -- ]  Gate %-3d released | Flight %s cleared\n",
                   curr->gateNumber, curr->assignedFlight);
            strcpy(curr->status, "Available");
            strcpy(curr->assignedFlight, "------");
            count++;
        }
        curr = curr->next;
    } while (curr != gateHead);
    if (count == 0) msgINFO("All gates were already available.");
    else { char msg[60]; sprintf(msg, "EMERGENCY RELEASE COMPLETE: %d gate(s) cleared.", count); msgOK(msg); }
}

GateNode* deleteGate(GateNode* head) {
    if (!head) { msgERR("No gates to delete."); return NULL; }
    int gateNum;
    printf("\n  Enter Gate Number to decommission: "); scanf("%d", &gateNum);
    GateNode* curr = head;
    do {
        if (curr->gateNumber == gateNum) {
            if (strcmp(curr->status, "Occupied") == 0) {
                msgERR("Cannot decommission occupied gate! Release it first.");
                return head;
            }
            break;
        }
        curr = curr->next;
    } while (curr != head);
    if (head->next == head) {
        char msg[50]; sprintf(msg, "Gate %d decommissioned.", head->gateNumber);
        free(head); msgOK(msg); return NULL;
    }
    GateNode* prev2 = head; curr = head->next;
    if (head->gateNumber == gateNum) {
        GateNode* tail = head;
        while (tail->next != head) tail = tail->next;
        tail->next = head->next;
        char msg[50]; sprintf(msg, "Gate %d decommissioned.", head->gateNumber);
        GateNode* newHead = head->next;
        free(head); msgOK(msg); return newHead;
    }
    while (curr != head) {
        if (curr->gateNumber == gateNum) {
            prev2->next = curr->next;
            char msg[50]; sprintf(msg, "Gate %d decommissioned.", curr->gateNumber);
            free(curr); msgOK(msg); return head;
        }
        prev2 = curr; curr = curr->next;
    }
    msgERR("Gate not found."); return head;
}

void gateMenu() {
    int c;
    do {
        printHeader("GATE CONTROL");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("GATE CONTROL CENTER");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add New Gate");
        boxRow("  2.  Assign Gate to Flight");
        boxRow("  3.  Release Gate");
        boxRow("  4.  View Gate Status Board");
        boxRow("  5.  Find Next Available Gate");
        boxRow("  6.  Gate Statistics");
        boxRow("  7.  Gate Flight History Log");
        boxRow("  8.  Decommission a Gate");
        boxRow("  9.  EMERGENCY: Release All Gates");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  GATE CONTROL > "); scanf("%d", &c);
        switch(c) {
            case 1: addGate();                       break;
            case 2: assignGate();                    break;
            case 3: releaseGate();                   break;
            case 4: displayAllGates();               break;
            case 5: findAvailableGate();             break;
            case 6: gateStatistics();                break;
            case 7: gateHistory();                   break;
            case 8: gateHead = deleteGate(gateHead); break;
            case 9: emergencyReleaseAllGates();       break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
