/* gates.h - Gate Control Header (Circular Linked List) */
#ifndef GATES_H
#define GATES_H

#include "types.h"

extern struct GateList gateList;

void initGateList(void);
int gateExists(int gateNum);
void addGate(void);
void assignGate(void);
void releaseGate(void);
void displayAllGates(void);
void gateStatistics(void);
void gateMenu(void);

#endif
