#pragma once

#include "Types.h"
#include "Input.h"

using namespace System::Input;

struct Controller {
	Controller(const byte data) :
		A(testBit(data, 0)),
		B(testBit(data, 1)),
		Select(testBit(data, 2)),
		Start(testBit(data, 3)),
		Left(testBit(data, 4)),
		Right(testBit(data, 5)),
		Up(testBit(data, 6)),
		Down(testBit(data, 7)) {
	}

	Controller() :
		Controller(getControllerBits()) {
	}

	bool A, B, Start, Select, Up, Down, Left, Right;
};