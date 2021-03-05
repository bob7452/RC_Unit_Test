#ifndef __Plane__H
#define __Plane__H

#include "Global_System_Variable__UT.h"

/*******************************************************************************************/
//                                         ADC                                             //
/*******************************************************************************************/
#define R_SHUNT1 75
#define R_SHUNT2 10

#define Pos_Filter 32
#define ADC_Sampling_Initial_Time_Count 999
#define V_FACTOR (uint16_t)(4096 * R_SHUNT2 / (R_SHUNT1 + R_SHUNT2))
/*******************************************************************************************/
//                                         PWM                                             //
/*******************************************************************************************/
#define PWM_FREQ                  16000
#define DEADTIME_NS 			  450 


/*******************************************************************************************/
//                                         ICP                                             //
/*******************************************************************************************/
#define PPM_Filter Off
#define PPM_Filter_Cnt 28

#define Dead_Band_Fnct On

#define Special_Mode    On
#define SSR_Mode        On

#define Special_Mode_Hz 833
#define Special_Mode_Pulse_Min 395 
#define Special_Mode_Pulse_Mid 760
#define Special_Mode_Pulse_Max 1125
#define Special_Signal_Buffer 5

#define SSR_Mode_Pulse_Min 45
#define SSR_Mode_Pulse_Mid 300
#define SSR_Mode_Pulse_Max 555
#define SSR_Signal_Buffer  0

#define Normal_Signal_Buffer 25

/*******************************************************************************************/
//                                         PID                                             //
/*******************************************************************************************/
#define PID_Pos_Loop_Time   19   //     (19 + 1) * 100u = 2ms
#define PID_Pos_Unit_Time   2    //     50/(PID_POSITION_SAMPLING_TIME+1)

#define PID_Spd_Loop_Time   9    //     ( 9 + 1) * 100u = 1ms
#define PID_Spd_Unit_Time   1	 //     10/(PID_SPEED_SAMPLING_TIME+1)


/*******************************************************************************************/
//                                     Control Mode                                        //
/*******************************************************************************************/
#define Driving_Mode    Complement            //      Mix     Biopolar    Complement
#define Stepping_Mode   Off
#define Signal_Sharp_Change_Therehold 25



/*******************************************************************************************/
//                                     Testing_Signal Mode                                 //
/*******************************************************************************************/
#define Signal_Noise Off
#define SSR_Signal On
#define Special_Signal On

#define Max_Period 40000    //50Hz
#define Min_Period 5000     //400Hz
#define Max_Pulse_Width 5000
#define Min_Pulse_Width 50

#define  Hold_Count    50

#define  Bounce_Range 1 

#endif