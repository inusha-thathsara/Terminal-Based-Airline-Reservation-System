/* passengers.c - Passenger Services (Array) */
#include <stdio.h>
#include "ui.h"
#include "utils.h"
#include "passengers.h"

struct Passenger passengers[100];
int passengerCount = 0;

void initPassengers() {
    passengerCount = 0;
}

int passengerExists(int id) {
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) return 1;
    }
    return 0;
}

void addPassenger() {
    struct Passenger p;
    int position, i;

    if (passengerCount >= 100) {
        msgERR("Passenger list is full!"); return;
    }

    printf("\n");
    boxLine();
    boxTitle("ADD PASSENGER");
    boxSep();
    printf("  Total passengers: %d\n", passengerCount);
    printf("  \n");
    printf("  Check-in position:\n");
    printf("    1 = Priority / Urgent Check-in\n");
    printf("    %d = Normal Check-in\n", passengerCount + 1);
    printf("    Any number between = Insert at that position\n");
    boxLine();
    printf("  Select position: ");
    scanf("%d", &position);

    if (position < 1 || position > passengerCount + 1) {
        msgERR("Invalid position!"); return;
    }

    printf("\n");
    boxLine();
    boxTitle("PASSENGER DETAILS");
    boxSep();
    printf("  | Passenger ID    : "); scanf("%d", &p.id);
    if (passengerExists(p.id)) {
        msgERR("Passenger ID already exists!"); return;
    }
    printf("  | Full Name       : "); scanf(" %[^\n]", p.name);
    printf("  | Age             : "); scanf("%d", &p.age);
    printf("  | Passport No.    : "); scanf(" %s", p.passport);
    printf("  | Destination     : "); scanf(" %[^\n]", p.destination);
    printf("  | Flight Number   : "); scanf(" %s", p.flightNumber);
    printf("  | Class (Economy/Business/First): "); scanf(" %s", p.seatClass);
    boxLine();

    for (i = passengerCount; i >= position; i--)
        passengers[i] = passengers[i - 1];
    passengers[position - 1] = p;
    passengerCount++;

    if (position == 1)
        msgOK("Passenger added via PRIORITY CHECK-IN.");
    else if (position == passengerCount)
        msgOK("Passenger added via NORMAL CHECK-IN.");
    else
        msgOK("Passenger added at specified position.");
}

void removePassenger() {
    int id, i;

    if (passengerCount == 0) { msgERR("No passengers in system."); return; }

    printf("\n");
    boxLine();
    boxTitle("REMOVE PASSENGER");
    boxSep();
    printf("  Enter Passenger ID to remove: ");
    scanf("%d", &id);
    boxLine();

    for (i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            for (int j = i; j < passengerCount - 1; j++)
                passengers[j] = passengers[j + 1];
            passengerCount--;
            msgOK("Passenger removed successfully.");
            return;
        }
    }
    msgERR("Passenger ID not found.");
}

void searchPassenger() {
    char query[50];
    int found = 0;

    if (passengerCount == 0) { msgERR("No passengers."); return; }

    printf("\n  Search (Name or ID): "); scanf(" %[^\n]", query);

    printf("\n");
    boxLine();
    boxTitle("SEARCH RESULTS");
    boxSep();
    printf("  | %-8s | %-20s | %-4s | %-15s | %-8s | %-9s |\n",
           "ID", "NAME", "AGE", "DESTINATION", "FLIGHT", "CLASS");
    boxSep();

    for (int i = 0; i < passengerCount; i++) {
        char idStr[12];
        sprintf(idStr, "%d", passengers[i].id);
        if (manualStrStr(passengers[i].name, query) || manualStrCmp(idStr, query) == 0) {
            printf("  | %-8d | %-20s | %-4d | %-15s | %-8s | %-9s |\n",
                passengers[i].id, passengers[i].name, passengers[i].age,
                passengers[i].destination, passengers[i].flightNumber,
                passengers[i].seatClass);
            found++;
        }
    }
    boxLine();
    if (!found) msgERR("No matching passenger found.");
}

void displayAllPassengers() {
    if (passengerCount == 0) { msgERR("No passengers."); return; }

    printf("\n");
    boxLine();
    boxTitle("PASSENGER MANIFEST");
    boxSep();
    printf("  | %-8s | %-20s | %-4s | %-15s | %-8s | %-9s |\n",
           "ID", "NAME", "AGE", "DESTINATION", "FLIGHT", "CLASS");
    boxSep();

    for (int i = 0; i < passengerCount; i++) {
        printf("  | %-8d | %-20s | %-4d | %-15s | %-8s | %-9s |\n",
            passengers[i].id, passengers[i].name, passengers[i].age,
            passengers[i].destination, passengers[i].flightNumber,
            passengers[i].seatClass);
    }
    boxSep();
    char msg[50];
    sprintf(msg, "TOTAL PASSENGERS: %d", passengerCount);
    boxTitle(msg);
    boxLine();
}

void updatePassenger() {
    int id;

    if (passengerCount == 0) { msgERR("No passengers."); return; }

    printf("\n  Enter Passenger ID: "); scanf("%d", &id);

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].id == id) {
            printf("\n");
            boxLine();
            boxTitle("UPDATE PASSENGER");
            boxSep();
            printf("  | New Name        : "); scanf(" %[^\n]", passengers[i].name);
            printf("  | New Age         : "); scanf("%d", &passengers[i].age);
            printf("  | New Destination : "); scanf(" %[^\n]", passengers[i].destination);
            printf("  | New Flight No.  : "); scanf(" %s", passengers[i].flightNumber);
            printf("  | New Class       : "); scanf(" %s", passengers[i].seatClass);
            boxLine();
            msgOK("Passenger updated.");
            return;
        }
    }
    msgERR("Passenger ID not found.");
}

void passengerStatistics() {
    int eco = 0, bus = 0, fst = 0;

    if (passengerCount == 0) { msgERR("No passengers."); return; }

    for (int i = 0; i < passengerCount; i++) {
        if      (manualStrCmp(passengers[i].seatClass, "Economy") == 0) eco++;
        else if (manualStrCmp(passengers[i].seatClass, "Business") == 0) bus++;
        else if (manualStrCmp(passengers[i].seatClass, "First") == 0) fst++;
    }

    printf("\n");
    boxLine();
    boxTitle("PASSENGER STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Passengers", passengerCount);
    printf("  | %-30s : %-30d |\n", "Economy Class",    eco);
    printf("  | %-30s : %-30d |\n", "Business Class",   bus);
    printf("  | %-30s : %-30d |\n", "First Class",      fst);
    boxLine();
}

void passengerMenu() {
    int c;
    do {
        printHeader("PASSENGER SERVICES");
        boxDbl();
        boxEmpty();
        boxTitle("PASSENGER SERVICES");
        boxEmpty();
        boxSep();
        boxRow("  1.  Add Passenger");
        boxRow("  2.  Remove Passenger");
        boxRow("  3.  Search Passenger");
        boxRow("  4.  View All Passengers");
        boxRow("  5.  Update Passenger");
        boxRow("  6.  Passenger Statistics");
        boxEmpty();
        boxSep();
        boxRow("  0.  Back to Main Menu");
        boxEmpty();
        boxDbl();
        printf("\n  PASSENGER > "); scanf("%d", &c);
        switch(c) {
            case 1: addPassenger(); break;
            case 2: removePassenger(); break;
            case 3: searchPassenger(); break;
            case 4: displayAllPassengers(); break;
            case 5: updatePassenger(); break;
            case 6: passengerStatistics(); break;
            case 0: break;
            default: msgERR("Invalid option.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
