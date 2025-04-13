// Copyright 2022 UNN-CS
#include "../include/circle.h"

Circle::Circle(double r) {
    applyRadius(r);
}

void Circle::applyRadius(double r) {
    radius = r;
    circ = 2.0 * MATH_PI * radius;
    surface = MATH_PI * radius * radius;
}

void Circle::applyCircum(double c) {
    circ = c;
    radius = c / (2.0 * MATH_PI);
    surface = MATH_PI * radius * radius;
}

void Circle::applySurface(double s) {
    surface = s;
    radius = std::sqrt(s / MATH_PI);
    circ = 2.0 * MATH_PI * radius;
}

double Circle::pullRadius() const {
    return radius;
}

double Circle::pullCircum() const {
    return circ;
}

double Circle::pullSurface() const {
    return surface;
}
