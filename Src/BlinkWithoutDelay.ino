/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  The circuit:
  - Use the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2005
  by David A. Mellis
  modified 8 Feb 2010
  by Paul Stoffregen
  modified 11 Nov 2013
  by Scott Fitzgerald
  modified 9 Jan 2017
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

#define PREP_TANK_WATER_FILLING_MAX_TIMEOUT          (0u)
#define MAX_TIMEOUT_PREP_TANK_ADD_INGRIDIANTS        (0u)
#define MAX_TIMEOUT_PREP_TANK_BOILING                (0u)
#define STORAGE_TANK_ZERO_LEVEL                      (0u)
#define STORAGE_TANK_MAX_LEVEL                       (0u)
#define STORAGE_TANK_MIN_LEVEL                       (0u)
#define MAX_PREP_TANK_TEMPERATUR                     (0u)
#define MAX_PREP_TANK_LEVEL                          (0u)
#define MIN_PREP_TANK_TEMPERATURE                    (0u)
#define MIN_PREP_TANK_LEVEL                          (0u)
#define TEA_MAKING_DECOCTION_TIMEOUT                 (0u)
#define TEA_MAKING_MILK_TIMEOUT                      (0u)
#define TEA_MAKING_SYRUP_TIMEOUT                     (0u)
#define TEA_SERVING_TIMEOUT                          (0u)
#define MAX_PREPERATION_TANK_CLEANING_TIMEOUT        (0u)
#define MAX_STORAGE_TANK_CLEANING_TIMEOUT            (0u)
/*PreperationTankStateType

  Summary:
    Holds the current state of Preperation tank state machine
  
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
  
*/
typedef enum 
{
  PREP_EMPTY_TANK,
  PREP_FILLING_WITH_WATER,
  PREP_ADDING_INGRIDIANTS,
  PREP_BOILING_DECOCTION,
  PREP_DECOCTION_READY,
  PREP_DISCHARGING_DECOCTION,
  PREP_TANK_CLEANING,
  PREP_TANK_INVALID_STATE
}PreperationTankStateType;

