/*******************************************************************************
 Tea Machine Application Source File
 
  Author:
    Santosh Male

  Company:
    Fracaso World Pvt. Ltd.

  File Name:
    TeaMachine.c

  Summary:
    This file contains the source code for the Tea machine controlling application.

  Description:
    This file contains the source code for the Tea machine controlling application. 
	It implements the logic of the application's state machine. All the macros 
	controlling the tea machine behaviour must tuned to proper values in TeaMachineCfg.h
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "TeaMachine.h"
#include "TeaMachineCfg.h"
#include "ActuatorsControls.h"
//#include "SensorsControls.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

/*gPreperationTankState_en

  Summary:
    Holds the current state of Preperation tank state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

PreperationTankStateType gPreperationTankState_en = EMPTY_TANK;

/*gStorageTankState_en

  Summary:
    Holds the current state of storage tank state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

StorageTankStateType gStorageTankState_en = TANK_IDLE;

/*gTeaServingState_en

  Summary:
    Holds the current state of tea serving state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

TeaServingStateType gTeaServingState_en = TEA_SERVING_IDLE;

/*gPrepTankCleanStatus_en

  Summary:
    Holds the current state of tea serving state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

TankCleanedStatusType gPrepTankCleanStatus_en = TANK_NOT_CLEANED;

/*gTimeOfday_en

  Summary:
    Holds the time of day either started or ended
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by real time clock. Sharp after 6 O clock evening the
	variable value will change to DAY_END.
	
*/

TimeOfDayType gTimeOfday_en = DAY_START;

/*gPrepWaterFillingTimeout_u32

  Summary:
    Holds the timeout count for filling water into preperation tank,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrepWaterFillingTimeout_u32 = 0u;

/*gPrepTankLevel_en

  Summary:
    Holds the current level of preperation tank
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by preperation tank level sensor.
	
*/

PreperationTankLevelType gPrepTankLevel_en = PREPERATION_TANK_ZERO_LEVEL;

/*gPrepTankIngredientsTImeout_u32

  Summary:
    Holds the timeout count for filling ingredients into preperation tank,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrepTankIngredientsTImeout_u32 = 0u;

/*gPrepTankBoilingTImeout_u32

  Summary:
    Holds the timeout count for boiling the preperation tank,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrepTankBoilingTImeout_u32 = 0u;

/*gPrepTankTemperature_u32

  Summary:
    Holds the preperation tank temperature value,
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by preperation tank temperature sensor.
	
*/

signed int gPrepTankTemperature_u32 = 0u;

/*gStorageTankReqForDecoction_en

  Summary:
    Holds the stoarege tank request status for decoction discharging,
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by application state machine.
	
*/

StorageTankRequestStatusType gStorageTankReqForDecoction_en = NOT_REQUESTED;

/*gStorageTankLevel_en

  Summary:
    Holds the current level of storage tank
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by storage tank level sensor.
	
*/

StorageTankLevelType gStorageTankLevel_en = STORAGE_TANK_ZERO_LEVEL;

/*gRequestForTeaStatus_en

  Summary:
    Holds the tea request status
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by user tea request input sensors.
	
*/

TeaRequestStatusType gRequestForTeaStatus_en = NOT_REQUESTED;

/*gTeaCupAvailable_en

  Summary:
    Holds the tea cup available status
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by tea cup proxmity sensor.
	
*/

TeaCupAvailableStatusType gTeaCupAvailable_en = TEA_CUP_AVAILABLE;

