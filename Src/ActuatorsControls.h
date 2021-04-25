/*******************************************************************************
 Tea Actuators controlling library  File
 
  Author:
    Santosh Male

  Company:
    Fracaso World Pvt. Ltd.

  File Name:
    ActuatorsControls.h

  Summary:
    This file contains the API functions to control the all the actators in Tea 
	machine.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "definitions.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: API functions
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    void vTurnOffPTOV ( void )

  Summary:
    Api function to turn off the preperation tank output valve.
 */
void vTurnOffPTOV(void)
{
	GPIO_PB05_PTOV_Set();
}
/*******************************************************************************
  Function:
    void vTurnOffSTIV ( void )

  Summary:
    Api function to turn off the storage tank input valve.
 */
void vTurnOffSTIV(void)
{
    GPIO_PA07_STIV_OUT_Set();
}

/*******************************************************************************
  Function:
    void vTurnOnPreperationTankSteamInValve ( void )

  Summary:
    Api function to turn on preperation tank steam input valve
 */
void vTurnOnPreperationTankSteamInValve(void)
{
	GPIO_PA23_PTSIV_OUT_Clear();
}
/*******************************************************************************
  Function:
    void vTurnOnPreperationTankSteamOutValve ( void )

  Summary:
    Api function to turn on preperation tank steam output valve
 */
void vTurnOnPreperationTankSteamOutValve(void)
{
	GPIO_PA22_PTSOV_OUT_Clear();
}
/*******************************************************************************
  Function:
    bool vRequestForStartWaterPumping ( void )

  Summary:
    This Api pumps the water into requested preperation tank if  availability of 
	water in water bubble is sufficient and water is pumping not busy in filling 
	other preperation tank. And returns the status of opearation.
	Returns false : if Water is not available or pump is busy
	Returns true : other wise
 */
bool vRequestForStartWaterPumping(void)
{
	
}
/*******************************************************************************
  Function:
    bool vRequestForStopWaterPumping ( void )

  Summary:
    This Api stops pumping water into preperation tank. and returns the status of 
	operation
 */
bool vRequestForStopWaterPumping(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnIngridiantsAddingMotorAndValve ( void )

  Summary:
    Api function to turn on preperation tank ingredients adding motor and valve.
 */
void vTurnOnIngridiantsAddingMotorAndValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffIngridiantsAddingMotorAndValve ( void )

  Summary:
    Api function to turn off preperation tank ingredients adding motor and valve.
 */
void vTurnOffIngridiantsAddingMotorAndValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnPrepTankInductionHeater ( void )

  Summary:
    Api function to turn on preperation tank induction heater.
 */
void vTurnOnPrepTankInductionHeater(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffPrepTankInductionHeater ( void )

  Summary:
    Api function to turn off preperation tank induction heater.
 */
void vTurnOffPrepTankInductionHeater(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnSTIV ( void )

  Summary:
    This Api is to turn on the storage tank input valve.
 */
void vTurnOnSTIV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnFilterMotor ( void )

  Summary:
    This Api is to turn on the filter motor.
 */
void vTurnOnFilterMotor(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnPTOV ( void )

  Summary:
    This Api is to turn on the preperation tank output valve.
 */
void vTurnOnPTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffFilterMotor ( void )

  Summary:
    This Api is to turn off the filter motor.
 */
void vTurnOffFilterMotor(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffPreperationTankSteamInValve ( void )

  Summary:
    This Api function is to turn off the preperation tank steam input valve.
 */
void vTurnOffPreperationTankSteamInValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffPreperationTankSteamOutValve ( void )

  Summary:
    This Api function is to turn off the preperation tank steam output valve.
 */
void vTurnOffPreperationTankSteamOutValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnStorageTankSteamInValve ( void )

  Summary:
    This Api function is to turn on the storage tank steam input valve.
 */
void vTurnOnStorageTankSteamInValve(void)
{
	
}
/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
    This Api function is to turn on the storage tank steam output valve.
 */
void vTurnOnStorageTankSteamOutValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffStorageTankSteamInValve ( void )

  Summary:
    This Api function is to turn off the storage tank steam input valve.
 */
void vTurnOffStorageTankSteamInValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffStorageTankSteamOutValve ( void )

  Summary:
    This Api function is to turn off the storage tank steam ouput valve.
 */
void vTurnOffStorageTankSteamOutValve(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnSTOV ( void )

  Summary:
    This Api function is to turn on the storage tank ouput valve.
 */
void vTurnOnSTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnMTOV ( void )

  Summary:
    This Api function is to turn on the milk tank ouput valve.
 */
void vTurnOnMTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnSyTOV ( void )

  Summary:
    This Api function is to turn on the syrup tank ouput valve.
 */
void vTurnOnSyTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffSTOV ( void )

  Summary:
    This Api function is to turn off the storage tank ouput valve.
 */
void vTurnOffSTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffMTOV ( void )

  Summary:
    This Api function is to turn off the milk tank ouput valve.
 */
void vTurnOffMTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffSyTOV ( void )

  Summary:
    This Api function is to turn off the syrup tank ouput valve.
 */
void vTurnOffSyTOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOnTFOV ( void )

  Summary:
    This Api function is to turn on the valve at the tea releasing funnel.
 */
void vTurnOnTFOV(void)
{
	
}
/*******************************************************************************
  Function:
    void vTurnOffTFOV ( void )

  Summary:
    This Api function is to turn off the valve at the tea releasing funnel.
 */
void vTurnOffTFOV(void)
{
	
}

/*******************************************************************************
 End of File
 */
