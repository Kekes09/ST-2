#include "tasks.h"
#include "circle.h"

double solveEarthAndRope(double earth_radius_km, double added_length_m) {
    double earth_radius_m = earth_radius_km * 1000.0;
    
    Circle earth(earth_radius_m);
    Circle rope;
    
    rope.setFerence(earth.getFerence() + added_length_m);
    
    return rope.getRadius() - earth.getRadius();
}

double solvePoolCost(double pool_radius_m, double path_width_m, 
                     double concrete_price, double fence_price) {
    Circle pool(pool_radius_m);
    Circle outer(pool_radius_m + path_width_m);
    
    double concrete_area = outer.getArea() - pool.getArea();
    double concrete_cost = concrete_area * concrete_price;
    
    double fence_length = outer.getFerence();
    double fence_cost   = fence_length * fence_price;
    
    return concrete_cost + fence_cost;
}