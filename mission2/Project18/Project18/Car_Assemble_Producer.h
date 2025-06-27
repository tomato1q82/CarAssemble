#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "Type.h"

class CarAssembleProducter
{
public:
    CarAssembleProducter(int* inputStack) : stack(inputStack) 
    {
		Car::GetInstance().Build();
        CarEngine::GetInstance().Build();
        Brake::GetInstance().Build();
        Steering::GetInstance().Build();
    }

    void handleSelection(int* step, int answer)
    {
        if (answer == 0)
        {
            *step = CarType_Q;
        }
        else if (answer == 1)
        {
            runProducedCar();
            delay(DELAY_TIME_FOR_INPUT);
        }
        else
        {
            printf("Test...\n");
            delay(DELAY_TIME_FOR_INPUT);
            testProducedCar();
            delay(DELAY_TIME_FOR_INPUT);
        }
    }

    bool runProducedCar()
    {
        bool isRunable = false;

        if (!isValidCheck())
        {
            printf("자동차가 동작되지 않습니다\n");
        }
        else
        {
            if (stack[Engine_Q] == BROKEN_ENGINE)
            {
                printf("엔진이 고장나있습니다.\n");
                printf("자동차가 움직이지 않습니다.\n");
            }
            else
            {
                printf("Car Type : %s \n", Car::GetInstance().GetTypeName(stack[CarType_Q]));
                printf("Engine : %s \n", CarEngine::GetInstance().GetTypeName(stack[Engine_Q]));
                printf("Brake System : %s \n", Brake::GetInstance().GetTypeName(stack[brakeSystem_Q]));
                printf("Steering System : %s \n", Steering::GetInstance().GetTypeName(stack[SteeringSystem_Q]));
                printf("자동차가 동작됩니다.\n");

                isRunable = true;
            }
        }

        return isRunable;
    }

    bool testProducedCar()
    {
        bool isRunable = false;

        if (!isValidCheck())
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");

            if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
            {
                printf("Sedan에는 Continental제동장치 사용 불가\n");
            }
            else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
            {
                printf("SUV에는 TOYOTA엔진 사용 불가\n");
            }
            else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
            {
                printf("Truck에는 WIA엔진 사용 불가\n");
            }
            else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
            {
                printf("Truck에는 Mando제동장치 사용 불가\n");
            }
            else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
            {
                printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
            }
        }
        else
        {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");

            isRunable = true;
        }

        return isRunable;
    }

private:
        int* stack;

		CarEngine carEngine;
        Brake brake;
		Steering streering;

        int isValidCheck()
        {
            if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
            {
                return false;
            }
            else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
            {
                return false;
            }
            else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
            {
                return false;
            }
            else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
            {
                return false;
            }
            else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
            {
                return false;
            }
            else
            {
                return true;
            }
            return true;
        }

        void delay(int ms)
        {
            Sleep(ms);
        }
};