/*StorageTankStateType

  Summary:
    Holds the current state of storage tank state machine
  
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize 
*/
typedef enum 
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
typedef enum 
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
typedef enum 
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
typedef enum 
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
typedef enum 
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
typedef enum 
{
  NOT_REQUESTED,
  REQUESTED_FOR_START_DISCHARGE,
  STARTED_DISCHARGING,
  REQUESTED_FOR_STOP_DISCHARGE,        
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
typedef enum 
{
  STORAGE_TANK_LEVEL_ZERO,
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
typedef enum 
{
  NO_REQUEST,
  REQUESTED,        
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
typedef enum 
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
void vServeTea(void);

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin
const int PrepTankOVPin = 1u;
const int PrepTankIVPin = 2u;
const int StorageTankOVPin = 3u;
const int StorageTankIVPin = 4u;
const int FilterMotorPin = 5u;
const int PrepTankSteamOVPin = 6u;
const int PrepTankSteamIVPin = 7u;
const int StorageTankSteamOVPin = 8u;
const int StorageTankSteamIVPin = 9u;
const int MilkTankOVPin = 10u; 
const int SyrupTankOVPin = 11u;
const int FunelOVPin = 12u;
const int WaterPumpPin = 13u;
const int WaterPumpOVPin = 14u;
const int IngredientMotorPin = 15u;
const int IngedientOVPin = 16u;
const int InductionHeaterPin = 18u;



// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

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

StorageTankLevelType gStorageTankLevel_en = STORAGE_TANK_LEVEL_ZERO;

/*gRequestForTeaStatus_en

  Summary:
    Holds the tea request status
  
  Description:

  Remarks:
    This variable should be initialized by the APP_Initialize and will 
  be maintained by user tea request input sensors.
  
*/

TeaRequestStatusType gRequestForTeaStatus_en = NO_REQUEST;

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

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

/*******************************************************************************
  Function:
    void vTurnOffPTOV ( void )

  Summary:
    Api function to turn off the preperation tank output valve.
 */
void vTurnOffPTOV(void)
{
  digitalWrite(PrepTankOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffSTIV ( void )

  Summary:
    Api function to turn off the storage tank input valve.
 */
void vTurnOffSTIV(void)
{
    digitalWrite(StorageTankIVPin, LOW);
}

/*******************************************************************************
  Function:
    void vTurnOnPreperationTankSteamInValve ( void )

  Summary:
    Api function to turn on preperation tank steam input valve
 */
void vTurnOnPreperationTankSteamInValve(void)
{
  digitalWrite(PrepTankSteamOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOnPreperationTankSteamOutValve ( void )

  Summary:
    Api function to turn on preperation tank steam output valve
 */
void vTurnOnPreperationTankSteamOutValve(void)
{
  digitalWrite(PrepTankSteamIVPin, HIGH);
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
  digitalWrite(WaterPumpPin, HIGH);
  digitalWrite(WaterPumpOVPin, HIGH);
  return true;
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
  digitalWrite(WaterPumpPin, LOW);
  digitalWrite(WaterPumpOVPin, LOW);
  return true;
}
/*******************************************************************************
  Function:
    void vTurnOnIngridiantsAddingMotorAndValve ( void )

  Summary:
    Api function to turn on preperation tank ingredients adding motor and valve.
 */
void vTurnOnIngridiantsAddingMotorAndValve(void)
{
  digitalWrite(IngredientMotorPin, HIGH);
  digitalWrite(IngedientOVPin, HIGH);
  
}
/*******************************************************************************
  Function:
    void vTurnOffIngridiantsAddingMotorAndValve ( void )

  Summary:
    Api function to turn off preperation tank ingredients adding motor and valve.
 */
void vTurnOffIngridiantsAddingMotorAndValve(void)
{
  digitalWrite(IngredientMotorPin, LOW);
  digitalWrite(IngedientOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOnPrepTankInductionHeater ( void )

  Summary:
    Api function to turn on preperation tank induction heater.
 */
void vTurnOnPrepTankInductionHeater(void)
{
  digitalWrite(InductionHeaterPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOffPrepTankInductionHeater ( void )

  Summary:
    Api function to turn off preperation tank induction heater.
 */
void vTurnOffPrepTankInductionHeater(void)
{
  digitalWrite(InductionHeaterPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOnSTIV ( void )

  Summary:
    This Api is to turn on the storage tank input valve.
 */
void vTurnOnSTIV(void)
{
  digitalWrite(StorageTankIVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOnFilterMotor ( void )

  Summary:
    This Api is to turn on the filter motor.
 */
void vTurnOnFilterMotor(void)
{
  digitalWrite(FilterMotorPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOnPTOV ( void )

  Summary:
    This Api is to turn on the preperation tank output valve.
 */
void vTurnOnPTOV(void)
{
  digitalWrite(PrepTankOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOffFilterMotor ( void )

  Summary:
    This Api is to turn off the filter motor.
 */
void vTurnOffFilterMotor(void)
{
  digitalWrite(FilterMotorPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffPreperationTankSteamInValve ( void )

  Summary:
    This Api function is to turn off the preperation tank steam input valve.
 */
void vTurnOffPreperationTankSteamInValve(void)
{
  digitalWrite(PrepTankSteamIVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffPreperationTankSteamOutValve ( void )

  Summary:
    This Api function is to turn off the preperation tank steam output valve.
 */
void vTurnOffPreperationTankSteamOutValve(void)
{
  digitalWrite(PrepTankSteamOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOnStorageTankSteamInValve ( void )

  Summary:
    This Api function is to turn on the storage tank steam input valve.
 */
void vTurnOnStorageTankSteamInValve(void)
{
  digitalWrite(StorageTankSteamIVPin, HIGH);
}
/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
    This Api function is to turn on the storage tank steam output valve.
 */
void vTurnOnStorageTankSteamOutValve(void)
{
  digitalWrite(StorageTankSteamOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOffStorageTankSteamInValve ( void )

  Summary:
    This Api function is to turn off the storage tank steam input valve.
 */
void vTurnOffStorageTankSteamInValve(void)
{
  digitalWrite(StorageTankSteamIVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffStorageTankSteamOutValve ( void )

  Summary:
    This Api function is to turn off the storage tank steam ouput valve.
 */
void vTurnOffStorageTankSteamOutValve(void)
{
  digitalWrite(StorageTankSteamOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOnSTOV ( void )

  Summary:
    This Api function is to turn on the storage tank ouput valve.
 */
void vTurnOnSTOV(void)
{
  digitalWrite(StorageTankOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOnMTOV ( void )

  Summary:
    This Api function is to turn on the milk tank ouput valve.
 */
void vTurnOnMTOV(void)
{
  digitalWrite(MilkTankOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOnSyTOV ( void )

  Summary:
    This Api function is to turn on the syrup tank ouput valve.
 */
void vTurnOnSyTOV(void)
{
  digitalWrite(SyrupTankOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOffSTOV ( void )

  Summary:
    This Api function is to turn off the storage tank ouput valve.
 */
void vTurnOffSTOV(void)
{
  digitalWrite(StorageTankOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffMTOV ( void )

  Summary:
    This Api function is to turn off the milk tank ouput valve.
 */
void vTurnOffMTOV(void)
{
  digitalWrite(MilkTankOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOffSyTOV ( void )

  Summary:
    This Api function is to turn off the syrup tank ouput valve.
 */
void vTurnOffSyTOV(void)
{
  digitalWrite(SyrupTankOVPin, LOW);
}
/*******************************************************************************
  Function:
    void vTurnOnTFOV ( void )

  Summary:
    This Api function is to turn on the valve at the tea releasing funnel.
 */
void vTurnOnTFOV(void)
{
  digitalWrite(FunelOVPin, HIGH);
}
/*******************************************************************************
  Function:
    void vTurnOffTFOV ( void )

  Summary:
    This Api function is to turn off the valve at the tea releasing funnel.
 */
void vTurnOffTFOV(void)
{
  digitalWrite(FunelOVPin, LOW);
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
                    vTurnOnIngridiantsAddingMotorAndValve();
                    gPrepTankIngredientsTImeout_u32 = MAX_TIMEOUT_PREP_TANK_ADD_INGRIDIANTS;
                    gPreperationTankState_en = PREP_ADDING_INGRIDIANTS;
                }else{
                    /*Pending*/
                }
            }else{
                if(gPrepWaterFillingTimeout_u32 == 0u){
                    /*Pending*/
                }else{/*Do nothing*/}
            }
            break;
        case PREP_ADDING_INGRIDIANTS:
            if(gPrepTankIngredientsTImeout_u32 == 0u){
                vTurnOffIngridiantsAddingMotorAndValve();
                gPrepTankBoilingTImeout_u32 = MAX_TIMEOUT_PREP_TANK_BOILING;
                vTurnOnPrepTankInductionHeater();
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
                vTurnOnSTIV();
                vTurnOnFilterMotor();
                vTurnOnPTOV();
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
                    vTurnOffPTOV();
                    vTurnOffFilterMotor();
                    vTurnOffSTIV();
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
                if((gRequestForTeaStatus_en = REQUESTED) && (gTeaCupAvailable_en == TEA_CUP_AVAILABLE)){ /*Checking if tea is requested by user and cup is available*/
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

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);


    
  }
}
