/* schedule.c - Emergency Management (Priority Queue + Sorting + Recursion) */
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "schedule.h"

struct PriorityQueue emergencyQueue;
struct ScheduleEntry schedule[100];
int scheduleCount = 0;

void initPriorityQueue() {
    emergencyQueue.front = NULL;
    emergencyQueue.rear = NULL;
}

struct PQNode* createPQNode() {
    struct PQNode* newNode = (struct PQNode*)malloc(sizeof(struct PQNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    return newNode;
}

int isPQEmpty() { return emergencyQueue.front == NULL; }

const char* priorityLabel(int p) {
    if (p == 1) return "EMERGENCY";
    if (p == 2) return "HIGH";
    return "NORMAL";
}

int flightInPQ(char* fn) {
    struct PQNode* temp = emergencyQueue.front;
    while (temp) {
        if (manualStrCmp(temp->flightNumber, fn) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

void addEmergencyFlight() {
    struct PQNode* newNode, *temp;

    newNode = createPQNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("ADD EMERGENCY FLIGHT");
    boxSep();
    printf("  | Flight Number   : "); scanf(" %s", newNode->flightNumber);
    if (flightInPQ(newNode->flightNumber)) {
        msgERR("Flight already in queue!"); free(newNode); return;
    }
    printf("  | Destination     : "); scanf(" %[^\n]", newNode->destination);
    printf("  | Scheduled Time  : "); scanf(" %s", newNode->scheduledTime);
    printf("  | Type (Takeoff/Landing): "); scanf(" %s", newNode->type);
    printf("  | Reason          : "); scanf(" %[^\n]", newNode->reason);
    printf("  | Priority (1=Emergency, 2=High, 3=Normal): ");
    scanf("%d", &newNode->priority);
    if (newNode->priority < 1 || newNode->priority > 3) newNode->priority = 3;
    boxLine();

    if (!emergencyQueue.front) {
        emergencyQueue.front = newNode;
        emergencyQueue.rear = newNode;
    } else if (newNode->priority < emergencyQueue.front->priority) {
        newNode->next = emergencyQueue.front;
        emergencyQueue.front = newNode;
    } else {
        temp = emergencyQueue.front;
        while (temp->next && temp->next->priority <= newNode->priority)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        if (!newNode->next) emergencyQueue.rear = newNode;
    }
    msgOK("Flight added with priority.");
}

void clearEmergencyFlight() {
    struct PQNode* temp;

    if (isPQEmpty()) { msgERR("Queue is empty."); return; }

    temp = emergencyQueue.front;
    emergencyQueue.front = emergencyQueue.front->next;
    if (!emergencyQueue.front) emergencyQueue.rear = NULL;
    free(temp);
    msgOK("Flight cleared.");
}

void displayEmergencyQueue() {
    struct PQNode* temp;
    int pos = 1;

    if (isPQEmpty()) { msgERR("Queue is empty."); return; }

    printf("\n");
    boxLine();
    boxTitle("EMERGENCY QUEUE");
    boxSep();
    printf("  | %-3s | %-8s | %-12s | %-7s | %-9s |\n",
           "POS", "FLIGHT", "DESTINATION", "TIME", "PRIORITY");
    boxSep();

    temp = emergencyQueue.front;
    while (temp) {
        printf("  | %-3d | %-8s | %-12s | %-7s | %-9s |\n",
            pos++, temp->flightNumber, temp->destination,
            temp->scheduledTime, priorityLabel(temp->priority));
        temp = temp->next;
    }
    boxLine();
}

void copyToSchedule() {
    struct PQNode* temp;
    scheduleCount = 0;

    temp = emergencyQueue.front;
    while (temp && scheduleCount < 100) {
        manualStrCpy(schedule[scheduleCount].flightNumber, temp->flightNumber);
        manualStrCpy(schedule[scheduleCount].destination, temp->destination);
        manualStrCpy(schedule[scheduleCount].departureTime, temp->scheduledTime);
        manualStrCpy(schedule[scheduleCount].origin, temp->type);
        schedule[scheduleCount].priority = temp->priority;
        manualStrCpy(schedule[scheduleCount].status, priorityLabel(temp->priority));
        scheduleCount++;
        temp = temp->next;
    }
}

void sortByPriority() {
    if (scheduleCount == 0) { msgERR("No data to sort."); return; }
    msgINFO("Sorting by urgency level...");
    for (int i = 0; i < scheduleCount - 1; i++) {
        for (int j = 0; j < scheduleCount - 1 - i; j++) {
            if (schedule[j].priority > schedule[j+1].priority) {
                struct ScheduleEntry temp = schedule[j];
                schedule[j] = schedule[j+1];
                schedule[j+1] = temp;
            }
        }
    }
    msgOK("Sorted by urgency.");
    for (int i = 0; i < scheduleCount; i++) {
        printf("  %s [%s]\n", schedule[i].flightNumber, schedule[i].status);
    }
}

void sortByTime() {
    if (scheduleCount == 0) { msgERR("No data to sort."); return; }
    msgINFO("Sorting by departure time...");
    for (int i = 1; i < scheduleCount; i++) {
        struct ScheduleEntry key = schedule[i];
        int j = i - 1;
        while (j >= 0 && manualStrCmp(schedule[j].departureTime, key.departureTime) > 0) {
            schedule[j+1] = schedule[j];
            j--;
        }
        schedule[j+1] = key;
    }
    msgOK("Sorted by time.");
    for (int i = 0; i < scheduleCount; i++) {
        printf("  %s [%s]\n", schedule[i].flightNumber, schedule[i].departureTime);
    }
}

void sortByFlightNo() {
    if (scheduleCount == 0) { msgERR("No data to sort."); return; }
    msgINFO("Sorting by flight number...");
    for (int i = 0; i < scheduleCount - 1; i++) {
        int minIdx = i;
        for (int j = i+1; j < scheduleCount; j++) {
            if (manualStrCmp(schedule[j].flightNumber, schedule[minIdx].flightNumber) < 0)
                minIdx = j;
        }
        if (minIdx != i) {
            struct ScheduleEntry temp = schedule[i];
            schedule[i] = schedule[minIdx];
            schedule[minIdx] = temp;
        }
    }
    msgOK("Sorted by flight number.");
    for (int i = 0; i < scheduleCount; i++) {
        printf("  %s\n", schedule[i].flightNumber);
    }
}

void recursiveSearch(int index, char* query) {
    if (index >= scheduleCount) return;
    if (manualStrStr(schedule[index].flightNumber, query) ||
        manualStrStr(schedule[index].destination, query)) {
        printf("  %s | %s | %s | %s\n",
            schedule[index].flightNumber,
            schedule[index].destination,
            schedule[index].departureTime,
            schedule[index].status);
    }
    recursiveSearch(index + 1, query);
}

void searchEmergencyFlight() {
    char query[50];
    if (scheduleCount == 0) { msgERR("No data to search."); return; }

    printf("\n  Search (Flight No. or Destination): ");
    scanf(" %[^\n]", query);

    printf("\n");
    boxLine();
    boxTitle("SEARCH RESULTS");
    boxSep();
    printf("  | %-8s | %-12s | %-8s | %-10s |\n",
           "FLIGHT", "DESTINATION", "TIME", "PRIORITY");
    boxSep();
    recursiveSearch(0, query);
    boxLine();
}

void emergencyMenu() {
    int c;
    do {
        printHeader("EMERGENCY MANAGEMENT");
        boxDbl();
        boxEmpty();
        boxTitle("EMERGENCY MANAGEMENT");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Emergency Flight");
        boxRow("  2.  Clear Flight");
        boxRow("  3.  View Emergency Queue");
        boxRow("  4.  Sort by Urgency");
        boxRow("  5.  Sort by Time");
        boxRow("  6.  Sort by Flight Number");
        boxRow("  7.  Search Flight");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  EMERGENCY > "); scanf("%d", &c);
        switch(c) {
            case 1: addEmergencyFlight(); break;
            case 2: clearEmergencyFlight(); break;
            case 3: displayEmergencyQueue(); break;
            case 4: copyToSchedule(); sortByPriority(); break;
            case 5: copyToSchedule(); sortByTime(); break;
            case 6: copyToSchedule(); sortByFlightNo(); break;
            case 7: copyToSchedule(); searchEmergencyFlight(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
