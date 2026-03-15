// ============================================================
//  MEMBER 7 — FLIGHT SCHEDULE
//  Data Structure: SORTING ALGORITHMS + RECURSION
// ============================================================

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "schedule.h"

ScheduleEntry schedule[MAX_SCHEDULE];
int           scheduleCount = 0;

int scheduleEntryExists(const char* fn) {
    for (int i = 0; i < scheduleCount; i++)
        if (strcmp(schedule[i].flightNumber, fn) == 0) return 1;
    return 0;
}

void addScheduleEntry() {
    if (scheduleCount >= MAX_SCHEDULE) { msgERR("Schedule is full."); return; }
    ScheduleEntry* e = &schedule[scheduleCount];
    printf("\n");
    boxTop();
    boxTitle("ADD FLIGHT TO TIMETABLE");
    boxSep();
    boxEmpty();
    printf("  | Flight Number   : "); scanf(" %s",  e->flightNumber);
    if (scheduleEntryExists(e->flightNumber)) {
        msgERR("Flight already in schedule!"); return;
    }
    printf("  | Origin          : "); scanf(" %[^\n]", e->origin);
    printf("  | Destination     : "); scanf(" %[^\n]", e->destination);
    printf("  | Departure Time  : "); scanf(" %s",  e->departureTime);
    printf("  | Arrival Time    : "); scanf(" %s",  e->arrivalTime);
    printf("  | Gate            : "); scanf(" %s",  e->gate);
    printf("  | Aircraft        : "); scanf(" %s",  e->aircraft);
    printf("  | Available Seats : "); scanf("%d",  &e->availableSeats);
    strcpy(e->status, "On-Time");
    boxEmpty();
    boxBottom();
    scheduleCount++;
    char msg[60]; sprintf(msg, "Flight %s added to timetable.", e->flightNumber);
    msgOK(msg);
}

void displaySortedSchedule() {
    if (scheduleCount == 0) { msgERR("Schedule is empty."); return; }
    printf("\n");
    boxTop();
    boxTitle("FLIGHT TIMETABLE");
    boxSep();
    printf("  | %-3s | %-8s | %-12s | %-12s | %-6s | %-6s | %-5s | %-8s |\n",
           "#","FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();
    for (int i = 0; i < scheduleCount; i++)
        printf("  | %-3d | %-8s | %-12s | %-12s | %-6s | %-6s | %-5d | %-8s |\n",
            i+1, schedule[i].flightNumber, schedule[i].origin,
            schedule[i].destination, schedule[i].departureTime,
            schedule[i].arrivalTime, schedule[i].availableSeats,
            schedule[i].status);
    boxSep();
    char msg[50]; sprintf(msg, "TOTAL SCHEDULED FLIGHTS: %d", scheduleCount);
    boxTitle(msg);
    boxBottom();
}

void bubbleSort() {
    msgINFO("Applying Bubble Sort — sorting by departure time...");
    for (int i = 0; i < scheduleCount - 1; i++)
        for (int j = 0; j < scheduleCount - i - 1; j++)
            if (strcmp(schedule[j].departureTime, schedule[j+1].departureTime) > 0) {
                ScheduleEntry tmp = schedule[j];
                schedule[j] = schedule[j+1]; schedule[j+1] = tmp;
            }
    msgOK("Schedule sorted by departure time.");
    displaySortedSchedule();
}

void insertionSort() {
    msgINFO("Applying Insertion Sort — sorting by destination A-Z...");
    for (int i = 1; i < scheduleCount; i++) {
        ScheduleEntry key = schedule[i]; int j = i - 1;
        while (j >= 0 && strcmp(schedule[j].destination, key.destination) > 0) {
            schedule[j+1] = schedule[j]; j--;
        }
        schedule[j+1] = key;
    }
    msgOK("Schedule sorted by destination.");
    displaySortedSchedule();
}

void selectionSort() {
    msgINFO("Applying Selection Sort — sorting by flight number...");
    for (int i = 0; i < scheduleCount - 1; i++) {
        int minIdx = i;
        for (int j = i+1; j < scheduleCount; j++)
            if (strcmp(schedule[j].flightNumber, schedule[minIdx].flightNumber) < 0)
                minIdx = j;
        if (minIdx != i) {
            ScheduleEntry tmp = schedule[i];
            schedule[i] = schedule[minIdx]; schedule[minIdx] = tmp;
        }
    }
    msgOK("Schedule sorted by flight number.");
    displaySortedSchedule();
}

void recursiveSearch(int index, char* query) {
    if (index >= scheduleCount) return;
    if (strstr(schedule[index].flightNumber, query) ||
        strstr(schedule[index].destination,  query) ||
        strstr(schedule[index].origin,       query))
        printf("  | %-3d | %-8s | %-12s | %-12s | %-6s | %-6s | %-5d | %-8s |\n",
            index+1, schedule[index].flightNumber, schedule[index].origin,
            schedule[index].destination, schedule[index].departureTime,
            schedule[index].arrivalTime, schedule[index].availableSeats,
            schedule[index].status);
    recursiveSearch(index + 1, query);
}

void scheduleMenu() {
    int c;
    do {
        printHeader("FLIGHT SCHEDULE");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("FLIGHT TIMETABLE MANAGEMENT");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Flight to Timetable");
        boxRow("  2.  Sort by Departure Time  (Bubble Sort)");
        boxRow("  3.  Sort by Destination A-Z (Insertion Sort)");
        boxRow("  4.  Sort by Flight Number   (Selection Sort)");
        boxRow("  5.  Search Timetable        (Recursive Search)");
        boxRow("  6.  View Full Timetable");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  FLIGHT SCHEDULE > "); scanf("%d", &c);
        switch(c) {
            case 1: addScheduleEntry();    break;
            case 2: bubbleSort();          break;
            case 3: insertionSort();       break;
            case 4: selectionSort();       break;
            case 5: {
                char q[MAX_DEST];
                printf("\n  Search (Flight / Origin / Destination): ");
                scanf(" %[^\n]", q);
                printf("\n");
                boxTop();
                boxTitle("TIMETABLE SEARCH RESULTS");
                boxSep();
                printf("  | %-3s | %-8s | %-12s | %-12s | %-6s | %-6s | %-5s | %-8s |\n",
                    "#","FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
                boxSep();
                recursiveSearch(0, q);
                boxBottom();
                break;
            }
            case 6: displaySortedSchedule(); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
