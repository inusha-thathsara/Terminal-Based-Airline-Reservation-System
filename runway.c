/* runway.c - Runway Control (Queue) */
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "runway.h"

struct Queue runwayQueue;

void initQueue() {
    runwayQueue.front = NULL;
    runwayQueue.rear = NULL;
}

struct QueueNode* createQueueNode() {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    return newNode;
}

int isQueueEmpty() { return runwayQueue.front == NULL; }

int isQueueFull() {
    int count = 0;
    struct QueueNode* temp = runwayQueue.front;
    while (temp) { count++; temp = temp->next; }
    return count >= 50;
}

int flightInQueue(char* fn) {
    struct QueueNode* temp = runwayQueue.front;
    while (temp) {
        if (manualStrCmp(temp->flightNumber, fn) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

void addToRunwayQueue() {
    struct QueueNode* newNode;

    if (isQueueFull()) { msgERR("Runway queue is full!"); return; }

    newNode = createQueueNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("ADD TO RUNWAY QUEUE");
    boxSep();
    printf("  | Flight Number   : "); scanf(" %s", newNode->flightNumber);
    if (flightInQueue(newNode->flightNumber)) {
        msgERR("Flight already in queue!"); free(newNode); return;
    }
    printf("  | Destination     : "); scanf(" %[^\n]", newNode->destination);
    printf("  | Scheduled Time  : "); scanf(" %s", newNode->scheduledTime);
    printf("  | Type (Takeoff/Landing): "); scanf(" %s", newNode->type);
    boxLine();

    if (!runwayQueue.rear) {
        runwayQueue.front = newNode;
        runwayQueue.rear = newNode;
    } else {
        runwayQueue.rear->next = newNode;
        runwayQueue.rear = newNode;
    }
    msgOK("Flight added to runway queue.");
}

void clearRunway() {
    struct QueueNode* temp;

    if (isQueueEmpty()) { msgERR("Queue is empty."); return; }

    temp = runwayQueue.front;
    runwayQueue.front = runwayQueue.front->next;
    if (!runwayQueue.front) runwayQueue.rear = NULL;
    free(temp);
    msgOK("Flight cleared for takeoff/landing.");
}

void viewNextFlight() {
    if (isQueueEmpty()) { msgERR("Queue is empty."); return; }

    printf("\n");
    boxLine();
    boxTitle("NEXT FLIGHT");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Flight", runwayQueue.front->flightNumber);
    printf("  | %-20s : %-40s |\n", "Destination", runwayQueue.front->destination);
    printf("  | %-20s : %-40s |\n", "Time", runwayQueue.front->scheduledTime);
    printf("  | %-20s : %-40s |\n", "Type", runwayQueue.front->type);
    boxLine();
}

void displayRunwayQueue() {
    struct QueueNode* temp;
    int pos = 1;

    if (isQueueEmpty()) { msgERR("Queue is empty."); return; }

    printf("\n");
    boxLine();
    boxTitle("RUNWAY QUEUE");
    boxSep();
    printf("  | %-4s | %-8s | %-14s | %-7s | %-8s |\n",
           "POS", "FLIGHT", "DESTINATION", "TIME", "TYPE");
    boxSep();

    temp = runwayQueue.front;
    while (temp) {
        printf("  | %-4d | %-8s | %-14s | %-7s | %-8s |\n",
            pos++, temp->flightNumber, temp->destination,
            temp->scheduledTime, temp->type);
        temp = temp->next;
    }
    boxLine();
}

void runwayMenu() {
    int c;
    do {
        printHeader("RUNWAY CONTROL");
        boxDbl();
        boxEmpty();
        boxTitle("RUNWAY CONTROL");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Flight to Runway Queue");
        boxRow("  2.  Clear Flight (Takeoff/Landing)");
        boxRow("  3.  View Next Flight");
        boxRow("  4.  View Full Queue");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  RUNWAY > "); scanf("%d", &c);
        switch(c) {
            case 1: addToRunwayQueue(); break;
            case 2: clearRunway(); break;
            case 3: viewNextFlight(); break;
            case 4: displayRunwayQueue(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
