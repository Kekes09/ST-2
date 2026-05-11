// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_
#include <cstdint>

class Circle {
 private:
    double radius;
    double area;
    double ference;

 public:
    explicit Circle(double r);
    void setRadius(double r);
    void setFerence(double r);
    void setArea(double r);
    double getRadius() const;
    double getFerence() const;
    double getArea() const;
};

#endif  // INCLUDE_CIRCLE_H_
