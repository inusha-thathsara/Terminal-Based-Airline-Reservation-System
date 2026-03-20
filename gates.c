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

// ─── Initialize List ──────────────────────────────────────────
void initGateList(struct GateList* list) {
    list->head = NULL;
}

// ─── Create New Gate Node ─────────────────────────────────────
struct GateNode* createGateNode(int gateNumber, char* terminal) {
    struct GateNode* newNode;
    newNode = (struct GateNode*)malloc(sizeof(struct GateNode));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->gateNumber   = gateNumber;
    strcpy(newNode->terminal,       terminal);
    strcpy(newNode->status,         "Available");
    strcpy(newNode->assignedFlight, "------");
    strcpy(newNode->lastFlight,     "------");
    newNode->historyCount = 0;
    newNode->next         = NULL;

    return newNode;
}

// ─── Check Duplicate ──────────────────────────────────────────
int gateExists(struct GateList* list, int gateNum) {
    struct GateNode* temp;

    if (list->head == NULL) return 0;

    temp = list->head;
    do {
        if (temp->gateNumber == gateNum) return 1;
        temp = temp->next;
    } while (temp != list->head);

    return 0;
}

// ─── 1. Add Gate ──────────────────────────────────────────────
void addGate(struct GateList* list) {
    int gateNumber;
    char terminal[10];
    struct GateNode* newNode;
    struct GateNode* tail;
    char msg[60];

    printf("\n  Enter Gate Number     : "); scanf("%d", &gateNumber);

    if (gateExists(list, gateNumber)) {
        msgERR("Gate already exists!"); return;
    }

    printf("  Enter Terminal (A/B/C): "); scanf(" %s", terminal);

    newNode = createGateNode(gateNumber, terminal);
    if (newNode == NULL) return;

    // Insert into circular linked list
    if (list->head == NULL) {
        // First node points to itself
        newNode->next = newNode;
        list->head    = newNode;
    } else {
        // Find tail (node that points back to head)
        tail = list->head;
        while (tail->next != list->head) {
            tail = tail->next;
        }
        tail->next    = newNode;
        newNode->next = list->head;
    }

    sprintf(msg, "Gate %d (Terminal %s) added.", gateNumber, terminal);
    msgOK(msg);
}

// ─── 2. Assign Gate to Flight ─────────────────────────────────
void assignGate(struct GateList* list) {
    char fn[MAX_FLIGHT_NO];
    struct GateNode* temp;
    char msg[80];

    if (list->head == NULL) { msgERR("No gates available."); return; }

    printf("\n  Enter Flight Number to assign: "); scanf(" %s", fn);

    // Rotate through circular list to find available gate
    temp = list->head;
    do {
        if (strcmp(temp->status, "Available") == 0) {
            strcpy(temp->status,         "Occupied");
            strcpy(temp->assignedFlight, fn);
            strcpy(temp->lastFlight,     fn);
            if (temp->historyCount < 3) {
                strcpy(temp->history[temp->historyCount], fn);
                temp->historyCount++;
            }
            sprintf(msg, "Gate %d (Terminal %s) assigned to Flight %s.",
                    temp->gateNumber, temp->terminal, fn);
            msgOK(msg);
            return;
        }
        temp = temp->next;
    } while (temp != list->head);

    msgERR("No available gates at this time.");
}

// ─── 3. Release Gate ──────────────────────────────────────────
void releaseGate(struct GateList* list) {
    int gnum;
    struct GateNode* temp;
    char msg[80];

    if (list->head == NULL) { msgERR("No gates in system."); return; }

    printf("\n  Enter Gate Number to release: "); scanf("%d", &gnum);

    temp = list->head;
    do {
        if (temp->gateNumber == gnum) {
            if (strcmp(temp->status, "Available") == 0) {
                msgERR("Gate is already available.");
            } else {
                sprintf(msg, "Gate %d released. Flight %s has departed.",
                        temp->gateNumber, temp->assignedFlight);
                strcpy(temp->status,         "Available");
                strcpy(temp->assignedFlight, "------");
                msgOK(msg);
            }
            return;
        }
        temp = temp->next;
    } while (temp != list->head);

    msgERR("Gate not found.");
}

// ─── 4. Display All Gates ─────────────────────────────────────
void displayAllGates(struct GateList* list) {
    struct GateNode* temp;

    if (list->head == NULL) { msgERR("No gates registered."); return; }

    printf("\n");
    boxTop();
    boxTitle("GATE STATUS BOARD");
    boxSep();
    printf("  | %-6s | %-8s | %-13s | %-10s | %-10s |\n",
           "GATE","TERMINAL","STATUS","FLIGHT","LAST FLIGHT");
    boxSep();

    temp = list->head;
    do {
        printf("  | %-6d | %-8s | %-13s | %-10s | %-10s |\n",
            temp->gateNumber, temp->terminal,
            temp->status, temp->assignedFlight, temp->lastFlight);
        temp = temp->next;
    } while (temp != list->head);

    boxBottom();
}

