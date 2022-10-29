/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				SmithWaterman.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	24.09.2021
Beschreibung:		Klasse zur Berechnung eines optimalen lokalen Alignments
					mit dem Smith-Waterman-Algorithmus (lineare Gap Penalty)
******************************************************************************/

#include "SmithWaterman.h"
#include <vector>
#include <algorithm>

using namespace std;

SmithWaterman::SmithWaterman(std::string seqA, std::string seqB) 
{
	sequenceA = seqA;
	sequenceB = seqB;
	F.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
	Z.SetSize(sequenceB.size() + 1, sequenceA.size() + 1);
}

int SmithWaterman::Score(char a, char b) {

	if (a == '-' || b == '-') return gapPenalty;
	if (a == b) return match;
	else return mismatch;
}

int SmithWaterman::max(int up, int diag, int left) {

	if (up >= diag) { // >=
		if (up >= left) return up;
		else return left;
	}
	else {
		if (diag >= left) return diag;
		else return left;
	}
}

int SmithWaterman::charMax(int up, int diag, int left) {

	if (up >= diag) { // >=
		if (up >= left) return 'U';
		else return 'L';
	}
	else {
		if (diag >= left) return 'D';
		else return 'L';
	}
}

int SmithWaterman::checkNegative(int u, int d, int l) {

	if (max(u, d, l) <= 0) return 0;
	else return max(u, d, l);
}

void SmithWaterman::FillMats() {

	for (unsigned int i = 1; i < F.GetNumRows(); i++) {
		for (unsigned j = 1; j < F.GetNumCols(); j++) {

			int up = F.At(i - 1, j)		  + Score(sequenceB[i], '-');
			int diag = F.At(i - 1, j - 1) + Score(sequenceB[i - 1], sequenceA[j - 1]);
			int left = F.At(i, j - 1)	  + Score('-', sequenceA[j]);

			F.SetValue(i, j, checkNegative(up, diag, left));

			if (F.At(i, j) > maxVal) {
				maxVal = F.At(i, j);
				iMax = i; 
				jMax = j;
			}

			if (checkNegative(up, diag, left) != 0) {
				Z.SetValue(i, j, charMax(up, diag, left));
			}
			else Z.SetValue(i, j, '0');
		}
	}
}

void SmithWaterman::Traceback() {

	Z.SetValue(0, 0, '0');
	for (unsigned i = 1; i < Z.GetNumRows(); i++) {
		Z.SetValue(i, 0, '0');
	}
	for (unsigned j = 1; j < Z.GetNumCols(); j++) {
		Z.SetValue(0, j, '0');
	}

	while (F.At(iMax, jMax) > 0) {

		if (Z.At(iMax, jMax) == 'D') {
			resultA.insert(resultA.begin(), sequenceA[jMax - 1]);
			resultB.insert(resultB.begin(), sequenceB[iMax - 1]);
			iMax--; jMax--;
		}
		else if (Z.At(iMax, jMax) == 'L') {
			resultA.insert(resultA.begin(), sequenceA[jMax - 1]);
			resultB.insert(resultB.begin(), '-');
			jMax--;
		}
		else if (Z.At(iMax, jMax) == 'U') {
			resultA.insert(resultA.begin(), '-');
			resultB.insert(resultB.begin(), sequenceB[iMax - 1]);
			iMax--;
		}
	}
}

AlignedData SmithWaterman::PerformAlignment(int const& match, int const& mismatch, int const& gapPenalty, int const& gapExtensionPenalty)
{
	this->match = match;
	this->mismatch = mismatch;
	this->gapPenalty = gapPenalty;
	this->gapExtensionPenalty = gapExtensionPenalty;
	FillMats();
	Traceback();

	return AlignedData{ F, Z, resultA, resultB };
}
