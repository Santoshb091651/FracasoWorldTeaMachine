/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "TeaMachine.h"
#include "TeaMachineCfg.h"
#include "ActuatorsControls.h"

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
    Holds the current state of preparation tank state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

PreperationTankStateType gPreperationTankState_en = PREP_EMPTY_TANK;

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

/*gPrepTankCleanStatus_en

  Summary:
    Holds the current state of tea serving state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/

TankCleanedStatusType gStorageTankCleanStatus_en = TANK_NOT_CLEANED;

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
    Holds the current level of preparation tank
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by preparation tank level sensor.
	
*/

PreperationTankLevelType gPrepTankLevel_en = PREPERATION_TANK_ZERO_LEVEL;

/*gPrepTankIngredientsTImeout_u32

  Summary:
    Holds the timeout count for filling ingredients into preparation tank,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrepTankIngredientsTImeout_u32 = 0u;

/*gPrepTankBoilingTImeout_u32

  Summary:
    Holds the timeout count for boiling the preparation tank,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrepTankBoilingTImeout_u32 = 0u;

/*gPrepTankTemperature_u32

  Summary:
    Holds the preparation tank temperature value,
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by preparation tank temperature sensor.
	
*/

signed int gPrepTankTemperature_u32 = 0u;

/*gStorageTankReqForDecoction_en

  Summary:
    Holds the storage tank request status for decoction discharging,
	
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
	be maintained by tea cup proximity sensor.
	
*/

TeaCupAvailableStatusType gTeaCupAvailable_en = TEA_CUP_AVAILABLE;

/*gTeaMakingDcecoctionTimeout

  Summary:
    Holds the timeout count for adding the decoction to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingDcecoctionTimeout_u32 = 0u;

/*gTeaMakingMilkTimeout

  Summary:
    Holds the timeout count for adding the milk to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingMilkTimeout_u32 = 0u;

/*gTeaMakingSyrupTimeout

  Summary:
    Holds the timeout count for adding the syrup to funnel,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaMakingSyrupTimeout_u32 = 0u;

/*gTeaServingTimeout

  Summary:
    Holds the timeout count for discharging tea to cup,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gTeaServingTimeout_u32 = 0u;


/*gStorageTankCleaningTimeout_u32

  Summary:
    Holds the timeout count for discharging tea to cup,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gStorageTankCleaningTimeout_u32 = 0u;

/*gPrperTankCleaningTimeout_u32

  Summary:
    Holds the timeout count for discharging tea to cup,
	
  Description:

  Remarks:
    This variable should be initialized by the application state machine.
	
*/

