#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "types.h"

// ============================================================
//  Inusha Gunasekara (244068K) � FLIGHT OPERATIONS
// ============================================================

extern FlightNode* flightHead;

int  flightExists(const char* fn);
void addFlight();
void removeFlight();
void searchFlight();
void displayAllFlights();
void updateFlightStatus();
void countFlights();
void flightMenu();

#endif
