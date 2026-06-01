// Copyright 2022 UNN-CS
#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
private:
    double radius_;
    double ference_;
    double area_;

    static constexpr double PI = 3.14159265358979323846;

    void recalcFromRadius();
    void recalcFromFerence();
    void recalcFromArea();

public:
    explicit Circle(double radius = 0.0);

    void setRadius(double radius);
    void setFerence(double ference);
    void setArea(double area);

    double getRadius() const;
    double getFerence() const;
    double getArea() const;
};

#endif // CIRCLE_H
