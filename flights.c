/* flights.c - Flight Operations (Singly Linked List) */
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "flights.h"

struct FlightList flightList;

void initFlightList() {
    flightList.head = NULL;
    flightList.tail = NULL;
}

struct FlightNode* createFlightNode() {
    struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));
    if (!newNode) return NULL;
    newNode->next = NULL;
    return newNode;
}

int flightExists(char* fn) {
    struct FlightNode* temp = flightList.head;
    while (temp) {
        if (manualStrCmp(temp->flightNumber, fn) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

int countFlights() {
    int count = 0;
    struct FlightNode* temp = flightList.head;
    while (temp) { count++; temp = temp->next; }
    return count;
}

void addFlight() {
    struct FlightNode* newNode;
    int position, i, total;

    total = countFlights();
    if (total >= 50) { msgERR("Flight list is full!"); return; }

    printf("\n");
    boxLine();
    boxTitle("ADD FLIGHT");
    boxSep();
    printf("  Total flights: %d\n", total);
    printf("  \n");
    printf("  Schedule position:\n");
    printf("    1 = Urgent Flight (Top of board)\n");
    printf("    %d = Normal Schedule (End of board)\n", total + 1);
    printf("    Any number between = Insert at that position\n");
    boxLine();
    printf("  Select position: ");
    scanf("%d", &position);

    if (position < 1 || position > total + 1) {
        msgERR("Invalid position!"); return;
    }

    newNode = createFlightNode();
    if (!newNode) return;

    printf("\n");
    boxLine();
    boxTitle("FLIGHT DETAILS");
    boxSep();
    printf("  | Flight Number   : "); scanf(" %s", newNode->flightNumber);
    if (flightExists(newNode->flightNumber)) {
        msgERR("Flight number exists!"); free(newNode); return;
    }
    printf("  | Origin          : "); scanf(" %[^\n]", newNode->origin);
    printf("  | Destination     : "); scanf(" %[^\n]", newNode->destination);
    printf("  | Departure Time  : "); scanf(" %s", newNode->departureTime);
    printf("  | Arrival Time    : "); scanf(" %s", newNode->arrivalTime);
    printf("  | Gate            : "); scanf(" %s", newNode->gate);
    printf("  | Aircraft        : "); scanf(" %s", newNode->aircraft);
    printf("  | Total Seats     : "); scanf("%d", &newNode->totalSeats);
    newNode->availableSeats = newNode->totalSeats;
    manualStrCpy(newNode->status, "On-Time");
    boxLine();

    if (position == 1) {
        newNode->next = flightList.head;
        flightList.head = newNode;
        if (!flightList.tail) flightList.tail = newNode;
        msgOK("Flight added as URGENT.");
    } else if (position == total + 1) {
        newNode->next = NULL;
        if (!flightList.head) {
            flightList.head = newNode;
            flightList.tail = newNode;
        } else {
            flightList.tail->next = newNode;
            flightList.tail = newNode;
        }
        msgOK("Flight scheduled normally.");
    } else {
        struct FlightNode* temp = flightList.head;
        for (i = 1; i < position - 1; i++) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        if (!newNode->next) flightList.tail = newNode;
        msgOK("Flight inserted at specified position.");
    }
}

void removeFlight() {
    char fn[10];
    struct FlightNode *temp, *prev;

    if (!flightList.head) { msgERR("No flights."); return; }

    printf("\n");
    boxLine();
    boxTitle("REMOVE FLIGHT");
    boxSep();
    printf("  Enter Flight Number to remove: ");
    scanf(" %s", fn);
    boxLine();

    if (manualStrCmp(flightList.head->flightNumber, fn) == 0) {
        temp = flightList.head;
        flightList.head = flightList.head->next;
        if (!flightList.head) flightList.tail = NULL;
        free(temp);
        msgOK("Flight removed.");
        return;
    }

    prev = flightList.head;
    temp = flightList.head->next;
    while (temp) {
        if (manualStrCmp(temp->flightNumber, fn) == 0) {
            prev->next = temp->next;
            if (!temp->next) flightList.tail = prev;
            free(temp);
            msgOK("Flight removed.");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    msgERR("Flight not found.");
}

void searchFlight() {
    char query[50];
    struct FlightNode* temp;
    int found = 0;

    if (!flightList.head) { msgERR("No flights."); return; }

    printf("\n  Search (Flight No. or Destination): "); scanf(" %[^\n]", query);

    printf("\n");
    boxLine();
    boxTitle("FLIGHT SEARCH");
    boxSep();
    printf("  | %-8s | %-12s | %-12s | %-6s | %-8s |\n",
           "FLIGHT", "FROM", "TO", "DEPART", "STATUS");
    boxSep();

    temp = flightList.head;
    while (temp) {
        if (manualStrStr(temp->flightNumber, query) || manualStrStr(temp->destination, query)) {
            printf("  | %-8s | %-12s | %-12s | %-6s | %-8s |\n",
                temp->flightNumber, temp->origin, temp->destination,
                temp->departureTime, temp->status);
            found++;
        }
        temp = temp->next;
    }
    boxLine();
    if (!found) msgERR("No matching flight.");
}

void displayAllFlights() {
    struct FlightNode* temp;
    int count = 0;

    if (!flightList.head) { msgERR("No flights."); return; }

    printf("\n");
    boxLine();
    boxTitle("FLIGHT SCHEDULE");
    boxSep();
    printf("  | %-8s | %-12s | %-12s | %-6s | %-6s | %-5s | %-8s |\n",
           "FLIGHT", "FROM", "TO", "DEP", "ARR", "SEATS", "STATUS");
    boxSep();

    temp = flightList.head;
    while (temp) {
        printf("  | %-8s | %-12s | %-12s | %-6s | %-6s | %-5d | %-8s |\n",
            temp->flightNumber, temp->origin, temp->destination,
            temp->departureTime, temp->arrivalTime,
            temp->availableSeats, temp->status);
        temp = temp->next;
        count++;
    }
    boxSep();
    char msg[50];
    sprintf(msg, "TOTAL FLIGHTS: %d", count);
    boxTitle(msg);
    boxLine();
}

void updateFlightStatus() {
    char fn[10];
    struct FlightNode* temp;

    if (!flightList.head) { msgERR("No flights."); return; }

    printf("\n  Enter Flight Number: "); scanf(" %s", fn);

    temp = flightList.head;
    while (temp) {
        if (manualStrCmp(temp->flightNumber, fn) == 0) {
            printf("  Status (On-Time/Delayed/Cancelled): ");
            scanf(" %s", temp->status);
            msgOK("Status updated.");
            return;
        }
        temp = temp->next;
    }
    msgERR("Flight not found.");
}

void flightStatistics() {
    struct FlightNode* temp;
    int count = 0, ontime = 0, delayed = 0, cancelled = 0, totalSeats = 0;

    temp = flightList.head;
    while (temp) {
        count++;
        if      (manualStrCmp(temp->status, "On-Time") == 0) ontime++;
        else if (manualStrCmp(temp->status, "Delayed") == 0) delayed++;
        else if (manualStrCmp(temp->status, "Cancelled") == 0) cancelled++;
        totalSeats += temp->availableSeats;
        temp = temp->next;
    }

    printf("\n");
    boxLine();
    boxTitle("FLIGHT STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Flights", count);
    printf("  | %-30s : %-30d |\n", "On-Time", ontime);
    printf("  | %-30s : %-30d |\n", "Delayed", delayed);
    printf("  | %-30s : %-30d |\n", "Cancelled", cancelled);
    printf("  | %-30s : %-30d |\n", "Available Seats", totalSeats);
    boxLine();
}

void flightMenu() {
    int c;
    do {
        printHeader("FLIGHT OPERATIONS");
        boxDbl();
        boxEmpty();
        boxTitle("FLIGHT OPERATIONS");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Flight");
        boxRow("  2.  Remove Flight");
        boxRow("  3.  Search Flight");
        boxRow("  4.  View All Flights");
        boxRow("  5.  Update Flight Status");
        boxRow("  6.  Flight Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  FLIGHT > "); scanf("%d", &c);
        switch(c) {
            case 1: addFlight(); break;
            case 2: removeFlight(); break;
            case 3: searchFlight(); break;
            case 4: displayAllFlights(); break;
            case 5: updateFlightStatus(); break;
            case 6: flightStatistics(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
