/*
 * TraceDbManager.cpp
 *
 *  Created on: 28 de jul de 2017
 *      Author: anderson
 */

#include "TraceDbManager.h"

TraceDbManager::TraceDbManager(std::string databaseFile) :
		m_db(DatabaseSqlite3(databaseFile, true))
{
	//m_db = DatabaseSqlite3(databaseFile, true);
}

TraceDbManager::~TraceDbManager()
{
}

std::string TraceDbManager::getTraceData(std::string traceName,
		std::string field, std::string& data)
{
	std::cout << "----1\n";

	m_db.max(field, "Traces", "", "", "", "", "traceName=\"" + traceName + "\"",
			data);
	//std::cout << ">>>> "<<  data << std::endl;

	return (data);
}

int TraceDbManager::getTraceData(std::string traceName, std::string field,
		int& data)
{
	return (m_db.max(field, "Traces", "", "", "", "",
			"traceName=\"" + traceName + "\"", data));
}

uint TraceDbManager::getTraceData(std::string traceName, std::string field,
		uint& data)
{
	return (m_db.max(field, "Traces", "", "", "", "",
			"traceName=\"" + traceName + "\"", data));
}

uint TraceDbManager::getNumberOfFlows(std::string traceName)
{
	int nflows;
	return (uint(
			m_db.max("flowID", "Flows", "Traces",
					"Traces.traceID=Flows.traceID", "", "",
					"traceName=\"" + traceName + "\"", nflows) + 1));
}

std::string TraceDbManager::getFlowData(std::string traceName, int flowID,
		std::string field, std::string& data)
{
	return (m_db.max(field, "Flows", "Traces", "Traces.traceID=Flows.traceID",
			"", "",
			" (Traces.traceName=\"" + traceName + "\" AND Flows.flowID="
					+ std::to_string(flowID) + " )", data));
}

int TraceDbManager::getFlowData(std::string traceName, int flowID,
		std::string field, int& data)
{
	int flowdata = 0;
	flowdata = m_db.max(field, "Flows", "Traces",
			"Traces.traceID=Flows.traceID", "", "",
			" (Traces.traceName=\"" + traceName + "\" AND Flows.flowID="
					+ std::to_string(flowID) + " )", flowdata);
	data = flowdata;
	return (flowdata);
}

uint TraceDbManager::getFlowData(std::string traceName, int flowID,
		std::string field, uint& data)
{
	uint flowdata = 0;
	flowdata = m_db.max(field, "Flows", "Traces",
			"Traces.traceID=Flows.traceID", "", "",
			" (Traces.traceName=\"" + traceName + "\" AND Flows.flowID="
					+ std::to_string(flowID) + " )", flowdata);
	data = flowdata;
	return (flowdata);
}

int TraceDbManager::getFlowPktData(std::string traceName, int flowID,
		std::string field, std::list<int>& dataList)
{
	return (m_db.join(field, "Packets", "Flows",
			"(Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)",
			"Traces", "Traces.traceID=Flows.traceID",
			"(Flows.flowID=" + std::to_string(flowID)
					+ " AND Traces.traceName=\"" + traceName + "\" )", dataList));
}

int TraceDbManager::getFlowPktData(std::string traceName, int flowID,
		std::string field, std::list<uint>& dataList)
{
	return (m_db.join(field, "Packets", "Flows",
			"(Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)",
			"Traces", "Traces.traceID=Flows.traceID",
			"(Flows.flowID=" + std::to_string(flowID)
					+ " AND Traces.traceName=\"" + traceName + "\" )", dataList));
}

int TraceDbManager::getFlowPktData(std::string traceName, int flowID,
		std::string field, std::list<double>& dataList)
{
	return (m_db.join(field, "Packets", "Flows",
			"(Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)",
			"Traces", "Traces.traceID=Flows.traceID",
			"(Flows.flowID=" + std::to_string(flowID)
					+ " AND Traces.traceName=\"" + traceName + "\" )", dataList));
}

int TraceDbManager::getFlowPktData(std::string traceName, int flowID,
		std::string field, std::list<std::string>& dataList)
{
	return (m_db.join(field, "Packets", "Flows",
			"(Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)",
			"Traces", "Traces.traceID=Flows.traceID",
			"(Flows.flowID=" + std::to_string(flowID)
					+ " AND Traces.traceName=\"" + traceName + "\" )", dataList));
}

int TraceDbManager::check_if_trace_exists_or_not_empty(std::string traceName)
{
	std::string str_ret;
	m_db.max("traceID", "Traces", "", "", "", "",
			"traceName=\"" + traceName + "\"", str_ret);
	if (str_ret == "")
	{
		printf("");
	}
	return (0);
}
