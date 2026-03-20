#ifndef BAGGAGE_H
#define BAGGAGE_H

#include "types.h"

// ============================================================
//  MEMBER 3 — BAGGAGE SERVICES (DOUBLY LINKED LIST)
// ============================================================

void initBaggageList(struct BaggageList* list);
struct BaggageNode* createBaggageNode(int baggageID, int passengerID,
                                       char* ownerName, float weight);
int  baggageIDExists(struct BaggageList* list, int id);
void addBaggage(struct BaggageList* list);
void removeBaggage(struct BaggageList* list);
void displayForward(struct BaggageList* list);
void displayBackward(struct BaggageList* list);
void searchBaggage(struct BaggageList* list);
void baggageStatistics(struct BaggageList* list);
void baggageMenu(struct BaggageList* list);

#endif
