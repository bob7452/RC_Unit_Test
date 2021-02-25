#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Signal_Generator.h"


void Random_Signal(Signal_Group * Signal)
{
    uint16_t max_pusle = Signal->GUI_Signal[0]+1;
    uint16_t max_period  = Max_Period+1;
    uint8_t  Real_Step = 0;

    srand(time(NULL));

    for(int i = 0;i<Signal_Count;i++)
    {      
        while(Signal->Signal_Period[i]<Min_Period || Signal->Signal_Period[i]==Special_Mode_Period_us)
            Signal->Signal_Period[i]=rand()%max_period;

        while(Signal->Signal_Width[i]<Signal->GUI_Signal[2])
            Signal->Signal_Width[i]=rand()%max_pusle;
    }
    
    #if(SSR_Signal ==On)
        max_pusle  = SSR_Mode_Pulse_Max_us+1;
        for(int i=1;i<=2;i++)
        {
            Signal->Signal_Period[i]=0;
            Signal->Signal_Width[i]=0;

            while(Signal->Signal_Width[i]<SSR_Mode_Pulse_Min)
                Signal->Signal_Width[i]=rand()%max_pusle;

            while(Signal->Signal_Period[i]<Min_Period || Signal->Signal_Period[i]==Special_Mode_Period_us)
                Signal->Signal_Period[i]=rand()%max_period;
        }
    #endif

    #if(Special_Signal ==On)
        max_pusle  = Special_Mode_Pulse_Max_us+1;
        for(int i=3;i<=4;i++)
        {
            Signal->Signal_Period[i]=0;
            Signal->Signal_Width[i]=0;

            while(Signal->Signal_Width[i]<Special_Mode_Pulse_Min_us)
                Signal->Signal_Width[i]=rand()%max_pusle;
            Signal->Signal_Period[i] = Special_Mode_Period_us;
        }
    #endif

    #if (Dead_Band_Fnct==On)
        for(int i=0;i<Signal_Count;i++)
        {
            
        }
    #endif
}

void Signal_Interrupt (Signal_Group * Test_Signal)
{
    static unsigned int            System_Count =  0;
    static unsigned int            System_Stamp =  0;
    static unsigned short int      ICP_Clock    =  0;
    static short int               Signal_Order = -1;
    unsigned int                   Signal_Period=  0;
    unsigned int                   Systme_Temp  =  0;
    static char                    Raising_Order=  0;
    static char                    Falling_Order=  0;

    Systme_Temp = System_Count-System_Stamp;

    if(Raising_Order == Signal_Count+1)
    {
        Test_Signal->Signal_Interrupt_Flag = 2;
        return;
    }

    if (Signal_Order==-1)
    {
        Signal_Period = 0;
        Signal_Order  = 0;
        Test_Signal->Signal_Interrupt_Flag =1;
        Test_Signal->ICP_Counter = ICP_Clock;
        Test_Signal->Signal_Level = 1;
        Test_Signal->Raising_Counter[Raising_Order++]=System_Count;
        return;
    } 
    else
        Signal_Period = (Systme_Temp)-Test_Signal->Signal_Period[Signal_Order]; 

    if(Signal_Period==0) //One Period 
    {
        System_Stamp = System_Count;
        Signal_Order++;
        Test_Signal->Signal_Interrupt_Flag = 1;
        Test_Signal->ICP_Counter = ICP_Clock;
        Test_Signal->Signal_Level = 1;
        Test_Signal->Raising_Counter[Raising_Order++]=System_Count;
    }

    if (Systme_Temp == Test_Signal->Signal_Width[Signal_Order]) //Falling Edge 
    {
        Test_Signal->Signal_Interrupt_Flag = 1;
        Test_Signal->ICP_Counter = ICP_Clock;
        Test_Signal->Signal_Level = 0;   
        Test_Signal->Falling_Counter[Falling_Order++]=System_Count;
    }
    
    System_Count++;
    ICP_Clock++;
}