// ─── 5. Find Available Gate ───────────────────────────────────
void findAvailableGate(struct GateList* list) {
    struct GateNode* temp;
    char msg[60];

    if (list->head == NULL) { msgERR("No gates in system."); return; }

    temp = list->head;
    do {
        if (strcmp(temp->status, "Available") == 0) {
            sprintf(msg, "Next available: Gate %d | Terminal %s",
                    temp->gateNumber, temp->terminal);
            msgOK(msg);
            return;
        }
        temp = temp->next;
    } while (temp != list->head);

    msgERR("All gates are currently occupied.");
}

// ─── 6. Gate Statistics — Additional Function ─────────────────
void gateStatistics(struct GateList* list) {
    struct GateNode* temp;
    int total = 0, available = 0, occupied = 0;

    if (list->head == NULL) { msgERR("No gates."); return; }

    temp = list->head;
    do {
        total++;
        if (strcmp(temp->status, "Available") == 0) available++;
        else occupied++;
        temp = temp->next;
    } while (temp != list->head);

    printf("\n");
    boxTop();
    boxTitle("GATE CONTROL STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Gates",     total);
    printf("  | %-30s : %-30d |\n", "Available Gates", available);
    printf("  | %-30s : %-30d |\n", "Occupied Gates",  occupied);
    boxBottom();
}

// ─── 7. Gate History ──────────────────────────────────────────
void gateHistory(struct GateList* list) {
    struct GateNode* temp;
    int i;

    if (list->head == NULL) { msgERR("No gates."); return; }

    printf("\n");
    boxTop();
    boxTitle("GATE FLIGHT HISTORY LOG");
    boxSep();

    temp = list->head;
    do {
        printf("  | Gate %-3d | Terminal %-3s | Last: %-8s | History: ",
               temp->gateNumber, temp->terminal, temp->lastFlight);
        if (temp->historyCount == 0) printf("None");
        else {
            for (i = 0; i < temp->historyCount; i++)
                printf("[%s] ", temp->history[i]);
        }
        printf("\n");
        temp = temp->next;
    } while (temp != list->head);

    boxBottom();
}

// ─── 8. Emergency Release All Gates ──────────────────────────
void emergencyReleaseAllGates(struct GateList* list) {
    struct GateNode* temp;
    int count = 0;
    char msg[60];

    if (list->head == NULL) { msgERR("No gates."); return; }

    msgWARN("EMERGENCY PROTOCOL ACTIVATED — Releasing all gates...");
    printf("\n");

    temp = list->head;
    do {
        if (strcmp(temp->status, "Occupied") == 0) {
            printf("  [ -- ]  Gate %-3d released | Flight %s cleared\n",
                   temp->gateNumber, temp->assignedFlight);
            strcpy(temp->status,         "Available");
            strcpy(temp->assignedFlight, "------");
            count++;
        }
        temp = temp->next;
    } while (temp != list->head);

    if (count == 0) msgINFO("All gates were already available.");
    else {
        sprintf(msg, "EMERGENCY RELEASE COMPLETE: %d gate(s) cleared.", count);
        msgOK(msg);
    }
}

// ─── 9. Delete Gate ───────────────────────────────────────────
void deleteGate(struct GateList* list) {
    int gateNum;
    struct GateNode* temp;
    struct GateNode* prev;
    struct GateNode* tail;
    char msg[50];

    if (list->head == NULL) { msgERR("No gates to delete."); return; }

    printf("\n  Enter Gate Number to decommission: "); scanf("%d", &gateNum);

    // Check if occupied
    temp = list->head;
    do {
        if (temp->gateNumber == gateNum) {
            if (strcmp(temp->status, "Occupied") == 0) {
                msgERR("Cannot decommission occupied gate! Release it first.");
                return;
            }
            break;
        }
        temp = temp->next;
    } while (temp != list->head);

    // Only one gate
    if (list->head->next == list->head) {
        if (list->head->gateNumber == gateNum) {
            sprintf(msg, "Gate %d decommissioned.", list->head->gateNumber);
            free(list->head);
            list->head = NULL;
            msgOK(msg);
        } else {
            msgERR("Gate not found.");
        }
        return;
    }

    // Find tail
    tail = list->head;
    while (tail->next != list->head) tail = tail->next;

    // Delete head
    if (list->head->gateNumber == gateNum) {
        tail->next = list->head->next;
        sprintf(msg, "Gate %d decommissioned.", list->head->gateNumber);
        free(list->head);
        list->head = tail->next;
        msgOK(msg);
        return;
    }

    // Delete non-head node
    prev = list->head;
    temp = list->head->next;
    while (temp != list->head) {
        if (temp->gateNumber == gateNum) {
            prev->next = temp->next;
            sprintf(msg, "Gate %d decommissioned.", temp->gateNumber);
            free(temp);
            msgOK(msg);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    msgERR("Gate not found.");
}

// ─── Menu ─────────────────────────────────────────────────────
void gateMenu(struct GateList* list) {
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
            case 1: addGate(list);                  break;
            case 2: assignGate(list);               break;
            case 3: releaseGate(list);              break;
            case 4: displayAllGates(list);          break;
            case 5: findAvailableGate(list);        break;
            case 6: gateStatistics(list);           break;
            case 7: gateHistory(list);              break;
            case 8: deleteGate(list);               break;
            case 9: emergencyReleaseAllGates(list); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
