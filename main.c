// ============================================================
//  SKYPORT TERMINAL — MAIN
//  Airport Flight Management System
//  Group Assignment — 7 Members
// ============================================================

#include <stdio.h>
#include "types.h"
#include "ui.h"
#include "passengers.h"
#include "flights.h"
#include "baggage.h"
#include "gates.h"
#include "boarding.h"
#include "runway.h"
#include "schedule.h"

int main() {
    initQueue();
    splashScreen();

    int choice;
    do {
        printHeader("MAIN TERMINAL");
        printFlightBoard();
        printf("\n");
        boxDbl();
        boxEmpty();
        boxTitle("M A I N   M E N U");
        boxEmpty();
        boxSep();
        boxRow("  1.  PASSENGER SERVICES          Check-in & Passenger Records");
        boxRow("  2.  FLIGHT OPERATIONS           Schedule & Flight Control");
        boxRow("  3.  BAGGAGE SERVICES            Baggage Check-in & Tracking");
        boxRow("  4.  GATE CONTROL                Gate Assignment & Status");
        boxRow("  5.  BOARDING CONTROL            Passenger Boarding Management");
        boxRow("  6.  RUNWAY CONTROL              Takeoff & Landing Queue");
        boxRow("  7.  FLIGHT SCHEDULE             Timetable & Sorting");
        boxEmpty();
        boxSep();
        boxRow("  0.  EXIT SYSTEM");
        boxEmpty();
        boxDbl();
        printf("\n  SKYPORT > Enter Selection: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: passengerMenu(); break;
            case 2: flightMenu();    break;
            case 3: baggageMenu();   break;
            case 4: gateMenu();      break;
            case 5: boardingMenu();  break;
            case 6: runwayMenu();    break;
            case 7: scheduleMenu();  break;
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
                msgERR("Invalid selection. Please try again.");
                pressEnter();
        }
    } while (choice != 0);

    return 0;
}
