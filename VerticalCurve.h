#pragma once
#pragma once
#pragma once

class VerticalCurve
{
public:
    VerticalCurve();
    void Run();

private:
    void GetInput();
    void Calculate();
    void DisplayResults();

    // Inputs
    double grade1Percent;
    double grade2Percent;
    double curveLength;
    double pviStation;
    double pviElevation;

    // Grades stored as decimals
    double grade1;
    double grade2;
    double algebraicGradeDifference;

    // Results
    double pvcStation;
    double pviStationCalculated;
    double pvtStation;

    double pvcElevation;
    double pvtElevation;

    double highLowPointDistance;
    double highLowPointStation;
    double highLowPointElevation;

    bool hasHighLowPoint;
};