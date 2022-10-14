/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				AlignedDataPrinter.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	20.09.2021
Beschreibung:		Klasse zur formattierten Ausgabe der Alignements
******************************************************************************/

#pragma once

#include <string>
#include "AlignedData.h"

class AlignedDataPrinter
{
public:
	AlignedDataPrinter(std::string seqA, std::string seqB, AlignedData const& alignedData);
	~AlignedDataPrinter();

	// Rückgabe der Matches als |
	std::string GetMatchPositions();

	// Rückgabe der Scoring- und Traceback-Matrizen
	std::string GetMatrices();

private:
	std::string seqA;
	std::string seqB;
	AlignedData alignedData;
};
