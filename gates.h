#ifndef GATES_H
#define GATES_H

#include "types.h"

// ============================================================
//  MEMBER 4 — GATE CONTROL
// ============================================================

extern GateNode* gateHead;

int       gateExists(int gateNum);
void      addGate();
void      assignGate();
void      releaseGate();
void      displayAllGates();
void      findAvailableGate();
void      gateStatistics();
void      gateHistory();
void      emergencyReleaseAllGates();
GateNode* deleteGate(GateNode* head);
void      gateMenu();

#endif
