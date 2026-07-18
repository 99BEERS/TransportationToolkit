#include "VerticalCurve.h"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

VerticalCurve::VerticalCurve()
{
    grade1Percent = 0.0;
    grade2Percent = 0.0;
    curveLength = 0.0;
    pviStation = 0.0;
    pviElevation = 0.0;

    grade1 = 0.0;
    grade2 = 0.0;
    algebraicGradeDifference = 0.0;

    pvcStation = 0.0;
    pviStationCalculated = 0.0;
    pvtStation = 0.0;

    pvcElevation = 0.0;
    pvtElevation = 0.0;

    highLowPointDistance = 0.0;
    highLowPointStation = 0.0;
    highLowPointElevation = 0.0;

    hasHighLowPoint = false;
}

void VerticalCurve::Run()
{
    GetInput();
    Calculate();
    DisplayResults();
}

void VerticalCurve::GetInput()
{
    cout << "\nVERTICAL CURVE CALCULATOR\n";
    cout << "-------------------------\n";

    cout << "Incoming grade g1 (%): ";
    cin >> grade1Percent;

    cout << "Outgoing grade g2 (%): ";
    cin >> grade2Percent;

    cout << "Curve length L (m): ";
    cin >> curveLength;

    cout << "PVI station (m): ";
    cin >> pviStation;

    cout << "PVI elevation (m): ";
    cin >> pviElevation;
}

void VerticalCurve::Calculate()
{
    // Convert percentages to decimal grades.
    grade1 = grade1Percent / 100.0;
    grade2 = grade2Percent / 100.0;

    algebraicGradeDifference = grade2 - grade1;

    // Symmetric vertical curve: PVI is halfway between PVC and PVT.
    pvcStation = pviStation - curveLength / 2.0;
    pviStationCalculated = pviStation;
    pvtStation = pviStation + curveLength / 2.0;

    // Tangent elevations at the curve endpoints.
    pvcElevation =
        pviElevation - grade1 * (curveLength / 2.0);

    pvtElevation =
        pviElevation + grade2 * (curveLength / 2.0);

    hasHighLowPoint = false;

    // A high or low point exists where the curve grade equals zero.
    if (fabs(algebraicGradeDifference) > 0.0000001)
    {
        highLowPointDistance =
            (-grade1 * curveLength) /
            algebraicGradeDifference;

        // The point must fall between the PVC and PVT.
        if (highLowPointDistance >= 0.0 &&
            highLowPointDistance <= curveLength)
        {
            hasHighLowPoint = true;

            highLowPointStation =
                pvcStation + highLowPointDistance;

            highLowPointElevation =
                pvcElevation
                + grade1 * highLowPointDistance
                + (algebraicGradeDifference
                    * highLowPointDistance
                    * highLowPointDistance)
                / (2.0 * curveLength);
        }
    }
}

void VerticalCurve::DisplayResults()
{
    cout << fixed << setprecision(3);

    cout << "\nVERTICAL CURVE RESULTS\n";
    cout << "----------------------\n";

    cout << "Incoming grade g1       : "
        << grade1Percent << " %\n";

    cout << "Outgoing grade g2       : "
        << grade2Percent << " %\n";

    cout << "Grade difference A      : "
        << grade2Percent - grade1Percent << " %\n";

    cout << "Curve length            : "
        << curveLength << " m\n";

    cout << "\nStations\n";
    cout << "PVC station             : "
        << pvcStation << " m\n";

    cout << "PVI station             : "
        << pviStationCalculated << " m\n";

    cout << "PVT station             : "
        << pvtStation << " m\n";

    cout << "\nElevations\n";
    cout << "PVC elevation           : "
        << pvcElevation << " m\n";

    cout << "PVI elevation           : "
        << pviElevation << " m\n";

    cout << "PVT elevation           : "
        << pvtElevation << " m\n";

    if (hasHighLowPoint)
    {
        cout << "\nHigh/Low Point\n";
        cout << "Distance from PVC       : "
            << highLowPointDistance << " m\n";

        cout << "Station                 : "
            << highLowPointStation << " m\n";

        cout << "Elevation               : "
            << highLowPointElevation << " m\n";

        if (algebraicGradeDifference < 0.0)
        {
            cout << "Point type              : High point\n";
        }
        else
        {
            cout << "Point type              : Low point\n";
        }
    }
    else
    {
        cout << "\nNo high or low point occurs "
            << "within the vertical curve.\n";
    }
}