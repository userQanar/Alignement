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

int NeedlemanWunschAffin::Score(char a, char b) const {
	if (a == b) {
		return match;
	}
	else {
		return mismatch;
	}
}

void NeedlemanWunschAffin::FillMats() {

	const auto numRows = F.GetNumRows();
	const auto numCols = F.GetNumCols();

	const auto lastRow = numRows - 1;
	const auto lastCol = numCols - 1;

	for (int i = 1; i < lastRow; i++) {

		F.SetValue(i + 1, 0, gapPenalty + i * gapExtensionPenalty);
		Z.SetValue(i + 1, 0, 'U');
	}
	for (int j = 1; j < lastCol; j++) {

		F.SetValue(0, j + 1, gapPenalty + j * gapExtensionPenalty);
		Z.SetValue(0, j + 1, 'L');
	}

	F.SetValue(0, 0, 0);
	F.SetValue(0, 1, gapPenalty);
	Z.SetValue(0, 1, 'L');
	F.SetValue(1, 0, gapPenalty);
	Z.SetValue(1, 0, 'U');

	for (unsigned int i = 1; i < numRows; i++) {
		for (unsigned j = 1; j < numCols; j++) {

			int diag = F.At(i - 1, j - 1) + Score(sequenceA[j - 1], sequenceB[i - 1]);
			int left; int up;

			if (Z.At(i - 1, j) == 'D') {
				up = F.At(i - 1, j) + gapPenalty;
			}
			else {
				up = F.At(i - 1, j) + gapExtensionPenalty;
			}
			
			if (Z.At(i, j - 1) == 'D' && j < lastCol) {
				left = F.At(i, j + 1) + gapPenalty;
			}
			else {
				left = F.At(i, j - 1) + gapExtensionPenalty;
			}

			if (diag >= up && diag >= left) {
				F.SetValue(i, j, diag);
				Z.SetValue(i, j, 'D');
			}

			else if (up > diag && up >= left) { // pick left or up to remove dead ends 
				F.SetValue(i, j, up);
				Z.SetValue(i, j, 'U');
			}

			else if (left > up && left > diag) {
				F.SetValue(i, j, left);
				Z.SetValue(i, j, 'L');
			}
		}
	}
}

void NeedlemanWunschAffin::Traceback() {
	
	int i = sequenceB.length();
	int j = sequenceA.length();

	while (i > 0 || j > 0) {

		if (Z.At(i, j) == 'D') {
			resultA.insert(resultA.begin(), sequenceA[j - 1]);
			resultB.insert(resultB.begin(), sequenceB[i - 1]);
			i--; j--; 
		}
		else if (Z.At(i, j) == 'L') {
			resultA.insert(resultA.begin(), sequenceA[j - 1]);
			resultB.insert(resultB.begin(), '-');
			j--; 
		}
		else if (Z.At(i, j) == 'U') {
			resultA.insert(resultA.begin(), '-');
			resultB.insert(resultB.begin(), sequenceB[i - 1]);
			i--; 
		}
		/*
		reverse(resultA.begin(), resultA.end());
		reverse(resultB.begin(), resultB.end());
		*/
	}
}

AlignedData NeedlemanWunschAffin::PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty)
{
	this->match = match;
	this->mismatch = mismatch;
	this->gapPenalty = gapPenalty;
	this->gapExtensionPenalty = gapExtensionPenalty;
	FillMats();
	Traceback();
	return AlignedData{ F, Z, resultA, resultB };
}
