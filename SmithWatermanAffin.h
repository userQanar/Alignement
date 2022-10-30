/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				SmithWatermanAffin.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.10.2021
Beschreibung:		Klasse zur Berechnung eines optimalen lokalen Alignments
					mit dem Smith-Waterman-Algorithmus (affine Gap Penalty)
******************************************************************************/

#pragma once

#include <string>
#include "BaseAlignment.h"
#include "AlignedData.h"

class SmithWatermanAffin : public BaseAlignment
{
public:
	SmithWatermanAffin(std::string seqA, std::string seqB);
	AlignedData PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty) override;

	int  Score(char a, char b) const;
	int  checkNegative(int u, int d, int l);
	int  max(int up, int diag, int left);
	int  charMax(int up, int diag, int left);
	void FillMats();
	void Traceback();

	int iMax = 0; int jMax = 0; int maxVal = 0;

private:
	
};
