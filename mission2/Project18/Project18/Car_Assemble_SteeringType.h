#pragma once  
#include "ICar_Assemble_Type.h"  
#include <stdio.h>
#include <string.h>

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

    virtual char* GetTypeName(int type) override
    {
        return typeNames[type];
    }

    virtual void AddType(const char* name) override
    {
        typeNames[totalType] = const_cast<char*>(name);
        totalType++;
    };

    virtual void Build() override
    {
        AddType("BOSCH_S");
        AddType("MOBIS");
    }

    virtual int GetTotalType() override { return totalType - 1; }

    virtual void PrintAllType() override
    {

        for (int i = 1; i < totalType; i++)
        {
            printf("%d. %s\n", i, typeNames[i]);
        }
    }

private:
    int totalType{ 1 };
    char* typeNames[256];
};