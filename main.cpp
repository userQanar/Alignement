/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				main.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	21.09.2021
Beschreibung:		Hauptprogramm (Qt)
******************************************************************************/

#include <qapplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QCoreApplication::addLibraryPath("plugins");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}

