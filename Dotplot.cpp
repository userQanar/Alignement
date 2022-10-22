/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Dotplot.cpp
Autoren:			Sascha Seifert, Max Barchet, Sophie Reimschüssel
Student:			Robin Hill
Letzte Änderung:	16.10.2022
Beschreibung:		Klasse zur Erstellung einer Matrix mit einem "Dotplot"
******************************************************************************/

#include "Dotplot.h"

Dotplot::Dotplot(std::string seqA, std::string seqB)
{
	sequenceA = seqA;
	sequenceB = seqB;
	D.SetSize((seqB.size()), (seqA.size()));
}

Dotplot::~Dotplot()
{

}

Matrix<char> Dotplot::Perform(std::string seqA, std::string seqB)
{
	const auto numRows = D.GetNumRows();
	const auto numCols = D.GetNumCols();

	const auto lastRow = numRows - 1;
	const auto lastCol = numCols - 1;

	char Marker		 = 88;
	char downgrade	 = 46;
	char permutation = 112;

	// Fill Hits
	for (unsigned int i = 0; i < numRows; i++) { 
		for (unsigned j = 0; j < numCols; j++) {	

			if(seqB[i]==seqA[j]) 
				D.SetValue(i, j, Marker);		
		}
	}
	// Remove Fog
	for (unsigned int i = 0; i < numRows; i++) { 
		for (unsigned j = 0; j < numCols; j++) {

			const auto Dat = D.At(i, j);
			const auto notDat = !D.At(i, j);

			if (Dat != Marker) {
				continue;
			}
			else {
				// useless Corners
				if (i == 0 && j == lastCol || (i == lastRow && j == 0)) {
					D.SetValue(i, j, downgrade);
					continue;
				}
				// Top & Left
				if ((i == 0 && j < lastCol) || j == 0 && i < lastRow) {

					if (Dat != D.At(i + 1, j + 1)) {
						D.SetValue(i, j, downgrade);
						continue;
					}
				}
				// Right & Bottom 
				if (i == lastRow || (j == lastCol) && (i && j)) {

					if (Dat != D.At(i - 1, j - 1)) {
						D.SetValue(i, j, downgrade);
						continue;
					}
				}
				// Mid
				if ((i && j >= 1) && (i < lastRow && (j < lastCol))) {

					if (notDat == (D.At(i - 1, j - 1) || D.At(i + 1, j + 1))) {
						D.SetValue(i, j, downgrade);
					}
				}
			}
		}
	} 
	//Permutation
	for (unsigned int i = 0; i < numRows; i++) { 
		for (unsigned j = 0; j < numCols; j++) {

			if (D.At(i, j) != downgrade) {
				continue;			
			}
			else {
				// useless Corners
				if ((i == 0 && j == 0) || (i == lastRow && j == lastCol)) {
					continue;
				}
				// Top & Right
				if (i < lastRow && j >= 1) {
					if (D.At(i + 1, j - 1) == downgrade) {
						if (!Marker == (D.At(i + 1, j) || D.At(i, j - 1))) {
							D.SetValue(i, j, permutation);
							continue;
						}
					}
				}
				// Bottom & Left  
				if (i >= 1 && j < lastCol) {
					if (D.At(i - 1, j + 1) == permutation) {
						D.SetValue(i, j, permutation);
					}
				}
			}
		}
	}
	//Permutation Fix -slow
	for (unsigned int i = 0; i < numRows; i++) {
		for (unsigned j = 0; j < numCols; j++) {

			if ((D.At(i, j) == permutation) && (i >=2 && j < lastCol-1)) {
				// false downgraded in (//Top & Right) 
				if (D.At(i - 2, j + 2) == downgrade) {
					D.SetValue(i - 2, j + 2, permutation);
				// remove false positives
					if(D.At(i - 1, j + 1) != permutation) {
						D.SetValue(i - 2, j + 2, downgrade);
					}
				}
			}
		}
	}
	return D;
}