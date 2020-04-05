#include <iostream>
#include <string>

#include "../runtime/star.h"

int main() {
	star::init();
	star::llvm::init();

	star::Type *Int32 = star::Type::fromName("Star.LLVM.Int32");
	star::Type *Dec64 = star::Type::fromName("Star.LLVM.Dec64");

	star::Value *myInt32 = new star::llvm::Int32(1);
	star::Value *myDec64 = new star::llvm::Dec64(2.3);

	std::cout << myInt32->isA(Int32) << "\n"; //=> 1
	std::cout << myInt32->isA(Dec64) << "\n"; //=> 0
	std::cout << myDec64->isA(Int32) << "\n"; //=> 0
	std::cout << myDec64->isA(Dec64) << "\n"; //=> 1

	myInt32->release();
	myDec64->release();

	star::deinit();

	return 0;
}


/*
#include "star_c.h"

int main() {
	star_init();
	star_llvm_init();
	
	star_Type Int32 = star_Type_fromName("Star.LLVM.Int32");
	star_Type Dec64 = star_Type_fromName("Star.LLVM.Dec64");

	star_Value myInt32 = star_llvm_Int32_wrap(1);
	star_Value myDec64 = star_llvm_Dec64_wrap(2.3);

	std::cout << star_Value_isA(myInt32, Int32) << "\n"; //=> 1
	std::cout << star_Value_isA(myInt32, Dec64) << "\n"; //=> 0
	std::cout << star_Value_isA(myDec64, Int32) << "\n"; //=> 0
	std::cout << star_Value_isA(myDec64, Dec64) << "\n"; //=> 1

	star_Value_release(myInt32);
	star_Value_release(myDec64);

	star_deinit();

	return 0;
}
*/