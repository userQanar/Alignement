/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				BaseAlignment.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.10.2021
Beschreibung:		Basisklasse zur Berechnung von paarweisen Alignements
******************************************************************************/

#pragma once

#include <string>
#include "AlignedData.h"
#include "Matrix.h"

class BaseAlignment
{
public: 
	virtual ~BaseAlignment() {}

	// Ausführung des Algorithmus zur Berechnung des paarweisen Alignements
	virtual AlignedData PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty) = 0;

protected:
	Matrix<int> F;
	Matrix<char> Z;
	std::string sequenceA;
	std::string sequenceB;
	std::string resultA;
	std::string resultB;
	int match = 0;
	int mismatch = 0;
	int gapPenalty = 0;
	int gapExtensionPenalty = 0;
};
