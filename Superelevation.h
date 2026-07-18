#pragma once


class Superelevation
{
public:

    Superelevation();

    void Run();

private:

    void GetInput();

    void Calculate();

    void DisplayResults();

    double speed;
    double radius;
    double friction;

    double superelevation;
    double superelevationPercent;
};
