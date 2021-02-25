#ifndef __Signal_Generator__H
#define __Signal_Generator__H

#include "Input_Capture_Simulation.h"
#include "Plane__UT.h"
#include "Global_System_Variable__UT.h"
#include "TIM_Input_Capture__UT.h"

void Random_Signal (Signal_Group* Signal);
void Signal_Interrupt (Signal_Group * Test_Signal);


#endif