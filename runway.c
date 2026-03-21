// ============================================================
//  MEMBER 6 — RUNWAY CONTROL
//  Data Structure: PRIORITY QUEUE
//  Priority 1 = Emergency (Highest)
//  Priority 2 = High
//  Priority 3 = Normal
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "runway.h"

// ─── Priority Label Helper ────────────────────────────────────
const char* priorityLabel(int p) {
    if (p == 1) return "EMERGENCY";
    if (p == 2) return "HIGH     ";
    return             "NORMAL   ";
}

// ─── Initialize Queue ─────────────────────────────────────────
void initQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear  = NULL;
    queue->size  = 0;
}

// ─── Create New Queue Node ────────────────────────────────────
struct QueueNode* createQueueNode(char* flightNumber, char* destination,
                                   char* scheduledTime, char* type, int priority) {
    struct QueueNode* newNode;
    newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(newNode->flightNumber,  flightNumber);
    strcpy(newNode->destination,   destination);
    strcpy(newNode->scheduledTime, scheduledTime);
    strcpy(newNode->type,          type);
    newNode->priority = priority;
    newNode->next     = NULL;

    return newNode;
}

// ─── Check if Queue is Empty ──────────────────────────────────
int isQueueEmpty(struct Queue* queue) {
    if (queue->front == NULL) return 1;
    else return 0;
}

// ─── Check Duplicate ──────────────────────────────────────────
int isFlightInQueue(struct Queue* queue, char* fn) {
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        if (strcmp(temp->flightNumber, fn) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

// ─── 1. Priority Enqueue ─────────────────────────────────────
// Lower priority number = higher priority
// Priority 1 (Emergency) inserted before Priority 2 and 3
// Priority 2 (High) inserted before Priority 3
void priorityEnqueue(struct Queue* queue) {
    char flightNumber[MAX_FLIGHT_NO], destination[MAX_DEST];
    char scheduledTime[MAX_TIME], type[10];
    int  priority;
    struct QueueNode* newNode;
    struct QueueNode* temp;
    char msg[100];

    printf("\n");
    boxTop();
    boxTitle("ADD TO RUNWAY QUEUE");
    boxSep();
    boxEmpty();
    printf("  | Flight Number              : "); scanf(" %s", flightNumber);

    if (isFlightInQueue(queue, flightNumber)) {
        msgERR("Flight already in runway queue!"); return;
    }

    printf("  | Destination               : "); scanf(" %[^\n]", destination);
    printf("  | Scheduled Time            : "); scanf(" %s", scheduledTime);
    printf("  | Type (Takeoff/Landing)    : "); scanf(" %s", type);
    printf("  | Priority (1=Emergency/2=High/3=Normal): "); scanf("%d", &priority);

    if (priority < 1 || priority > 3) {
        msgERR("Invalid priority! Enter 1, 2 or 3."); return;
    }

    boxEmpty();
    boxBottom();

    newNode = createQueueNode(flightNumber, destination,
                              scheduledTime, type, priority);
    if (newNode == NULL) return;

    // Insert based on priority
    // Case 1 — Queue is empty
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear  = newNode;

    // Case 2 — New node has highest priority (insert at front)
    } else if (newNode->priority < queue->front->priority) {
        newNode->next = queue->front;
        queue->front  = newNode;

    // Case 3 — Find correct position based on priority
    } else {
        temp = queue->front;
        while (temp->next != NULL &&
               temp->next->priority <= newNode->priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next    = newNode;

        // Update rear if inserted at end
        if (newNode->next == NULL) {
            queue->rear = newNode;
        }
    }

    queue->size++;

    sprintf(msg, "Flight %s [%s] added to queue. Position based on priority.",
            flightNumber, priorityLabel(priority));
    msgOK(msg);
}

// ─── 2. Dequeue — Clear Flight from Runway ───────────────────
void dequeue(struct Queue* queue) {
    struct QueueNode* temp;
    char msg[80];

    if (isQueueEmpty(queue)) { msgERR("Runway queue is empty."); return; }

    temp         = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    queue->size--;

    sprintf(msg, "CLEARED: Flight %s [%s] — %s approved!",
            temp->flightNumber, priorityLabel(temp->priority), temp->type);
    free(temp);
    msgOK(msg);
}

// ─── 3. Peek — View Next Flight ───────────────────────────────
void peekQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) { msgERR("Runway queue is empty."); return; }

    printf("\n");
    boxTop();
    boxTitle("NEXT FOR RUNWAY CLEARANCE");
    boxSep();
    printf("  | %-20s : %-40s |\n", "Flight",         queue->front->flightNumber);
    printf("  | %-20s : %-40s |\n", "Destination",    queue->front->destination);
    printf("  | %-20s : %-40s |\n", "Scheduled Time", queue->front->scheduledTime);
    printf("  | %-20s : %-40s |\n", "Type",           queue->front->type);
    printf("  | %-20s : %-40s |\n", "Priority",       priorityLabel(queue->front->priority));
    boxBottom();
}

