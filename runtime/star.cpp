#include "star.h"

namespace star {

void init() {
	Type::types = {};
	Type::maxID = 0;
	Category::categories = {};
	Category::maxID = 0;

	Type::types.push_back(
		new Type(
			"Star.Value",
			Type::newID(),
			Structure::Protocol,
			{},
			new SelTable(),
			new SelTable(
				{
					new Sel::Single("retain", 1),
					new Sel::Single("release", 1)
				},
				{
					new Method([](Value *value) {value->retain();}),
					new Method([](Value *value) {value->release();})
				}
			),
			sizeof(Value),
			Value::init,
			[](Value* value) {value->deinit();}
		)
	);

	
	Type::types.push_back(
		new Type(
			"Star.Void",
			Type::newID(),
			Structure::Native,
			{},
			new SelTable(),
			new SelTable(),
			sizeof(Void),
			[] {return (Value*) new Void();},
			nullptr
		)
	);
}

void deinit() {
	auto& cats = Category::categories;
	auto& typs = Type::types;
	
	for(auto cat = cats.rbegin(); cat != cats.rend(); cat++) {
		delete *cat;
	}
	
	for(auto type = typs.rbegin(); type != typs.rend(); type++) {
		delete *type;
	}
}

size_t numTypes() {
	return Type::types.size();
}

std::vector<Type*>& types() {
	return Type::types;
}

void registerType(Type *type) {
	Type::types.push_back(type);
}

size_t numCategories() {
	return Category::categories.size();
}

std::vector<Category*>& categories() {
	return Category::categories;
}

void registerCategory(Category *category) {
	Category::categories.push_back(category);
}

Type* valueType() {
	return Type::types[0];
}

Type* voidType() {
	return Type::types[1];
}

}