/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Fasta.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zum Umgang mit Dateien im FASTA-Format
******************************************************************************/

#include "Fasta.h"

#include <iostream>
#include <fstream>

using namespace std;


Fasta::Fasta(string file)
{
	filename = file;
	ExtractFastaFile();
}

Fasta::~Fasta()
{
}


string Fasta::GetSequence()
{
	return sequence;
}

string Fasta::GetHeader()
{
	return header;
}

void Fasta::ExtractFastaFile()
{
	// Implementierung nutzt Teile aus http://rosettacode.org/wiki/FASTA_format
	string line, name, content;

	ifstream input(filename);
	
	if (!input)
		cout << "Datei wurde nicht gefunden!" << endl;

	while (getline(input, line).good())
	{
		if (line[0] == '>')
		{
			name = line.substr(1);
		}
		else if (!name.empty()){
			content += line;
		}
	}

	header = name;
	sequence = content;
}
