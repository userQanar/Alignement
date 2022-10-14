/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				NeedlemanWunschAffin.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	24.09.2021
Beschreibung:		Klasse zur Berechnung eines optimalen globalen Alignments
					mit dem Needleman-Wunsch-Algorithmus (affine Gap Penalty)
******************************************************************************/

#include "NeedlemanWunschAffin.h"
#include <vector>
#include <algorithm>

using namespace std;

NeedlemanWunschAffin::NeedlemanWunschAffin(std::string seqA, std::string seqB) 
{
	sequenceA = seqA;
	sequenceB = seqB;
	F.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
	Z.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
}

AlignedData NeedlemanWunschAffin::PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty)
{
	this->match = match;
	this->mismatch = mismatch;
	this->gapPenalty = gapPenalty;
	this->gapExtensionPenalty = gapExtensionPenalty;

	

	return AlignedData{F, Z, resultA, resultB};
}
