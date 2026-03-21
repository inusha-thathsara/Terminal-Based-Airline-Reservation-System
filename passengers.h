#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "types.h"

// ============================================================
//  MEMBER 1 — PASSENGER SERVICES (ARRAY)
// ============================================================

int  passengerIDExists(struct Passenger passengers[], int count, int id);
void addPassenger(struct Passenger passengers[], int* count);
void removePassenger(struct Passenger passengers[], int* count);
void searchPassenger(struct Passenger passengers[], int count);
void displayAllPassengers(struct Passenger passengers[], int count);
void updatePassenger(struct Passenger passengers[], int count);
void passengerStatistics(struct Passenger passengers[], int count);
void passengerMenu(struct Passenger passengers[], int* count);

#endif
