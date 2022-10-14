/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				DotplotPrinter.h
Autoren:			Sascha Seifert, Max Barchet, Sophie Reimsch�ssel
Letzte �nderung:	09.08.2022
Beschreibung:		Klasse zur formattierten Ausgabe eines Dotplots
******************************************************************************/

#pragma once

#include<string>
#include"Matrix.h"

class DotplotPrinter
{
public:
	DotplotPrinter(std::string seqA, std::string seqB, Matrix<char> D);
	~DotplotPrinter();

	// R�ckgabe der Matrix mit dem Dotplot
	std::string GetMatrix();

private:
	std::string seqA;
	std::string seqB;
	Matrix<char> D;
};
