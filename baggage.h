
#ifndef BAGGAGE_H
#define BAGGAGE_H

#include "types.h"

extern struct BaggageList baggageList;

void initBaggageList(void);
int baggageExists(int id);
void addBaggage(void);
void removeBaggage(void);
void displayBaggageForward(void);
void displayBaggageBackward(void);
void baggageStatistics(void);
void baggageMenu(void);

#endif
