// ============================================================
//  MEMBER 6 — RUNWAY CONTROL
//  Data Structure: QUEUE
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "runway.h"

RunwayQueue runwayQueue;

void initQueue() {
    runwayQueue.front = NULL;
    runwayQueue.rear  = NULL;
    runwayQueue.size  = 0;
}

int isFlightInQueue(const char* fn) {
    QueueNode* curr = runwayQueue.front;
    while (curr) { if (strcmp(curr->flightNumber, fn) == 0) return 1; curr = curr->next; }
    return 0;
}

void enqueue() {
    QueueNode* n = (QueueNode*)malloc(sizeof(QueueNode));
    if (!n) { msgERR("Memory allocation failed."); return; }
    printf("\n");
    boxTop();
    boxTitle("ADD TO RUNWAY QUEUE");
    boxSep();
    boxEmpty();
    printf("  | Flight Number         : "); scanf(" %s", n->flightNumber);
    if (isFlightInQueue(n->flightNumber)) {
        msgERR("Flight already in runway queue!"); free(n); return;
    }
    printf("  | Destination           : "); scanf(" %[^\n]", n->destination);
    printf("  | Scheduled Time        : "); scanf(" %s", n->scheduledTime);
    printf("  | Type (Takeoff/Landing): "); scanf(" %s", n->type);
    printf("  | Priority (1=High/2=Normal): "); scanf("%d", &n->priority);
    n->next = NULL;
    boxEmpty();
    boxBottom();
    if (!runwayQueue.rear) { runwayQueue.front = runwayQueue.rear = n; }
    else { runwayQueue.rear->next = n; runwayQueue.rear = n; }
    runwayQueue.size++;
    char msg[80];
    sprintf(msg, "Flight %s queued for %s. Position: %d",
            n->flightNumber, n->type, runwayQueue.size);
    msgOK(msg);
}

void dequeue() {
    if (!runwayQueue.front) { msgERR("Runway queue is empty."); return; }
    QueueNode* temp = runwayQueue.front;
    runwayQueue.front = runwayQueue.front->next;
    if (!runwayQueue.front) runwayQueue.rear = NULL;
    runwayQueue.size--;
    char msg[80];
    sprintf(msg, "CLEARED: Flight %s — %s approved!", temp->flightNumber, temp->type);
    free(temp); msgOK(msg);
}

void peekQueue() {
    if (!runwayQueue.front) { msgERR("Runway queue is empty."); return; }
    printf("\n");
    boxTop();
    boxTitle("NEXT FOR RUNWAY CLEARANCE");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Flight",         runwayQueue.front->flightNumber);
    printf("  | %-20s : %-40s |\n", "Destination",    runwayQueue.front->destination);
    printf("  | %-20s : %-40s |\n", "Scheduled Time", runwayQueue.front->scheduledTime);
    printf("  | %-20s : %-40s |\n", "Type",           runwayQueue.front->type);
    printf("  | %-20s : %-40d |\n", "Priority",       runwayQueue.front->priority);
    boxBottom();
}

void displayQueue() {
    if (!runwayQueue.front) { msgERR("Runway queue is empty."); return; }
    printf("\n");
    boxTop();
    boxTitle("RUNWAY CONTROL QUEUE");
    boxSep();
    printf("  | %-4s | %-8s | %-14s | %-7s | %-8s | %-4s |\n",
           "POS","FLIGHT","DESTINATION","TIME","TYPE","PRI");
    boxSep();
    QueueNode* curr = runwayQueue.front; int pos = 1;
    while (curr) {
        printf("  | %-4d | %-8s | %-14s | %-7s | %-8s | %-4d |\n",
            pos++, curr->flightNumber, curr->destination,
            curr->scheduledTime, curr->type, curr->priority);
        curr = curr->next;
    }
    boxSep();
    char msg[50]; sprintf(msg, "TOTAL IN QUEUE: %d", runwayQueue.size);
    boxTitle(msg);
    boxBottom();
}

int isQueueEmpty() { return (runwayQueue.front == NULL); }

void runwayMenu() {
    int c;
    do {
        printHeader("RUNWAY CONTROL");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("RUNWAY CONTROL TOWER");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Flight to Runway Queue");
        boxRow("  2.  Clear Flight for Takeoff/Landing");
        boxRow("  3.  View Next Flight");
        boxRow("  4.  View Full Runway Queue");
        boxRow("  5.  Check Runway Status");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  RUNWAY CONTROL > "); scanf("%d", &c);
        switch(c) {
            case 1: enqueue();   break;
            case 2: dequeue();   break;
            case 3: peekQueue(); break;
            case 4: displayQueue(); break;
            case 5:
                if (isQueueEmpty()) msgOK("RUNWAY CLEAR. No flights in queue.");
                else { char m[60]; sprintf(m, "RUNWAY BUSY. %d flight(s) in queue.", runwayQueue.size); msgWARN(m); }
                break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
