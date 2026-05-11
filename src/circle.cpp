// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cstdint>
#include <cmath>
#include "circle.h"

Circle::Circle(double r) {
    setRadius(r);
}

void Circle::setRadius(double r) {
    radius = r;
    ference = 2 * M_PI * r;
    area = M_PI * radius * radius;
}

void Circle::setFerence(double r) {
    ference = r;
    radius = ference/(M_PI*2);
    area = (ference*ference)/(4*M_PI);
}

void Circle::setArea(double r) {
    area = r;
    radius = std::sqrt(area/M_PI);
    ference = 2 * M_PI * radius;
}

double Circle::getArea() const {
    return area;
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}
