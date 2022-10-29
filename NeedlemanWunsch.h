/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				NeedlemanWunsch.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.10.2021
Beschreibung:		Klasse zur Berechnung eines optimalen globalen Alignments
					mit dem Needleman-Wunsch-Algorithmus (lineare Gap Penalty)
******************************************************************************/

#pragma once

#include <string>
#include "BaseAlignment.h"
#include "AlignedData.h"

class NeedlemanWunsch : public BaseAlignment
{
public:
	NeedlemanWunsch(std::string seqA, std::string seqB);
	AlignedData PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty) override;
	int  Score(char a, char b) const;
	void FillMats();
	void Traceback();

private:
	
};
