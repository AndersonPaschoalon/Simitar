/*
 * DatabaseSqlite3.cpp
 *
 *  Created on: 28 de jul de 2017
 *      Author: anderson
 */

#include "DatabaseSqlite3.h"

//DatabaseSqlite3::DatabaseSqlite3()
//{
//	m_db = NULL;
//	m_db_is_open = false;
//	m_verbose = false;
//}

DatabaseSqlite3::DatabaseSqlite3(std::string databaseFile, bool verbose)
{
	if (sqlite3_open(databaseFile.c_str(), &m_db) != SQLITE_OK)
	{
		error_cant_open();
	}
	//m_db_is_open = true;
	m_verbose = verbose;
}

DatabaseSqlite3::~DatabaseSqlite3()
{
	sqlite3_close(m_db);
	//m_db_is_open = false;
}

int DatabaseSqlite3::query(std::string sql_query,
		std::list<std::string>& out_values)
{

	//std::cout << "DatabaseSqlite3 Debug: Query> " << sql_query << std::endl;

	//database handler
	sqlite3_stmt *res;

	//create SQL statement definition
	if (sqlite3_prepare_v2(m_db, sql_query.c_str(), -1, &res, 0) != SQLITE_OK)
	{
		error_failed_to_fetch(sql_query);
	}

	//capture values until the table finishes
	while (true)
	{

		if (sqlite3_step(res) != SQLITE_ROW)
		{
			break;
		}
		else
		{
			out_values.push_back((const char*) sqlite3_column_text(res, 0));
		}
	}

	sqlite3_finalize(res);
	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::get(std::string table, std::string thecolumn,
		std::list<std::string>& out_values)
{
	std::string sql_query = "SELECT " + thecolumn + " FROM " + table + ";";

	query(sql_query, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

std::string DatabaseSqlite3::max(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, std::string& value)
{


	std::string sql_query;
	std::list<std::string> out_values;
	if (joinTable2 != "")
	{
		sql_query = "SELECT MAX(" + table + "." + column + ") FROM " + table
				+ " INNER JOIN " + joinTable1 + " ON " + table1_constraint
				+ " INNER JOIN " + joinTable2 + " ON " + table2_constaint
				+ " WHERE " + where_constraint + ";";

	}
	else if (joinTable1 != "")
	{
		sql_query = "SELECT MAX(" + table + "." + column + ") FROM " + table
				+ " INNER JOIN " + joinTable1 + " ON " + table1_constraint
				+ " WHERE " + where_constraint + ";";
	}
	else
	{
		sql_query = "SELECT MAX(" + table + "." + column + ") FROM " + table
				+ " WHERE " + where_constraint + ";";

	}
	query(sql_query, out_values);

	if (out_values.empty() != true)
	{
		value = *out_values.begin();
	}
	else
	{
		error_data_list_empty(sql_query);
	}

	return (value);
}

int DatabaseSqlite3::get_where(std::string table, std::string thecolumn,
		std::string where_constraint, std::list<std::string>& out_values)
{
	std::string sql_query = "SELECT " + thecolumn + " FROM " + table + " WHERE "
			+ where_constraint + ";";

	query(sql_query, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::join(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, std::list<std::string>& out_values)
{
//SELECT Packets.seq, Packets.traceID, Packets.flowID FROM Packets
//	INNER JOIN Flows ON (Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)
//	INNER JOIN Traces ON Traces.traceID=Flows.traceID
//	WHERE (Flows.flowID=0 AND Traces.traceName="arboc" );

	std::string sql_query;
	if (joinTable2 != "")
	{
		sql_query = "SELECT " + table + "." + column + " FROM " + table
				+ " INNER JOIN " + joinTable1 + " ON " + table1_constraint
				+ " INNER JOIN " + joinTable2 + " ON " + table2_constaint
				+ " WHERE " + where_constraint + ";";

	}
	else if (joinTable1 != "")
	{
		sql_query = "SELECT " + table + "." + column + " FROM " + table
				+ " INNER JOIN " + joinTable1 + " ON " + table1_constraint
				+ " WHERE " + where_constraint + ";";
	}
	else
	{
		sql_query = "SELECT " + table + "." + column + " FROM " + table
				+ " WHERE " + where_constraint + ";";

	}
	query(sql_query, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::get(std::string table, std::string thecolumn,
		std::list<double>& out_values)
{
	std::list<std::string> out_str;

	get(table, thecolumn, out_str);
	string_to_double(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::get_where(std::string table, std::string thecolumn,
		std::string where_constraint, std::list<double>& out_values)
{
	std::list<std::string> out_str;

	get_where(table, thecolumn, where_constraint, out_str);
	string_to_double(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::join(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, std::list<double>& out_values)
{
	std::list<std::string> out_str;

	join(column, table, joinTable1, table1_constraint, joinTable2,
			table2_constaint, where_constraint, out_str);
	string_to_double(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

double DatabaseSqlite3::max(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, double& value)
{
	std::string out_str;

	max(column, table, joinTable1, table1_constraint, joinTable2,
			table2_constaint, where_constraint, out_str);
	value = std::stof(out_str);

	return (value);
}

int DatabaseSqlite3::get(std::string table, std::string thecolumn,
		std::list<int>& out_values)
{
	std::list<std::string> out_str;

	get(table, thecolumn, out_str);
	string_to_int(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::get_where(std::string table, std::string thecolumn,
		std::string where_constraint, std::list<int>& out_values)
{
	std::list<std::string> out_str;

	get_where(table, thecolumn, where_constraint, out_str);
	string_to_int(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::join(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, std::list<int>& out_values)
{
	std::list<std::string> out_str;

	join(column, table, joinTable1, table1_constraint, joinTable2,
			table2_constaint, where_constraint, out_str);

	string_to_int(out_str, out_values);

	return (DATABASE_SQLITE3_SUCCSESS);
}

int DatabaseSqlite3::max(std::string column, std::string table,
		std::string joinTable1, std::string table1_constraint,
		std::string joinTable2, std::string table2_constaint,
		std::string where_constraint, int& value)
{

	std::string out_str;

	max(column, table, joinTable1, table1_constraint, joinTable2,
			table2_constaint, where_constraint, out_str);
	value = std::stoi(out_str);

	return (value);
}

void DatabaseSqlite3::string_to_int(std::list<std::string> inlist,
		std::list<int>& outlist)
{
	if (inlist.empty() == true)
		return;

	for (std::list<std::string>::iterator it = inlist.begin();
			it != inlist.end(); it++)
	{
		outlist.push_back(std::stoi(*it));
	}
}

void DatabaseSqlite3::string_to_double(std::list<std::string> inlist,
		std::list<double>& outlist)
{
	if (inlist.empty() == true)
		return;

	for (std::list<std::string>::iterator it = inlist.begin();
			it != inlist.end(); it++)
	{
		outlist.push_back(std::stof(*it));
	}
}

void DatabaseSqlite3::error_cant_open()
{
	fprintf(stderr, "DatabaseSqlite3 Error: Can't open database: %s\n",
			sqlite3_errmsg(m_db));
	sqlite3_close(m_db);
	exit(DATABASE_SQLITE3_CANT_OPEN);
}

void DatabaseSqlite3::error_failed_to_fetch(std::string sql_query)
{
	fprintf(stderr, "DatabaseSqlite3 Error: Failed to fetch data: %s\n",
			sqlite3_errmsg(m_db));
	std::cerr << "DatabaseSqlite3 Info: Query> " << sql_query << std::endl;
	sqlite3_close(m_db);
	exit(DATABASE_SQLITE3_FAILED_FETCH_DATA);
}

void DatabaseSqlite3::error_table_not_found()
{
	fprintf(stderr, "DatabaseSqlite3 Error: Table not found: %s\n",
			sqlite3_errmsg(m_db));
	sqlite3_close(m_db);
	exit(DATABASE_SQLITE3_TABLE_NOT_FOUND);
}

void DatabaseSqlite3::error_column_not_found()
{
	fprintf(stderr, "DatabaseSqlite3 Error: Column not found: %s\n",
			sqlite3_errmsg(m_db));
	sqlite3_close(m_db);
	exit(DATABASE_SQLITE3_COLUMN_NOT_FOUND);
}

void DatabaseSqlite3::error_data_list_empty(std::string query)
{
	std::cerr << "DatabaseSqlite3 Error: Query \n" << query
			<< "\n returned a empty list of values. Wrong input values."
			<< std::endl;
}

//void DatabaseSqlite3::continue_if_is_instantiated()
//{
//	if (m_db_is_open == false)
//	{
//		fprintf(stderr,
//				"DatabaseSqlite3 Error: Database is not instantiated.\n");
//		sqlite3_close(m_db);
//		exit(DATABASE_SQLITE3_CANT_OPEN);
//	}
//}
