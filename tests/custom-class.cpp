#include <iostream>
#include <string>

#include "../runtime/star.h"


class Core_Int : public star::Value {
public:
	static star::TypeID typeID;

	star::llvm::Int32 *native;

	Core_Int(): native(nullptr) {
		this->md = new star::MD(Core_Int::typeID);
	}
	
	Core_Int(star::llvm::Int32 *native): native(native) {
		this->md = new star::MD(Core_Int::typeID);
	}

	~Core_Int() {}
};

star::TypeID Core_Int::typeID;


void Core_Int__initWithNative(star::Value *_this, star::Value *_native) {
	auto this_ = (Core_Int*) _this;
	auto native = (star::llvm::Int32*) _native;

	this_->native = native;
}

star::Value* Core_Int__add(star::Value *_this, star::Value *_other) {
	auto this_ = (Core_Int*) _this;
	auto other = (Core_Int*) _other;

	return new Core_Int(
		new star::llvm::Int32(
			this_->native->repr + other->native->repr
		)
	);
}


int main() {
	star::init();
	star::llvm::init();
	
	star::Type *Value = star::valueType();
	star::Type *Void = star::voidType();
	star::Type *Int32 = star::Type::fromName("Star.LLVM.Int32");

	/* ---------------------- */

	Core_Int::typeID = star::Type::newID();

	auto selInit = new star::Sel::Multi(
		{"newWithNative"},
		{Int32->id},
		Void->id
	);

	auto selAdd = new star::Sel::Multi(
		{"+"},
		{Core_Int::typeID},
		Core_Int::typeID
	);

	star::Type *Int = new star::Type(
		"Star.Core.Int",
		Core_Int::typeID,
		star::Structure::Class,
		{Value},
		new star::SelTable(),
		new star::SelTable(
			{
				selInit,
				selAdd
			},
			{
				new star::Method((star::RawMethod) Core_Int__initWithNative, star::Method::Attr::Init),
				new star::Method((star::RawMethod) Core_Int__add)
			}
		),
		sizeof(Core_Int),
		[]() {return (star::Value*) new Core_Int();},
		[](star::Value *value) {
			((Core_Int*) value)->native->release();
		}
	);
	star::registerType(Int);

	
	auto int1 = (Core_Int*) Int->init();
	auto int2 = (Core_Int*) Int->init();

	int1->dispatch(selInit, {new star::llvm::Int32(1)});
	int2->dispatch(selInit, {new star::llvm::Int32(2)});

	auto int3 = (Core_Int*) *int1->dispatch(selAdd, {int2});

	std::cout << int1->md->format() << "\n";
	std::cout << int2->md->format() << "\n";
	std::cout << int3->md->format() << "\n\n";

	std::cout << int1->native->repr << "\n";
	std::cout << int2->native->repr << "\n";
	std::cout << int3->native->repr << "\n\n";
	
	int1->release();
	int2->release();
	int3->release();


	star::deinit();

	return 0;
}