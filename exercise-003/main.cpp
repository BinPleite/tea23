#include <fmt/chrono.h>
#include <fmt/format.h>
#include <stdio.h>

typedef enum {
    STATE_UP,
    STATE_STOP_UP,
    STATE_DOWN,
    STATE_STOP_DOWN,
    STATE_CLOSED,
    STATE_OPEN
} GateState;

typedef enum {
    EVENT_TASTE,
    EVENT_ENDSCHALTER_OBEN,
    EVENT_ENDSCHALTER_UNTEN,
    EVENT_NONE
} GateEvent;

GateState fsm(GateState current, GateEvent event) {
    switch (current) {
        case STATE_UP:
        if (event == EVENT_TASTE)
            return STATE_STOP_UP;
        if (event == EVENT_ENDSCHALTER_OBEN)
            return STATE_OPEN;
        break;

        case STATE_STOP_UP:
            if (event == EVENT_TASTE)
                return STATE_DOWN;
            break;

        case STATE_DOWN:
            if(event == EVENT_TASTE)
                return STATE_STOP_DOWN;
            if (event == EVENT_ENDSCHALTER_UNTEN)
                return STATE_CLOSED;
            break;

        case STATE_STOP_DOWN:
            if (event == EVENT_TASTE)
                return STATE_UP;
            break;
        
        case STATE_CLOSED:
            if(event == EVENT_TASTE)
                return STATE_UP;
            break;
        
        case STATE_OPEN:
            if (event = EVENT_TASTE)
                return STATE_DOWN;
        break;

        default:
            break;
    }
    return current; // keine Änderungen
}


int main()
{
    GateState state = STATE_UP;
    GateEvent event;

    while(1) {
        printf("Current state: &d\n, state");
        printf("Event? (0=Taste, 1=Oben, 2=Unten, 9=Exit):");
        int input;
        scanf("%d", &input);
        
        if (input == 9) break;
        
        switch (input){
            case 0: event = EVENT_TASTE; break;
            case 1: event = EVENT_ENDSCHALTER_OBEN; break;
            case 2: event = EVENT_ENDSCHALTER_UNTEN; break;
            default: event = EVENT_NONE; break;
        }
        state = fsm(state, event);
    }
    return 0; /* exit gracefully*/
}
