// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include "circle.h"
#include "tasks.h"
#include <cmath>

const double EPS = 1e-6;
constexpr double PI = 3.14159265358979323846;

TEST(CircleTest, ct1) {
    Circle c;
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ct2) {
    Circle c(5.0);
    EXPECT_NEAR(c.getRadius(), 5.0, EPS);
    EXPECT_NEAR(c.getFerence(), 2 * PI * 5.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(CircleTest, ct3) {
    Circle c(2.0);
    c.setRadius(10.0);
    EXPECT_NEAR(c.getRadius(), 10.0, EPS);
    EXPECT_NEAR(c.getFerence(), 20.0 * PI, EPS);
    EXPECT_NEAR(c.getArea(), 100.0 * PI, EPS);
}

TEST(CircleTest, ct4) {
    Circle c(2.0);
    c.setFerence(20.0);
    double expected_r = 20.0 / (2.0 * PI);
    EXPECT_NEAR(c.getRadius(), expected_r, EPS);
    EXPECT_NEAR(c.getFerence(), 20.0, EPS);
    EXPECT_NEAR(c.getArea(), PI * expected_r * expected_r, EPS);
}

TEST(CircleTest, ct5) {
    Circle c(2.0);
    c.setArea(50.0);
    double expected_r = std::sqrt(50.0 / PI);
    EXPECT_NEAR(c.getRadius(), expected_r, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * expected_r, EPS);
    EXPECT_NEAR(c.getArea(), 50.0, EPS);
}

TEST(CircleTest, ct6) {
    Circle c;
    c.setRadius(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPS);
    EXPECT_NEAR(c.getFerence(), 0.0, EPS);
    EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, ct7) {
    double r = 100000.0;
    Circle c(r);
    EXPECT_NEAR(c.getRadius(), r, EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
    EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ct8) {
    Circle c(3.0);
    EXPECT_NEAR(c.getArea(), PI * std::pow(c.getRadius(), 2), EPS);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPS);
}

TEST(CircleTest, ct9) {
    Circle c;
    c.setFerence(100.0);
    double r = c.getRadius();
    EXPECT_NEAR(c.getArea(), PI * r * r, EPS);
}

TEST(CircleTest, ct10) {
    Circle c;
    c.setArea(200.0);
    double r = c.getRadius();
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPS);
}

TEST(CircleTest, ct11) {
    Circle c(1.0);
    c.setRadius(2.0);
    c.setArea(c.getArea() * 4.0); // Должно вернуться к r=4.0
    EXPECT_NEAR(c.getRadius(), 4.0, EPS);
}

TEST(CircleTest, ct12) {
    Circle c(1.0);
    double r_from_f = c.getFerence() / (2.0 * PI);
    EXPECT_NEAR(c.getRadius(), r_from_f, 1e-10);
    double r_from_a = std::sqrt(c.getArea() / PI);
    EXPECT_NEAR(c.getRadius(), r_from_a, 1e-10);
}


TEST(TaskEarthRope, ethrope1) {
    double gap = solveEarthAndRope(6378.1, 1.0);
    EXPECT_NEAR(gap, 1.0 / (2.0 * PI), 1e-6);
}

TEST(TaskEarthRope, ethrope2) {
    double gap1 = solveEarthAndRope(1000.0, 1.0);
    double gap2 = solveEarthAndRope(6378.1, 1.0);
    EXPECT_NEAR(gap1, gap2, 1e-6);
}

TEST(TaskEarthRope, ethrope3) {
    double gap = solveEarthAndRope(6378.1, 2.0);
    EXPECT_NEAR(gap, 2.0 / (2.0 * PI), 1e-6);
}

TEST(TaskEarthRope, ethrope4) {
    double gap = solveEarthAndRope(6.3781, 1.0);
    EXPECT_NEAR(gap, 1.0 / (2.0 * PI), 1e-6);
}

TEST(TaskPool, p1) {
    double cost = solvePoolCost(3.0, 1.0, 1000.0, 2000.0);
    double outer_r = 4.0;
    double area_path = PI * (outer_r * outer_r - 3.0 * 3.0);
    double fence_len = 2.0 * PI * outer_r;
    double expected = area_path * 1000.0 + fence_len * 2000.0;
    EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p2) {
    double cost = solvePoolCost(3.0, 0.0, 1000.0, 2000.0);
    double expected = (2.0 * PI * 3.0) * 2000.0;
    EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p3) {
    double cost = solvePoolCost(5.0, 2.0, 500.0, 1500.0);
    double outer_r = 7.0;
    double area_path = PI * (outer_r * outer_r - 25.0);
    double expected = area_path * 500.0 + (2.0 * PI * outer_r) * 1500.0;
    EXPECT_NEAR(cost, expected, 0.1);
}

TEST(TaskPool, p4) {
    double cost1 = solvePoolCost(2.0, 1.0, 1.0, 1.0);
    double cost2 = solvePoolCost(4.0, 2.0, 1.0, 1.0);
    EXPECT_GT(cost2, cost1 * 2.0);
}

TEST(TaskPool, p5) {
    double cost = solvePoolCost(1.0, 1.0, 1.0, 1.0);
    double expected = PI * (4 - 1) * 1.0 + 2.0 * PI * 2.0 * 1.0; // 3π + 4π = 7π
    EXPECT_NEAR(cost, 7.0 * PI, 0.1);
}
