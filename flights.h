/* flights.h - Flight Operations Header (Singly Linked List) */
#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "types.h"

extern struct FlightList flightList;

void initFlightList(void);
int flightExists(char* fn);
int countFlights(void);
void addFlight(void);
void removeFlight(void);
void searchFlight(void);
void displayAllFlights(void);
void updateFlightStatus(void);
void flightStatistics(void);
void flightMenu(void);

#endif
