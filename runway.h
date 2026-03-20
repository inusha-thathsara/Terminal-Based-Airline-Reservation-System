#ifndef RUNWAY_H
#define RUNWAY_H

#include "types.h"

// ============================================================
//  MEMBER 6 — RUNWAY CONTROL (PRIORITY QUEUE)
// ============================================================

void initQueue(struct Queue* queue);
struct QueueNode* createQueueNode(char* flightNumber, char* destination,
                                   char* scheduledTime, char* type, int priority);
int  isQueueEmpty(struct Queue* queue);
int  isFlightInQueue(struct Queue* queue, char* fn);
void priorityEnqueue(struct Queue* queue);
void dequeue(struct Queue* queue);
void peekQueue(struct Queue* queue);
void displayQueue(struct Queue* queue);
void queueStatistics(struct Queue* queue);
void runwayMenu(struct Queue* queue);

#endif
