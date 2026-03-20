#ifndef GATES_H
#define GATES_H

#include "types.h"

// ============================================================
//  MEMBER 4 — GATE CONTROL (CIRCULAR LINKED LIST)
// ============================================================

void initGateList(struct GateList* list);
struct GateNode* createGateNode(int gateNumber, char* terminal);
int  gateExists(struct GateList* list, int gateNum);
void addGate(struct GateList* list);
void assignGate(struct GateList* list);
void releaseGate(struct GateList* list);
void displayAllGates(struct GateList* list);
void findAvailableGate(struct GateList* list);
void gateStatistics(struct GateList* list);
void gateHistory(struct GateList* list);
void emergencyReleaseAllGates(struct GateList* list);
void deleteGate(struct GateList* list);
void gateMenu(struct GateList* list);

#endif
