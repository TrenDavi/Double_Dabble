// Double_Dabble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <assert.h>

#define BINARY_WIDTH 16

void displayBCD(uint32_t bcd) {
	for (int i = 19; i >= 0; i--) {
		std::cout << ((bcd >> i) & 1);
		if (((i % 4) == 0) && i != 20) {
			std::cout << " ";
		}
	}
	std::cout << "\n";

	for (int i = 4; i >= 0; i--) {
		int nib = (bcd >> (i * 4)) & 15;

		std::cout << nib;
		if (i < 10) {
			std::cout << "    ";
		}
		else {
			std::cout << "   ";
		}
	}

	std::cout << "\n";
}

int main()
{
	assert(BINARY_WIDTH % 8 == 0);
	assert(BINARY_WIDTH != 0);

	uint16_t bn = 5461;			// Original Binary Number
	const uint16_t bnc = bn;	// Original Binary Number Const
	uint32_t bcd = 0;			// Bianry Coded Decimal


	for (int i = 0; i < 15; i++) {
		bcd = bcd << 1;
		if (bn & 32768)
			bcd += 1;
		bn = bn << 1;

		// Find all nibbles > 4
		for (int j = 0; j < 5; j++) {
			int mask = 15 << (j*4);
			int mask_val = (bcd & mask);
			mask_val >>= j * 4;
			if (mask_val > 4) {
				mask_val += 3;
				bcd &= ~mask;
				bcd |= (mask_val << (j * 4));
			}
		}
	}

	bcd = bcd << 1;
	if (bn & 32768)
		bcd += 1;

	std::cout << "Number: " << bnc << "\n";
	displayBCD(bcd);

	return(0);
}
