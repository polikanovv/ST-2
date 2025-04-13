// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

#include <cstdint>
#include <cmath>

class Circle {

private:
    double radius;
    double circ;
    double surface;
    static constexpr double MATH_PI = 3.14159265358979323846;

public:
    explicit Circle(double r);

    void applyRadius(double r);
    void applyCircum(double c);
    void applySurface(double s);

    double pullRadius() const;
    double pullCircum() const;
    double pullSurface() const;
};

#endif // INCLUDE_CIRCLE_H_
