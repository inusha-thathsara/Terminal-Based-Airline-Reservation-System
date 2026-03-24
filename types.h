/* types.h - Shared Structure Definitions */
#ifndef TYPES_H
#define TYPES_H

// Member 1: Array - Passenger Structure
struct Passenger {
    int  id;
    char name[50];
    char destination[50];
    char flightNumber[10];
    int  age;
    char seatClass[20];
    char passport[20];
};

// Member 2: Singly Linked List - Flight Structures
struct FlightNode {
    char flightNumber[10];
    char origin[50];
    char destination[50];
    char departureTime[10];
    char arrivalTime[10];
    char gate[10];
    char aircraft[20];
    int  totalSeats;
    int  availableSeats;
    char status[20];
    struct FlightNode* next;
};

struct FlightList {
    struct FlightNode* head;
    struct FlightNode* tail;
};

// Member 3: Doubly Linked List - Baggage Structures
struct BaggageNode {
    int   baggageID;
    int   passengerID;
    char  ownerName[50];
    float weight;
    char  tag[20];
    char  status[20];
    struct BaggageNode* next;
    struct BaggageNode* prev;
};

struct BaggageList {
    struct BaggageNode* head;
    struct BaggageNode* tail;
};

// Member 4: Circular Linked List - Gate Structures
struct GateNode {
    int  gateNumber;
    char terminal[10];
    char status[20];
    char assignedFlight[10];
    char lastFlight[10];
    struct GateNode* next;
};

struct GateList {
    struct GateNode* head;
};

// Member 5: Stack - Boarding Structures
struct StackNode {
    int  passengerID;
    char passengerName[50];
    char seatNumber[10];
    char boardingPass[20];
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

// Member 6: Queue - Runway Structures
struct QueueNode {
    char flightNumber[10];
    char destination[50];
    char scheduledTime[10];
    char type[10];
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Member 7: Priority Queue - Emergency Structures
struct PQNode {
    char flightNumber[10];
    char destination[50];
    char scheduledTime[10];
    char type[10];
    int  priority;
    char reason[50];
    struct PQNode* next;
};

struct PriorityQueue {
    struct PQNode* front;
    struct PQNode* rear;
};

// Member 7: Schedule Array
struct ScheduleEntry {
    char flightNumber[10];
    char origin[50];
    char destination[50];
    char departureTime[10];
    char arrivalTime[10];
    int  priority;
    char status[20];
};

#endif
