#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Signal_Generator.h"


void Random_Signal(Signal_Group * Signal)
{
    uint16_t max_pusle = Signal->GUI_Signal[0]+1;
    uint16_t max_period  = Max_Period+1;
    uint8_t  Real_Step = 0;
    int8_t  bounce = 0;

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
        for(int i=0;i <Dead_Band_Count;i++)
        {
            if(i<(Dead_Band_Count/2))
                Signal->Dead_Band_Signal[i]=1500+i;
            else
                Signal->Dead_Band_Signal[i]=1500+(Dead_Band_Count-i);
        }
    #endif
}

void Random_Signal_Single(Single_Signal * Signal,GUI *gui)
{
    uint16_t max_pusle = gui->GUI_PPM[0]+1;
    uint16_t max_period  = Max_Period+1;
    uint8_t  Real_Step = 0;
    uint8_t  PPM_Mode  = 0;
    int8_t  bounce = 0;
    static  uint8_t  temp_Status = 0;
    static  uint16_t temp = 1500;
    const   uint16_t top  = 1550;
    const   uint16_t bot  = 1450;

    srand(time(NULL));

    #if (Dead_Band_Fnct == Off && SSR_Signal == On && Special_Signal ==On)
        PPM_Mode = rand()%3;
    #elif (Dead_Band_Fnct == off && SSR_Signal== On && Special_Signal == Off)
        PPM_Mode = rand()%2;
    #elif (Dead_Band_Fnct == Off && SSR_Signal==Off && Special_Signal == Off)
        PPM_Mode = 0;    
    #elif (Dead_Band_Fnct == On)
        PPM_Mode = 3;
    #endif

    Signal->PPM_Mode = PPM_Mode;

    switch (PPM_Mode) 
    {
        case 0:
            while(Signal->Signal_Period<Min_Period || Signal->Signal_Period==Special_Mode_Period_us)
                Signal->Signal_Period=rand()%max_period;

            while(Signal->Signal_Pulse<gui->GUI_PPM[2])
                Signal->Signal_Pulse=rand()%max_pusle;
        break;
        case 1:
            max_pusle  = SSR_Mode_Pulse_Max_us+1;
            while(Signal->Signal_Pulse<SSR_Mode_Pulse_Min)
                Signal->Signal_Pulse=rand()%max_pusle;

            while(Signal->Signal_Period<Min_Period || Signal->Signal_Period==Special_Mode_Period_us)
                Signal->Signal_Period=rand()%max_period;
        break;
        case 2:
            max_pusle  = Special_Mode_Pulse_Max_us+1;

            while(Signal->Signal_Pulse<Special_Mode_Pulse_Min_us)
                Signal->Signal_Pulse=rand()%max_pusle;
            Signal->Signal_Period= Special_Mode_Period_us;
        break;
        case 3:
            Signal->Signal_Period = 40000;
            if(temp_Status)
                Signal->Signal_Pulse  = temp++;
            else
                Signal->Signal_Pulse  = temp--;

            if(temp >top)
                temp_Status =0;
            if (temp<bot)
                temp_Status =1;
        break;
    }
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

uint8_t Signal_Interrupt_Single (Single_Signal * Input_Signal,Single_Signal* Output_Signal)
{
    static unsigned short int      ICP_Clock    =  0;
    static int8_t                  Signal_Order = -1;
    static unsigned int            System_Count =  0;
    static uint8_t                 Nosie_Status =  0;
    
    if(Signal_Order==-1)
    {
        Signal_Order                    = 0;
        System_Count                    = 0;
        Input_Signal->Signal_Level      = 1;
        Output_Signal->Signal_Flag      = 1;
        Output_Signal->Count            = ICP_Clock;
        Output_Signal->Signal_Level     = 1; 
    }
    #if (Signal_Noise == On)
    else
    {
      Nosie_Status =  Nosie_Gen((Single_Signal *) Input_Signal);
    }
    #endif

    if((Input_Signal->Signal_Level==0 && Nosie_Status==0) || (System_Count == Input_Signal->Signal_Pulse))
    {
        Output_Signal->Signal_Flag      = 1;
        Output_Signal->Count            = ICP_Clock;
        Output_Signal->Signal_Level     = 0;
    }

    if((Input_Signal->Signal_Level==1 && Nosie_Status==1) || (System_Count == Input_Signal->Signal_Period))
    {
        Output_Signal->Signal_Flag      = 2;
        Output_Signal->Count            = ICP_Clock;
        Output_Signal->Signal_Level     = 1;

        if(System_Count == Input_Signal->Signal_Period)
            Signal_Order                =-1;
    }

    ICP_Clock++;
    System_Count++;
    return Signal_Order;
}

#if (Signal_Noise==On)
uint8_t Nosie_Gen(Single_Signal * Input_Signal)
{
    static uint8_t                 Noise        =  0;
    static uint8_t                 Nosie_Status =  0;

    Noise  = rand()%2;

    if(Nosie_Status == 0 && Noise ==1)
    {
        Nosie_Status=1;
        Input_Signal->Signal_Level = 1;
    }
    else if (Nosie_Status == 1)
    {
        Input_Signal->Signal_Level = 0;
        Nosie_Status = 0;
    }

    return Nosie_Status;
}
#endif