unsigned int gPrperTankCleaningTimeout_u32 = 0u;
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
        case PREP_EMPTY_TANK:
            if(gPrepTankCleanStatus_en == TANK_CLEANED){
                if(gTimeOfday_en == DAY_END){
                    /*Do nothing*/
                }else{
                    if(vRequestForStartWaterPumping()){
						gPrepTankCleanStatus_en = TANK_NOT_CLEANED;
                        gPrepWaterFillingTimeout_u32 == PREP_TANK_WATER_FILLING_MAX_TIMEOUT;
                        gPreperationTankState_en = PREP_FILLING_WITH_WATER;
                    }else{/*Do nothing*/}
                }
            }else{
                gPreperationTankState_en = PREP_TANK_CLEANING;
                gPrperTankCleaningTimeout_u32 = MAX_PREPERATION_TANK_CLEANING_TIMEOUT;
                vTurnOffPTOV();
                vTurnOffSTIV();
                vTurnOnPreperationTankSteamInValve();
                vTurnOnPreperationTankSteamOutValve();
            }
            break;
        case PREP_FILLING_WITH_WATER:
            if(gPrepTankLevel_en > MAX_PREP_TANK_LEVEL){
                if(vRequestForStopWaterPumping()){
                    vTurnOnPrepTankInductionHeater();
                    gPreperationTankState_en = PREP_TANK_BOILING_WATER;
                }else{
                    /*Pending*/
                }
            }else{
                if(gPrepWaterFillingTimeout_u32 == 0u){
                    /*Pending*/
                }else{/*Do nothing*/}
            }
            break;
        case PREP_TANK_BOILING_WATER:
            if(gPrepTankTemperature_u32 >= WATER_BOILING_POINT){
                vTurnOnIngridiantsAddingMotorAndValve();
                gPrepTankIngredientsTImeout_u32 = MAX_TIMEOUT_PREP_TANK_ADD_INGRIDIANTS;
                gPreperationTankState_en = PREP_ADDING_INGRIDIANTS;
            }else{
                /*Do nothing*/
            }
            break;
        case PREP_ADDING_INGRIDIANTS:
            if(gPrepTankIngredientsTImeout_u32 == 0u){
                vTurnOffIngridiantsAddingMotorAndValve();
                gPrepTankBoilingTImeout_u32 = MAX_TIMEOUT_PREP_TANK_BOILING;
                gPreperationTankState_en = PREP_BOILING_DECOCTION;
            }else{
                /*Do nothing*/
            }
            break;
        case PREP_BOILING_DECOCTION:
            if((gPrepTankTemperature_u32 >= MAX_PREP_TANK_TEMPERATUR) && (gPrepTankBoilingTImeout_u32 == 0u)){
                vTurnOffPrepTankInductionHeater();
                gPreperationTankState_en = PREP_DECOCTION_READY;
            }else{
                /*Do nothing*/
            }
            break;
        case PREP_DECOCTION_READY:
            if(gStorageTankReqForDecoction_en == REQUESTED_FOR_START_DISCHARGE){
                vTurnOnFTOPSV();
                vTurnOnFilterMotor();
                vTurnOnSM(); /*Preparation tank output valve controlling servo motor*/
                gStorageTankReqForDecoction_en == STARTED_DISCHARGING;
                gPreperationTankState_en = PREP_DISCHARGING_DECOCTION;
            }else{
                if(gPrepTankTemperature_u32 < MIN_PREP_TANK_TEMPERATURE){
                    gPreperationTankState_en = PREP_BOILING_DECOCTION;
                }else{/*Do nothing*/}
            }
            break;
        case PREP_DISCHARGING_DECOCTION:
            if(gPrepTankLevel_en < MIN_PREP_TANK_LEVEL){
                gPreperationTankState_en = PREP_EMPTY_TANK;
                vTurnOffPTOV();
                vTurnOffFilterMotor();
                vTurnOffSTIV();
                gStorageTankReqForDecoction_en = STOPPED_DISCHARGING;
            }else{
                if(gStorageTankReqForDecoction_en == REQUESTED_FOR_STOP_DISCHARGE){
                    gPreperationTankState_en = PREP_DECOCTION_READY;
                    vTurnOffSM();/*Preparation tank output valve controlling servo motor*/
                    vTurnOffFilterMotor();
                    vTurnOffFTOPSV();
                    gStorageTankReqForDecoction_en = STOPPED_DISCHARGING;
                }else{
					/*Do nothing*/
				}
            }
            break;
        case PREP_TANK_CLEANING:
            if(gPrperTankCleaningTimeout_u32 == 0u){
                vTurnOffPreperationTankSteamInValve();
                vTurnOffPreperationTankSteamOutValve();
                gPrepTankCleanStatus_en = TANK_CLEANED
                gPreperationTankState_en = PREP_EMPTY_TANK;
            }else{
                gPrperTankCleaningTimeout_u32--;
            }
            break;
        default:
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
                gStorageTankCleaningTimeout_u32 = MAX_STORAGE_TANK_CLEANING_TIMEOUT;
                gStorageTankState_en = TANK_CLEANING;
            }else{
                /*Do nothing*/
            }
            break;
        case TANK_CLEANING:
            if(gStorageTankCleaningTimeout_u32 == 0u){
                vTurnOffStorageTankSteamInValve();
                vTurnOffStorageTankSteamOutValve();
                if(gTimeOfday_en != DAY_END){
                    gStorageTankState_en = TANK_EMPTY;
                    gStorageTankReqForDecoction_en = REQUESTED_FOR_START_DISCHARGE;
                }else{
                    gStorageTankState_en = TANK_IDLE;
                }
            }else{
                gStorageTankCleaningTimeout_u32--;
                /*Do nothing*/
            }
            break;
        case TANK_EMPTY:
            if(gStorageTankReqForDecoction_en == STARTED_DISCHARGING){
                gStorageTankState_en = TANK_FILLING_WITH_DECOCTION;
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
                    gStorageTankState_en = TANK_FILLING_WITH_DECOCTION;
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
                if(gRequestForTeaStatus_en = REQUESTED && (gTeaCupAvailable_en == TEA_CUP_AVAILABLE)){ /*Checking if tea is requested by user and cup is available*/
                    gRequestForTeaStatus_en = REQUEST_SERVING; /*Changing the tea request flag to serving status*/ 
                    vTurnOnSTOV(); /*Turning ON the decoction tank output valve*/
                    vTurnOnMTOV(); /*Turning ON the milk tank output valve*/
                    vTurnOnSyTOV(); /*Turning ON the syrup tank output valve*/
                    gTeaMakingDcecoctionTimeout_u32 = TEA_MAKING_DECOCTION_TIMEOUT; /*Initializing the timeout value for discharging the decoction to funnel*/
                    gTeaMakingMilkTimeout_u32 = TEA_MAKING_MILK_TIMEOUT; /*Initializing the timeout value for discharging the milk to funnel*/
                    gTeaMakingSyrupTimeout_u32 = TEA_MAKING_SYRUP_TIMEOUT; /*Initializing the timeout value for discharging the syrup to funnel*/
                    gTeaServingState_en = TEA_MAKING_INACTION;  /* Setting the tea serving state variable to making state*/
                }else{
                    gRequestForTeaStatus_en = NO_REQUEST;
                }
                break;
            case TEA_MAKING_INACTION:
                if(gTeaMakingDcecoctionTimeout_u32 > 0u){
                    gTeaMakingDcecoctionTimeout_u32--;
                }else{
                    vTurnOffSTOV(); /*Turning OFF the storage tank output valve*/
                }
                if(gTeaMakingMilkTimeout_u32 > 0u){
                    gTeaMakingMilkTimeout_u32--;
                }else{
                    vTurnOffMTOV(); /*Turning OFF the milk tank output valve*/
                }
                if(gTeaMakingSyrupTimeout_u32 > 0u){
                    gTeaMakingSyrupTimeout_u32--;
                }else{
                    vTurnOffSyTOV(); /*Turning OFF the syrup tank output valve*/
                }
				/*Checking all the ingredients got properly mixed for making tea*/
                if((gTeaMakingDcecoctionTimeout_u32 == 0u) && (gTeaMakingMilkTimeout_u32 == 0u) && (gTeaMakingSyrupTimeout_u32 == 0u)){
                    gTeaServingTimeout_u32 = TEA_SERVING_TIMEOUT; /*Initializing the timeout value for discharging the tea into the cup*/
                    vTurnOnTFOV(); /*Turning OFF the Tea funnel output valve*/
                    gTeaServingState_en = TEA_SERVING_INACTION; /* Setting the tea serving state variable to serving state*/
                }else{
                    /*Do nothing*/
                }
                break;
            case TEA_SERVING_INACTION:
                if(gTeaServingTimeout_u32 > 0u){
                    gTeaServingTimeout_u32--;
                }else{
                    vTurnOffTFOV(); /*Turning OFF the Tea funnel output valve*/
					gRequestForTeaStatus_en = NO_REQUEST; /*Changing the tea request flag to no request status*/ 
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