/*gTeaMakingDcecoctionTimeout

  Summary:
    Holds the timeout count for adding the decoction to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingDcecoctionTimeout = 0u;

/*gTeaMakingMilkTimeout

  Summary:
    Holds the timeout count for adding the milk to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingMilkTimeout = 0u;

/*gTeaMakingSyrupTimeout

  Summary:
    Holds the timeout count for adding the syrup to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingSyrupTimeout = 0u;

/*gTeaServingTimeout

  Summary:
    Holds the timeout count for discharging tea to cup,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaServingTimeout = 0u;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;

            if (appInitialized)
            {
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            vPreperationTankFSM();
            vStorageTankFSM();
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void vPreperationTankFSM(void)
{
    switch(gPreperationTankState_en)
    {
        case EMPTY_TANK:
            if(gPrepTankCleanStatus_en == TANK_CLEANED){
                if(gTimeOfday_en == DAY_END){
                    /*Do nothing*/
                }else{
                    if(vRequestForStartWaterPumping()){
						gPrepTankCleanStatus_en = TANK_NOT_CLEANED;
                        gPrepWaterFillingTimeout_u32 == PREP_TANK_WATER_FILLING_MAX_TIMEOUT;
                        gPreperationTankState_en = FILLING_WITH_WATER;
                    }else{/*Do nothing*/}
                }
            }else{
                gPreperationTankState_en = TANK_CLEANING;
                vTurnOffPTOV();
                vTurnOffSTIV();
                vTurnOnPreperationTankSteamInValve();
                vTurnOnPreperationTankSteamOutValve();
            }
            break;
        case FILLING_WITH_WATER:
            if(gPrepTankLevel_en > MAX_PREP_TANK_LEVEL){
                if(vRequestForStopWaterPumping()){
                    vTurnOnIngridiantsAddingMotorAndValve();
                    gPrepTankIngredientsTImeout_u32 = MAX_TIMEOUT_PREP_TANK_ADD_INGRIDIANTS;
                    gPreperationTankState_en = ADDING_INGRIDIANTS;
                }else{
                    /*Pending*/
                }
            }else{
                if(gPrepWaterFillingTimeout_u32 == 0u){
                    /*Pending*/
                }else{/*Do nothing*/}
            }
            break;
        case ADDING_INGRIDIANTS:
            if(gPrepTankIngredientsTImeout_u32 == 0u){
                vTurnOffIngridiantsAddingMotorAndValve();
                gPrepTankBoilingTImeout = MAX_TIMEOUT_PREP_TANK_BOILING;
                vTurnOnPrepTankInductionHeater();
                gPreperationTankState_en = BOILING_DECOCTION;
            }else{
                /*Do nothing*/
            }
            break;
        case BOILING_DECOCTION:
            if((gPrepTankTemperature_u32 >= MAX_PREP_TANK_TEMPERATUR) && (gPrepTankBoilingTImeout == 0u{
                vTurnOffPrepTankInductionHeater();
                gPreperationTankState_en = DECOCTION_READY;
            }else{
                /*Do nothing*/
            }
            break;
        case DECOCTION_READY:
            if(gStorageTankReqForDecoction_en == REQUESTED_FOR_START_DISCHARGE){
                vTurnOnSTIV();
                vTrnOnFilterMotor();
                vTurnOnPTOV();
                gStorageTankReqForDecoction_en == STARTED_DISCHARGING;
                gPreperationTankState_en = DISCHARGING_DECOCTION;
            }else{
                if(gPrepTankTemperature_u32 < MIN_PREP_TANK_TEMPERATURE){
                    gPreperationTankState_en = BOILING_DECOCTION;
                }else{/*Do nothing*/}
            }
            break;
        case DISCHARGING_DECOCTION:
            if(gPrepTankLevel_en < MIN_PREP_TANK_LEVEL){
                gPreperationTankState_en = EMPTY_TANK;
                vTurnOffPTOV();
                vTurnOffFilterMotor();
                vTurnOffSTIV();
                gStorageTankReqForDecoction_en = STOPPED_DISCHARGING;
            }else{
                if(gStorageTankReqForDecoction_en == REQUESTED_FOR_STOP_DISCHARGE){
                    gPreperationTankState_en = DECOCTION_READY;
                    vTurnOffPTOV();
                    vTurnOffFilterMotor();
                    vTurnOffSTIV();
                    gStorageTankReqForDecoction_en = STOPPED_DISCHARGING;
                }else{
					/*Do nothing*/
				}
            }
            break;
        case TANK_CLEANING:
            if(gPrepTankCleanStatus_en == TANK_CLEANED){
                vTurnOffPreperationTankSteamInValve();
                vTurnOffPreperationTankSteamOutValve();
                gPreperationTankState_en = EMPTY_TANK;
            }else{
                /*Do nothing*/
            }
            break;
        case default:
            break;
            
    }
}

void vStorageTankFSM()
{
    switch(gStorageTankState_en){
        case TANK_IDLE:
            if(gTimeOfday_en == DAY_START){
                vTurnOnStorageTankSteamInValve();
                vTurnOnStorageTankSteamOutValve();
                gStorageTankState_en = TANK_CLEANING;
            }else{
                /*Do nothing*/
            }
            break;
        case TANK_CLEANING:
            if(gStorageTankCleanStatus == TANK_CLEANED){
                vTurnOffStorageTankSteamInValve();
                vTurnOffStorageTankSteamOutValve();
                if(gTimeOfday_en != DAY_END){
                    gStorageTankState_en = TANK_EMPTY;
                    gStorageTankReqForDecoction_en = REQUESTED_FOR_START_DISCHARGE;
                }else{
                    gStorageTankState_en = TANK_IDLE;
                }
            }else{
                /*Do nothing*/
            }
            break;
        case TANK_EMPTY:
            if(gStorageTankReqForDecoction_en == STARTED_DISCHARGING){
                gStorageTankState_en = TANK_FILLING_WITH_DECOTION;
            }else if(gStorageTankReqForDecoction_en == STOPPED_DISCHARGING){
                gStorageTankReqForDecoction_en = REQUESTED_FOR_START_DISCHARGE;
            }else{
                /*Do nothing*/
            }
            break;
        case TANK_STORAGE_LESSTHAN_MIN:
            if(gStorageTankLevel_en == STORAGE_TANK_ZERO_LEVEL){
                gStorageTankState_en = TANK_EMPTY;
            }else{
                if(gStorageTankReqForDecoction_en == STOPPED_DISCHARGING){
                    gStorageTankReqForDecoction_en = REQUESTED_FOR_START_DISCHARGE;
                }else if(gStorageTankReqForDecoction_en == STARTED_DISCHARGING){
                    gStorageTankState_en = TANK_FILLING_WITH_DECOTION;
                }else{
                    /*Do nothing*/
                }
                vServeTea();
            }
            break;
        case TANK_FILLING_WITH_DECOCTION:
            if(gStorageTankReqForDecoction_en == STOPPED_DISCHARGING){
                if(gStorageTankLevel_en < STORAGE_TANK_MIN_LEVEL){
                    gStorageTankState_en = TANK_STORAGE_LESSTHAN_MIN;
                }else{
                    gStorageTankState_en = TANK_LAVEL_REACHED_TO_MAX;
                }
            }else{
                if(gStorageTankLevel_en >= STORAGE_TANK_MAX_LEVEL){
                    gStorageTankReqForDecoction_en = REQUESTED_FOR_STOP_DISCHARGE;
                    gStorageTankState_en = TANK_LAVEL_REACHED_TO_MAX;
                }else{
                    /*Do Nothing*/
                }
            }
            vServeTea();
            break;
        case TANK_LAVEL_REACHED_TO_MAX:
            if(gTimeOfday_en != DAY_END){
                if(gStorageTankLevel_en < STORAGE_TANK_MIN_LEVEL){
                    gStorageTankState_en = TANK_STORAGE_LESSTHAN_MIN;
                }else{
                    /*Do nothing*/
                }
            }else{
                vTurnOnStorageTankSteamOutValve();
                gStorageTankState_en = STORAGE_TANK_DRAINING;
            }
            vServeTea();
            break;
        case STORAGE_TANK_DRAINING:
            if(gStorageTankLevel_en == STORAGE_TANK_ZERO_LEVEL){
                vTurnOffStorageTankSteamOutValve();
                gStorageTankState_en = TANK_CLEANING;
            }
            break;
        default:
            break;
    }
}

