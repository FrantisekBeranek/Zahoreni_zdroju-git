#ifndef GLOBAL_MACROS
#define GLOBAL_MACROS

typedef struct
{
    unsigned int measureInProgress  : 1;
    unsigned int manualMode         : 1;
    unsigned int calibInProgress    : 1;
    unsigned int COMstate           : 2;
        // 0 -> port OK
        // 1 -> port Disconnected
        // 2 -> port Unactive
}appStatus;

//#define QT_NO_DEBUG_OUTPUT

//---Počet měřených veličin---//
#define MEAS_TYPES_COUNT 7
//#define FINAL

#ifdef FINAL
//---Počty měření v jednotlivých fázích---//
    #define START_MEAS_COUNT 1
    #define MAIN_MEAS_COUNT 18
    #define BAT_START_MEAS_COUNT 0
    #define BAT_MAIN_MEAS_COUNT 3
#else
    #define START_MEAS_COUNT 1
    #define MAIN_MEAS_COUNT 10
    #define BAT_START_MEAS_COUNT 0
    #define BAT_MAIN_MEAS_COUNT 3
#endif

#endif