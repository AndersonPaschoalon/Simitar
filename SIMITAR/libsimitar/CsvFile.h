/*
 * CsvFile.h
 *
 *  Created on: 3 de ago de 2017
 *      Author: anderson
 */

#ifndef CSVFILE_H_
#define CSVFILE_H_

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
	/**
	 *
	 * @param index
	 * @return
	 */
	std::string const& operator[](std::size_t index) const;

	/**
	 *
	 * @return
	 */
	std::size_t size() const;

	/**
	 *
	 * @param str
	 */
	void readNextRow(std::istream& str);

private:
	/**
	 *
	 */
	std::vector<std::string> m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data);

class CSVIterator
{
public:
	typedef std::input_iterator_tag iterator_category;
	typedef CSVRow value_type;
	typedef std::size_t difference_type;
	typedef CSVRow* pointer;
	typedef CSVRow& reference;

	CSVIterator(std::istream& str);

	CSVIterator();

	// Pre Increment
	CSVIterator& operator++();

	// Post increment
	CSVIterator operator++(int);

	CSVRow const& operator*() const;

	CSVRow const* operator->() const;

	bool operator==(CSVIterator const& rhs);

	bool operator!=(CSVIterator const& rhs);

private:

	std::istream* m_str;
	CSVRow m_row;
};


class CsvFile
{
public:
	/**
	 *
	 * @param filename
	 */
	CsvFile(const char* filename);

	/**
	 *
	 */
	void reset();

	/**
	 *
	 * @return
	 */
	bool next_line();

	/**
	 *
	 * @param i
	 * @return
	 */
	std::string column(uint i);

private:
	std::string _filename;
	CSVIterator _loop;
	std::ifstream _file;

};

#endif /* CSVFILE_H_ */
