#pragma once
#include "TBase.h"
#include "TPoint.h"

class TLine : public TBase
{
protected:
	TPoint p1, p2;
	virtual void SetChild(TBase* c, int i);
public:
	TLine(){}
	TLine(const TPoint& _p1, const TPoint& _p2);
	TLine(const TLine& _line);

	TPoint& getFirst();
	TPoint& getSecond();

	virtual void Print();
	virtual double GetVal(int i);
	virtual double SetVal(double val, int i);
	virtual double& operator[](char* name);
	virtual double& operator[](int i);

	virtual TBase* GetChild(int i);
	virtual TBase* Clone();

	friend std::ostream& operator<<(std::ostream& out, const TLine& _line);
};