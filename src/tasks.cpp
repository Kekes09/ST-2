// Copyright 2022 UNN-CS
#include "tasks.h"
#include <cmath>
#include "circle.h"

double Rope() {
    double earth = 6378100.0;
    Circle rope(earth);
    double nFerence = rope.getFerence() + 1.0;
    rope.setFerence(nFerence);
    return rope.getRadius() - earth;
}

double Pool() {
    double rPool = 3.0;
    double rRoad = 1.0;

    Circle pool(rPool);
    Circle road(rPool + rRoad);

    double priceOgrada = road.getFerence() * 2000.0;
    double priceDoroga = (road.getArea() - pool.getArea()) * 1000.0;
    return priceOgrada + priceDoroga;
}
