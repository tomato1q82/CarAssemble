#pragma once  
#include "ICar_Assemble_Type.h"  
#include <stdio.h>
#include <string.h>

const int MAX_STEERING_TYPE = 256;

enum SteeringSystem
{
    START_STEERING_SYSTEM_TYPE = 1,

    BOSCH_S = START_STEERING_SYSTEM_TYPE,
    MOBIS,

    NUM_TOTAL_STEERING_SYSTEM_TYPE = MOBIS
};

class Steering : public ICarAssembleType
{
public:
    static Steering& GetInstance()
    {
        static Steering instance;
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
        AddType("BOSCH_S");
        AddType("MOBIS");
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
    char* typeNames[MAX_STEERING_TYPE];
};