#pragma once

#include "star_dispatch.h"
#include "star_llvm.h"

namespace star {

void init();

void deinit();

size_t numTypes();

std::vector<Type*>& types();

void registerType(Type*);

size_t numCategories();

std::vector<Category*>& categories();

void registerCategory(Category*);

Type* valueType();

Type* voidType();

}