#ifndef __Global_System_Variable__UT__H
#define __Global_System_Variable__UT__H

#include "Input_Capture_Simulation.h"
#include <stdint.h>

/*******************************************************************************************/
//                             		Math_Formula_Define                                    //
/*******************************************************************************************/
#define Abs(x) (x ^ (x >> 31)) - (x >> 31)
#define Round_Value(x,y) (x+(y>>1))/y 
#define Round_Value_Nbit(x,N) (x+(1<<(N-1)))>>N
#define Min_Value(x,y) (x>y) ? y : x
#define Max_Value(x,y) (x>y) ? x : y
/*******************************************************************************************/
//                             				CLK_Freq                                       //
/*******************************************************************************************/
#define CLK_Freq_Mhz 10

/*******************************************************************************************/
//                                  ICP_Flag_Declaration                                   //
/*******************************************************************************************/
#define ICP_Initial_Finish 				1
#define ICP_Period_Finish 				2
#define ICP_Pusle_Width_Finish 			4
#define ICP_Dead_Band_Check_Real 		8
#define ICP_Signal_Sharp_Change_Flag 	16
#define ICP_PPM_Filter_Raising_Lock		32
#define ICP_PPM_Soft_Lock_Flag			64
#define ICP_PPM_Soft_Interrupt_Flag		128
/*******************************************************************************************/
//                                  Bus_Status_Flag_Declaration                            //
/*******************************************************************************************/
#define Bus_Peripheral					0x01
#define	Bus_Uart_Status_Busy 			0x02 				 
#define Bus_Arbitration	   				0x04


/*******************************************************************************************/
//                             System_Count_Declaration                                    //
/*******************************************************************************************/
// SysTick Parameters
#define ERROR_SAMPLING_TIME 	   		999		//(999 + 1) * 100u = 100ms
#define NO_CMD_TIME 			   		999	    //(4999 + 1) * 100u = 500ms
#define LED_FLICKER_TIME 		 		49999	    //(4999 + 1) * 100u = 5s
#define LED_LIGHT_TIME 			  		5000	    // 5000 * 100u = 500ms
#define LED_LIGHT_OFF_TIME 				(LED_FLICKER_TIME - LED_LIGHT_TIME)
#define PROTECTION_TIME 				999		//(999 + 1) * 100u = 100ms
#define DEBUG_TIME 						19999	//(4999 + 1) * 100u = 5s
#define DEBUG_TIME2 					59999	//(4999 + 1) * 100u = 5s
#define SETPWM_THRESHOLD_TIME  			9
#define ADC_SAMPLING_TIME      			0
#define IBusPROTECTION_TIME 	 		49		//(49 + 1) * 100u = 5ms
#define LOCK_PROTETION_TIME    			9999 //1 sec
#define LOCK_PROTETION_SEC		 		10


/*******************************************************************************************/
//                             System_Variable_Definition                                  //
/*******************************************************************************************/
#define System_Clock      16000000uL
#define System_Extern_Osi 16000000uL


#define On 1
#define Off 0

enum System_State_Machine
{
    Initial =0,
    Start,
    Finish,
	Idle = 0,
	Busy,
};

typedef struct 
{
	// Protection
	uint16_t u16OvdOnOff;            // 0:Off, 1:On
	uint16_t u16OvdMaxVolt;          // 0~60
	uint16_t u16OvdRecVolt;          // 0~60
	uint16_t u16LvdOnOff;            // 0:Off, 1:On
	uint16_t u16LvdMinVolt;          // 0~60
	uint16_t u16LvdRecVolt;          // 0~60
	uint16_t u16MaxPwmDuty;          // 50~100%, interval 5%
	uint16_t u16MinPwmDuty;          // 0~100%, interval 1%
	uint16_t u16LockOnOff;           // 0:Off, 1:On
	uint16_t u16LockMaxPwmDuty;      // 0~100%
	uint16_t u16LockContTime;        // 0.5 ~ 600 sec
	uint16_t u16LockDecay;           //// 0 ~ 100 %/sec
	uint16_t u16TempProtOnOff;       // 0:Off, 1:On
	uint16_t u16TempProtStart;       // 60 ~ 95 degree C
	uint16_t u16TempRecovery;        // 70 ~ 105  
	uint16_t u16TempCutoff;	         // 80 ~ 200
	uint16_t u16TempDecay;	         //// 0 ~ 100 %
	uint16_t u16PpmLossTime;         // 0.1 ~ 5.0 sec
	uint16_t u16PpmLossAct;          // 0:free, 1:lock
	uint16_t u16HallFailOnOff;       // 0:Off, 1:On	
	uint16_t u16PtMaxAngle;          //// 0 ~ 360 degree C
	uint16_t u16PtMiddle;            //// 1048 ~ 3048	
}sProtection_t;

typedef struct 
{
	// Driving Basic Design
	uint16_t u16PulseCentralTime;    // 1300~1700us    
	uint16_t u16PulseHigherTime;     // 2100 +/- 200us
	uint16_t u16PulseHigherAng;      // 60 +/- 20 degree
	uint16_t u16PulseLowerTime;      // 900 +/- 200us
	uint16_t u16PulseLowerAng;       // -60 +/- 20 degree
	uint16_t u16DeadBand;            // 1~5
	uint16_t u16MotDrvLogic;         // 0:L, 1:H
	uint16_t u16PtDrvLogic;          // 0:L, 1:H
}sDrvBasic_t;

