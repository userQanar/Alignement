/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				MainWindow.h
Autoren:			Sascha Seifert
                    Max Barchet, Joachim Storz, Sophie Reimschüssel
Letzte Änderung:	13.09.2022
Beschreibung:		Hauptfenster (Qt)
******************************************************************************/

#pragma once

#include <QtWidgets/QMainWindow>
#include <string>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindow ui;
    std::string sequenceA;
    std::string headerA;
    std::string sequenceB;
    std::string headerB;

private slots:
    void PerformAlignment();
    void PrintDotplot();
    void ChooseSequenceA();
    void ChooseSequenceB();
};
