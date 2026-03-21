// ============================================================
//  MEMBER 1 — PASSENGER SERVICES
//  Data Structure: ARRAY
// ============================================================

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "ui.h"
#include "passengers.h"

// ─── Check if Passenger ID already exists ────────────────────
int passengerIDExists(struct Passenger passengers[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (passengers[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// ─── 1. Add Passenger ────────────────────────────────────────
void addPassenger(struct Passenger passengers[], int* count) {
    struct Passenger p;

    if (*count >= MAX_PASSENGERS) {
        msgERR("Passenger capacity full!"); return;
    }

    printf("\n");
    boxTop();
    boxTitle("NEW PASSENGER CHECK-IN");
    boxSep();
    boxEmpty();
    printf("  | Passenger ID    : "); scanf("%d", &p.id);

    if (passengerIDExists(passengers, *count, p.id)) {
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

    passengers[*count] = p;
    (*count)++;

    char msg[100];
    sprintf(msg, "Passenger '%s' checked in. (ID: %d)", p.name, p.id);
    msgOK(msg);
}

// ─── 2. Remove Passenger ─────────────────────────────────────
void removePassenger(struct Passenger passengers[], int* count) {
    int id, i, j;
    char msg[100];

    if (*count == 0) { msgERR("No passengers in system."); return; }

    printf("\n  Enter Passenger ID to remove: "); scanf("%d", &id);

    for (i = 0; i < *count; i++) {
        if (passengers[i].id == id) {
            sprintf(msg, "Passenger '%s' removed.", passengers[i].name);

            // Shift elements left
            for (j = i; j < *count - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*count)--;
            msgOK(msg);
            return;
        }
    }
    msgERR("Passenger ID not found.");
}

// ─── 3. Search Passenger ─────────────────────────────────────
void searchPassenger(struct Passenger passengers[], int count) {
    char query[MAX_NAME];
    char idStr[10];
    int i, found = 0;

    if (count == 0) { msgERR("No passengers in system."); return; }

    printf("\n  Search Passenger (Name or ID): "); scanf(" %[^\n]", query);

    printf("\n");
    boxTop();
    boxTitle("PASSENGER SEARCH RESULTS");
    boxSep();
    printf("  | %-5s | %-18s | %-4s | %-14s | %-8s | %-8s |\n",
           "ID","NAME","AGE","DESTINATION","FLIGHT","CLASS");
    boxSep();

    for (i = 0; i < count; i++) {
        sprintf(idStr, "%d", passengers[i].id);
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

// ─── 4. Display All Passengers ───────────────────────────────
void displayAllPassengers(struct Passenger passengers[], int count) {
    int i;
    char msg[60];

    if (count == 0) { msgERR("No passengers registered."); return; }

    printf("\n");
    boxTop();
    boxTitle("PASSENGER MANIFEST");
    boxSep();
    printf("  | %-5s | %-18s | %-4s | %-14s | %-8s | %-8s |\n",
           "ID","NAME","AGE","DESTINATION","FLIGHT","CLASS");
    boxSep();

    for (i = 0; i < count; i++) {
        printf("  | %-5d | %-18s | %-4d | %-14s | %-8s | %-8s |\n",
            passengers[i].id, passengers[i].name, passengers[i].age,
            passengers[i].destination, passengers[i].flightNumber,
            passengers[i].seatClass);
    }

    boxSep();
    sprintf(msg, "TOTAL PASSENGERS: %d", count);
    boxTitle(msg);
    boxBottom();
}

// ─── 5. Update Passenger ─────────────────────────────────────
void updatePassenger(struct Passenger passengers[], int count) {
    int id, i;

    if (count == 0) { msgERR("No passengers to update."); return; }

    printf("\n  Enter Passenger ID to update: "); scanf("%d", &id);

    for (i = 0; i < count; i++) {
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
            msgOK("Passenger record updated successfully.");
            return;
        }
    }
    msgERR("Passenger ID not found.");
}

// ─── 6. Passenger Statistics (Additional Function) ───────────
void passengerStatistics(struct Passenger passengers[], int count) {
    int i, eco = 0, bus = 0, fst = 0;

    if (count == 0) { msgERR("No passengers."); return; }

    for (i = 0; i < count; i++) {
        if (strcmp(passengers[i].seatClass, "Economy")  == 0) eco++;
        else if (strcmp(passengers[i].seatClass, "Business") == 0) bus++;
        else if (strcmp(passengers[i].seatClass, "First")    == 0) fst++;
    }

    printf("\n");
    boxTop();
    boxTitle("PASSENGER LOAD STATISTICS");
    boxSep();
    printf("  | %-30s : %-30d |\n", "Total Passengers", count);
    printf("  | %-30s : %-30d |\n", "Economy Class",    eco);
    printf("  | %-30s : %-30d |\n", "Business Class",   bus);
    printf("  | %-30s : %-30d |\n", "First Class",      fst);
    boxBottom();
}

// ─── Menu ─────────────────────────────────────────────────────
void passengerMenu(struct Passenger passengers[], int* count) {
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
            case 1: addPassenger(passengers, count);        break;
            case 2: removePassenger(passengers, count);     break;
            case 3: searchPassenger(passengers, *count);    break;
            case 4: displayAllPassengers(passengers, *count);break;
            case 5: updatePassenger(passengers, *count);    break;
            case 6: passengerStatistics(passengers, *count);break;
            case 0: break;
            default: msgERR("Invalid selection.");
        }
        if (c != 0) pressEnter();
    } while (c != 0);
}
