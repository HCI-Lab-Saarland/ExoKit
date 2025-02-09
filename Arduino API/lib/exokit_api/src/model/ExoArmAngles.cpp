#include "ExoArmAngles.h"

void ExoArmAngles::delShoulderSideAngle() {
    hasShoulderSide = false;
}

void ExoArmAngles::delShoulderBackAngle() {
    hasShoulderBack = false;
}

void ExoArmAngles::delElbowAngle() {
    hasElbow = false;
}

void ExoArmAngles::setElbowAngle(float angle) {
    hasElbow = true;
    elbowAngle = angle;
}

void ExoArmAngles::setShoulderBackAngle(float angle) {
    hasShoulderBack = true;
    shoulderBackAngle = angle;
}

void ExoArmAngles::setShoulderSideAngle(float angle) {
    hasShoulderSide = true;
    shoulderSideAngle = angle;
}

float ExoArmAngles::getElbowAngle() {
    return elbowAngle;
}

float ExoArmAngles::getShoulderBackAngle() {
    return shoulderBackAngle;
}

float ExoArmAngles::getShoulderSideAngle() {
    return shoulderSideAngle;
}

bool ExoArmAngles::isHasShoulderBack() {
    return hasShoulderBack;
}

bool ExoArmAngles::isHasShoulderSide() {
    return hasShoulderSide;
}

bool ExoArmAngles::isHasElbow() {
    return hasElbow;
}




