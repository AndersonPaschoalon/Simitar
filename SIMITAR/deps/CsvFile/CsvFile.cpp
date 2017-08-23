/*
 * CsvFile.cpp
 *
 *  Created on: 7 de ago de 2017
 *      Author: anderson
 */

#include "CsvFile.h"

const std::string& CSVRow::operator [](std::size_t index) const
{
	return m_data[index];
}

std::size_t CSVRow::size() const
{
	return m_data.size();
}

void CSVRow::readNextRow(std::istream& str)
{
	std::string line;
	std::getline(str, line);

	std::stringstream lineStream(line);
	std::string cell;

	m_data.clear();
	while (std::getline(lineStream, cell, ','))
	{
		m_data.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		m_data.push_back("");
	}
}

inline std::istream& operator >>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

CSVIterator::CSVIterator(std::istream& str) :
		m_str(str.good() ? &str : NULL)
{
	++(*this);
}

CSVIterator::CSVIterator() :
		m_str(NULL)
{
}

CSVIterator& CSVIterator::operator ++()

{
	if (m_str)
	{
		if (!((*m_str) >> m_row))
		{
			m_str = NULL;
		}
	}
	return *this;
}

CSVIterator CSVIterator::operator ++(int int1)
			{
				CSVIterator tmp(*this);
				++(*this);
				return tmp;
			}

const CSVRow& CSVIterator::operator *() const
{
	return m_row;
}

const CSVRow* CSVIterator::operator ->() const
{
	return &m_row;
}

bool CSVIterator::operator ==(const CSVIterator& rhs)
			{
				return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
			}

bool CSVIterator::operator !=(const CSVIterator& rhs)
			{
				return !((*this) == rhs);
			}

CsvFile::CsvFile(const char* filename): _filename(filename)
	{
		_file.open(filename);
		_loop = CSVIterator(_file);
	}

void CsvFile::reset()
{
	_file.close();
	_file.open(_filename);
	_loop = CSVIterator(_file);
}

bool CsvFile::next_line()
{
	++_loop;
	if (_loop != CSVIterator())
	{
		return (true);
	}
	return false;
}

std::string CsvFile::column(uint i)
{
	std::string column_str = (*_loop)[i];
	return column_str;
}

