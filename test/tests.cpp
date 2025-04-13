// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include "../include/circle.h"
#include "../include/tasks.h"

constexpr double EPSILON = 1e-6;

TEST(CircleTest, ConstructorAndGetRadius) {
    Circle c(5.0);
    EXPECT_NEAR(c.pullRadius(), 5.0, EPSILON);
}

TEST(CircleTest, GetCircAndSurface) {
    Circle c(2.0);
    double expectedCirc = 2.0 * 3.14159265358979323846 * 2.0;
    double expectedArea = 3.14159265358979323846 * 2.0 * 2.0;
    EXPECT_NEAR(c.pullCircum(), expectedCirc, EPSILON);
    EXPECT_NEAR(c.pullSurface(), expectedArea, EPSILON);
}

TEST(CircleTest, ApplyRadiusUpdatesValues) {
    Circle c(1.0);
    c.applyRadius(4.0);
    double expectedCirc = 2.0 * 3.14159265358979323846 * 4.0;
    double expectedArea = 3.14159265358979323846 * 4.0 * 4.0;
    EXPECT_NEAR(c.pullRadius(), 4.0, EPSILON);
    EXPECT_NEAR(c.pullCircum(), expectedCirc, EPSILON);
    EXPECT_NEAR(c.pullSurface(), expectedArea, EPSILON);
}

TEST(CircleTest, ApplyCircUpdatesValues) {
    Circle c(1.0);
    double newCirc = 15.707963;
    c.applyCircum(newCirc);
    double expectedRadius = newCirc / (2.0 * 3.14159265358979323846);
    double expectedArea = 3.14159265358979323846
        * expectedRadius * expectedRadius;
    EXPECT_NEAR(c.pullRadius(), expectedRadius, EPSILON);
    EXPECT_NEAR(c.pullCircum(), newCirc, EPSILON);
    EXPECT_NEAR(c.pullSurface(), expectedArea, EPSILON);
}

TEST(CircleTest, ApplySurfaceUpdatesValues) {
    Circle c(1.0);
    double newSurface = 50.265482;
    c.applySurface(newSurface);
    double expectedRadius = std::sqrt(newSurface / 3.14159265358979323846);
    double expectedCirc = 2.0 * 3.14159265358979323846 * expectedRadius;
    EXPECT_NEAR(c.pullRadius(), expectedRadius, EPSILON);
    EXPECT_NEAR(c.pullSurface(), newSurface, EPSILON);
    EXPECT_NEAR(c.pullCircum(), expectedCirc, EPSILON);
}

TEST(CircleTest, SequentialUpdates) {
    Circle c(3.0);
    c.applyRadius(6.0);
    double updatedCirc = c.pullCircum();
    c.applyCircum(updatedCirc);
    double updatedArea = c.pullSurface();
    c.applySurface(updatedArea);
    EXPECT_NEAR(c.pullRadius(), 6.0, EPSILON);
}

TEST(CircleTest, IdenticalCircles) {
    Circle c1(10.0);
    Circle c2(10.0);
    EXPECT_NEAR(c1.pullCircum(), c2.pullCircum(), EPSILON);
    EXPECT_NEAR(c1.pullSurface(), c2.pullSurface(), EPSILON);
}

TEST(CircleTest, ZeroRadius) {
    Circle c(0.0);
    EXPECT_NEAR(c.pullRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.pullCircum(), 0.0, EPSILON);
    EXPECT_NEAR(c.pullSurface(), 0.0, EPSILON);
}

TEST(CircleTest, NegativeRadius) {
    Circle c(-5.0);
    EXPECT_NEAR(c.pullRadius(), -5.0, EPSILON);
    double expectedCirc = 2.0 * 3.14159265358979323846 * (-5.0);
    double expectedArea = 3.14159265358979323846 * 25.0;
    EXPECT_NEAR(c.pullCircum(), expectedCirc, EPSILON);
    EXPECT_NEAR(c.pullSurface(), expectedArea, EPSILON);
}

