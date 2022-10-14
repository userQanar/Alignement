/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				MainWindow.cpp
Autoren:			Sascha Seifert
					Max Barchet, Joachim Storz, Sophie Reimschüssel
Letzte Änderung:	13.09.2022
Beschreibung:		Hauptfenster (Qt)
******************************************************************************/

#include "MainWindow.h"

#include <qfiledialog.h>
#include <memory>

#include "Fasta.h"
#include "AlignedData.h"
#include "NeedlemanWunsch.h"
#include "NeedlemanWunschAffin.h"
#include "SmithWaterman.h"
#include "SmithWatermanAffin.h"
#include "AlignedDataPrinter.h"
#include "Matrix.h"
#include "Dotplot.h"
#include "DotplotPrinter.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonPerformAlignment, &QPushButton::clicked, this, &MainWindow::PerformAlignment);
	connect(ui.pushButtonDotplot, &QPushButton::clicked, this, &MainWindow::PrintDotplot);
	connect(ui.pushButtonSequenceA, &QPushButton::clicked, this, &MainWindow::ChooseSequenceA);
	connect(ui.pushButtonSequenceB, &QPushButton::clicked, this, &MainWindow::ChooseSequenceB);
}

void MainWindow::PerformAlignment()
{
	std::unique_ptr<BaseAlignment> alg = nullptr;
	if (ui.radioButtonNW->isChecked() == true)
	{
		alg = std::make_unique<NeedlemanWunsch>(sequenceA, sequenceB);
	}
	else if (ui.radioButtonNWAffin->isChecked() == true)
	{
		alg = std::make_unique<NeedlemanWunschAffin>(sequenceA, sequenceB);
	}
	else if (ui.radioButtonSW->isChecked() == true)
	{
		alg = std::make_unique<SmithWaterman>(sequenceA, sequenceB);
	}
	else
	{
		alg = std::make_unique<SmithWatermanAffin>(sequenceA, sequenceB);
	}
	AlignedData alignedData = alg->PerformAlignment(ui.lineEditMatch->text().toInt(), ui.lineEditMismatch->text().toInt(), ui.lineEditgapPenalty->text().toInt(), ui.lineEditGapExtensionPenalty->text().toInt());

	AlignedDataPrinter printer(sequenceA, sequenceB, alignedData);
	ui.plainTextEditMatrices->setPlainText(QString::fromStdString(printer.GetMatrices()));
	ui.plainTextEditMatrices->setTabStopDistance(60);

	ui.labelResultA->setText(QString::fromStdString(alignedData.resultA));
	ui.labelResultA->setFont(QFont("Courier New"));
	ui.labelAlign->setText(QString::fromStdString(printer.GetMatchPositions()));
	ui.labelAlign->setFont(QFont("Courier New"));
	ui.labelResultB->setText(QString::fromStdString(alignedData.resultB));
	ui.labelResultB->setFont(QFont("Courier New"));
}

void MainWindow::PrintDotplot()
{
	Dotplot dotplot = Dotplot(sequenceA, sequenceB);
	Matrix<char> DotMatrix = dotplot.Perform(sequenceA, sequenceB);

	DotplotPrinter printer(sequenceA, sequenceB, DotMatrix);

	ui.plainTextEditDotplot->setPlainText(QString::fromStdString(printer.GetMatrix()));
	ui.plainTextEditDotplot->setTabStopDistance(30);
}

void MainWindow::ChooseSequenceA()
{
	QString filename = QFileDialog::getOpenFileName(this, "Choose a file", "../", "Fasta-File (*.fasta)");

	Fasta fastaA(filename.toStdString());
	sequenceA = fastaA.GetSequence();
	headerA = fastaA.GetHeader();

	ui.labelSequenceA->setText(QString::fromStdString(sequenceA));
	ui.labelHeaderA->setText(QString::fromStdString(headerA));
}

void MainWindow::ChooseSequenceB()
{
	QString filename = QFileDialog::getOpenFileName(this, "Choose a file", "../", "Fasta-File (*.fasta)");

	Fasta fastaB(filename.toStdString());
	sequenceB = fastaB.GetSequence();
	headerB = fastaB.GetHeader();

	ui.labelSequenceB->setText(QString::fromStdString(sequenceB));
	ui.labelHeaderB->setText(QString::fromStdString(headerB));
}
