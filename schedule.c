// ============================================================
//  MEMBER 7 — FLIGHT SCHEDULE
//  Data Structure: ARRAY
//  Operations: Bubble Sort, Insertion Sort, Selection Sort,
//              Recursive Search
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "ui.h"
#include "schedule.h"

// ─── Check Duplicate ──────────────────────────────────────────
int scheduleEntryExists(struct ScheduleEntry schedule[], int count, char* fn) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(schedule[i].flightNumber, fn) == 0) return 1;
    }
    return 0;
}

// ─── Add Schedule Entry ───────────────────────────────────────
void addScheduleEntry(struct ScheduleEntry schedule[], int* count) {
    struct ScheduleEntry e;
    char msg[60];

    if (*count >= MAX_SCHEDULE) { msgERR("Schedule is full."); return; }

    printf("\n");
    boxTop();
    boxTitle("ADD FLIGHT TO TIMETABLE");
    boxSep();
    boxEmpty();
    printf("  | Flight Number   : "); scanf(" %s",  e.flightNumber);

    if (scheduleEntryExists(schedule, *count, e.flightNumber)) {
        msgERR("Flight already in schedule!"); return;
    }

    printf("  | Origin          : "); scanf(" %[^\n]", e.origin);
    printf("  | Destination     : "); scanf(" %[^\n]", e.destination);
    printf("  | Departure Time  : "); scanf(" %s",  e.departureTime);
    printf("  | Arrival Time    : "); scanf(" %s",  e.arrivalTime);
    printf("  | Gate            : "); scanf(" %s",  e.gate);
    printf("  | Aircraft        : "); scanf(" %s",  e.aircraft);
    printf("  | Available Seats : "); scanf("%d",  &e.availableSeats);
    strcpy(e.status, "On-Time");
    boxEmpty();
    boxBottom();

    schedule[*count] = e;
    (*count)++;

    sprintf(msg, "Flight %s added to timetable.", e.flightNumber);
    msgOK(msg);
}

