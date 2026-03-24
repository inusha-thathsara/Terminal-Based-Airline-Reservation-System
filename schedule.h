/* schedule.h - Emergency Management Header (Priority Queue + Sorting + Recursion) */
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "types.h"

extern struct PriorityQueue emergencyQueue;
extern struct ScheduleEntry schedule[100];
extern int scheduleCount;

void initPriorityQueue(void);
int isPQEmpty(void);
int flightInPQ(char* fn);
void addEmergencyFlight(void);
void clearEmergencyFlight(void);
void displayEmergencyQueue(void);
void copyToSchedule(void);
void sortByPriority(void);
void sortByTime(void);
void sortByFlightNo(void);
void recursiveSearch(int index, char* query);
void searchEmergencyFlight(void);
void emergencyMenu(void);

#endif
