#pragma once  
#include "ICar_Assemble_Type.h"  
#include <stdio.h>
#include <string.h>
enum CarType
{
    START_CART_TYPE = 1,

    SEDAN = START_CART_TYPE,
    SUV,
    TRUCK,

    NUM_TOTAL_CAR_TYPE = TRUCK
};

class Car : public ICarAssembleType
{  
public:  
    static Car& GetInstance()
    { 
        static Car instance;
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
        AddType("SEDAN");  
        AddType("SUV");  
        AddType("TRUCK");  
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
	Car() = default;

    int totalType{ 1 };  
    char* typeNames[256];  
};