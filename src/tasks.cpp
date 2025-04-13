// Copyright 2022 UNN-CS
#include "../include/tasks.h"
#include "../include/circle.h"

double computeRopeClearance() {
    double earthRadiusM = 6378.1 * 1000.0;

    Circle earth(earthRadiusM);
    double oldCirc = earth.pullCircum();

    double newCirc = oldCirc + 1.0;

    Circle expandedEarth(earthRadiusM);
    expandedEarth.applyCircum(newCirc);

    double clearance = expandedEarth.pullRadius() - earth.pullRadius();
    return clearance;
}

void computePoolExpenses(double& cCost, double& fCost) {
    double poolRad = 3.0;
    double walkwayW = 1.0;

    Circle basePool(poolRad);

    Circle extendedPool(poolRad + walkwayW);

    double ringArea = extendedPool.pullSurface() - basePool.pullSurface();
    cCost = ringArea * 1000.0;

    double fencePerimeter = extendedPool.pullCircum();
    fCost = fencePerimeter * 2000.0;
}
