#pragma once
#include <iostream>
#include <fstream>

class Date
{
private:
    int day, month, year;

public:
    Date(int d = 1, int m = 1, int y = 1970) noexcept(false);

    void setDay(int d) noexcept(false);
    void setMonth(int m) noexcept(false);
    void setYear(int y) noexcept(true);

    void show() const;
};