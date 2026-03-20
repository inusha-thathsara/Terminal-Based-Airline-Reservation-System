#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "types.h"

// ============================================================
//  MEMBER 7 — FLIGHT SCHEDULE (ARRAY + SORTING + RECURSION)
// ============================================================

int  scheduleEntryExists(struct ScheduleEntry schedule[], int count, char* fn);
void addScheduleEntry(struct ScheduleEntry schedule[], int* count);
void displaySortedSchedule(struct ScheduleEntry schedule[], int count);
void bubbleSort(struct ScheduleEntry schedule[], int count);
void insertionSort(struct ScheduleEntry schedule[], int count);
void selectionSort(struct ScheduleEntry schedule[], int count);
void recursiveSearch(struct ScheduleEntry schedule[], int count,
                     int index, char* query);
void scheduleStatistics(struct ScheduleEntry schedule[], int count);
void scheduleMenu(struct ScheduleEntry schedule[], int* count);

#endif
