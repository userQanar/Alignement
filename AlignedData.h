/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Matrix.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.10.2021
Beschreibung:		Datenstruktur zur Speicherung der ausgerichteten Sequenzen 
					sowie der Scoring- und Traceback-Matrizen
******************************************************************************/

#pragma once

#include <string>
#include "Matrix.h"

struct AlignedData
{
	Matrix<int> F; // Scoring-Matrix
	Matrix<char> Z; // Traceback-Matrix
	std::string resultA; // Ausgerichtete Sequenz A
	std::string resultB; // Ausgerichtete Sequenz B
};
