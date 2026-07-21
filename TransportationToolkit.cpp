// TransportationToolkit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HorizontalCurve.h"
#include "VerticalCurve.h"
#include "Superelevation.h"
#include "StoppingSightDistance.h"
#include "CoordinateGeometry.h"
#include "QuantityCalculations.h"
#include "CsvImportExport.h"
#include "Reports.h"

using namespace std;


int main()
{
    
    int choice = 0;

	do
	{
		cout << endl;
		cout << " ********************* ENGINEERING TOOLKIT ********************" << endl;
		
		cout << endl;
		cout << "1. Horizontal Curve Calculator" << endl;
		cout << "2. Vertical Curve Calculator" << endl;
		cout << "3. Superelevation" << endl;
		cout << "4. Sight Distance" << endl;
		cout << "5. Coordinate Geometry (COGO)" << endl;
		cout << "6. Quantity Calculations" << endl;
		cout << "7. CSV Import/Export" << endl;
		cout << "8. Reports" << endl;
		cout << "0. Exit" << endl;
		
		cout << endl;
		cout << "Selection: ";
		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			HorizontalCurve hc;
			hc.Run();

			break;
		}
		case 2:
		{
			VerticalCurve vc;
			vc.Run();

			break;
		}
		case 3:
		{
			Superelevation tool;
			tool.Run();

			break;
		}
		case 4:
		{
			StoppingSightDistance tool;
			tool.Run();

			break;
		}
		case 5:
		{
			CoordinateGeometry tool;
			tool.Run();

			break;
		}
		case 6:
		{
			QuantityCalculations tool;
			tool.Run();

			break;
		}
		case 7:
		{
			CsvImportExport tool;
			tool.Run();

			break;
		}
		case 8:
		{
			Reports tool;
			tool.Run();

			break;
		}
		
		case 0:
		{
			cout << endl;
			cout << "Exit toolkit" << endl;

			break;
		}

		default:
		{
			cout << endl;
			cout << "Invalid Selection" << endl;

			break;
		}
		}
	} 
		while (choice != 0);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
