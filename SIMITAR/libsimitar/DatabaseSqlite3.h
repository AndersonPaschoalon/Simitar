/*
 * DatabaseSqlite3.h
 *
 *  Created on: 28 de jul de 2017
 *      Author: anderson
 */

#ifndef DATABASE_SQLITE3_H_
#define DATABASE_SQLITE3_H_

#include <sqlite3.h>
#include <iostream>
#include <list>
#include <string>

/**
 * Mutex used to perform operations
 */
//std::mutex db_mutex;
/**
 * Used if the database operations was succeed
 */
const int DATABASE_SQLITE3_SUCCSESS = 0;

/**
 * Used if the wasn't possible to open the database.
 * Eg.: access denied of file does not exist.
 */
const int DATABASE_SQLITE3_CANT_OPEN = -1;

/**
 * Used if the data cant be read
 */
const int DATABASE_SQLITE3_FAILED_FETCH_DATA = -2;

/**
 * Used if the data cant be read
 */
const int DATABASE_SQLITE3_TABLE_NOT_FOUND = -3;

/**
 * Used if the data cant be read
 */
const int DATABASE_SQLITE3_COLUMN_NOT_FOUND = -4;

/**
 * Usef for minor errors
 */
const int DATABASE_SQLITE3_WARNING = -5;

/**
 * A thread safe sqlite3 C++ wrapper
 */
class DatabaseSqlite3
{
public:

	/**
	 * Constructor. Open the connection
	 */
	DatabaseSqlite3(std::string databaseFile, bool verbose);

	/**
	 * Destructor. Close the connection
	 */
	virtual ~DatabaseSqlite3();

	//string queries///////////////////////////////////////////////////////////

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param out_values
	 * @return
	 */
	int get(std::string table, std::string thecolumn,
			std::list<std::string>& out_values);

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int get_where(std::string table, std::string thecolumn,
			std::string where_constraint, std::list<std::string>& out_values);

	/**
	 * To join only two tables, just use "" as joinTable2.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int join(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			std::list<std::string>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param value
	 * @return
	 */
	std::string max(std::string column, std::string table,
			std::string joinTable1, std::string table1_constraint,
			std::string joinTable2, std::string table2_constaint,
			std::string where_constraint, std::string& value);

	//double queries///////////////////////////////////////////////////////////

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param out_values
	 * @return
	 */
	int get(std::string table, std::string thecolumn,
			std::list<double>& out_values);

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int get_where(std::string table, std::string thecolumn,
			std::string where_constraint, std::list<double>& out_values);

	/**
	 * To join only two tables, just use "" as joinTable2.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int join(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			std::list<double>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param value
	 * @return
	 */
	double max(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			double& value);

	//int queries//////////////////////////////////////////////////////////////

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param out_values
	 * @return
	 */
	int get(std::string table, std::string thecolumn,
			std::list<int>& out_values);

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int get_where(std::string table, std::string thecolumn,
			std::string where_constraint, std::list<int>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int join(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			std::list<int>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param value
	 * @return
	 */
	int max(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			int& value);

	//uint/////////////////////////////////////////////////////////////////////

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param out_values
	 * @return
	 */
	int get(std::string table, std::string thecolumn,
			std::list<uint>& out_values);

	/**
	 *
	 * @param table
	 * @param thecolumn
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int get_where(std::string table, std::string thecolumn,
			std::string where_constraint, std::list<uint>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param out_values
	 * @return
	 */
	int join(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			std::list<uint>& out_values);

	/**
	 * Put "" on joinTable fields that are not going to be used.
	 * If no joinTable is filed, it workas as the get_where() method.
	 *
	 * @param column
	 * @param table
	 * @param joinTable1
	 * @param table1_constraint
	 * @param joinTable2
	 * @param table2_constaint
	 * @param where_constraint
	 * @param value
	 * @return
	 */
	uint max(std::string column, std::string table, std::string joinTable1,
			std::string table1_constraint, std::string joinTable2,
			std::string table2_constaint, std::string where_constraint,
			uint& value);

	//query////////////////////////////////////////////////////////////////////
	/**
	 *
	 * @param sql_query
	 * @param out_values
	 * @return
	 */
	int query(std::string sql_query, std::list<std::string>& out_values);

private:

	// members

	/**
	 * Pointer to the database
	 */
	sqlite3 *m_db;

	/**
	 * Print warning messages
	 */
	bool m_verbose = false;

	/**
	 * flag that tells if the database is open or not
	 */
	//bool m_db_is_open = false;
	// private methods

	/**
	 * @brief Convert a string list to a int list
	 * @param inlist
	 * @param outlist
	 */
	void string_to_int(std::list<std::string> inlist, std::list<int>& outlist);

	/**
	 * @brief Convert a string list to a int list
	 * @param inlist
	 * @param outlist
	 */
	void string_to_uint(std::list<std::string> inlist,
			std::list<uint>& outlist);

	/**
	 * @brief Convert a string list to a double list
	 * @param inlist
	 * @param outlist
	 */
	void string_to_double(std::list<std::string> inlist,
			std::list<double>& outlist);

	/**
	 *
	 */
	void error_cant_open();

	/**
	 *
	 */
	void error_failed_to_fetch(std::string sql_query);

	/**
	 *
	 */
	void error_table_not_found();

	/**
	 *
	 */
	void error_column_not_found();

	/**
	 *
	 */
	void error_data_list_empty(std::string query);

};

// Used for debug purposes
template<typename T>
void printList(std::list<T>& theList)
{
	std::cout << "[";
	for (typename std::list<T>::iterator it = theList.begin();
			it != theList.end(); it++)
	{
		std::cout << *it << ", ";
	}
	std::cout << "]" << std::endl;
}

#endif /* DATABASE_SQLITE3_H_ */
