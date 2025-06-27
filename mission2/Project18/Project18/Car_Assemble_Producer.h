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
            printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        }
        else
        {
            if (stack[Engine_Q] == BROKEN_ENGINE)
            {
                printf("������ ���峪�ֽ��ϴ�.\n");
                printf("�ڵ����� �������� �ʽ��ϴ�.\n");
            }
            else
            {
                printf("Car Type : %s \n", Car::GetInstance().GetTypeName(stack[CarType_Q]));
                printf("Engine : %s \n", CarEngine::GetInstance().GetTypeName(stack[Engine_Q]));
                printf("Brake System : %s \n", Brake::GetInstance().GetTypeName(stack[brakeSystem_Q]));
                printf("Steering System : %s \n", Steering::GetInstance().GetTypeName(stack[SteeringSystem_Q]));
                printf("�ڵ����� ���۵˴ϴ�.\n");

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
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");

            if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
            {
                printf("Sedan���� Continental������ġ ��� �Ұ�\n");
            }
            else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
            {
                printf("SUV���� TOYOTA���� ��� �Ұ�\n");
            }
            else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
            {
                printf("Truck���� WIA���� ��� �Ұ�\n");
            }
            else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
            {
                printf("Truck���� Mando������ġ ��� �Ұ�\n");
            }
            else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
            {
                printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
            }
        }
        else
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");

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