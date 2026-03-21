// ============================================================
//  MEMBER 2 — FLIGHT OPERATIONS
//  Data Structure: SINGLY LINKED LIST
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "flights.h"

// ─── Initialize List ──────────────────────────────────────────
void initFlightList(struct FlightList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// ─── Create New Flight Node ───────────────────────────────────
struct FlightNode* createFlightNode(char* flightNumber, char* origin,
                                     char* destination, char* departureTime,
                                     char* arrivalTime, char* gate,
                                     char* aircraft, int totalSeats) {
    struct FlightNode* newNode;
    newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(newNode->flightNumber,  flightNumber);
    strcpy(newNode->origin,        origin);
    strcpy(newNode->destination,   destination);
    strcpy(newNode->departureTime, departureTime);
    strcpy(newNode->arrivalTime,   arrivalTime);
    strcpy(newNode->gate,          gate);
    strcpy(newNode->aircraft,      aircraft);
    newNode->totalSeats     = totalSeats;
    newNode->availableSeats = totalSeats;
    strcpy(newNode->status, "On-Time");
    newNode->next = NULL;

    return newNode;
}

// ─── Check Duplicate ──────────────────────────────────────────
int flightExists(struct FlightList* list, char* fn) {
    struct FlightNode* temp = list->head;
    while (temp != NULL) {
        if (strcmp(temp->flightNumber, fn) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

// ─── 1. Add Flight (Insert Rear) ─────────────────────────────
void addFlight(struct FlightList* list) {
    char flightNumber[MAX_FLIGHT_NO], origin[MAX_DEST];
    char destination[MAX_DEST], departureTime[MAX_TIME];
    char arrivalTime[MAX_TIME], gate[10], aircraft[20];
    int  totalSeats;
    struct FlightNode* newNode;

    printf("\n");
    boxTop();
    boxTitle("SCHEDULE NEW FLIGHT");
    boxSep();
    boxEmpty();
    printf("  | Flight Number   : "); scanf(" %s", flightNumber);

    if (flightExists(list, flightNumber)) {
        msgERR("Flight number already exists!"); return;
    }

    printf("  | Origin          : "); scanf(" %[^\n]", origin);
    printf("  | Destination     : "); scanf(" %[^\n]", destination);
    printf("  | Departure Time  : "); scanf(" %s", departureTime);
    printf("  | Arrival Time    : "); scanf(" %s", arrivalTime);
    printf("  | Gate            : "); scanf(" %s", gate);
    printf("  | Aircraft Type   : "); scanf(" %s", aircraft);
    printf("  | Total Seats     : "); scanf("%d", &totalSeats);
    boxEmpty();
    boxBottom();

    newNode = createFlightNode(flightNumber, origin, destination,
                               departureTime, arrivalTime, gate,
                               aircraft, totalSeats);
    if (newNode == NULL) return;

    // Insert at rear — singly linked list
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    char msg[100];
    sprintf(msg, "Flight %s to %s scheduled!", flightNumber, destination);
    msgOK(msg);
}

// ─── 2. Remove Flight ─────────────────────────────────────────
void removeFlight(struct FlightList* list) {
    char fn[MAX_FLIGHT_NO];
    struct FlightNode* temp;
    struct FlightNode* prev;
    char msg[60];

    if (list->head == NULL) { msgERR("No flights in system."); return; }

    printf("\n  Enter Flight Number to cancel: "); scanf(" %s", fn);

    temp = list->head;
    prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->flightNumber, fn) == 0) {
            if (prev == NULL) {
                list->head = temp->next;
            } else {
                prev->next = temp->next;
            }
            if (temp->next == NULL) {
                list->tail = prev;
            }
            sprintf(msg, "Flight %s cancelled and removed.", fn);
            free(temp);
            msgOK(msg);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    msgERR("Flight not found.");
}

// ─── 3. Search Flight ─────────────────────────────────────────
void searchFlight(struct FlightList* list) {
    char query[MAX_DEST];
    struct FlightNode* temp;
    int found = 0;

    if (list->head == NULL) { msgERR("No flights in system."); return; }

    printf("\n  Search (Flight No. or Destination): "); scanf(" %[^\n]", query);

    printf("\n");
    boxTop();
    boxTitle("FLIGHT SEARCH RESULTS");
    boxSep();
    printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();

    temp = list->head;
    while (temp != NULL) {
        if (strstr(temp->flightNumber, query) || strstr(temp->destination, query)) {
            printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5d | %-7s |\n",
                temp->flightNumber, temp->origin, temp->destination,
                temp->departureTime, temp->arrivalTime,
                temp->availableSeats, temp->status);
            found++;
        }
        temp = temp->next;
    }
    boxBottom();
    if (!found) msgERR("No matching flight found.");
}

// ─── 4. Display All Flights ───────────────────────────────────
void displayAllFlights(struct FlightList* list) {
    struct FlightNode* temp;
    int count = 0;
    char msg[50];

    if (list->head == NULL) { msgERR("No flights scheduled."); return; }

    printf("\n");
    boxTop();
    boxTitle("FLIGHT OPERATIONS BOARD");
    boxSep();
    printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();

    temp = list->head;
    while (temp != NULL) {
        printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5d | %-7s |\n",
            temp->flightNumber, temp->origin, temp->destination,
            temp->departureTime, temp->arrivalTime,
            temp->availableSeats, temp->status);
        temp = temp->next;
        count++;
    }

    boxSep();
    sprintf(msg, "TOTAL FLIGHTS: %d", count);
    boxTitle(msg);
    boxBottom();
}

// ─── 5. Update Flight Status ──────────────────────────────────
void updateFlightStatus(struct FlightList* list) {
    char fn[MAX_FLIGHT_NO];
    struct FlightNode* temp;

    if (list->head == NULL) { msgERR("No flights in system."); return; }

    printf("\n  Enter Flight Number: "); scanf(" %s", fn);

    temp = list->head;
    while (temp != NULL) {
        if (strcmp(temp->flightNumber, fn) == 0) {
            printf("  Status (On-Time/Delayed/Cancelled/Boarding): ");
            scanf(" %s", temp->status);
            msgOK("Flight status updated.");
            return;
        }
        temp = temp->next;
    }
    msgERR("Flight not found.");
}

// ─── 6. Count Flights — Additional Function ───────────────────
void countFlights(struct FlightList* list) {
    struct FlightNode* temp;
    int count = 0, ontime = 0, delayed = 0, cancelled = 0;

    temp = list->head;
    while (temp != NULL) {
        count++;
        if      (strcmp(temp->status, "On-Time")   == 0) ontime++;
        else if (strcmp(temp->status, "Delayed")   == 0) delayed++;
        else if (strcmp(temp->status, "Cancelled") == 0) cancelled++;
        temp = temp->next;
    }

    printf("\n");
    boxTop();
    boxTitle("FLIGHT OPERATIONS SUMMARY");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Flights",  count);
    printf("  | %-30s : %-30d |\n", "On-Time",        ontime);
    printf("  | %-30s : %-30d |\n", "Delayed",        delayed);
    printf("  | %-30s : %-30d |\n", "Cancelled",      cancelled);
    boxBottom();
}

// ─── Menu ─────────────────────────────────────────────────────
void flightMenu(struct FlightList* list) {
    int c;
    do {
        printHeader("FLIGHT OPERATIONS");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("FLIGHT OPERATIONS CONTROL");
        boxEmpty();
        boxSep();
        boxRow("  1.  Schedule New Flight");
        boxRow("  2.  Cancel / Remove Flight");
        boxRow("  3.  Search Flight");
        boxRow("  4.  View All Flights");
        boxRow("  5.  Update Flight Status");
        boxRow("  6.  Flight Operations Summary");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  FLIGHT OPS > "); scanf("%d", &c);

        switch(c) {
            case 1: addFlight(list);          break;
            case 2: removeFlight(list);       break;
            case 3: searchFlight(list);       break;
            case 4: displayAllFlights(list);  break;
            case 5: updateFlightStatus(list); break;
            case 6: countFlights(list);       break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
