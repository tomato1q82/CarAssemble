#pragma once  
#include "ICar_Assemble_Type.h"  
#include <stdio.h>
#include <string.h>

const int MAX_BRAKE_TYPE = 256;

enum brakeSystem
{
    START_BRAKE_SYSTEM_TYPE = 1,

    MANDO = START_BRAKE_SYSTEM_TYPE,
    CONTINENTAL,
    BOSCH_B,
    NUM_TOTAL_BRAKE_SYSTEM_TYPE = BOSCH_B
};

class Brake : public ICarAssembleType
{
public:
    static Brake& GetInstance()
    {
        static Brake instance;
        return instance;
    }

    char* GetTypeName(int type) override
    {
        return typeNames[type];
    }

    void AddType(const char* name) override
    {
        typeNames[totalType] = const_cast<char*>(name);
        totalType++;
    };

    void Build() override
    {
        AddType("MANDO");
        AddType("CONTINENTAL");
        AddType("BOSCH_B");
    }

    int GetTotalType() override { return totalType - 1; }

    void PrintAllType() override
    {

        for (int i = 1; i < totalType; i++)
        {
            printf("%d. %s\n", i, typeNames[i]);
        }
    }

private:
    int totalType{ 1 };
    char* typeNames[MAX_BRAKE_TYPE];
};