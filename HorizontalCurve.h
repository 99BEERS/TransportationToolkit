#pragma once
class HorizontalCurve
{
public:

	HorizontalCurve();
	void Run();

private:

	void GetInput();
	void Calculate();
	void DisplayResults();

	double radius;
	double delta;
	double tangent;
	double length;
	double chord;
	double external;
	double middleOrdinate;

};
