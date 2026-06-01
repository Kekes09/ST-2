// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>

#include "circle.h"
#include "tasks.h"

constexpr double EPS = 1e-5;
constexpr double PI = 3.14159265358979323846;

TEST(CircleTest, DefaultConstructor) {
  Circle c;
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ConstructorWithRadius) {
  Circle c(7.5);
  EXPECT_NEAR(c.getRadius(), 7.5, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 7.5, EPS);
  EXPECT_NEAR(c.getArea(), PI * 7.5 * 7.5, EPS);
}

TEST(CircleTest, SetRadiusRecalculates) {
  Circle c(2.0);
  c.setRadius(12.0);
  EXPECT_NEAR(c.getRadius(), 12.0, EPS);
  EXPECT_NEAR(c.getFerence(), 24.0 * PI, EPS);
  EXPECT_NEAR(c.getArea(), 144.0 * PI, EPS);
}

TEST(CircleTest, SetFerenceRecalculates) {
  Circle c(3.0);
  c.setFerence(40.0);
  double expected_r = 40.0 / (2.0 * PI);
  EXPECT_NEAR(c.getRadius(), expected_r, EPS);
  EXPECT_NEAR(c.getFerence(), 40.0, EPS);
  EXPECT_NEAR(c.getArea(), PI * expected_r * expected_r, EPS);
}

TEST(CircleTest, SetAreaRecalculates) {
  Circle c(2.0);
  c.setArea(80.0);
  double expected_r = std::sqrt(80.0 / PI);
  EXPECT_NEAR(c.getRadius(), expected_r, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * expected_r, EPS);
  EXPECT_NEAR(c.getArea(), 80.0, EPS);
}

TEST(CircleTest, ZeroValues) {
  Circle c;
  c.setRadius(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, LargeRadius) {
  double r = 75000.0;
  Circle c(r);
  EXPECT_NEAR(c.getRadius(), r, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
  EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ConsistencyRadiusToOthers) {
  Circle c(5.0);
  EXPECT_NEAR(c.getArea(), PI * c.getRadius() * c.getRadius(), EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPS);
}

TEST(CircleTest, ConsistencyFerenceToOthers) {
  Circle c;
  c.setFerence(120.0);
  double r = c.getRadius();
  EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ConsistencyAreaToOthers) {
  Circle c;
  c.setArea(250.0);
  double r = c.getRadius();
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
}

TEST(CircleTest, ChainUpdates) {
  Circle c(1.5);
  c.setRadius(3.0);
  c.setArea(c.getArea() * 4.0);
  EXPECT_NEAR(c.getRadius(), 6.0, EPS);
}

TEST(CircleTest, PrecisionCheck) {
  Circle c(4.0);
  double r_from_f = c.getFerence() / (2.0 * PI);
  EXPECT_NEAR(c.getRadius(), r_from_f, 1e-9);
  double r_from_a = std::sqrt(c.getArea() / PI);
  EXPECT_NEAR(c.getRadius(), r_from_a, 1e-9);
}


TEST(TaskEarthRope, ResultIsPositive) {
  EXPECT_GT(solveEarthAndRope(), 0.0);
}

TEST(TaskEarthRope, ExpectedValue) {
  EXPECT_NEAR(solveEarthAndRope(), 1.0 / (2.0 * PI), EPS);
}

TEST(TaskEarthRope, LessThanOneMeter) {
  EXPECT_LT(solveEarthAndRope(), 1.0);
}

TEST(TaskEarthRope, PrecisionStable) {
  double r1 = solveEarthAndRope();
  double r2 = solveEarthAndRope();
  EXPECT_DOUBLE_EQ(r1, r2);
}

TEST(TaskPool, ResultIsPositive) {
  EXPECT_GT(solvePoolCost(), 0.0);
}

TEST(TaskPool, ExpectedValue) {
  EXPECT_NEAR(solvePoolCost(), 72256.6, 1.0);
}

TEST(TaskPool, MinimumReasonableCost) {
  EXPECT_GE(solvePoolCost(), 70000.0);
}

TEST(TaskPool, Deterministic) {
  double c1 = solvePoolCost();
  double c2 = solvePoolCost();
  EXPECT_DOUBLE_EQ(c1, c2);
}

TEST(TaskPool, ConcreteCostComponent) {
  constexpr double pool_r = 3.0;
  constexpr double path_w = 1.0;
  constexpr double concrete_price = 1000.0;
  Circle pool(pool_r);
  Circle outer(pool_r + path_w);
  double expected_concrete =
   (outer.getArea() - pool.getArea()) * concrete_price;
  EXPECT_NEAR(expected_concrete, 21991.0, 1.0);
}

TEST(TaskPool, FenceCostComponent) {
  constexpr double outer_r = 4.0;
  constexpr double fence_price = 2000.0;
  Circle outer(outer_r);
  double expected_fence = outer.getFerence() * fence_price;
  EXPECT_NEAR(expected_fence, 50265.0, 1.0);
}
