#ifndef TYPE_H  
#define TYPE_H  

#include "Car_Assemble_CarType.h"
#include "Car_Assemble_EngineType.h"
#include "Car_Assemble_SteeringType.h"
#include "Car_Assemble_BrakeType.h"

constexpr auto CLEAR_SCREEN = "\033[H\033[2J";
constexpr auto DELAY_TIME_FOR_INPUT = 500;  
constexpr auto INVALID_INPUT = -1;  
constexpr auto RETURN_TO_PREVIOUS = 0;  
constexpr auto RETURN_TO_START = 0;  

enum QuestionType  
{  
    CarType_Q,  
    Engine_Q,  
    brakeSystem_Q,  
    SteeringSystem_Q,  
    Run_Test,  
    NUM_TOTAL_STACK = Run_Test  
};  

enum RunTest  
{  
    START_RUN_TEST_TYPE = 1,  

    RUN = START_RUN_TEST_TYPE,  
    TEST,  

    NUM_TOTAL_RUN_TEST_TYPE = TEST  
};  

#endif // TYPE_H