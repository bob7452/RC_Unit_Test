#ifndef __Signal_Generator__H
#define __Signal_Generator__H

#include "Input_Capture_Simulation.h"
#include "Plane__UT.h"
#include "Global_System_Variable__UT.h"
#include "TIM_Input_Capture__UT.h"

void Random_Signal (Signal_Group* Signal);
void Random_Signal_Single(Single_Signal * Signal,GUI *gui);
void Signal_Interrupt (Signal_Group * Test_Signal);
uint8_t Nosie_Gen(Single_Signal * Input_Signal);
uint8_t Signal_Interrupt_Single (Single_Signal * Input_Signal,Single_Signal* Output_Signal);


#endif