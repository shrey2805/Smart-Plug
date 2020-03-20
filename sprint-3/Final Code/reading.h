#include "application.h"
#include "Particle.h"

const int analogInPin = A3;

// Number of samples to average the reading over
// Change this to make the reading smoother... but beware of buffer overflows!
const int avgSamples = 10;

int reading();
