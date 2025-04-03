// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cstdint>
#include "circle.h"


#include <iostream>
#include <cassert>
#include <cmath>
#include "circle.h"
#include "tasks.h"

const double PI = 3.141592653589793;
const double EPSILON = 1e-6;

void testCircleSetRadius() {
    Circle c(1.0);
    c.setRadius(2.0);
    assert(std::abs(c.getRadius() - 2.0) < EPSILON);
    assert(std::abs(c.getFerence() - (2 * PI * 2.0)) < EPSILON);
    assert(std::abs(c.getArea() - (PI * 4.0)) < EPSILON);
}

void testCircleSetFerence() {
    Circle c(1.0);
    double newFerence = 10.0;
    c.setFerence(newFerence);
    double expectedRadius = newFerence / (2 * PI);
    double expectedArea = PI * expectedRadius * expectedRadius;
    assert(std::abs(c.getRadius() - expectedRadius) < EPSILON);
    assert(std::abs(c.getFerence() - newFerence) < EPSILON);
    assert(std::abs(c.getArea() - expectedArea) < EPSILON);
}

void testCircleSetArea() {
    Circle c(1.0);
    double newArea = 50.0;
    c.setArea(newArea);
    double expectedRadius = std::sqrt(newArea / PI);
    double expectedFerence = 2 * PI * expectedRadius;
    assert(std::abs(c.getRadius() - expectedRadius) < EPSILON);
    assert(std::abs(c.getFerence() - expectedFerence) < EPSILON);
    assert(std::abs(c.getArea() - newArea) < EPSILON);
}

void testConstructor() {
    Circle c(3.0);
    assert(std::abs(c.getRadius() - 3.0) < EPSILON);
    assert(std::abs(c.getFerence() - (2 * PI * 3.0)) < EPSILON);
    assert(std::abs(c.getArea() - (PI * 9.0)) < EPSILON);
}

void testEarthAndRopeGap() {
    double earthRadiusKm = 6378.1;
    double extraLengthMeter = 1.0;
    double gap = earthAndRopeGap(earthRadiusKm, extraLengthMeter);
    double expectedGap = (extraLengthMeter / 1000.0) / (2 * PI);
    assert(std::abs(gap - expectedGap) < EPSILON);
}

void testPoolCostsConcreteArea() {
    double poolRadius = 3.0;
    double roadWidth = 1.0;
    double costPerSquareMeterConcrete = 1000.0;
    double costPerMeterFence = 2000.0;
    double concreteCost, fenceCost;
    poolCosts(poolRadius, roadWidth, costPerSquareMeterConcrete, costPerMeterFence, concreteCost, fenceCost);

    Circle inner(poolRadius);
    Circle outer(poolRadius + roadWidth);
    double expectedConcreteCost = (outer.getArea() - inner.getArea()) * costPerSquareMeterConcrete;
    assert(std::abs(concreteCost - expectedConcreteCost) < EPSILON);
}

void testPoolCostsFenceCost() {
    double poolRadius = 3.0;
    double roadWidth = 1.0;
    double costPerSquareMeterConcrete = 1000.0;
    double costPerMeterFence = 2000.0;
    double concreteCost, fenceCost;
    poolCosts(poolRadius, roadWidth, costPerSquareMeterConcrete, costPerMeterFence, concreteCost, fenceCost);

    Circle outer(poolRadius + roadWidth);
    double expectedFenceCost = outer.getFerence() * costPerMeterFence;
    assert(std::abs(fenceCost - expectedFenceCost) < EPSILON);
}

void testCircleMultipleUpdates() {
    Circle c(5.0);
    c.setFerence(2 * PI * 10.0); 
    assert(std::abs(c.getRadius() - 10.0) < EPSILON);
    c.setArea(PI * 16.0); 
    assert(std::abs(c.getRadius() - 4.0) < EPSILON);
}

void testNegativeRadius() {

    Circle c(1.0);
    c.setRadius(-5.0);
    assert(std::abs(c.getRadius() + 5.0) < EPSILON);
}

void testZeroValues() {
    Circle c(0.0);
    assert(std::abs(c.getRadius() - 0.0) < EPSILON);
    assert(std::abs(c.getFerence() - 0.0) < EPSILON);
    assert(std::abs(c.getArea() - 0.0) < EPSILON);
}

