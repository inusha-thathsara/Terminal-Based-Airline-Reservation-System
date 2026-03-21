#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "types.h"

// ============================================================
//  MEMBER 2 — FLIGHT OPERATIONS (SINGLY LINKED LIST)
// ============================================================

void initFlightList(struct FlightList* list);
struct FlightNode* createFlightNode(char* flightNumber, char* origin,
                                    char* destination, char* departureTime,
                                    char* arrivalTime, char* gate,
                                    char* aircraft, int totalSeats);
int  flightExists(struct FlightList* list, char* fn);
void addFlight(struct FlightList* list);
void removeFlight(struct FlightList* list);
void searchFlight(struct FlightList* list);
void displayAllFlights(struct FlightList* list);
void updateFlightStatus(struct FlightList* list);
void countFlights(struct FlightList* list);
void flightMenu(struct FlightList* list);

#endif
