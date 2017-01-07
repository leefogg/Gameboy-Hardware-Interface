#include "system.h"
#include "LCD.h"

void System::enableScanlineInterrput() {
	System::Output::LCD::Stats |= BIT6;
}
void System::enableOAMInterrupt() {
	System::Output::LCD::Stats |= BIT5;
}
void System::enableVblankInterrput() {
	System::Output::LCD::Stats |= BIT4;
}
void System::enableHblankInterrput() {
	System::Output::LCD::Stats |= BIT3;
}