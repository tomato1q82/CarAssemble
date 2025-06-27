#pragma once

class ICarAssembleType
{
public:
	virtual void AddType(const char* name) = 0;
	virtual void Build() = 0;

	virtual char* GetTypeName(int type) = 0;
	virtual int GetTotalType() = 0;
	virtual void PrintAllType() = 0;
};