#include "Object.h"

AutoPilot::AutoPilot(Point p) {
    kernel.push(p);
}

Point AutoPilot::getPosition() {
    return kernel.front();
}

Point AutoPilot::fetchPosition() {
    Point temp = kernel.front();
    kernel.pop();
    return temp;
}

void AutoPilot::updateKernel(Point position) {
    kernel.push(position);
}

void AutoPilot::updateKernel(Kernel newKernel) {
    kernel = newKernel;
}

bool AutoPilot::emptyPosition() {
    return kernel.empty();
}

void AutoPilot::move() {
    kernel.pop();
}