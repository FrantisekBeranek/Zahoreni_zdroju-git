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

//___Calibration konstant for internal reference of MCU___//
#define CALIB_CONSTANT 1525

//___Transfer values of each voltage divider___//
#define U24V_TRANSFER_CONSTANT	    11.989011f
#define U24VO2_TRANSFER_CONSTANT	11.989011f
#define U15V_TRANSFER_CONSTANT	    7.7083333f
#define U12V_TRANSFER_CONSTANT	    5.5880893f
#define UBAT_TRANSFER_CONSTANT	    4.3404035f
#define U5V_TRANSFER_CONSTANT	    2.3294642f
#define U5VK_TRANSFER_CONSTANT	    2.3275047f

//---Počet měřených veličin---//
#define MEAS_TYPES_COUNT 7
#define FINAL

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