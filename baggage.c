// ============================================================
//  MEMBER 3 — BAGGAGE SERVICES
//  Data Structure: DOUBLY LINKED LIST
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "baggage.h"

// ─── Initialize List ──────────────────────────────────────────
void initBaggageList(struct BaggageList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// ─── Create New Baggage Node ──────────────────────────────────
struct BaggageNode* createBaggageNode(int baggageID, int passengerID,
                                       char* ownerName, float weight) {
    struct BaggageNode* newNode;
    newNode = (struct BaggageNode*)malloc(sizeof(struct BaggageNode));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->baggageID   = baggageID;
    newNode->passengerID = passengerID;
    strcpy(newNode->ownerName, ownerName);
    newNode->weight = weight;
    sprintf(newNode->tag, "TAG-%04d", baggageID);
    strcpy(newNode->status, "Checked-In");
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

// ─── Check Duplicate ──────────────────────────────────────────
int baggageIDExists(struct BaggageList* list, int id) {
    struct BaggageNode* temp = list->head;
    while (temp != NULL) {
        if (temp->baggageID == id) return 1;
        temp = temp->next;
    }
    return 0;
}

// ─── 1. Add Baggage (Insert Rear) ────────────────────────────
void addBaggage(struct BaggageList* list) {
    int baggageID, passengerID;
    char ownerName[MAX_NAME];
    float weight;
    struct BaggageNode* newNode;
    char msg[100];

    printf("\n");
    boxTop();
    boxTitle("BAGGAGE CHECK-IN");
    boxSep();
    boxEmpty();
    printf("  | Baggage Tag ID  : "); scanf("%d", &baggageID);

    if (baggageIDExists(list, baggageID)) {
        msgERR("Baggage ID already exists!"); return;
    }

    printf("  | Passenger ID    : "); scanf("%d", &passengerID);
    printf("  | Owner Name      : "); scanf(" %[^\n]", ownerName);
    printf("  | Weight (kg)     : "); scanf("%f", &weight);
    boxEmpty();
    boxBottom();

    if (weight > 30.0) {
        msgWARN("Baggage exceeds 30kg! Additional charges apply.");
    }

    newNode = createBaggageNode(baggageID, passengerID, ownerName, weight);
    if (newNode == NULL) return;

    // Insert at rear — doubly linked list
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev    = list->tail;
        list->tail       = newNode;
    }

    sprintf(msg, "Baggage checked in. Tag: TAG-%04d | Weight: %.1f kg",
            baggageID, weight);
    msgOK(msg);
}

// ─── 2. Remove Baggage ────────────────────────────────────────
void removeBaggage(struct BaggageList* list) {
    int id;
    struct BaggageNode* temp;
    char msg[50];

    if (list->head == NULL) { msgERR("No baggage records."); return; }

    printf("\n  Enter Baggage Tag ID to remove: "); scanf("%d", &id);

    temp = list->head;
    while (temp != NULL) {
        if (temp->baggageID == id) {
            // Update prev link
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                list->head = temp->next;
            }
            // Update next link
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            } else {
                list->tail = temp->prev;
            }
            sprintf(msg, "Baggage TAG-%04d removed.", id);
            free(temp);
            msgOK(msg);
            return;
        }
        temp = temp->next;
    }
    msgERR("Baggage ID not found.");
}

// ─── 3. Display Forward (Head to Tail) ───────────────────────
void displayForward(struct BaggageList* list) {
    struct BaggageNode* temp;

    if (list->head == NULL) { msgERR("No baggage records."); return; }

    printf("\n");
    boxTop();
    boxTitle("BAGGAGE MANIFEST  [FORWARD SCAN]");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();

    // Traverse from head to tail
    temp = list->head;
    while (temp != NULL) {
        printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
            temp->tag, temp->passengerID,
            temp->ownerName, temp->weight, temp->status);
        temp = temp->next;
    }
    boxBottom();
}

// ─── 4. Display Backward (Tail to Head) ──────────────────────
void displayBackward(struct BaggageList* list) {
    struct BaggageNode* temp;

    if (list->head == NULL) { msgERR("No baggage records."); return; }

    printf("\n");
    boxTop();
    boxTitle("BAGGAGE MANIFEST  [REVERSE SCAN]");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();

    // Traverse from tail to head using prev pointer
    temp = list->tail;
    while (temp != NULL) {
        printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
            temp->tag, temp->passengerID,
            temp->ownerName, temp->weight, temp->status);
        temp = temp->prev;
    }
    boxBottom();
}

// ─── 5. Search Baggage by Passenger ID ───────────────────────
void searchBaggage(struct BaggageList* list) {
    int pid, found = 0;
    struct BaggageNode* temp;

    if (list->head == NULL) { msgERR("No baggage records."); return; }

    printf("\n  Enter Passenger ID: "); scanf("%d", &pid);

    printf("\n");
    boxTop();
    boxTitle("BAGGAGE SEARCH RESULTS");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();

    temp = list->head;
    while (temp != NULL) {
        if (temp->passengerID == pid) {
            printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
                temp->tag, temp->passengerID,
                temp->ownerName, temp->weight, temp->status);
            found++;
        }
        temp = temp->next;
    }
    boxBottom();
    if (!found) msgERR("No baggage found for this passenger.");
}

// ─── 6. Baggage Statistics — Additional Function ──────────────
void baggageStatistics(struct BaggageList* list) {
    struct BaggageNode* temp;
    int count = 0;
    float total = 0, heaviest = 0;

    if (list->head == NULL) { msgERR("No baggage records."); return; }

    temp = list->head;
    while (temp != NULL) {
        count++;
        total += temp->weight;
        if (temp->weight > heaviest) heaviest = temp->weight;
        temp = temp->next;
    }

    printf("\n");
    boxTop();
    boxTitle("BAGGAGE LOAD REPORT");
    boxSep();
    printf("  | %-30s : %-30d |\n",   "Total Bags Checked",  count);
    printf("  | %-30s : %-29.1f  |\n","Total Weight (kg)",   total);
    printf("  | %-30s : %-29.1f  |\n","Average Weight (kg)", total / count);
    printf("  | %-30s : %-29.1f  |\n","Heaviest Bag (kg)",   heaviest);
    boxBottom();
}

// ─── Menu ─────────────────────────────────────────────────────
void baggageMenu(struct BaggageList* list) {
    int c;
    do {
        printHeader("BAGGAGE SERVICES");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("BAGGAGE SERVICES");
        boxEmpty();
        boxSep();
        boxRow("  1.  Baggage Check-In");
        boxRow("  2.  Remove Baggage");
        boxRow("  3.  View Baggage (Forward Scan)");
        boxRow("  4.  View Baggage (Reverse Scan)");
        boxRow("  5.  Search Baggage by Passenger");
        boxRow("  6.  Baggage Load Report");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  BAGGAGE SERVICES > "); scanf("%d", &c);

        switch(c) {
            case 1: addBaggage(list);        break;
            case 2: removeBaggage(list);     break;
            case 3: displayForward(list);    break;
            case 4: displayBackward(list);   break;
            case 5: searchBaggage(list);     break;
            case 6: baggageStatistics(list); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
