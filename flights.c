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

FlightNode* flightHead = NULL;

int flightExists(const char* fn) {
    FlightNode* curr = flightHead;
    while (curr) {
        if (strcmp(curr->flightNumber, fn) == 0) return 1;
        curr = curr->next;
    }
    return 0;
}

void addFlight() {
    FlightNode* n = (FlightNode*)malloc(sizeof(FlightNode));
    if (!n) { msgERR("Memory allocation failed."); return; }
    printf("\n");
    boxTop();
    boxTitle("SCHEDULE NEW FLIGHT");
    boxSep();
    boxEmpty();
    printf("  | Flight Number   : "); scanf(" %s", n->flightNumber);
    if (flightExists(n->flightNumber)) {
        msgERR("Flight number already exists!"); free(n); return;
    }
    printf("  | Origin          : "); scanf(" %[^\n]", n->origin);
    printf("  | Destination     : "); scanf(" %[^\n]", n->destination);
    printf("  | Departure Time  : "); scanf(" %s", n->departureTime);
    printf("  | Arrival Time    : "); scanf(" %s", n->arrivalTime);
    printf("  | Gate            : "); scanf(" %s", n->gate);
    printf("  | Aircraft Type   : "); scanf(" %s", n->aircraft);
    printf("  | Total Seats     : "); scanf("%d", &n->totalSeats);
    n->availableSeats = n->totalSeats;
    strcpy(n->status, "On-Time");
    n->next = NULL; n->prev = NULL;
    boxEmpty();
    boxBottom();
    if (!flightHead) { flightHead = n; }
    else {
        FlightNode* t = flightHead;
        while (t->next) t = t->next;
        t->next = n; n->prev = t;
    }
    char msg[120];
    sprintf(msg, "Flight %s to %s scheduled!", n->flightNumber, n->destination);
    msgOK(msg);
}

void removeFlight() {
    if (!flightHead) { msgERR("No flights in system."); return; }
    char fn[MAX_FLIGHT_NO];
    printf("\n  Enter Flight Number to cancel: "); scanf(" %s", fn);
    FlightNode *curr = flightHead, *prev = NULL;
    while (curr) {
        if (strcmp(curr->flightNumber, fn) == 0) {
            if (prev) prev->next = curr->next;
            else flightHead = curr->next;
            if (curr->next) curr->next->prev = prev;
            char msg[60]; sprintf(msg, "Flight %s cancelled and removed.", fn);
            free(curr); msgOK(msg); return;
        }
        prev = curr; curr = curr->next;
    }
    msgERR("Flight not found.");
}

void searchFlight() {
    if (!flightHead) { msgERR("No flights in system."); return; }
    char query[MAX_DEST];
    printf("\n  Search (Flight No. or Destination): "); scanf(" %[^\n]", query);
    int found = 0;
    printf("\n");
    boxTop();
    boxTitle("FLIGHT SEARCH RESULTS");
    boxSep();
    printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();
    FlightNode* curr = flightHead;
    while (curr) {
        if (strstr(curr->flightNumber, query) || strstr(curr->destination, query)) {
            printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5d | %-7s |\n",
                curr->flightNumber, curr->origin, curr->destination,
                curr->departureTime, curr->arrivalTime,
                curr->availableSeats, curr->status);
            found++;
        }
        curr = curr->next;
    }
    boxBottom();
    if (!found) msgERR("No matching flight found.");
}

void displayAllFlights() {
    if (!flightHead) { msgERR("No flights scheduled."); return; }
    printf("\n");
    boxTop();
    boxTitle("FLIGHT OPERATIONS BOARD");
    boxSep();
    printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5s | %-7s |\n",
           "FLIGHT","FROM","TO","DEP","ARR","SEATS","STATUS");
    boxSep();
    FlightNode* curr = flightHead; int count = 0;
    while (curr) {
        printf("  | %-8s | %-13s | %-13s | %-7s | %-7s | %-5d | %-7s |\n",
            curr->flightNumber, curr->origin, curr->destination,
            curr->departureTime, curr->arrivalTime,
            curr->availableSeats, curr->status);
        curr = curr->next; count++;
    }
    boxSep();
    char msg[50]; sprintf(msg, "TOTAL FLIGHTS: %d", count);
    boxTitle(msg);
    boxBottom();
}

void updateFlightStatus() {
    if (!flightHead) { msgERR("No flights in system."); return; }
    char fn[MAX_FLIGHT_NO];
    printf("\n  Enter Flight Number: "); scanf(" %s", fn);
    FlightNode* curr = flightHead;
    while (curr) {
        if (strcmp(curr->flightNumber, fn) == 0) {
            printf("  Status (On-Time/Delayed/Cancelled/Boarding): ");
            scanf(" %s", curr->status);
            msgOK("Flight status updated."); return;
        }
        curr = curr->next;
    }
    msgERR("Flight not found.");
}

void countFlights() {
    int count = 0, ontime = 0, delayed = 0, cancelled = 0;
    FlightNode* curr = flightHead;
    while (curr) {
        count++;
        if (strcmp(curr->status, "On-Time")   == 0) ontime++;
        else if (strcmp(curr->status, "Delayed")   == 0) delayed++;
        else if (strcmp(curr->status, "Cancelled") == 0) cancelled++;
        curr = curr->next;
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

void flightMenu() {
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
            case 1: addFlight();         break;
            case 2: removeFlight();      break;
            case 3: searchFlight();      break;
            case 4: displayAllFlights(); break;
            case 5: updateFlightStatus();break;
            case 6: countFlights();      break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
