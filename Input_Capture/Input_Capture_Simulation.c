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
    int8_t Signal_Order      = 0;

int main (int argc,char* argv[])
{
    sEscParas_t    EscConfig;
    Parameter_Initial(&EscConfig);
    
    System_Flag    Sys_Flag;
    memset(&Sys_Flag,0,sizeof(Sys_Flag));

    Signal_Group Test_Signal;
    memset(&Test_Signal,0,sizeof(Test_Signal));

    Cmd_Group cmd;
    memset(&cmd,0,sizeof(cmd));

    Single_Signal Input_Signal,Output_Signal;
    memset(&Input_Signal,0,sizeof(Input_Signal));
    memset(&Output_Signal,0,sizeof(Output_Signal));

    GUI gui;

    PPM_Capture_Parameters_Init(&EscConfig,&Sys_Flag,&Test_Signal);
    GUI_Cofficient_GeT(&gui);

    //Random_Signal(&Test_Signal);
    
    //Random_Signal_Single(&Input_Signal, &gui);

     while(1)
     {
        #if (Dead_Band_Fnct==On)

        if(Hold_On_Count == 0)
        {
            Random_Signal_Single(&Input_Signal,&gui);
            Hold_On_Count = Hold_Count;
        }
        
        Hold_Flag=Signal_Interrupt_Single(&Input_Signal,&Output_Signal);
        
        if(Hold_Flag == -1)
            Hold_On_Count--;

        if(Output_Signal.Flag)
        {
            TIM_Input_Capture_Interrupt_Fnct_Single(&Sys_Flag,&Output_Signal);
            Output_Signal.Flag = 0;

            if((Sys_Flag.ICP_Flag & ICP_Period_Finish)>>1)
            {
                Sys_Flag.ICP_Flag &= (~ICP_Period_Finish);
                //PPM_Process_Fnct(&Sys_Flag,&cmd,&Input_Signal);
            }
        }

        #endif
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


