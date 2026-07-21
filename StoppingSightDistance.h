#pragma once

class StoppingSightDistance
{
public:

    StoppingSightDistance();

    void Run();

private:

    bool GetInput();

    bool Calculate();

    void DisplayResults();

    double speed;

    double reactionTime;

    double friction;

    double gradePercent;

    double grade;

    double reactionDistance;

    double brakingDistance;

    double stoppingSightDistance;
};
