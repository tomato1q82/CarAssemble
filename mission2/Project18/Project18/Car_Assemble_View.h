#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "Type.h"

class CarAssembleView {
public:
    CarAssembleView(int* stack) : inputStack(stack)
    {
	}

    void displayView(int step)
    {
        if (step == CarType_Q)
        {
            printf(CLEAR_SCREEN);

            printf("        ______________\n");
            printf("       /|            | \n");
            printf("  ____/_|_____________|____\n");
            printf(" |                      O  |\n");
            printf(" '-(@)----------------(@)--'\n");
            printf("===============================\n");
            printf("� ���� Ÿ���� �����ұ��?\n");

            printf("1. Sedan\n");
            printf("2. SUV\n");
            printf("3. Truck\n");
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ ž���ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. ���峭 ����\n");
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
            printf("� ������ �ұ��?\n");
            printf("0. ó�� ȭ������ ���ư���\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        printf("===============================\n");
    }

    int getUserInput(int step)
    {
        char buf[MAX_BUFFER];
        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("���̹���\n");
            exit(0);
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if (*checkNumber != '\0')
        {
            printf("ERROR :: ���ڸ� �Է� ����\n");
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }

        // ��ȿ�� �˻�
        switch (step)
        {
        case CarType_Q:
            if (!(answer >= START_CART_TYPE && answer <= NUM_TOTAL_CAR_TYPE))
            {
                printf("ERROR :: ���� Ÿ���� %d ~ %d ������ ���� ����\n", START_CART_TYPE, NUM_TOTAL_CAR_TYPE);
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case Engine_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= NUM_TOTAL_ENGINE_TYPE))
            {
                printf("ERROR :: ������ %d ~ %d ������ ���� ����\n", START_ENGINE_TYPE, NUM_TOTAL_ENGINE_TYPE);
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case brakeSystem_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= NUM_TOTAL_BRAKE_SYSTEM_TYPE))
            {
                printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", START_BRAKE_SYSTEM_TYPE, NUM_TOTAL_BRAKE_SYSTEM_TYPE);
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case SteeringSystem_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= NUM_TOTAL_STEERING_SYSTEM_TYPE))
            {
                printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", START_STEERING_SYSTEM_TYPE, NUM_TOTAL_STEERING_SYSTEM_TYPE);
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case Run_Test:
            if (!(answer >= RETURN_TO_START && answer <= NUM_TOTAL_RUN_TEST_TYPE))
            {
                printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        }
        return answer;
    }

    void handleSelection(int* step, int answer)
    {
        if (answer == 0 && *step >= 1)
        {
            (*step)--;
        }
        else
        {
            switch (*step)
            {
            case CarType_Q:
                selectCarType(answer);
                break;
            case Engine_Q:
                selectEngine(answer);
                break;
            case brakeSystem_Q:
                selectbrakeSystem(answer);
                break;
            case SteeringSystem_Q:
                selectSteeringSystem(answer);
                break;
            }

            (*step)++;
            delay(DELAY_TIME_FOR_INPUT);
        }
    }


private:
		int* inputStack;

        void delay(int ms)
        {
			Sleep(ms);
        }

        void selectCarType(int answer)
        {
            inputStack[CarType_Q] = answer;
            
            printf("���� Ÿ������ %s �� �����ϼ̽��ϴ�.\n", Car::GetInstance().GetTypeName(inputStack[CarType_Q]));
        }

        void selectEngine(int answer)
        {
            inputStack[Engine_Q] = answer;

            printf("%s ������ �����ϼ̽��ϴ�.\n", CarEngine::GetInstance().GetTypeName(inputStack[Engine_Q]));
        }

        void selectbrakeSystem(int answer)
        {
            inputStack[brakeSystem_Q] = answer;

            printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", Brake::GetInstance().GetTypeName(inputStack[brakeSystem_Q]));
        }

        void selectSteeringSystem(int answer)
        {
            inputStack[SteeringSystem_Q] = answer;

            printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", Steering::GetInstance().GetTypeName(inputStack[SteeringSystem_Q]));
        }
};
