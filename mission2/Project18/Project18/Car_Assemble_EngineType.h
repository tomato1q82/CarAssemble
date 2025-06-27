#pragma once  
#include "ICar_Assemble_Type.h"  
#include <stdio.h>
#include <string.h>

const int MAX_ENGINE_TYPE = 256;

enum Engine
{
    START_ENGINE_TYPE = 1,

    GM = START_ENGINE_TYPE,
    TOYOTA,
    WIA,
    BROKEN_ENGINE,

    NUM_TOTAL_ENGINE_TYPE = BROKEN_ENGINE
};

class CarEngine : public ICarAssembleType
{
public:
    static CarEngine& GetInstance()
    {
        static CarEngine instance;
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
        AddType("GM");
        AddType("TOYOTA");
        AddType("WIA");
        AddType("BROKEN_ENGINE");
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
    char* typeNames[MAX_ENGINE_TYPE];
};