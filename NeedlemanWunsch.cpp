/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				NeedlemanWunsch.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	24.09.2021
Beschreibung:		Klasse zur Berechnung eines optimalen globalen Alignments
					mit dem Needleman-Wunsch-Algorithmus (lineare Gap Penalty)
******************************************************************************/

#include "NeedlemanWunsch.h"
#include <vector>
#include <algorithm>

using namespace std;

NeedlemanWunsch::NeedlemanWunsch(std::string seqA, std::string seqB)
{
	sequenceA = seqA;
	sequenceB = seqB;
	F.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
	Z.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
}

int NeedlemanWunsch::Score(char a, char b) const {

	if (a == b) return match;
	else return mismatch;
}

void NeedlemanWunsch::FillMats() {

	const auto numRows = F.GetNumRows();
	const auto numCols = F.GetNumCols();

	for (int i = 1; i < numRows; i++) {

		F.SetValue(i , 0, i * gapPenalty);
		Z.SetValue(i , 0, 'U');
	}
	for (int j = 1; j < numCols; j++) {

		F.SetValue(0, j , j * gapPenalty);
		Z.SetValue(0, j , 'L');
	}
		F.SetValue(0, 0, 0);

	for (unsigned int i = 1; i < numRows; i++) {
		for (unsigned j = 1; j < numCols; j++) {

			int diag = F.At(i - 1, j - 1) + Score(sequenceA[j - 1], sequenceB[i - 1]);
			int up   = F.At(i - 1, j) + gapPenalty;
			int left = F.At(i, j - 1) + gapPenalty;

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

void NeedlemanWunsch::Traceback() {

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
	}
}

AlignedData NeedlemanWunsch::PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty)
{
	this->match = match;
	this->mismatch = mismatch;
	this->gapPenalty = gapPenalty;
	this->gapExtensionPenalty = gapExtensionPenalty;
	FillMats();
	Traceback();
	return AlignedData{F, Z, resultA, resultB};
}
