cmake_minimum_required (VERSION 3.8)

add_library($ENV{COSMO_NAME} STATIC
	"Catalog/Catalog.h"

	"Celestial/Unit.h"
	"Celestial/Unit.cpp"
	"Celestial/Celestial.h"
	"Celestial/Star.h"
	"Celestial/Star.cpp"
	"Celestial/Planet.h"
	"Celestial/Planet.cpp"
)