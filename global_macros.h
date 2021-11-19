#ifndef GLOBAL_MACROS
#define GLOBAL_MACROS

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