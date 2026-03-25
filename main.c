
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"
#include "passengers.h"
#include "flights.h"
#include "baggage.h"
#include "gates.h"
#include "boarding.h"
#include "runway.h"
#include "schedule.h"

int main() {
    // Initialize all data structures
    initPassengers();
    initFlightList();
    initBaggageList();
    initGateList();
    initStack();
    initQueue();
    initPriorityQueue();

    splashScreen();

    int choice;
    do {
        printHeader("MAIN TERMINAL");

        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("LIVE DEPARTURES BOARD");
        boxEmpty();
        boxDbl();

        // Display live departures board
        if (flightList.head == NULL) {
            boxEmpty();
            boxTitle("-- NO FLIGHTS SCHEDULED --");
            boxEmpty();
            boxLine();
        } else {
            struct FlightNode* curr = flightList.head;
            int count = 0;
            printf("  | %-9s | %-13s | %-13s | %-7s | %-5s | %-7s |\n",
                   "FLIGHT", "FROM", "TO", "TIME", "GATE", "STATUS");
            boxSep();
            while (curr && count < 5) {
                printf("  | %-9s | %-13s | %-13s | %-7s | %-5s | %-7s |\n",
                    curr->flightNumber, curr->origin, curr->destination,
                    curr->departureTime, curr->gate, curr->status);
                curr = curr->next;
                count++;
            }
            boxLine();
        }

        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("MAIN MENU");
        boxEmpty();
        boxSep();
        boxRow("  1.  PASSENGER SERVICES");
        boxRow("  2.  FLIGHT OPERATIONS");
        boxRow("  3.  BAGGAGE SERVICES");
        boxRow("  4.  GATE CONTROL");
        boxRow("  5.  BOARDING CONTROL");
        boxRow("  6.  RUNWAY CONTROL");
        boxRow("  7.  EMERGENCY MANAGEMENT");
        boxEmpty();
        boxSep();
        boxRow("  0.  EXIT SYSTEM");
        boxEmpty();
        boxDbl();
        printf("\n  SKYPORT > "); scanf("%d", &choice);

        switch(choice) {
            case 1: passengerMenu(); break;
            case 2: flightMenu(); break;
            case 3: baggageMenu(); break;
            case 4: gateMenu(); break;
            case 5: boardingMenu(); break;
            case 6: runwayMenu(); break;
            case 7: emergencyMenu(); break;
            case 0:
                clrscr();
                printf("\n\n");
                boxDbl();
                boxEmpty();
                boxTitle("LOGGING OUT OF SKYPORT TERMINAL");
                boxEmpty();
                boxTitle("Thank you. Have a safe flight!");
                boxEmpty();
                boxDbl();
                printf("\n");
                break;
            default:
                msgERR("Invalid selection.");
                pressEnter();
        }
    } while (choice != 0);

    return 0;
}
