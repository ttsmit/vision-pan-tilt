#pragma once
#include "xxtypes.h"

void home_motors(void);
void updateControl(XXDouble* u, XXDouble* y, XXDouble t);
void getPositions(XXDouble* u);