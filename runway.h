#ifndef RUNWAY_H
#define RUNWAY_H

#include "types.h"

// ============================================================
//  MEMBER 6 — RUNWAY CONTROL
// ============================================================

extern RunwayQueue runwayQueue;

void initQueue();
int  isFlightInQueue(const char* fn);
void enqueue();
void dequeue();
void peekQueue();
void displayQueue();
int  isQueueEmpty();
void runwayMenu();

#endif
