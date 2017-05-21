/*
 * DatabaseInterface.cpp
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#include "DatabaseInterface.h"

//DONE
DatabaseInterface::DatabaseInterface()
{
	char databaseName[] = "data/trace.db";	//database file name
	int rc = 0; //control output flag

	//init members
	tracesList_table = "ExperimentList";
	capture_table = "TraceCapture";
	rc = sqlite3_open(databaseName, &db);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 1;
	}
	else
	{
		databaseInterface_error = 0;

#ifdef DEBUG_DatabaseInterface
		cout << "atabaseInterface_error: " << databaseInterface_error << endl;
#endif
	}

}

//DONE
DatabaseInterface::~DatabaseInterface()
{
	sqlite3_close(db);
}

//DONE
string DatabaseInterface::toString()
{
	string info = "database status: ";
	string status = to_string(databaseInterface_error);
	return (info + status);
}

int DatabaseInterface::getTraceData(const string experimentName,
		const string label, string* value)
{
	string string_sql; //SQL string query
	char* sql = NULL; //SQL char[] query
	int rc = 0; //control output flag
	sqlite3_stmt *res; //database handle

	//create
	string_sql = "select " + label + " from " + tracesList_table + " where "
			+ "experimentName=\"" + experimentName + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//this command captures a single value
	rc = sqlite3_step(res);
	if (rc != SQLITE_ROW)
	{
		perror("Error @ `int DatabaseInterface::getTraceData()`, column not found");
		databaseInterface_error = 3;
	}

	*value = (const char*) sqlite3_column_text(res, 0);

#ifdef DEBUG
	printf("Debug: %s\n", sqlite3_column_text(res, 0));
#endif

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (0);
}

int DatabaseInterface::getTraceData(const string experimentName,
		const string label, int* value)
{
	string temp_int;
	int ret_value;

	ret_value = this->getTraceData(experimentName, label, &temp_int);
	//TODO replace obsolete function atoi()
	*value = atoi(temp_int.c_str());
	//cout << temp_int << endl;
	//*value = stoi(temp_int, nullptr, 10);

	return ret_value;
}

int DatabaseInterface::getTraceList(list<string>& traceNames_list)
{
	int rc = 0; 				//control output flag
	char* sql = NULL; 			//SQL char[] query
	string string_sql; 			//SQL string query
	sqlite3_stmt *res; 			//database handle

	//create SQL query
	string_sql = "select experimentName from " + tracesList_table + ";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		traceNames_list.push_back((const char*) sqlite3_column_text(res, 0));
	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);
	return (0);
}

int DatabaseInterface::getNumberOfFlows(string experimentName, long int* nflows)
{
	string string_sql; 						//SQL string query
	char* sql = NULL; 						//SQL char[] query
	int rc = 0; 							//control output flag
	sqlite3_stmt *res; 						//database handle
	char strExperimentId[INT_BUFFER_SIZE]; 	// FlowID string
	int experimentID;

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create sql query
	string_sql = "select max(FlowId) from " + capture_table + " where "
			+ "experimentID=\"" + strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (-2);
	}

	//this command captures a single value
	rc = sqlite3_step(res);
	if (rc != SQLITE_ROW)
	{
		perror("Error @ `DatabaseInterface::getNumberOfFlows()`, column not found");
		databaseInterface_error = 3;
		return (-3);
	}

	//TODO replace obsolete function atoi()
	*nflows = atoi((const char*) sqlite3_column_text(res, 0));

#ifdef DEBUG
	printf("Debug: %s\n", sqlite3_column_text(res, 0));
#endif

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (*nflows + 1);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, long int* value)
{
	string temp_int;
	int ret_value;

	ret_value = this->getFlowData(experimentName, flowID, label, &temp_int);
	//TODO replace obsolete function atoi()
	*value = atoi(temp_int.c_str());

	return (ret_value);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, double* value)
{
	string temp_d;
	int ret_value;

	ret_value = this->getFlowData(experimentName, flowID, label, &temp_d);
	//TODO replace obsolete function atof()
	*value = (double) atof(temp_d.c_str());

	return (ret_value);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, string* str)
{
	int rc = 0; 							//control output flag
	int experimentID;
	char strFlowId[INT_BUFFER_SIZE]; 		// FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	// FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res; 						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//this command captures a single value
	rc = sqlite3_step(res);
	if (rc != SQLITE_ROW)
	{
		perror("Error @ `DatabaseInterface::getFlowData()`, column not found");
		databaseInterface_error = 3;
	}

	*str = (const char*) sqlite3_column_text(res, 0);

#ifdef DEBUG
	printf("Debug: %s\n", sqlite3_column_text(res, 0));
#endif

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (0);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, list<long int>& value_list)
{
	int rc = 0; 							//control output flag
	int experimentID;
	long int value; 						//rows values
	char strFlowId[INT_BUFFER_SIZE]; 		// FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	// FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res;						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		//TODO replace obsolete function atoi()
		value = atoi((const char*) sqlite3_column_text(res, 0));
		value_list.push_back(value);
	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (0);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, list<int>& value_list)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int rc = 0; 							//control output flag
	int experimentID;
	int value; 								//rows values
	char strFlowId[INT_BUFFER_SIZE]; 		//FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	//FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res;						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		//TODO replace obsolete function atoi()
		value = atoi((const char*) sqlite3_column_text(res, 0));
		value_list.push_back(value);
	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (0);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, list<unsigned int>& value_list)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int rc = 0; 							//control output flag
	int experimentID;
	int value; 								//rows values
	char strFlowId[INT_BUFFER_SIZE]; 		//FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	//FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res;						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		//TODO replace obsolete function atoi()
		value = unsigned(atoi((const char*) sqlite3_column_text(res, 0)));
		value_list.push_back(value);
	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);

	return (0);
}


int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, list<double>& value_list)
{
	int rc = 0; 							//control output flag
	int experimentID;
	double value; 							//rows values
	char strFlowId[INT_BUFFER_SIZE]; 		// FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	// FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res; 						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		value = stod((const char*) sqlite3_column_text(res, 0), NULL);
		value_list.push_back(value);

	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);
	return (0);
}

int DatabaseInterface::getFlowData(string experimentName, int flowID,
		string label, list<string>& value_list)
{
	int rc = 0; 							//control output flag
	int experimentID;						//
	char strFlowId[INT_BUFFER_SIZE]; 		// FlowID string
	char strExperimentId[INT_BUFFER_SIZE]; 	// FlowID string
	char* sql = NULL; 						//SQL char[] query
	string string_sql; 						//SQL string query
	sqlite3_stmt *res; 						//database handle

	this->getTraceData(experimentName, "experimentName", &experimentID);
	//convert flowID and experimentID to string
	snprintf(strFlowId, sizeof(strFlowId), "%d", flowID);
	snprintf(strExperimentId, sizeof(strExperimentId), "%d", experimentID);

	//create SQL query
	string_sql = "select " + label + " from " + capture_table
			+ " where  FlowID=\"" + strFlowId + "\" and experimentID=\""
			+ strExperimentId + "\";";
	sql = new char[string_sql.length() + 1];
	strcpy(sql, string_sql.c_str());

	//create SQL statement definition
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc != SQLITE_OK)
	{
		errno = ENOENT;
		fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		databaseInterface_error = 2;
		return (1);
	}

	//capture values until the table finishes
	while (true)
	{
		rc = sqlite3_step(res);
		if (rc != SQLITE_ROW)
		{
			break;
		}
		value_list.push_back((const char*) sqlite3_column_text(res, 0));
	}

	//free allocated memory
	delete[] sql;
	sqlite3_finalize(res);
	return (0);
}
