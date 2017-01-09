#ifndef CLOCK_H
#define CLOCK_H


class Clock
{
public:
    Clock();

    GetElapsedTime() const;

    restart();

private:
    double fStartTime;
};

#endif // CLOCK_H
