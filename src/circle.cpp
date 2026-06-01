// Copyright 2022 UNN-CS
#include <cstdint>
#include "circle.h"
#include <cmath>

Circle::Circle(double radius) : radius_(0.0), ference_(0.0), area_(0.0) {
    setRadius(radius);
}

void Circle::recalcFromRadius() {
    ference_ = 2.0 * PI * radius_;
    area_    = PI * radius_ * radius_;
}

void Circle::recalcFromFerence() {
    radius_ = ference_ / (2.0 * PI);
    area_   = PI * radius_ * radius_;
}

void Circle::recalcFromArea() {
    radius_ = std::sqrt(area_ / PI);
    ference_= 2.0 * PI * radius_;
}

void Circle::setRadius(double radius) {
    radius_ = radius;
    recalcFromRadius();
}

void Circle::setFerence(double ference) {
    ference_ = ference;
    recalcFromFerence();
}

void Circle::setArea(double area) {
    area_ = area;
    recalcFromArea();
}

double Circle::getRadius() const { return radius_; }
double Circle::getFerence() const { return ference_; }
double Circle::getArea() const { return area_; }
