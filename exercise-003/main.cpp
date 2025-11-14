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

const char* stateToString(GateState s) {
    switch (s) {
        case STATE_UP:         return "Fahre hoch";
        case STATE_STOP_UP:    return "Stop (Weg nach oben)";
        case STATE_DOWN:       return "Fahre runter";
        case STATE_STOP_DOWN:  return "Stop (Weg nach unten)";
        case STATE_CLOSED:     return "Garagentor zu";
        case STATE_OPEN:       return "Garagentor offen";
        default:               return "Unbekannt";
    }
}

const char* eventToString(GateEvent e) {
    switch (e) {
        case EVENT_TASTE:                return "Taste";
        case EVENT_ENDSCHALTER_OBEN:     return "Endschalter oben";
        case EVENT_ENDSCHALTER_UNTEN:    return "Endschalter unten";
        case EVENT_NONE:                 return "Kein gültiges Event";
        default:                         return "Unbekannt";
    }
}

GateState fsm(GateState current, GateEvent event) {
    switch (current) {
        case STATE_UP:
            if (event == EVENT_TASTE) return STATE_STOP_UP;
            if (event == EVENT_ENDSCHALTER_OBEN) return STATE_OPEN;
            break;

        case STATE_STOP_UP:
            if (event == EVENT_TASTE) return STATE_DOWN;
            break;

        case STATE_DOWN:
            if (event == EVENT_TASTE) return STATE_STOP_DOWN;
            if (event == EVENT_ENDSCHALTER_UNTEN) return STATE_CLOSED;
            break;

        case STATE_STOP_DOWN:
            if (event == EVENT_TASTE) return STATE_UP;
            break;

        case STATE_CLOSED:
            if (event == EVENT_TASTE) return STATE_UP;
            break;

        case STATE_OPEN:
            if (event == EVENT_TASTE) return STATE_DOWN;
            break;
    }
    return current;
}

int main() {
    GateState state = STATE_CLOSED;
    GateEvent event;

    while (1) {
        printf("=====================================\n");
        printf("Aktueller Zustand (%d): %s\n", state, stateToString(state));

        printf("\nEvent eingeben:\n");
        printf("  0 = Taste\n");
        printf("  1 = Endschalter oben\n");
        printf("  2 = Endschalter unten\n");
        printf("  9 = Beenden\n");
        printf("Eingabe: ");
        fflush(stdout);

        int input;

        // --- robuste Eingabe ---
        while (scanf(" %d", &input) != 1) {
            printf("Ungültige Eingabe! Bitte Zahl eingeben.\nEingabe: ");
            fflush(stdout);
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Puffer leeren
        }
        // ------------------------

        if (input == 9) break;

        switch (input) {
            case 0: event = EVENT_TASTE; break;
            case 1: event = EVENT_ENDSCHALTER_OBEN; break;
            case 2: event = EVENT_ENDSCHALTER_UNTEN; break;
            default: event = EVENT_NONE; break;
        }

        printf("Event (%d): %s\n", event, eventToString(event));

        state = fsm(state, event);
    }

    return 0;
}
