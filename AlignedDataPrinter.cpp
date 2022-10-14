/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				AlignedDataPrinter.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	20.09.2021
Beschreibung:		Klasse zur formattierten Ausgabe der Alignements
******************************************************************************/

#include "AlignedDataPrinter.h"
#include <iostream>

using namespace std;


AlignedDataPrinter::AlignedDataPrinter(std::string seqA, std::string seqB, AlignedData const& alignedData)
{
	this->alignedData.F = alignedData.F;
	this->alignedData.Z = alignedData.Z;
	this->alignedData.resultA = alignedData.resultA;
	this->alignedData.resultB = alignedData.resultB;
	this->seqA = seqA;
	this->seqB = seqB;
}


AlignedDataPrinter::~AlignedDataPrinter()
{
}


std::string AlignedDataPrinter::GetMatchPositions()
{
	string vis;
	for (unsigned int i = 0; i < alignedData.resultA.length(); i++)
	{
		if (alignedData.resultA.substr(i, 1) == alignedData.resultB.substr(i, 1))
			vis.append("|");
		else
			vis.append(" ");
	}

	return vis;
}


std::string AlignedDataPrinter::GetMatrices()
{
	if (alignedData.F.GetNumCols() == 0 && alignedData.F.GetNumRows() == 0)
		return "";

	std::string matrix = "";
	matrix.append("\t\t");
	for (int i = 0; i < seqA.size(); i++)
	{
		{
			matrix.push_back(seqA[i]);
			matrix.append("\t");
		}
	}

	matrix.append("\n");
	for (int i = 0; i < alignedData.F.GetNumRows(); i++)
	{
		if (i == 0)
			matrix.append("\t");

		else
		{
			matrix.push_back(seqB[i - 1]);
			matrix.append("\t");
		}
		for (int j = 0; j < alignedData.F.GetNumCols(); j++)
		{
			matrix.append(std::to_string(alignedData.F.At(i, j)));
			matrix.append(" ");
			switch (alignedData.Z.At(i, j))
			{
			case 'D':
				matrix.append(u8"\u2196");
				break;
			case 'L':
				matrix.append(u8"\u2190");
				break;
			case 'U':
				matrix.append(u8"\u2191");
				break;
			default:
				matrix.append(" ");
			}
			matrix.append("\t");
		}
		matrix.append("\n");
	}
	return matrix;
}
