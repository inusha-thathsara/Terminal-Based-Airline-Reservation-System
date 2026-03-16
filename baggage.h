#ifndef BAGGAGE_H
#define BAGGAGE_H

#include "types.h"

// ============================================================
//  MEMBER 3 — BAGGAGE SERVICES
// ============================================================

extern BaggageNode* baggageHead;

int  baggageIDExists(int id);
void addBaggage();
void removeBaggage();
void displayForward();
void displayBackward();
void searchBaggage();
void baggageStatistics();
void baggageMenu();

#endif