TEST(CircleTest, NegativeCirc) {
    Circle c(5.0);
    double negCirc = -31.415926;
    c.applyCircum(negCirc);
    double expectedRadius = negCirc / (2.0 * 3.14159265358979323846);
    double expectedArea = 3.14159265358979323846
        * expectedRadius * expectedRadius;
    EXPECT_NEAR(c.pullRadius(), expectedRadius, EPSILON);
    EXPECT_NEAR(c.pullCircum(), negCirc, EPSILON);
    EXPECT_NEAR(c.pullSurface(), expectedArea, EPSILON);
}

TEST(TaskTest, RopeClearanceCalculation) {
    double gap = computeRopeClearance();
    double expectedGap = 1.0 / (2.0 * 3.14159265358979323846);
    EXPECT_NEAR(gap, expectedGap, 1e-5);
}

TEST(TaskTest, PoolConcreteCost) {
    double concreteCost = 0.0, fenceCost = 0.0;
    computePoolExpenses(concreteCost, fenceCost);
    double expectedConcrete = 7.0 * 3.14159265358979323846 * 1000.0;
    EXPECT_NEAR(concreteCost, expectedConcrete, 1e-2);
}

TEST(TaskTest, PoolFenceCost) {
    double concreteCost = 0.0, fenceCost = 0.0;
    computePoolExpenses(concreteCost, fenceCost);
    double expectedFence = 2.0 * 3.14159265358979323846 * 4.0 * 2000.0;
    EXPECT_NEAR(fenceCost, expectedFence, 1e-2);
}

TEST(CircleTest, MultipleSequentialUpdates) {
    Circle c(2.0);
    c.applyRadius(3.0);
    double f1 = c.pullCircum();
    c.applyCircum(f1 + 5.0);
    double r1 = c.pullRadius();
    c.applySurface(c.pullSurface() + 10.0);
    double r2 = c.pullRadius();
    EXPECT_FALSE(std::isnan(r1));
    EXPECT_FALSE(std::isnan(r2));
}

TEST(CircleTest, FloatPrecision) {
    Circle a(3.1415);
    Circle b(3.1415);
    EXPECT_NEAR(a.pullRadius(), b.pullRadius(), EPSILON);
    EXPECT_NEAR(a.pullCircum(), b.pullCircum(), EPSILON);
    EXPECT_NEAR(a.pullSurface(), b.pullSurface(), EPSILON);
}

TEST(CircleTest, LargeValueCheck) {
    Circle c(1e6);
    c.applyRadius(1e6);
    double expectedCirc = 2.0 * 3.14159265358979323846 * 1e6;
    EXPECT_NEAR(c.pullCircum(), expectedCirc, 1e-2);
}

TEST(CircleTest, SequentialCircAndArea) {
    Circle c(10.0);
    c.applyCircum(20.0);
    double rAfterCirc = c.pullRadius();
    c.applySurface(314.159265);
    double rAfterArea = c.pullRadius();
    EXPECT_FALSE(std::isnan(rAfterCirc));
    EXPECT_FALSE(std::isnan(rAfterArea));
}

TEST(CircleTest, SetAreaCorrectness) {
    Circle c(0.5);
    double newSurface = 100.0;
    c.applySurface(newSurface);
    double expectedRadius = std::sqrt(newSurface / 3.14159265358979323846);
    EXPECT_NEAR(c.pullRadius(), expectedRadius, EPSILON);
}

TEST(CircleTest, SetCircumferenceCorrectness) {
    Circle c(4.0);
    double newCirc = 2.0 * 3.14159265358979323846 * 4.0 + 0.123456;
    c.applyCircum(newCirc);
    double expectedRadius = newCirc / (2.0 * 3.14159265358979323846);
    EXPECT_NEAR(c.pullRadius(), expectedRadius, 1e-5);
}

TEST(TaskTest, PoolExpensesNonNegative) {
    double concreteCost = 0.0, fenceCost = 0.0;
    computePoolExpenses(concreteCost, fenceCost);
    EXPECT_GE(concreteCost, 0.0);
    EXPECT_GE(fenceCost, 0.0);
}
