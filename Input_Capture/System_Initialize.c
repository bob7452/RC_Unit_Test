#include "System_Initialize.h"

void Parameter_Initial(sEscParas_t *ptr)
{
	ptr->DrvAdv.u16Kd                   = 60;//170;//140; //180;//150;//120;//= 100;
	ptr->DrvAdv.u16Ki                   = 0;
	ptr->DrvAdv.u16Kp                   = 90;//97;//100; //45;//28;//80;// = 80;

	//
	ptr->DrvBas.u16PulseCentralTime      = 1500;
	ptr->DrvBas.u16PulseHigherTime       = 2100;//= 2100;
	ptr->DrvBas.u16PulseHigherAng        = 2400;//=2400;	
	ptr->DrvBas.u16PulseLowerTime        = 900;	
	ptr->DrvBas.u16PulseLowerAng         = 1200;
	ptr->DrvBas.u16DeadBand              = 1;//1; //1ms
	ptr->DrvBas.u16MotDrvLogic           = 1;
	ptr->DrvBas.u16PtDrvLogic            = 0;

	//
	ptr->Protect.u16OvdOnOff             = 1;
	ptr->Protect.u16OvdMaxVolt           = 90;
	ptr->Protect.u16OvdRecVolt           = 84;

	ptr->Protect.u16LvdOnOff           	 = 1;
	ptr->Protect.u16LvdMinVolt           = 40;
	ptr->Protect.u16LvdRecVolt           = 45;

	ptr->Protect.u16MaxPwmDuty           = 100;

	ptr->Protect.u16LockContTime       	 = 50;
	ptr->Protect.u16LockMaxPwmDuty       = 85;
	ptr->Protect.u16LockOnOff            = 1;
	ptr->Protect.u16LockDecay            = 10;

	ptr->Protect.u16HallFailOnOff 		 = 0;

	ptr->Protect.u16TempProtOnOff		 = 1;
	ptr->Protect.u16TempProtStart          = 972;
	ptr->Protect.u16TempRecovery         = 1657;
	ptr->Protect.u16TempCutoff           = 195;
	ptr->Protect.u16TempDecay             = 20;

	ptr->Protect.u16PpmLossAct  		 = 1;
	ptr->Protect.u16PpmLossTime 		 = 10;

	ptr->VerCtrl.u8FwVer[0]              = 0;
	ptr->VerCtrl.u8ProjectName[0]      	 = 0;  

	ptr->DrvAdv.u16PosiDiv                 = 700;//800;//800;//600;//800;
	ptr->DrvAdv.u16SpdKpGain              = 230;//300;//800;//300;//700;//220;//= 280;
	ptr->DrvAdv.u16MotorFreeErr          = 36;//45; 
	ptr->DrvAdv.u16MotorFreeTime           = 0;

	ptr->DrvAdv.u16SpdKdGain              = 100;//170;//170;//50;//170;//= 170;
	ptr->DrvAdv.u16SpdDiv                 = 1;

	ptr->DrvAdv.u16InitialSpeed           = 45;	
	ptr->DrvAdv.u16InitialTimeOut         = 2;

	ptr->Protect.u16PtMaxAngle            = 220;//= 220;
	ptr->Protect.u16PtMiddle              = 2048;

}