typedef struct 
{
	// Driving Advanced Design
	uint16_t u16Kp;                  // 0~65535
	uint16_t u16Ki;                  // 0~65535
	uint16_t u16Kd;                  // 0~65535
	uint16_t u16LoopSamplingTime;    // 1~50ms
	uint16_t u16MaxPwmDutyViSat;     // 1~100%
	uint16_t u16SleepMinPwmDutyVdl;  // 0~100%
	uint16_t u16SleepContTime;       // 0~60000ms
	uint16_t u16WakeupMaxPwmDutyVdh; // 0~100%
	uint16_t u16WakeupEmaxDegree;    // 0~360

	uint16_t u16PosiDiv;                     // 0~65535 cnt
	uint16_t u16SpdKpGain;               // 0~65535 cnt
	uint16_t u16MotorFreeErr;            // 0~65535 cnt
	uint16_t u16MotorFreeTime;        // 0~65535 ms

	uint16_t u16SpdKdGain;               // 0~65535 cnt    
	uint16_t u16SpdDiv;                     // 0~65535 cnt    
	uint16_t u16InitialSpeed;               // 0~65535 cnt
	uint16_t u16InitialTimeOut;    // 3~60 s
}sDrvAdvanced_t;

typedef struct 
{
	// Version Control
	uint8_t u8ProjectName[16];
	uint8_t u8FwVer[16];
}sVerCtrl_t;

typedef struct 
{   
	sProtection_t   Protect;
	sDrvBasic_t     DrvBas;
	sDrvAdvanced_t  DrvAdv;
	sVerCtrl_t      VerCtrl;
}sEscParas_t;


/*******************************************************************************************/
//                                         ICP                                             //
/*******************************************************************************************/
typedef struct
{
     volatile  uint16_t CaptureMax;
     volatile  uint16_t CaptureMid;
     volatile  uint16_t CaptureMin;
	 volatile  uint16_t CaptureLimit;
	 volatile  uint16_t Capture_Div;
	 volatile  uint32_t Capture_Period;
	 volatile  uint16_t Capture_Raising_Edge[2];
	 volatile  uint16_t Capture_Both_Edge[2];
	 volatile  uint16_t Capture_Pulse_Width[2];
	 volatile  uint16_t Uart_Port_Ms_Lower;
     volatile  uint16_t Uart_Port_Ms_Upper;
}Capture_Group;

#if (Driving_Mode == Mix)
	typedef struct 
	{
		volatile  uint16_t PPM_Capture_Delta;
		volatile  uint8_t  PPM_Capture_Dir[2];
	}Mix_Mode_Group;
 #endif

 typedef struct 
 {
	volatile int32_t  Target_Cmd;
	volatile int16_t  Vr_Middle_Point;
	volatile int16_t  PPM_Factor;
	volatile uint8_t  Step_Count;
	volatile uint8_t  PPM_Mode;
	volatile uint16_t PPM_Period;
	volatile uint16_t PPM_Pulse;
 }Cmd_Group;
 
/*******************************************************************************************/
//                                         ADC                                             //
/*******************************************************************************************/


typedef struct 
{
    volatile uint16_t    U16_VDCBus;
    volatile int16_t     I16_Position;
    volatile uint16_t    U16_VDD;
    volatile uint16_t    U16_Temperature;
    volatile int16_t     I16_D_Factor; // VR ADC_value <-> S16 Form
}Data_From_ADC;

/*******************************************************************************************/
//                                		Control_Mode                                       //
/*******************************************************************************************/

/*******************************************************************************************/
//                                         PWM                                             //
/*******************************************************************************************/
enum PWM_State
{
	PWM_Brake =0,
	PWM_Run,
	PWM_FreeRun,
	Biopolar =0,
	Complement,
	Mix
};

typedef struct
{
  volatile unsigned short        PWM1;
  volatile unsigned short        PWM2;
  volatile unsigned short        PWM3;
  volatile unsigned short        CCER_Reg;
  volatile unsigned char         Hall_Status;
  volatile unsigned char         PWM_Status;
} PWM_OutputTypeDef;

/*******************************************************************************************/
//                                         FLAG                                            //
/*******************************************************************************************/
typedef struct 
{
	volatile  uint8_t Bus_Status_Flag; 
	volatile  uint8_t ICP_Flag;
	volatile  uint8_t Motor_Operation_Status_Flag;  
}System_Flag;


/*******************************************************************************************/
//                                         Count                                           //
/*******************************************************************************************/
typedef struct
{
    volatile uint16_t ADC_Time_Count;
	volatile uint16_t PPM_Loss_Count;
	volatile uint16_t Pid_Pos_Count;
	volatile uint8_t  ICP_Filter_Count;
}System_Count;

/*******************************************************************************************/
//                                         Testing                                         //
/*******************************************************************************************/
#define Signal_Count 30
#define Dead_Band_Count 30

typedef struct 
{
    uint16_t Signal_Period [Signal_Count];
    uint16_t Signal_Width  [Signal_Count];
	uint16_t Dead_Band_Signal [Dead_Band_Count];

    uint16_t ICP_Counter;
    uint8_t  Signal_Level;
    uint8_t  Signal_Interrupt_Flag;
    uint16_t GUI_Signal[3];

    uint32_t Raising_Counter [Signal_Count+1];
    uint32_t Falling_Counter [Signal_Count+1];

    uint16_t Capture_Period [Signal_Count];
    uint16_t Capture_Width  [Signal_Count];

    uint8_t  PPM_State[Signal_Count];
    uint16_t  PPM_State_Count;

}Signal_Group;

typedef struct
{
	uint16_t Signal_Pulse;
	uint16_t Signal_Period;
	uint8_t  Signal_Level;
	uint8_t  Flag;
	uint16_t Count;
	uint8_t PPM_Mode;
	uint8_t Last_PPM_Mode;

	uint16_t History[3];
}Single_Signal;

typedef struct
{
	uint16_t GUI_PPM[3];
}GUI;

#endif