#pragma once

#include "star_dispatch.h"

void star_initStar(void);
void star_initLLVM(void);
void star_deinitStar(void);

size_t star_getNumTypes(void);
Type*** star_getTypes(void);
void star_registerType(Type*);

size_t star_getNumCategories(void);
Category*** star_getCategories(void);
void star_registerCategory(Category*);

Type** star_getValueType(void);
Type** star_getVoidType(void);