// ─── 4. Display Full Queue ────────────────────────────────────
void displayQueue(struct Queue* queue) {
    struct QueueNode* temp;
    int pos = 1;
    char msg[50];

    if (isQueueEmpty(queue)) { msgERR("Runway queue is empty."); return; }

    printf("\n");
    boxTop();
    boxTitle("RUNWAY CONTROL QUEUE");
    boxSep();
    printf("  | %-4s | %-8s | %-14s | %-7s | %-8s | %-9s |\n",
           "POS","FLIGHT","DESTINATION","TIME","TYPE","PRIORITY");
    boxSep();

    temp = queue->front;
    while (temp != NULL) {
        printf("  | %-4d | %-8s | %-14s | %-7s | %-8s | %-9s |\n",
            pos++, temp->flightNumber, temp->destination,
            temp->scheduledTime, temp->type,
            priorityLabel(temp->priority));
        temp = temp->next;
    }

    boxSep();
    sprintf(msg, "TOTAL IN QUEUE: %d", queue->size);
    boxTitle(msg);
    boxBottom();
}

// ─── 5. Queue Statistics — Additional Function ───────────────
void queueStatistics(struct Queue* queue) {
    struct QueueNode* temp;
    int emergency = 0, high = 0, normal = 0;
    int takeoff = 0, landing = 0;

    if (isQueueEmpty(queue)) { msgERR("Runway queue is empty."); return; }

    temp = queue->front;
    while (temp != NULL) {
        if      (temp->priority == 1) emergency++;
        else if (temp->priority == 2) high++;
        else                          normal++;

        if (strcmp(temp->type, "Takeoff") == 0) takeoff++;
        else                                     landing++;

        temp = temp->next;
    }

    printf("\n");
    boxTop();
    boxTitle("RUNWAY QUEUE STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Flights in Queue", queue->size);
    printf("  | %-30s : %-30d |\n", "Emergency Priority",     emergency);
    printf("  | %-30s : %-30d |\n", "High Priority",          high);
    printf("  | %-30s : %-30d |\n", "Normal Priority",        normal);
    boxSep();
    printf("  | %-30s : %-30d |\n", "Takeoffs",               takeoff);
    printf("  | %-30s : %-30d |\n", "Landings",               landing);
    boxBottom();
}

// ─── Menu ─────────────────────────────────────────────────────
void runwayMenu(struct Queue* queue) {
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
        boxRow("  6.  Runway Queue Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  RUNWAY CONTROL > "); scanf("%d", &c);

        switch(c) {
            case 1: priorityEnqueue(queue); break;
            case 2: dequeue(queue);         break;
            case 3: peekQueue(queue);       break;
            case 4: displayQueue(queue);    break;
            case 5:
                if (isQueueEmpty(queue))
                    msgOK("RUNWAY CLEAR. No flights in queue.");
                else {
                    char m[60];
                    sprintf(m, "RUNWAY BUSY. %d flight(s) in queue.", queue->size);
                    msgWARN(m);
                }
                break;
            case 6: queueStatistics(queue); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
