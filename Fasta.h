/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Fasta.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zum Umgang mit Dateien im FASTA-Format
******************************************************************************/

#pragma once /*	Befehl ist nicht C++-standardkonform, wird jedoch von fast allen C++-Kompilern unterstützt.
				Vorteile gegenüber klassischer Lösung mit Präprozessor-Makros (#ifndef/#define...):
				Weniger fehleranfällig (keine Symbolkonflikte möglich), eleganter und kompakter. */

#include <string>


/******************************************************************************
Beispiel zur Nutzung der Klasse "Fasta"

--> Instanz mit FASTA-Datei beispiel.fasta anlegen:
Fasta fastaBsp("beispiel.fasta");

--> Rückgabe des Headers als string:
string header = fastaBsp.GetHeader();

--> Wert des Koeffizienten an der Stelle (4 / 1) zurückgeben:
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