// ─── Display Schedule ─────────────────────────────────────────
void displaySortedSchedule(struct ScheduleEntry schedule[], int count) {
    int i;
    char msg[50];

    if (count == 0) { msgERR("Schedule is empty."); return; }

    printf("\n");
    boxTop();
    boxTitle("FLIGHT TIMETABLE");
    boxSep();
    printf("  | %-3s | %-8s | %-12s | %-12s | %-6s | %-6s | %-5s | %-8s |\n",
           "#","FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();

    for (i = 0; i < count; i++) {
        printf("  | %-3d | %-8s | %-12s | %-12s | %-6s | %-6s | %-5d | %-8s |\n",
            i+1, schedule[i].flightNumber, schedule[i].origin,
            schedule[i].destination, schedule[i].departureTime,
            schedule[i].arrivalTime, schedule[i].availableSeats,
            schedule[i].status);
    }

    boxSep();
    sprintf(msg, "TOTAL SCHEDULED FLIGHTS: %d", count);
    boxTitle(msg);
    boxBottom();
}

// ─── 1. Bubble Sort — by Departure Time ──────────────────────
void bubbleSort(struct ScheduleEntry schedule[], int count) {
    int i, j, k;
    bool swapped;
    struct ScheduleEntry temp;

    msgINFO("Applying Bubble Sort — sorting by departure time...");

    for (i = 0; i < count - 1; i++) {
        swapped = false;

        for (j = 0; j < count - 1 - i; j++) {
            if (strcmp(schedule[j].departureTime,
                       schedule[j+1].departureTime) > 0) {
                // Swap
                temp          = schedule[j];
                schedule[j]   = schedule[j+1];
                schedule[j+1] = temp;
                swapped = true;
            }
        }

        // Print after each pass
        printf("  Pass %d: ", i+1);
        for (k = 0; k < count; k++)
            printf("[%s] ", schedule[k].departureTime);
        printf("\n");

        // Early exit if no swaps
        if (!swapped) break;
    }

    msgOK("Schedule sorted by departure time.");
    displaySortedSchedule(schedule, count);
}

// ─── 2. Insertion Sort — by Destination A-Z ──────────────────
void insertionSort(struct ScheduleEntry schedule[], int count) {
    int i, j, k;
    struct ScheduleEntry key;

    msgINFO("Applying Insertion Sort — sorting by destination A-Z...");

    for (i = 1; i < count; i++) {
        key = schedule[i];
        j   = i;

        while (j > 0 && strcmp(schedule[j-1].destination,
                                key.destination) > 0) {
            schedule[j] = schedule[j-1];
            j--;
        }
        schedule[j] = key;

        // Print after each pass
        printf("  Pass %d: ", i);
        for (k = 0; k < count; k++)
            printf("[%s] ", schedule[k].destination);
        printf("\n");
    }

    msgOK("Schedule sorted by destination.");
    displaySortedSchedule(schedule, count);
}

// ─── 3. Selection Sort — by Flight Number ────────────────────
void selectionSort(struct ScheduleEntry schedule[], int count) {
    int i, j, k, minIdx;
    struct ScheduleEntry temp;

    msgINFO("Applying Selection Sort — sorting by flight number...");

    for (i = 0; i < count - 1; i++) {
        minIdx = i;

        for (j = i + 1; j < count; j++) {
            if (strcmp(schedule[j].flightNumber,
                       schedule[minIdx].flightNumber) < 0) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            temp           = schedule[i];
            schedule[i]    = schedule[minIdx];
            schedule[minIdx] = temp;
        }

        // Print after each pass
        printf("  Pass %d: ", i+1);
        for (k = 0; k < count; k++)
            printf("[%s] ", schedule[k].flightNumber);
        printf("\n");
    }

    msgOK("Schedule sorted by flight number.");
    displaySortedSchedule(schedule, count);
}

// ─── 4. Recursive Search ─────────────────────────────────────
void recursiveSearch(struct ScheduleEntry schedule[], int count,
                     int index, char* query) {
    // Base case — reached end of array
    if (index >= count) return;

    // Check current entry
    if (strstr(schedule[index].flightNumber, query) ||
        strstr(schedule[index].destination,  query) ||
        strstr(schedule[index].origin,       query)) {
        printf("  | %-3d | %-8s | %-12s | %-12s | %-6s | %-6s | %-5d | %-8s |\n",
            index+1, schedule[index].flightNumber, schedule[index].origin,
            schedule[index].destination, schedule[index].departureTime,
            schedule[index].arrivalTime, schedule[index].availableSeats,
            schedule[index].status);
    }

    // Recursive call — check next entry
    recursiveSearch(schedule, count, index + 1, query);
}

// ─── 5. Schedule Statistics — Additional Function ─────────────
void scheduleStatistics(struct ScheduleEntry schedule[], int count) {
    int i, j;
    int ontime = 0, delayed = 0, cancelled = 0, totalSeats = 0;
    char busiest[MAX_DEST] = "None";
    int busiestCount = 0;

    if (count == 0) { msgERR("Schedule is empty."); return; }

    for (i = 0; i < count; i++) {
        totalSeats += schedule[i].availableSeats;

        if      (strcmp(schedule[i].status, "On-Time")   == 0) ontime++;
        else if (strcmp(schedule[i].status, "Delayed")   == 0) delayed++;
        else if (strcmp(schedule[i].status, "Cancelled") == 0) cancelled++;

        // Find busiest destination
        int destCount = 0;
        for (j = 0; j < count; j++) {
            if (strcmp(schedule[j].destination,
                       schedule[i].destination) == 0) destCount++;
        }
        if (destCount > busiestCount) {
            busiestCount = destCount;
            strcpy(busiest, schedule[i].destination);
        }
    }

    printf("\n");
    boxTop();
    boxTitle("FLIGHT SCHEDULE STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Scheduled Flights", count);
    printf("  | %-30s : %-30d |\n", "On-Time Flights",         ontime);
    printf("  | %-30s : %-30d |\n", "Delayed Flights",         delayed);
    printf("  | %-30s : %-30d |\n", "Cancelled Flights",       cancelled);
    printf("  | %-30s : %-30d |\n", "Total Available Seats",   totalSeats);
    printf("  | %-30s : %-30s |\n", "Busiest Destination",     busiest);
    boxBottom();
}

// ─── Menu ─────────────────────────────────────────────────────
void scheduleMenu(struct ScheduleEntry schedule[], int* count) {
    int c;
    char q[MAX_DEST];

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
        boxRow("  7.  Schedule Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  FLIGHT SCHEDULE > "); scanf("%d", &c);

        switch(c) {
            case 1: addScheduleEntry(schedule, count);      break;
            case 2: bubbleSort(schedule, *count);           break;
            case 3: insertionSort(schedule, *count);        break;
            case 4: selectionSort(schedule, *count);        break;
            case 5:
                printf("\n  Search (Flight / Origin / Destination): ");
                scanf(" %[^\n]", q);
                printf("\n");
                boxTop();
                boxTitle("TIMETABLE SEARCH RESULTS");
                boxSep();
                printf("  | %-3s | %-8s | %-12s | %-12s | %-6s | %-6s | %-5s | %-8s |\n",
                    "#","FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
                boxSep();
                recursiveSearch(schedule, *count, 0, q);
                boxBottom();
                break;
            case 6: displaySortedSchedule(schedule, *count); break;
            case 7: scheduleStatistics(schedule, *count);    break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
