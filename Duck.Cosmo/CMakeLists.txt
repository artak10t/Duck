cmake_minimum_required (VERSION 3.8)

add_library($ENV{COSMO_NAME} STATIC
	"Celestial/Star.h"
	"Celestial/Star.cpp"
	"Celestial/Planet.h"
	"Celestial/Planet.cpp"

	"Math/ISolver.h"
	"Generation/IGenerator.h"
)