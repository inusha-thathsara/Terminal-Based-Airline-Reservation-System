// ============================================================
//  MEMBER 1 — PASSENGER SERVICES
//  Data Structure: ARRAY
// ============================================================

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "passengers.h"

Passenger passengers[MAX_PASSENGERS];
int       passengerCount = 0;

int passengerIDExists(int id) {
    for (int i = 0; i < passengerCount; i++)
        if (passengers[i].id == id) return 1;
    return 0;
}

void addPassenger() {
    if (passengerCount >= MAX_PASSENGERS) {
        msgERR("Passenger capacity full!"); return;
    }
    Passenger p;
    printf("\n");
    boxTop();
    boxTitle("NEW PASSENGER CHECK-IN");
    boxSep();
    boxEmpty();
    printf("  | Passenger ID    : "); scanf("%d", &p.id);
    if (passengerIDExists(p.id)) {
        msgERR("Passenger ID already exists! Use a unique ID."); return;
    }
    printf("  | Full Name       : "); scanf(" %[^\n]", p.name);
    printf("  | Age             : "); scanf("%d", &p.age);
    printf("  | Passport No.    : "); scanf(" %s", p.passport);
    printf("  | Destination     : "); scanf(" %[^\n]", p.destination);
    printf("  | Flight Number   : "); scanf(" %s", p.flightNumber);
    printf("  | Class (Economy/Business/First): "); scanf(" %s", p.seatClass);
    boxEmpty();
    boxBottom();
    passengers[passengerCount++] = p;
    char msg[120];
    sprintf(msg, "Passenger '%s' checked in. (ID: %d)", p.name, p.id);
    msgOK(msg);
}

void removePassenger() {
    if (passengerCount == 0) { msgERR("No passengers in system."); return; }
    int id;
    printf("\n  Enter Passenger ID to remove: "); scanf("%d", &id);
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            char msg[120];
            sprintf(msg, "Passenger '%s' removed.", passengers[i].name);
            for (int j = i; j < passengerCount - 1; j++)
                passengers[j] = passengers[j + 1];
            passengerCount--;
            msgOK(msg); return;
        }
    }
    msgERR("Passenger ID not found.");
}

void searchPassenger() {
    if (passengerCount == 0) { msgERR("No passengers in system."); return; }
    char query[MAX_NAME];
    printf("\n  Search Passenger (Name or ID): "); scanf(" %[^\n]", query);
    int found = 0;
    printf("\n");
    boxTop();
    boxTitle("PASSENGER SEARCH RESULTS");
    boxSep();
    printf("  | %-5s | %-18s | %-4s | %-14s | %-8s | %-8s |\n",
           "ID","NAME","AGE","DESTINATION","FLIGHT","CLASS");
    boxSep();
    for (int i = 0; i < passengerCount; i++) {
        char idStr[10]; sprintf(idStr, "%d", passengers[i].id);
        if (strstr(passengers[i].name, query) || strcmp(idStr, query) == 0) {
            printf("  | %-5d | %-18s | %-4d | %-14s | %-8s | %-8s |\n",
                passengers[i].id, passengers[i].name, passengers[i].age,
                passengers[i].destination, passengers[i].flightNumber,
                passengers[i].seatClass);
            found++;
        }
    }
    boxBottom();
    if (!found) msgERR("No matching passenger found.");
    else { char m[50]; sprintf(m, "%d record(s) found.", found); msgINFO(m); }
}

void displayAllPassengers() {
    if (passengerCount == 0) { msgERR("No passengers registered."); return; }
    printf("\n");
    boxTop();
    boxTitle("PASSENGER MANIFEST");
    boxSep();
    printf("  | %-5s | %-18s | %-4s | %-14s | %-8s | %-8s |\n",
           "ID","NAME","AGE","DESTINATION","FLIGHT","CLASS");
    boxSep();
    for (int i = 0; i < passengerCount; i++)
        printf("  | %-5d | %-18s | %-4d | %-14s | %-8s | %-8s |\n",
            passengers[i].id, passengers[i].name, passengers[i].age,
            passengers[i].destination, passengers[i].flightNumber,
            passengers[i].seatClass);
    boxSep();
    char msg[60]; sprintf(msg, "TOTAL PASSENGERS: %d", passengerCount);
    boxTitle(msg);
    boxBottom();
}

void updatePassenger() {
    if (passengerCount == 0) { msgERR("No passengers to update."); return; }
    int id;
    printf("\n  Enter Passenger ID to update: "); scanf("%d", &id);
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            printf("\n");
            boxTop();
            boxTitle("UPDATE PASSENGER RECORD");
            boxSep();
            printf("  | New Full Name   : "); scanf(" %[^\n]", passengers[i].name);
            printf("  | New Age         : "); scanf("%d", &passengers[i].age);
            printf("  | New Destination : "); scanf(" %[^\n]", passengers[i].destination);
            printf("  | New Flight No.  : "); scanf(" %s", passengers[i].flightNumber);
            printf("  | New Class       : "); scanf(" %s", passengers[i].seatClass);
            boxBottom();
            msgOK("Passenger record updated successfully."); return;
        }
    }
    msgERR("Passenger ID not found.");
}

void passengerStatistics() {
    if (passengerCount == 0) { msgERR("No passengers."); return; }
    int eco = 0, bus = 0, fst = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].seatClass, "Economy") == 0) eco++;
        else if (strcmp(passengers[i].seatClass, "Business") == 0) bus++;
        else if (strcmp(passengers[i].seatClass, "First") == 0) fst++;
    }
    printf("\n");
    boxTop();
    boxTitle("PASSENGER LOAD STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Passengers", passengerCount);
    printf("  | %-30s : %-30d |\n", "Economy Class",    eco);
    printf("  | %-30s : %-30d |\n", "Business Class",   bus);
    printf("  | %-30s : %-30d |\n", "First Class",      fst);
    boxBottom();
}

void passengerMenu() {
    int c;
    do {
        printHeader("PASSENGER SERVICES");
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("PASSENGER SERVICES");
        boxEmpty();
        boxSep();
        boxRow("  1.  New Passenger Check-In");
        boxRow("  2.  Remove Passenger");
        boxRow("  3.  Search Passenger");
        boxRow("  4.  View Passenger Manifest");
        boxRow("  5.  Update Passenger Record");
        boxRow("  6.  Passenger Load Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Return to Main Terminal");
        boxEmpty();
        boxDbl();
        printf("\n  PASSENGER SERVICES > "); scanf("%d", &c);
        switch(c) {
            case 1: addPassenger();        break;
            case 2: removePassenger();     break;
            case 3: searchPassenger();     break;
            case 4: displayAllPassengers();break;
            case 5: updatePassenger();     break;
            case 6: passengerStatistics(); break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
