#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "types.h"

// ============================================================
//  MEMBER 7 — FLIGHT SCHEDULE
// ============================================================

extern ScheduleEntry schedule[];
extern int           scheduleCount;

int  scheduleEntryExists(const char* fn);
void addScheduleEntry();
void displaySortedSchedule();
void bubbleSort();
void insertionSort();
void selectionSort();
void recursiveSearch(int index, char* query);
void scheduleMenu();

#endif
