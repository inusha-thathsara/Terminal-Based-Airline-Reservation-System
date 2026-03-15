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

BaggageNode* baggageHead = NULL;

int baggageIDExists(int id) {
    BaggageNode* curr = baggageHead;
    while (curr) { if (curr->baggageID == id) return 1; curr = curr->next; }
    return 0;
}

void addBaggage() {
    BaggageNode* n = (BaggageNode*)malloc(sizeof(BaggageNode));
    if (!n) { msgERR("Memory allocation failed."); return; }
    printf("\n");
    boxTop();
    boxTitle("BAGGAGE CHECK-IN");
    boxSep();
    boxEmpty();
    printf("  | Baggage Tag ID  : "); scanf("%d", &n->baggageID);
    if (baggageIDExists(n->baggageID)) {
        msgERR("Baggage ID already exists!"); free(n); return;
    }
    printf("  | Passenger ID    : "); scanf("%d", &n->passengerID);
    printf("  | Owner Name      : "); scanf(" %[^\n]", n->ownerName);
    printf("  | Weight (kg)     : "); scanf("%f", &n->weight);
    sprintf(n->tag, "TAG-%04d", n->baggageID);
    strcpy(n->status, "Checked-In");
    n->next = NULL; n->prev = NULL;
    boxEmpty();
    boxBottom();
    if (n->weight > 30.0)
        msgWARN("Baggage exceeds 30kg! Additional charges apply.");
    if (!baggageHead) { baggageHead = n; }
    else {
        BaggageNode* curr = baggageHead;
        while (curr->next) curr = curr->next;
        curr->next = n; n->prev = curr;
    }
    char msg[80];
    sprintf(msg, "Baggage checked in. Tag: %s | Weight: %.1f kg", n->tag, n->weight);
    msgOK(msg);
}

void removeBaggage() {
    if (!baggageHead) { msgERR("No baggage records."); return; }
    int id;
    printf("\n  Enter Baggage Tag ID to remove: "); scanf("%d", &id);
    BaggageNode* curr = baggageHead;
    while (curr) {
        if (curr->baggageID == id) {
            if (curr->prev) curr->prev->next = curr->next;
            else baggageHead = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            char msg[50]; sprintf(msg, "Baggage TAG-%04d removed.", id);
            free(curr); msgOK(msg); return;
        }
        curr = curr->next;
    }
    msgERR("Baggage ID not found.");
}

void displayForward() {
    if (!baggageHead) { msgERR("No baggage records."); return; }
    printf("\n");
    boxTop();
    boxTitle("BAGGAGE MANIFEST  [FORWARD SCAN]");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();
    BaggageNode* curr = baggageHead;
    while (curr) {
        printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
            curr->tag, curr->passengerID,
            curr->ownerName, curr->weight, curr->status);
        curr = curr->next;
    }
    boxBottom();
}

void displayBackward() {
    if (!baggageHead) { msgERR("No baggage records."); return; }
    BaggageNode* tail = baggageHead;
    while (tail->next) tail = tail->next;
    printf("\n");
    boxTop();
    boxTitle("BAGGAGE MANIFEST  [REVERSE SCAN]");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();
    BaggageNode* curr = tail;
    while (curr) {
        printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
            curr->tag, curr->passengerID,
            curr->ownerName, curr->weight, curr->status);
        curr = curr->prev;
    }
    boxBottom();
}

void searchBaggage() {
    if (!baggageHead) { msgERR("No baggage records."); return; }
    int pid;
    printf("\n  Enter Passenger ID: "); scanf("%d", &pid);
    int found = 0;
    printf("\n");
    boxTop();
    boxTitle("BAGGAGE SEARCH RESULTS");
    boxSep();
    printf("  | %-10s | %-6s | %-18s | %-8s | %-12s |\n",
           "TAG","PAX ID","OWNER","WEIGHT","STATUS");
    boxSep();
    BaggageNode* curr = baggageHead;
    while (curr) {
        if (curr->passengerID == pid) {
            printf("  | %-10s | %-6d | %-18s | %-8.1f | %-12s |\n",
                curr->tag, curr->passengerID,
                curr->ownerName, curr->weight, curr->status);
            found++;
        }
        curr = curr->next;
    }
    boxBottom();
    if (!found) msgERR("No baggage found for this passenger.");
}

void baggageStatistics() {
    if (!baggageHead) { msgERR("No baggage records."); return; }
    int count = 0; float total = 0, heaviest = 0;
    BaggageNode* curr = baggageHead;
    while (curr) {
        count++; total += curr->weight;
        if (curr->weight > heaviest) heaviest = curr->weight;
        curr = curr->next;
    }
    printf("\n");
    boxTop();
    boxTitle("BAGGAGE LOAD REPORT");
    boxSep();
    printf("  | %-30s : %-30d |\n",   "Total Bags Checked",  count);
    printf("  | %-30s : %-29.1f  |\n","Total Weight (kg)",   total);
    printf("  | %-30s : %-29.1f  |\n","Average Weight (kg)", total/count);
    printf("  | %-30s : %-29.1f  |\n","Heaviest Bag (kg)",   heaviest);
    boxBottom();
}

void baggageMenu() {
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
            case 1: addBaggage();        break;
            case 2: removeBaggage();     break;
            case 3: displayForward();    break;
            case 4: displayBackward();   break;
            case 5: searchBaggage();     break;
            case 6: baggageStatistics(); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
