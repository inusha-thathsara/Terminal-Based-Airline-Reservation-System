#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "types.h"

// ============================================================
//  MEMBER 1 — PASSENGER SERVICES
// ============================================================

extern Passenger passengers[];
extern int       passengerCount;

int  passengerIDExists(int id);
void addPassenger();
void removePassenger();
void searchPassenger();
void displayAllPassengers();
void updatePassenger();
void passengerStatistics();
void passengerMenu();

#endif
