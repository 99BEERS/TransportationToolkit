#include "Superelevation.h"
#include <iostream>

#include "Constants.h"
#include <cmath>
#include <iomanip>

using namespace std;

Superelevation::Superelevation()
{
    speed = 0.0;
    radius = 0.0;
    friction = 0.0;

    superelevation = 0.0;
    superelevationPercent = 0.0;
}

void Superelevation::Run()
{
    cout << "\nSUPERELEVATION CALCULATOR\n";
    cout << "-------------------------\n";

    cout << "Design Speed (km/h): ";
    cin >> speed;

    cout << "Radius (m): ";
    cin >> radius;

    cout << "Side Friction Factor: ";
    cin >> friction;


    superelevation =
        (speed * speed) /
        (127.0 * radius)
        - friction;

    superelevationPercent =
        superelevation * 100.0;

        cout << fixed << setprecision(3);

        cout << "\nRESULTS\n";
        cout << "-------------------------\n";

        cout << "Speed               : "
            << speed << " km/h\n";

        cout << "Radius              : "
            << radius << " m\n";

        cout << "Friction            : "
            << friction << endl;

        cout << "Superelevation      : "
            << superelevation << endl;

        cout << "Superelevation (%)  : "
            << superelevationPercent
            << " %\n";
    }