void vServeTea(void)
{
    if(gStorageTankLevel_en > STORAGE_TANK_ZERO_LEVEL){
        switch(gTeaServingState_en)
        {
            case TEA_SERVING_IDLE:
                if(gRequestForTeaStatus_en = RQUESTED && (gTeaCupAvailable_en == TEA_CUP_AVAILABLE){ /*Checking if tea is requested by user and cup is availbe*/
                    gRequestForTeaStatus_en = REQUEST_SERVING; /*Changing the tea request flag to serving status*/ 
                    vTurnOnSTOV(); /*Turning ON the decoction tank output valve*/
                    vTurnOnMTOV(); /*Turning ON the milk tank output valve*/
                    vTurnOnSyTOV(); /*Turning ON the syrup tank output valve*/
                    gTeaMakingDcecoctionTimeout = TEA_MAKING_DECOCTION_TIMEOUT; /*Initializing the timeout value for discharging the decoction to funnel*/
                    gTeaMakingMilkTimeout = TEA_MAKING_MILK_TIMEOUT; /*Initializing the timeout value for discharging the milk to funnel*/
                    gTeaMakingSyrupTimeout = TEA_MAKING_SYRUP_TIMEOUT; /*Initializing the timeout value for discharging the syrup to funnel*/
                    gTeaServingState_en = TEA_MAKING_INACTION;  /* Setting the tea serving state variable to making state*/
                }else{
                    gRequestForTeaStatus_en = NOT_REQUESTED;
                }
                break;
            case TEA_MAKING_INACTION:
                if(gTeaMakingDcecoctionTimeout > 0u){
                    gTeaMakingDcecoctionTimeout--;
                }else{
                    vTurnOffSTOV(); /*Turning OFF the storage tank output valve*/
                }
                if(gTeaMakingMilkTimeout > 0u){
                    gTeaServingMilkTimeout--;
                }else{
                    vTurnOffMTOV(); /*Turning OFF the milk tank output valve*/
                }
                if(gTeaMakingSyrupTimeout > 0u){
                    gTeaServingSyrupTimeout--;
                }else{
                    vTurnOffSyTOV(); /*Turning OFF the syrup tank output valve*/
                }
				/*Checking all the ingredients got properly mixed for making tea*/
                if((gTeaMakingDcecoctionTimeout == 0u) && (gTeaMakingMilkTimeout == 0u) && (gTeaMakingSyrupTimeout == 0u)){
                    gTeaServingTimeout = TEA_SERVING_TIMEOUT; /*Initializing the timeout value for discharging the tea into the cup*/
                    vTurnOnTFOV(); /*Turning OFF the Tea funnel output valve*/
                    gTeaServingState_en = TEA_SERVING_INACTION; /* Setting the tea serving state variable to serving state*/
                }else{
                    /*Do nothing*/
                }
                break;
            case TEA_SERVING_INACTION:
                if(gTeaMakingMilkTimeout > 0u){
                    gTeaServingMilkTimeout--;
                }else{
                    vTurnOffTFOV(); /*Turning OFF the Tea funnel output valve*/
					gRequestForTeaStatus_en = NOT_REQUESTED; /*Changing the tea request flag to no request status*/ 
                    gTeaServingState_en = TEA_SERVING_IDLE; /* Setting the tea serving state variable to Idle state*/
                }
                break;
		    default:
				break;
        }
    }else{
        /*Do nothing*/
    }
}

/*******************************************************************************
 End of File
 */
