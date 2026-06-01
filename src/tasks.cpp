// Copyright 2022 UNN-CS

#include "tasks.h"

#include "circle.h"

double solveEarthAndRope() {
  constexpr double earth_radius_km = 6378.1;
  constexpr double added_length_m = 1.0;

  double earth_radius_m = earth_radius_km * 1000.0;

  Circle earth(earth_radius_m);

  Circle new_rope;
  new_rope.setFerence(earth.getFerence() + added_length_m);

  return new_rope.getRadius() - earth.getRadius();
}

double solvePoolCost() {
  constexpr double pool_radius_m = 3.0;
  constexpr double path_width_m = 1.0;
  constexpr double concrete_price_per_m2 = 1000.0;
  constexpr double fence_price_per_m = 2000.0;

  Circle pool(pool_radius_m);

  Circle outer(pool_radius_m + path_width_m);

  double concrete_area = outer.getArea() - pool.getArea();
  double concrete_cost = concrete_area * concrete_price_per_m2;

  double fence_length = outer.getFerence();
  double fence_cost = fence_length * fence_price_per_m;

  return concrete_cost + fence_cost;
}
