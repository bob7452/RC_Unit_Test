#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Input_Capture_Simulation.h"
#include "Global_System_Variable__UT.h"
#include "Signal_Generator.h"
#include "TIM_Input_Capture__UT.h"
#include "System_Initialize.h"
#include "Plane__UT.h"

void printf_fnct(Signal_Group* Test_Signal);

#if (Dead_Band_Fnct==On)
    uint16_t Hold_On_Count   = 0;
    int8_t   Hold_Flag       = 0;
#endif
    int8_t   Signal_Order    = 0;
    uint32_t Testing_Count   = 0;
    uint8_t  Stop            = 0;
    uint16_t  print_cnt       = 0;


int main (int argc,char* argv[])
{
    sEscParas_t    EscConfig;
    Parameter_Initial(&EscConfig);
    
    System_Flag    Sys_Flag;
    memset(&Sys_Flag,0,sizeof(Sys_Flag));

    Signal_Group Test_Signal;
    memset(&Test_Signal,0,sizeof(Test_Signal));

    Cmd_Group Cmd;
    memset(&Cmd,0,sizeof(Cmd));

    Single_Signal Input_Signal,Output_Signal,UnBounce_Signal;
    memset(&Input_Signal,0,sizeof(Input_Signal));
    memset(&Output_Signal,0,sizeof(Output_Signal));
    memset(&UnBounce_Signal,0,sizeof(UnBounce_Signal));

    GUI gui;

    PPM_Capture_Parameters_Init(&EscConfig,&Sys_Flag,&Test_Signal);
    GUI_Cofficient_GeT(&gui);

    srand(time(NULL));

    Random_Signal_Single(&Input_Signal,&gui);
    UnBounce_Signal = Input_Signal;
    printf("Input Period : %d\t ; Input Pulse : %d\n",UnBounce_Signal.Signal_Period,UnBounce_Signal.Signal_Pulse);

    Signal_Order=Signal_Interrupt_Single(&Input_Signal,&Output_Signal); 

    if(Output_Signal.Flag)
    {
        TIM_Input_Capture_Interrupt_Fnct_Single(&Sys_Flag,&Output_Signal);
        Output_Signal.Flag=0;
    }

    while(1)
    {
        Signal_Order=Signal_Interrupt_Single(&Input_Signal,&Output_Signal);

        if(Output_Signal.Flag)
        {
            TIM_Input_Capture_Interrupt_Fnct_Single(&Sys_Flag,&Output_Signal);
            Output_Signal.Flag=0;
        }

        if(((Sys_Flag.ICP_Flag & ICP_Period_Finish)>>1)==1) 
        {
            Sys_Flag.ICP_Flag &=(~ICP_Period_Finish);
            PPM_Process_Fnct_Single(&Sys_Flag,&Cmd);

            // if(!(Cmd.PPM_Period != UnBounce_Signal.Signal_Period || Cmd.PPM_Pulse != UnBounce_Signal.Signal_Pulse || Cmd.PPM_Mode != UnBounce_Signal.PPM_Mode ))
            // {
            //     printf("Input Period : %d\t ; Input Pulse : %d\t ; Input PPM Mode : %d\t ; Input Last PPM Mode : %d\n",UnBounce_Signal.Signal_Period,UnBounce_Signal.Signal_Pulse,UnBounce_Signal.PPM_Mode,UnBounce_Signal.Last_PPM_Mode);
            //     printf("Period : %d\t ; Pulse : %d\t ; PPM Mode : %d\n",Cmd.PPM_Period,Cmd.PPM_Pulse,Cmd.PPM_Mode);
            //     printf("Count[0]  : %d\t ; Count[1] : %d\t ; Count[2] : %d\n",Output_Signal.History[0],Output_Signal.History[2],Output_Signal.History[1]);
            // }
            if(Cmd.PPM_Period != UnBounce_Signal.Signal_Period || Cmd.PPM_Pulse != UnBounce_Signal.Signal_Pulse || Cmd.PPM_Mode != UnBounce_Signal.PPM_Mode ) //
            {
                //PPM_Process_Fnct_Single(&Sys_Flag,&Cmd);
                // printf("Input Period : %d\t ; Input Pulse : %d\t ; Input PPM Mode : %d\t ; Input Last PPM Mode : %d\n",UnBounce_Signal.Signal_Period,UnBounce_Signal.Signal_Pulse,UnBounce_Signal.PPM_Mode,UnBounce_Signal.Last_PPM_Mode);
                // printf("Period : %d\t ; Pulse : %d\t ; PPM Mode : %d\n",Cmd.PPM_Period,Cmd.PPM_Pulse,Cmd.PPM_Mode);
                // printf("Count[0]  : %d\t ; Count[1] : %d\t ; Count[2] : %d\n",Output_Signal.History[0],Output_Signal.History[2],Output_Signal.History[1]);
                break;
            }

            // if(!(Cmd.PPM_Period != Input_Signal.Signal_Period || Cmd.PPM_Pulse != Input_Signal.Signal_Pulse || Cmd.PPM_Mode != Input_Signal.PPM_Mode ))
            // {
            //     printf("Input Period : %d\t ; Input Pulse : %d\t ; Input PPM Mode : %d\t ; Input Last PPM Mode : %d\n",Input_Signal.Signal_Period,Input_Signal.Signal_Pulse,Input_Signal.PPM_Mode,Input_Signal.Last_PPM_Mode);
            //     printf("Period : %d\t ; Pulse : %d\t ; PPM Mode : %d\n",Cmd.PPM_Period,Cmd.PPM_Pulse,Cmd.PPM_Mode);
            //     printf("Count[0]  : %d\t ; Count[1] : %d\t ; Count[2] : %d\n",Output_Signal.History[0],Output_Signal.History[2],Output_Signal.History[1]);
            // }
            // if(Cmd.PPM_Period != Input_Signal.Signal_Period || Cmd.PPM_Pulse != Input_Signal.Signal_Pulse || Cmd.PPM_Mode != Input_Signal.PPM_Mode ) //
            // {
            //     PPM_Process_Fnct_Single(&Sys_Flag,&Cmd);
            //     printf("Input Period : %d\t ; Input Pulse : %d\t ; Input PPM Mode : %d\t ; Input Last PPM Mode : %d\n",Input_Signal.Signal_Period,Input_Signal.Signal_Pulse,Input_Signal.PPM_Mode,Input_Signal.Last_PPM_Mode);
            //     printf("Period : %d\t ; Pulse : %d\t ; PPM Mode : %d\n",Cmd.PPM_Period,Cmd.PPM_Pulse,Cmd.PPM_Mode);
            //     printf("Count[0]  : %d\t ; Count[1] : %d\t ; Count[2] : %d\n",Output_Signal.History[0],Output_Signal.History[2],Output_Signal.History[1]);
            //     printf("Fail in %d Counts\n",print_cnt);
            //     break;
            // }
        }

        if(Signal_Order ==-1)
        {
            Hold_On_Count++;
            if(Hold_On_Count==Hold_Count)
            {
                Random_Signal_Single(&Input_Signal,&gui);
                UnBounce_Signal = Input_Signal;
                Hold_On_Count = 0;
            }
            else 
            {
                Signal_Bounce(&Input_Signal);
            }
        } 
    }

    // while (1)
    // {
    //     Signal_Interrupt(&Test_Signal);
    //     if (Test_Signal.Signal_Interrupt_Flag==1)
    //     {
    //         TIM_Input_Capture_Interrupt_Fnct(&Sys_Flag,&Test_Signal);
    //         Test_Signal.Signal_Interrupt_Flag=0;
    //         if((Sys_Flag.ICP_Flag & ICP_Period_Finish)>>1)
    //         {
    //             Sys_Flag.ICP_Flag &= (~ICP_Period_Finish);
    //             PPM_Process_Fnct(&Sys_Flag,&cmd,&Test_Signal);
    //         }
    //     }
    //     if (Test_Signal.Signal_Interrupt_Flag==2)
    //         break;
    // }

  // printf_fnct(&Test_Signal);
    return 0;
}




void printf_fnct(Signal_Group* Test_Signal)
{
    for(int i =0; i<Signal_Count ; i++)
        printf("Signal_Width[%d] : %d\t ; Signal_Period[%d] : %d\t ; Signal_PPM_Mode[%d] : %d\n",i,Test_Signal->Signal_Width[i],i,Test_Signal->Signal_Period[i],i,Test_Signal->PPM_State[i]);
    
    printf("\n");

    // for(int i =0; i<Signal_Count ; i++)
    //     printf("Ans_Width[%d] : %d\t ; Ans_Period[%d] : %d\t ; Ans_PPM_Mode[%d] : %d\n" ,i,Test_Signal->Capture_Width[i],i,Test_Signal->Capture_Period[i],i,Test_Signal->PPM_State[i]);
    
    // printf("\n");
}


