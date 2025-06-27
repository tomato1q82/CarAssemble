#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
constexpr auto DELAY_TIME_FOR_INPUT = 1200;
constexpr auto INVALID_INPUT = -1;

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);
void displayView(int step);
int getUserInput(int step);
void handleSelection(int* step, int answer);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    NUM_TOTAL_STACK = Run_Test
};

int stack[NUM_TOTAL_STACK];

enum CarType
{
    START_CART_TYPE = 1,

    SEDAN = START_CART_TYPE,
    SUV,
    TRUCK,

    NUM_TOTAL_CAR_TYPE = TRUCK
};

enum Engine
{
    START_ENGINE_TYPE = 1,

    GM = START_ENGINE_TYPE,
    TOYOTA,
    WIA,
    BRAEK_EMGINE,

    NUM_TOTAL_ENGINE_TYPE = BRAEK_EMGINE
};

enum brakeSystem
{
    START_BRAKE_SYSTEM_TYPE = 1,

    MANDO = START_BRAKE_SYSTEM_TYPE,
    CONTINENTAL,
    BOSCH_B,
    NUM_TOTAL_BRAKE_SYSTEM_TYPE = BOSCH_B

};

enum SteeringSystem
{
    START_STEERING_SYSTEM_TYPE = 1,

    BOSCH_S = START_STEERING_SYSTEM_TYPE,
    MOBIS,

    NUM_TOTAL_STEERING_SYSTEM_TYPE = MOBIS
};

enum RunTest
{
    START_RUN_TEST_TYPE = 1,

    RUN = START_RUN_TEST_TYPE,
    TEST,

    NUM_TOTAL_RUN_TEST_TYPE = TEST
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main()
{
    int step = CarType_Q;

    while (true)
    {
        displayView(step);

        int answer = getUserInput(step);
        if (answer == INVALID_INPUT)
            continue;

        handleSelection(&step, answer);
    }
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
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
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
    printf("===============================\n");
}

int getUserInput(int step)
{
    char buf[100];
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        exit(0);
    }

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
        if (!(answer >= START_CART_TYPE && answer <= NUM_TOTAL_CAR_TYPE))
        {
            printf("ERROR :: 차량 타입은 %d ~ %d 범위만 선택 가능\n", START_CART_TYPE, NUM_TOTAL_CAR_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case Engine_Q:
        if (!(answer >= 0 && answer <= NUM_TOTAL_ENGINE_TYPE))
        {
            printf("ERROR :: 엔진은 %d ~ %d 범위만 선택 가능\n", START_ENGINE_TYPE, NUM_TOTAL_ENGINE_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case brakeSystem_Q:
        if (!(answer >= 0 && answer <= NUM_TOTAL_BRAKE_SYSTEM_TYPE))
        {
            printf("ERROR :: 제동장치는 %d ~ %d 범위만 선택 가능\n", START_BRAKE_SYSTEM_TYPE, NUM_TOTAL_BRAKE_SYSTEM_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case SteeringSystem_Q:
        if (!(answer >= 0 && answer <= NUM_TOTAL_STEERING_SYSTEM_TYPE))
        {
            printf("ERROR :: 조향장치는 %d ~ %d 범위만 선택 가능\n", START_STEERING_SYSTEM_TYPE, NUM_TOTAL_STEERING_SYSTEM_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case Run_Test:
        if (!(answer >= 0 && answer <= NUM_TOTAL_RUN_TEST_TYPE))
        {
            printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    }
    return answer;
}

void handleSelection(int* step, int answer)
{
    if (answer == 0 && *step == Run_Test)
    {
        *step = CarType_Q;
    }
    else if (answer == 0 && *step >= 1)
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
        case Run_Test:
            if (answer == RUN)
            {
                runProducedCar();
                delay(DELAY_TIME_FOR_INPUT);
            }
            else if (answer == TEST)
            {
                printf("Test...\n");
                delay(DELAY_TIME_FOR_INPUT);
                testProducedCar();
                delay(DELAY_TIME_FOR_INPUT);
            }
            return;
            break;
        }

        (*step)++;
        delay(DELAY_TIME_FOR_INPUT);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

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

void runProducedCar()
{
    if (!isValidCheck())
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");
            if (stack[brakeSystem_Q] == 1)
                printf("Brake System : Mando");
            if (stack[brakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
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
    }
}

#endif