void testCirclePrecision() {
    Circle c(1.2345);
    double r = c.getRadius();
    double f = c.getFerence();
    double a = c.getArea();
    assert(std::abs(r - 1.2345) < EPSILON);
    assert(std::abs(f - (2 * PI * 1.2345)) < EPSILON);
    assert(std::abs(a - (PI * 1.2345 * 1.2345)) < EPSILON);
}

void testPoolCostsDifferentParameters() {
    double poolRadius = 4.0;
    double roadWidth = 2.0;
    double costPerSquareMeterConcrete = 1200.0;
    double costPerMeterFence = 2500.0;
    double concreteCost, fenceCost;
    poolCosts(poolRadius, roadWidth, costPerSquareMeterConcrete, costPerMeterFence, concreteCost, fenceCost);

    Circle inner(poolRadius);
    Circle outer(poolRadius + roadWidth);
    double expectedConcreteCost = (outer.getArea() - inner.getArea()) * costPerSquareMeterConcrete;
    double expectedFenceCost = outer.getFerence() * costPerMeterFence;
    assert(std::abs(concreteCost - expectedConcreteCost) < EPSILON);
    assert(std::abs(fenceCost - expectedFenceCost) < EPSILON);
}

void testCircleSetAndGetConsistency() {
    Circle c(10.0);
    c.setRadius(15.0);
    double r = c.getRadius();
    c.setFerence(c.getFerence());
    assert(std::abs(c.getRadius() - r) < EPSILON);
}

void testTaskEdgeCase() {

    double gap = earthAndRopeGap(100.0, 0.0);
    assert(std::abs(gap - 0.0) < EPSILON);
}

void testPoolCostsZeroRoadWidth() {
    double poolRadius = 3.0;
    double roadWidth = 0.0;
    double costPerSquareMeterConcrete = 1000.0;
    double costPerMeterFence = 2000.0;
    double concreteCost, fenceCost;
    poolCosts(poolRadius, roadWidth, costPerSquareMeterConcrete, costPerMeterFence, concreteCost, fenceCost);

    Circle pool(poolRadius);
    assert(std::abs(concreteCost - 0.0) < EPSILON);
    assert(std::abs(fenceCost - (pool.getFerence() * costPerMeterFence)) < EPSILON);
}

void testAdditionalConsistency() {

    Circle c(2.0);
    c.setRadius(5.0);
    double r1 = c.getRadius();
    c.setFerence(c.getFerence());
    double r2 = c.getRadius();
    c.setArea(c.getArea());
    double r3 = c.getRadius();
    assert(std::abs(r1 - r2) < EPSILON);
    assert(std::abs(r2 - r3) < EPSILON);
}

void testSmallPoolParameters() {

    double poolRadius = 1.0;
    double roadWidth = 0.5;
    double costPerSquareMeterConcrete = 800.0;
    double costPerMeterFence = 1500.0;
    double concreteCost, fenceCost;
    poolCosts(poolRadius, roadWidth, costPerSquareMeterConcrete, costPerMeterFence, concreteCost, fenceCost);
    Circle inner(poolRadius);
    Circle outer(poolRadius + roadWidth);
    assert(std::abs(concreteCost - ((outer.getArea() - inner.getArea()) * costPerSquareMeterConcrete)) < EPSILON);
    assert(std::abs(fenceCost - (outer.getFerence() * costPerMeterFence)) < EPSILON);
}

void testLargeExtraLength() {

    double gap = earthAndRopeGap(5000.0, 100.0);
    double expectedGap = (100.0 / 1000.0) / (2 * PI);
    assert(std::abs(gap - expectedGap) < EPSILON);
}

void testExtremeValues() {

    Circle c2(1e6);
    c2.setRadius(1e7);
    assert(c2.getRadius() == 1e7);

    Circle c3(1e-6);
    c3.setRadius(1e-7);
    assert(c3.getRadius() == 1e-7);
}

void runTests() {
    testCircleSetRadius();
    testCircleSetFerence();
    testCircleSetArea();
    testConstructor();
    testEarthAndRopeGap();
    testPoolCostsConcreteArea();
    testPoolCostsFenceCost();
    testCircleMultipleUpdates();
    testNegativeRadius();
    testZeroValues();
    testCirclePrecision();
    testPoolCostsDifferentParameters();
    testCircleSetAndGetConsistency();
    testTaskEdgeCase();
    testPoolCostsZeroRoadWidth();
    testAdditionalConsistency();
    testSmallPoolParameters();
    testLargeExtraLength();
    testExtremeValues();

    std::cout << "Все тесты успешно пройдены." << std::endl;
}

