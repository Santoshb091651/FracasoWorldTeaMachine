/*******************************************************************************
 Tea Machine Application header File
 
  Author:
    Santosh Male

  Company:
    Fracaso World Pvt. Ltd.

  File Name:
    TeaMachine.h

  Summary:
    This file contains the typedefinations and function protypes for the Tea machine 
	controlling application.
*******************************************************************************/
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Data type definations
// *****************************************************************************
// *****************************************************************************

/*PreperationTankStateType

  Summary:
    Holds the current state of Preperation tank state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/
typedef struct PreperationTankStateType_t
{
	EMPTY_TANK,
	FILLING_WITH_WATER,
	ADDING_INGRIDIANTS,
	BOILING_DECOCTION,
	DECOCTION_READY,
	DISCHARGING_DECOCTION,
	TANK_CLEANING,
	PREP_TANK_INVALID_STATE
}PreperationTankStateType;

/*StorageTankStateType

  Summary:
    Holds the current state of storage tank state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/
typedef struct StorageTankStateType_t
{
	TANK_IDLE,
	TANK_CLEANING,
	TANK_EMPTY,
	TANK_STORAGE_LESSTHAN_MIN,
	TANK_FILLING_WITH_DECOCTION,
	TANK_LAVEL_REACHED_TO_MAX,
	STORAGE_TANK_DRAINING,
	STORAGE_TANK_INVALID_STATE
}StorageTankStateType;

/*TeaServingStateType

  Summary:
    Holds the current state of tea serving state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/
typedef struct TeaServingStateType_t
{
	TEA_SERVING_IDLE,
	TEA_MAKING_INACTION,
	TEA_SERVING_INACTION,
	TEA_SERVING_INVALID_STATE
}TeaServingStateType;

/*TankCleanedStatusType

  Summary:
    Holds the current state of tea serving state machine
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
	
*/
typedef struct TankCleanedStatusType_t
{
	TANK_NOT_CLEANED,
	TANK_CLEANED,
	TANK_CLEAN_STATUS_INVALID
}TankCleanedStatusType;

/*TimeOfDayType

  Summary:
    Holds the time of day either started or ended
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by real time clock. Sharp after 6 O clock evening the
	variable value will change to DAY_END.
	
*/
typedef struct TimeOfDayType_t
{
	DAY_START,
	DAY_END,
	INVALID_TIME_DAY,
}TimeOfDayType;

/*PreperationTankLevelType

  Summary:
    Holds the current level of preperation tank
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by preperation tank level sensor.
	
*/
typedef struct PreperationTankLevelType_t
{
	PREPERATION_TANK_ZERO_LEVEL,
	/*Need add few more levels here*/
	PREPERATION_TANK_LEVEL_INVALID
	
}PreperationTankLevelType;
	
/*StorageTankRequestStatusType

  Summary:
    Holds the stoarege tank request status for decoction discharging,
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by application state machine.
	
*/
typedef struct 	StorageTankRequestStatusType_t
{
	NOT_REQUESTED,
	REQUESTED_FOR_START_DISCHARGE,
	STARTED_DISCHARGING,
	STOPPED_DISCHARGING,
	INVALID_REQUEST_STATUS
}StorageTankRequestStatusType;

/*StorageTankLevelType

  Summary:
    Holds the current level of storage tank
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by storage tank level sensor.
	
*/
typedef struct StorageTankLevelType_t{
	STORAGE_TANK_ZERO_LEVEL,
	/*Need add few more levels here*/
	STORAGE_TANK_LEVEL_INVALID
}StorageTankLevelType;

/*TeaRequestStatusType

  Summary:
    Holds the tea request status
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by user tea request input sensors.
	
*/
typedef struct TeaRequestStatusType_t
{
	NOT_REQUESTED,
	REQUEST_SERVING,
	REQUEST_STATUS_INVALID
}TeaRequestStatusType;

/*TeaCupAvailableStatusType

  Summary:
    Holds the tea cup available status
	
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
	be maintained by tea cup proxmity sensor.
	
*/
typedef struct TeaCupAvailableStatusType_t
{
	TEA_CUP_AVAILABLE,
	TEA_CUP_NOT_AVAILABLE,
	TEA_CUP_AVAILABLE_STATUS_INVALID
}TeaCupAvailableStatusType;


// *****************************************************************************
// *****************************************************************************
// Section: Function prototypes
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    void vPreperationTankFSM ( void )

  Summary:
    Finite state machine for controlling preperation tank
 */
void vPreperationTankFSM(void);
/*******************************************************************************
  Function:
    void vStorageTankFSM ( void )

  Summary:
    Finite state machine for controlling storage tank
 */
void vStorageTankFSM(void);
/*******************************************************************************
  Function:
    void vServeTea ( void )

  Summary:
    function for preparing tand dispening the tea
 */
void vServeTea(void)