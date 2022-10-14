/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Fasta.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Klasse zum Umgang mit Dateien im FASTA-Format
******************************************************************************/

#pragma once /*	Befehl ist nicht C++-standardkonform, wird jedoch von fast allen C++-Kompilern unterst�tzt.
				Vorteile gegen�ber klassischer L�sung mit Pr�prozessor-Makros (#ifndef/#define...):
				Weniger fehleranf�llig (keine Symbolkonflikte m�glich), eleganter und kompakter. */

#include <string>


/******************************************************************************
Beispiel zur Nutzung der Klasse "Fasta"

--> Instanz mit FASTA-Datei beispiel.fasta anlegen:
Fasta fastaBsp("beispiel.fasta");

--> R�ckgabe des Headers als string:
string header = fastaBsp.GetHeader();

--> Wert des Koeffizienten an der Stelle (4 / 1) zur�ckgeben:
double val = M.At(4, 1);
******************************************************************************/
class Fasta
{
public:
	Fasta(std::string file);
	~Fasta();

	std::string GetSequence();
	std::string GetHeader();

private:
	std::string filename;
	std::string sequence;
	std::string header;
	void ExtractFastaFile();
};
