/* passengers.h - Passenger Services Header (Array) */
#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "types.h"

extern struct Passenger passengers[100];
extern int passengerCount;

void initPassengers(void);
int passengerExists(int id);
void addPassenger(void);
void removePassenger(void);
void searchPassenger(void);
void displayAllPassengers(void);
void updatePassenger(void);
void passengerStatistics(void);
void passengerMenu(void);

#endif
