
#ifndef RUNWAY_H
#define RUNWAY_H

#include "types.h"

extern struct Queue runwayQueue;

void initQueue(void);
int isQueueEmpty(void);
int isQueueFull(void);
int flightInQueue(char* fn);
void addToRunwayQueue(void);
void clearRunway(void);
void viewNextFlight(void);
void displayRunwayQueue(void);
void runwayMenu(void);

#endif
