#include "StoppingSightDistance.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;


StoppingSightDistance::StoppingSightDistance()
{
    speed = 0.0;

    reactionTime = 2.5;

    friction = 0.35;

    gradePercent = 0.0;

    grade = 0.0;

    reactionDistance = 0.0;

    brakingDistance = 0.0;

    stoppingSightDistance = 0.0;
}

void StoppingSightDistance::Run()
{
    if (!GetInput() || !Calculate())
    {
        return;
    }

    DisplayResults();
}

bool StoppingSightDistance::GetInput()
{
    cout << "\nSTOPPING SIGHT DISTANCE\n";
    cout << "------------------------\n";

    cout << "Design Speed (km/h): ";
    cin >> speed;

    cout << "Reaction Time (s): ";
    cin >> reactionTime;

    cout << "Coefficient of Friction: ";
    cin >> friction;

    cout << "Road Grade (%): ";
    cin >> gradePercent;

    if (!cin || speed < 0.0 || reactionTime < 0.0 || friction < 0.0)
    {
        cout << "\nInvalid input. Enter non-negative numeric values.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool StoppingSightDistance::Calculate()
{
    grade = gradePercent / 100.0;

    const double brakingFactor = friction + grade;
    if (brakingFactor <= 0.0)
    {
        cout << "\nCannot calculate: friction plus grade must be greater than zero.\n";
        return false;
    }

    reactionDistance =
        0.278 * speed * reactionTime;

    brakingDistance =
        (speed * speed)
        /
        (254.0 * brakingFactor);

    stoppingSightDistance =
        reactionDistance +
        brakingDistance;

    return true;
}

void StoppingSightDistance::DisplayResults()
{
    cout << fixed << setprecision(2);

    cout << "\nRESULTS\n";
    cout << "-------------------------\n";

    cout << "Reaction Distance : "
         << reactionDistance << " m\n";

    cout << "Braking Distance  : "
         << brakingDistance << " m\n";

    cout << "Stopping Distance : "
         << stoppingSightDistance
         << " m\n";
}
