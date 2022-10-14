/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Dotplot.cpp
Autoren:			Sascha Seifert, Max Barchet, Sophie Reimschüssel
Letzte Änderung:	13.09.2022
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
	for (unsigned int i = 0; i < D.GetNumRows(); i++){ // Fill Hits

		for (unsigned j = 0; j < D.GetNumCols(); j++){
		
			if(seqB[i]==seqA[j]) D.SetValue(i, j, 88);		
		}
	}
	
	for (unsigned int i = 0; i < D.GetNumRows(); i++) { // Remove Fog

		for (unsigned j = 0; j < D.GetNumCols(); j++) {

			if (D.At((i), (j)) == 88) {

				if (i == 0 && j == D.GetNumCols() - 1)	D.SetValue(i, j, 46);

				if (i == 0 && j < D.GetNumCols()-1) {	

					if ((D.At((i), (j))) != (D.At((i + 1), (j + 1)))) D.SetValue(i, j, 46);
				}

				if ((i == (D.GetNumRows()-1) || (j == (D.GetNumCols()-1)))&& (i > 0 && j > 0)) {

					if ((D.At((i), (j))) != (D.At((i - 1),(j - 1)))) D.SetValue(i, j, 46);


				}
			
				if (((i && j >= 1)) && (i < (D.GetNumRows()-1) && (j < (D.GetNumCols()-1)))) {

					if (!(D.At((i), (j))) == (D.At((i - 1), (j - 1)) || D.At((i + 1), (j + 1)))) {

						D.SetValue(i, j, 46);
					}
				}
			}
		}
	} 
	return D;
}