#include "HorizontalCurve.h"
#include "Constants.h">

#include <iostream>
#include <cmath>

using namespace std;


HorizontalCurve::HorizontalCurve()

{
	radius = 0;
	delta = 0;

	tangent = 0;
	length = 0;
	chord = 0;
	external = 0;
	middleOrdinate = 0;

}

void HorizontalCurve::Run()

{
	cout << endl;
	cout << "************** Horizontal Curve Calcaltor ************" << endl;

	cout << endl;
	cout << "Radius (m):";
	cout << endl;
	cin >> radius;


	cout << endl;
	cout << "Delta Angle (degrees):";

	cout << endl;
	cin >> delta;

	double halfAngle = delta / 2.0;
	double radians = halfAngle * PI / 180.0;

	tangent = radius * tan(radians);
	
	length = PI * radius * delta / 180.0;

	chord = 2 * radius * sin(radians);

	external = radius * ((1 / cos(radians)) - 1);
	
	middleOrdinate = radius * (1 - cos(radians));

	cout << "\nResults\n";
	cout << "---------\n";

cout <<	"Tangent Length : " << tangent << " m\n";
cout << "Curve Length : " << length << " m\n";
cout << "Long Chord : " << chord << " m\n";
cout << "External Dist. : " << external << " m\n";
cout << "Middle Ordinate : " << middleOrdinate << " m\n";

//// expr double DegreesTo Radians (double degrees)) 
//// eturn degrees * PI / 180"



	




}