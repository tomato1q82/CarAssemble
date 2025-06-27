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
    char buf[100];
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
        if (!(answer >= 0 && answer <= NUM_TOTAL_ENGINE_TYPE))
        {
            printf("ERROR :: ������ %d ~ %d ������ ���� ����\n", START_ENGINE_TYPE, NUM_TOTAL_ENGINE_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case brakeSystem_Q:
        if (!(answer >= 0 && answer <= NUM_TOTAL_BRAKE_SYSTEM_TYPE))
        {
            printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", START_BRAKE_SYSTEM_TYPE, NUM_TOTAL_BRAKE_SYSTEM_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case SteeringSystem_Q:
        if (!(answer >= 0 && answer <= NUM_TOTAL_STEERING_SYSTEM_TYPE))
        {
            printf("ERROR :: ������ġ�� %d ~ %d ������ ���� ����\n", START_STEERING_SYSTEM_TYPE, NUM_TOTAL_STEERING_SYSTEM_TYPE);
            delay(DELAY_TIME_FOR_INPUT);
            return -1;
        }
        break;
    case Run_Test:
        if (!(answer >= 0 && answer <= NUM_TOTAL_RUN_TEST_TYPE))
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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
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
    }
}

#endif