/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Dotplot.h
Autoren:			Sascha Seifert, Max Barchet, Sophie Reimschüssel
Letzte Änderung:	09.08.2022
Beschreibung:		Klasse zur Erstellung einer Matrix mit einem "Dotplot"
******************************************************************************/

#pragma once

#include <string>
#include "Matrix.h"

class Dotplot
{
public:
	Dotplot(std::string seqA, std::string seqB);
	~Dotplot();
	Matrix<char> Perform(std::string seqA, std::string seqB);

private:
	std::string sequenceA;
	std::string sequenceB;
	Matrix<char> D;
};
