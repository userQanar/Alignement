/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Matrix.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	01.09.2021
Beschreibung:		Template-Klasse zum Umgang mit 2D-Matrizen
******************************************************************************/

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/******************************************************************************
Beispiel zur Nutzung der Klasse "Matrix"

--> Matrix "M" vom Typ double mit 5 Zeilen und 3 Spalten anlegen:
Matrix<double> M(5, 3);

--> Koeffizient an der Stelle (1 / 2) auf den Wert 5,3 setzen:
M.SetValue(1, 2, 5.3);

--> Wert des Koeffizienten an der Stelle (4 / 1) zurückgeben:
double val = M.At(4, 1);
******************************************************************************/
template<typename X> class Matrix
{
public:
	Matrix();
	Matrix(size_t m, size_t n);
	~Matrix();

	// Größe der Matrix festlegen
	void SetSize(size_t m, size_t n);

	// Anzahl der Zeilen zurückgeben
	size_t GetNumRows() const;

	// Anzahl der Spalten zurückgeben
	size_t GetNumCols() const;

	// Koeffizient an der Stelle (m,n) zurückgeben
	X At(size_t m, size_t n) const;

	// Koeffizient an der Stelle (m,n) setzen
	void SetValue(size_t m, size_t n, X val);

	// Matrix auf Kommandozeile ausgeben
	void Print() const;

	// Matrix in Stream ausgeben
	void Write(std::ofstream& o) const;

	// Indizes des größten Koeffizienten bestimmen
	void MaxPos(size_t& m, size_t& n) const;

	// Rückgabe der Matrix als std::string 
	// (Mit Tabulatoren und Zeilenumbrüchen formatiert)
	std::string GetString() const;

private:
	size_t row;
	size_t col;
	std::vector<std::vector<X>> M;
};


template<typename X> Matrix<X>::Matrix()
{
	row = 0;
	col = 0;
}

template<typename X> Matrix<X>::Matrix(size_t m, size_t n)
{
	row = m;
	col = n;
	M.resize(row);
	for (size_t i = 0; i < row; i++)
		M[i].resize(col);
}

template<typename X> Matrix<X>::~Matrix()
{
}


template<typename X> void Matrix<X>::SetSize(size_t m, size_t n)
{
	row = m;
	col = n;
	M.resize(row);
	for (size_t i = 0; i < row; i++)
		M[i].resize(col);
}

template<typename X> size_t Matrix<X>::GetNumRows() const
{
	return row;
}

template<typename X> size_t Matrix<X>::GetNumCols() const
{
	return col;
}

template<typename X> X Matrix<X>::At(size_t m, size_t n) const
{
	return M[m][n];
}

template<typename X> void Matrix<X>::SetValue(size_t m, size_t n, X val)
{
	M[m][n] = val;
}

template<typename X> void Matrix<X>::Print() const
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			std::cout << M[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

template<typename X> void Matrix<X>::Write(std::ofstream& o) const
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			o << M[i][j] << "\t";
		}
		o << std::endl;
	}
}

template<typename X> void Matrix<X>::MaxPos(size_t& m, size_t& n) const
{
	m = 0;
	n = 0;
	X maxVal = M[m][n];
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			if (M[i][j] > maxVal)
			{
				maxVal = M[i][j];
				m = i;
				n = j;
			}
		}
	}
}

template<typename X> std::string Matrix<X>::GetString() const
{
	std::string s;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			s.append(std::to_string(M[i][j]));
			s.append("\t");
		}
		s.append("\n");
	}
	return s;
}
