/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				SmithWaterman.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.10.2021
Beschreibung:		Klasse zur Berechnung eines optimalen lokalen Alignments
					mit dem Smith-Waterman-Algorithmus (lineare Gap Penalty)
******************************************************************************/

#pragma once

#include <string>
#include "BaseAlignment.h"
#include "AlignedData.h"

class SmithWaterman : public BaseAlignment
{
public:
	SmithWaterman(std::string seqA, std::string seqB);
	AlignedData PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty) override;

private:
	
};
