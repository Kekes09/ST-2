// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include "circle.h"
#include "tasks.h"

#include <cmath>


const double EPS = 1e-5;
constexpr double PI = 3.14159265358979323846;

TEST(CircleTest, ct1) {
  Circle c;
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ct2) {
  Circle c(7.5);
  EXPECT_NEAR(c.getRadius(), 7.5, EPS);
  EXPECT_NEAR(c.getFerence(), 2 * PI * 7.5, EPS);
  EXPECT_NEAR(c.getArea(), PI * 56.25, EPS);
}

TEST(CircleTest, ct3) {
  Circle c(3.5);
  c.setRadius(15.0);
  EXPECT_NEAR(c.getRadius(), 15.0, EPS);
  EXPECT_NEAR(c.getFerence(), 30.0 * PI, EPS);
  EXPECT_NEAR(c.getArea(), 225.0 * PI, EPS);
}

TEST(CircleTest, ct4) {
  Circle c(4.0);
  c.setFerence(50.0);
  double expected_r = 50.0 / (2.0 * PI);
  EXPECT_NEAR(c.getRadius(), expected_r, EPS);
  EXPECT_NEAR(c.getFerence(), 50.0, EPS);
  EXPECT_NEAR(c.getArea(), PI * expected_r * expected_r, EPS);
}

TEST(CircleTest, ct5) {
  Circle c(1.5);
  c.setArea(75.0);
  double expected_r = std::sqrt(75.0 / PI);
  EXPECT_NEAR(c.getRadius(), expected_r, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * expected_r, EPS);
  EXPECT_NEAR(c.getArea(), 75.0, EPS);
}

TEST(CircleTest, ct6) {
  Circle c;
  c.setRadius(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ct7) {
  double r = 50000.0;
  Circle c(r);
  EXPECT_NEAR(c.getRadius(), r, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
  EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ct8) {
  Circle c(6.0);
  EXPECT_NEAR(c.getArea(), PI * std::pow(c.getRadius(), 2), EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPS);
}

TEST(CircleTest, ct9) {
  Circle c;
  c.setFerence(150.0);
  double r = c.getRadius();
  EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ct10) {
  Circle c;
  c.setArea(300.0);
  double r = c.getRadius();
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
}

TEST(CircleTest, ct11) {
  Circle c(2.5);
  c.setRadius(5.0);
  c.setArea(c.getArea() * 4.0);
  EXPECT_NEAR(c.getRadius(), 10.0, EPS);
}

TEST(CircleTest, ct12) {
  Circle c(3.0);
  double r_from_f = c.getFerence() / (2.0 * PI);
  EXPECT_NEAR(c.getRadius(), r_from_f, 1e-9);
  double r_from_a = std::sqrt(c.getArea() / PI);
  EXPECT_NEAR(c.getRadius(), r_from_a, 1e-9);
}


TEST(TaskEarthRope, ethrope1) {
  double gap = solveEarthAndRope(6400.0, 1.5);
  EXPECT_NEAR(gap, 1.5 / (2.0 * PI), 1e-5);
}

TEST(TaskEarthRope, ethrope2) {
  double gap1 = solveEarthAndRope(1200.0, 1.5);
  double gap2 = solveEarthAndRope(6400.0, 1.5);
  EXPECT_NEAR(gap1, gap2, 1e-5);
}

TEST(TaskEarthRope, ethrope3) {
  double gap = solveEarthAndRope(6400.0, 3.0);
  EXPECT_NEAR(gap, 3.0 / (2.0 * PI), 1e-5);
}

TEST(TaskEarthRope, ethrope4) {
  double gap = solveEarthAndRope(6.4, 1.5);
  EXPECT_NEAR(gap, 1.5 / (2.0 * PI), 1e-5);
}

TEST(TaskPool, p1) {
  double cost = solvePoolCost(4.0, 1.5, 1200.0, 2500.0);
  double outer_r = 5.5;
  double area_path = PI * (outer_r * outer_r - 4.0 * 4.0);
  double fence_len = 2.0 * PI * outer_r;
  double expected = area_path * 1200.0 + fence_len * 2500.0;
  EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p2) {
  double cost = solvePoolCost(4.0, 0.0, 1200.0, 2500.0);
  double expected = (2.0 * PI * 4.0) * 2500.0;
  EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p3) {
  double cost = solvePoolCost(6.0, 2.5, 600.0, 1800.0);
  double outer_r = 8.5;
  double area_path = PI * (outer_r * outer_r - 36.0);
  double expected = area_path * 600.0 + (2.0 * PI * outer_r) * 1800.0;
  EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p4) {
  double cost1 = solvePoolCost(3.0, 1.5, 1.0, 1.0);
  double cost2 = solvePoolCost(6.0, 3.0, 1.0, 1.0);
  EXPECT_GT(cost2, cost1 * 2.0);
}

TEST(TaskPool, p5) {
  double cost = solvePoolCost(2.0, 1.5, 1.0, 1.0);
  double expected = PI * (12.25 - 4.0) * 1.0 + 2.0 * PI * 3.5 * 1.0;
  EXPECT_NEAR(cost, 15.25 * PI, 0.1);
}
