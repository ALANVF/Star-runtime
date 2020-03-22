#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "star_id.h"
#include "star.h"

size_t $NumTypes, $NumCategories;
Type *$Value, *$Void, *$LLVM$Int32, *$LLVM$Dec64;
Type* **$Types;
Category* **$Categories;


void star_initStar(void) {
	$Value = Type_new(
		"Star.Value",
		TypeID$Value,
		TypeStructure$Protocol,
		NULL,
		SelTable_newEmpty(),
		SelTable_new(
			(Sel[]) {
				Sel_newSingle("retain", TypeID$Void),
				Sel_newSingle("release", TypeID$Void)
			},
			(Method[]) {
				Value_retain,
				Value_release
			},
			2
		),
		sizeof(Value),
		Value_init,
		Value_deinit
	);

	$Void = Type_new(
		"Star.Void",
		TypeID$Void,
		TypeStructure$Native,
		NULL,
		SelTable_newEmpty(),
		SelTable_newEmpty(),
		sizeof(Void),
		Void_init,
		NULL
	);

	$NumTypes = 2;
	$Types = malloc(sizeof(Type**) * $NumTypes);
	$Types[TypeID$Value] = &$Value;
	$Types[TypeID$Void] = &$Void;

	$NumCategories = 0;
	$Categories = malloc($NumCategories);
}

void star_deinitStar(void) {
	for(int i = $NumCategories-1; i >= 0; i--) {
		Category_cleanup(*$Categories[i]);
		*$Categories[i] = NULL;
	}

	free($Categories);
	
	for(int i = $NumTypes-1; i >= 0; i--) {
		Type_cleanup(*$Types[i]);
		*$Types[i] = NULL;
	}

	free($Types);
}

size_t star_getNumTypes(void) {
	return $NumTypes;
}

Type*** star_getTypes(void) {
	return $Types;
}

void star_registerType(Type *type) {
	if(type == NULL) {
		perror("Internal error: Cannot register a null type!");
		exit(1);
	} else {
		$Types = realloc($Types, sizeof(Type**) * ++$NumTypes);
		$Types[$NumTypes - 1] = &type;
	}
}

size_t star_getNumCategories(void) {
	return $NumCategories;
}

Category*** star_getCategories(void) {
	return $Categories;
}

void star_registerCategory(Category *category) {
	$Categories = realloc($Categories, sizeof(Category**) * ++$NumCategories);
	$Categories[$NumCategories - 1] = &category;
}

Type** star_getValueType(void) {
	return &$Value;
}

Type** star_getVoidType(void) {
	return &$Void;
}