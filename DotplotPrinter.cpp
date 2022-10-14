/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				DotplotPrinter.h
Autoren:			Sascha Seifert, Max Barchet, Sophie Reimschüssel
Letzte Änderung:	09.08.2022
Beschreibung:		Klasse zur formattierten Ausgabe eines Dotplots
******************************************************************************/

#include "DotplotPrinter.h"

DotplotPrinter::DotplotPrinter(std::string seqA, std::string seqB, Matrix<char> D)
{
	this->seqA = seqA;
	this->seqB = seqB;
	this->D = D;
}

DotplotPrinter::~DotplotPrinter()
{
}

std::string DotplotPrinter::GetMatrix()
{
	if (D.GetNumCols() == 0 && D.GetNumRows() == 0)
		return "";

	std::string matrix = "";
	matrix.append("\t");
	for (unsigned int i = 0; i < seqA.size(); i++)
	{
		matrix.push_back(seqA[i]);
		matrix.append("\t");
	}
	matrix.append("\n");


	for (unsigned int i = 0; i < D.GetNumRows(); i++)
	{
		matrix.push_back(seqB[i]);
		matrix.append("\t");

		for (unsigned j = 0; j < D.GetNumCols(); j++)
		{
			matrix.push_back((D.At(i, j)));
			matrix.append("\t");
		}
		matrix.append("\n");
	}

	return matrix;
}
