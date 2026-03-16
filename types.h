#ifndef TYPES_H
#define TYPES_H

// ============================================================
//  SKYPORT TERMINAL — SHARED TYPE DEFINITIONS
// ============================================================

#define MAX_PASSENGERS  100
#define MAX_NAME        50
#define MAX_FLIGHT_NO   10
#define MAX_TIME        10
#define MAX_DEST        50
#define MAX_SCHEDULE    100
#define WIDTH           70

// ─── Passenger ───────────────────────────────────────────────
typedef struct {
    int  id;
    char name[MAX_NAME];
    char destination[MAX_DEST];
    char flightNumber[MAX_FLIGHT_NO];
    int  age;
    char seatClass[20];
    char passport[20];
} Passenger;

// ─── Flight Node (Singly & Doubly Linked List) ───────────────
typedef struct FlightNode {
    char flightNumber[MAX_FLIGHT_NO];
    char destination[MAX_DEST];
    char origin[MAX_DEST];
    char departureTime[MAX_TIME];
    char arrivalTime[MAX_TIME];
    char gate[10];
    int  totalSeats;
    int  availableSeats;
    char status[20];
    char aircraft[20];
    struct FlightNode* next;
    struct FlightNode* prev;
} FlightNode;

// ─── Baggage Node (Doubly Linked List) ───────────────────────
typedef struct BaggageNode {
    int   baggageID;
    int   passengerID;
    char  ownerName[MAX_NAME];
    float weight;
    char  status[20];
    char  tag[20];
    struct BaggageNode* next;
    struct BaggageNode* prev;
} BaggageNode;

// ─── Gate Node (Circular Linked List) ────────────────────────
typedef struct GateNode {
    int  gateNumber;
    char terminal[10];
    char status[20];
    char assignedFlight[MAX_FLIGHT_NO];
    char lastFlight[MAX_FLIGHT_NO];
    char history[3][MAX_FLIGHT_NO];
    int  historyCount;
    struct GateNode* next;
} GateNode;

// ─── Boarding Stack Node ──────────────────────────────────────
typedef struct StackNode {
    int  passengerID;
    char passengerName[MAX_NAME];
    char seatNumber[10];
    char boardingPass[20];
    struct StackNode* next;
} StackNode;

// ─── Runway Queue Node ────────────────────────────────────────
typedef struct QueueNode {
    char flightNumber[MAX_FLIGHT_NO];
    char destination[MAX_DEST];
    char scheduledTime[MAX_TIME];
    char type[10];
    int  priority;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int        size;
} RunwayQueue;

// ─── Schedule Entry ───────────────────────────────────────────
typedef struct {
    char flightNumber[MAX_FLIGHT_NO];
    char origin[MAX_DEST];
    char destination[MAX_DEST];
    char departureTime[MAX_TIME];
    char arrivalTime[MAX_TIME];
    char gate[10];
    int  availableSeats;
    char status[20];
    char aircraft[20];
} ScheduleEntry;

#endif // TYPES_H
