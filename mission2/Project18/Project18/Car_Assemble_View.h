#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "Type.h"
#include <stdexcept>

class CarAssembleView {
public:
    CarAssembleView(int* stack) : inputStack(stack)
    {
	}

    void displayUserView(int step)
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
            printf("어떤 차량 타입을 선택할까요?\n");

            Car::GetInstance().PrintAllType();
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 엔진을 탑재할까요?\n");
            printf("0. 뒤로가기\n");

            CarEngine::GetInstance().PrintAllType();
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 제동장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");

            Brake::GetInstance().PrintAllType();
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 조향장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");

            Steering::GetInstance().PrintAllType();
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("멋진 차량이 완성되었습니다.\n");
            printf("어떤 동작을 할까요?\n");
            printf("0. 처음 화면으로 돌아가기\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        else
        {
			throw std::invalid_argument("Invalid step for displayUserView");
        }

        printf("===============================\n");
    }

    int getValidatedUserInput(int step)
    {
        char buf[MAX_BUFFER];
        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // 엔터 개행문자 제거
        DeleteLineFeed(buf);

        // 숫자로 된 대답인지 확인
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

        // 입력받은 문자가 숫자가 아니라면
        if (*checkNumber != '\0')
        {
            printf("ERROR :: 숫자만 입력 가능\n");
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }

        // 유효성 검사
        switch (step)
        {
        case CarType_Q:
            if (!(answer >= START_CART_TYPE && answer <= Car::GetInstance().GetTotalType()))
            {
                printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", START_CART_TYPE, Car::GetInstance().GetTotalType());
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case Engine_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= CarEngine::GetInstance().GetTotalType()))
            {
                printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", START_ENGINE_TYPE, CarEngine::GetInstance().GetTotalType());
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case brakeSystem_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= Brake::GetInstance().GetTotalType()))
            {
                printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", START_BRAKE_SYSTEM_TYPE, Brake::GetInstance().GetTotalType());
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case SteeringSystem_Q:
            if (!(answer >= RETURN_TO_PREVIOUS && answer <= Steering::GetInstance().GetTotalType()))
            {
                printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", START_STEERING_SYSTEM_TYPE, Steering::GetInstance().GetTotalType());
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        case Run_Test:
            if (!(answer >= RETURN_TO_START && answer <= NUM_TOTAL_RUN_TEST_TYPE))
            {
                printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
                delay(DELAY_TIME_FOR_INPUT);
                return -1;
            }
            break;
        }
        return answer;
    }

    void DeleteLineFeed(char  buf[100])
    {
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("바이바이\n");
            exit(0);
        }
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
            default:
                throw std::invalid_argument("Invalid step for displayUserView");
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
            
            printf("차량 타입으로 %s 을 선택하셨습니다.\n", Car::GetInstance().GetTypeName(inputStack[CarType_Q]));
        }

        void selectEngine(int answer)
        {
            inputStack[Engine_Q] = answer;

            printf("%s 엔진을 선택하셨습니다.\n", CarEngine::GetInstance().GetTypeName(inputStack[Engine_Q]));
        }

        void selectbrakeSystem(int answer)
        {
            inputStack[brakeSystem_Q] = answer;

            printf("%s 제동장치를 선택하셨습니다.\n", Brake::GetInstance().GetTypeName(inputStack[brakeSystem_Q]));
        }

        void selectSteeringSystem(int answer)
        {
            inputStack[SteeringSystem_Q] = answer;

            printf("%s 조향장치를 선택하셨습니다.\n", Steering::GetInstance().GetTypeName(inputStack[SteeringSystem_Q]));
        }
};
