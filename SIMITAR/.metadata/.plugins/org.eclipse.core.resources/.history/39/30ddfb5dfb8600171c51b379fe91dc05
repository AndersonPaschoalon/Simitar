/*
 * TraceDbManager.h
 *
 *  Created on: 28 de jul de 2017
 *      Author: anderson
 */

#ifndef TRACEDBMANAGER_H_
#define TRACEDBMANAGER_H_

#include <string>
#include <string.h>
#include <list>

#include "DatabaseSqlite3.h"

/**
TODO 1: CHECHAR SE O TRACE EXISTE, SE NÃO SAIR COM MENSAGEM DE ERRO
TODO 2: CHECAR SE FLOWS DO TRACE EXISTEM, SE NÃO SAIR COM MENSAGEM DE ERRO
TODO 3: CHECAR SE AS LISTAS ESTÃO VAZIS ANTES DE USALAS. SE ISSO OCORRER É UM BUG, REPORTAR
 */

/**
 Algumas queries que podem ser uteis
 SELECT Packets.seq, Packets.traceID, Packets.flowID FROM Packets
 	 INNER JOIN Flows ON (Flows.flowID=Packets.flowID) AND (Flows.traceID=Packets.traceID)
 	 INNER JOIN Traces ON Traces.traceID=Flows.traceID
 WHERE (Flows.flowID=0 AND Traces.traceName="arboc" );

 -- query para pegar a lista de protocolos do trace arboc
SELECT 	protocolNetwork FROM Flows
	INNER JOIN Traces ON Traces.traceID=Flows.traceID
WHERE traceName="arboc";

-- query para pegar o protocolo de rede to trace "arboc" do flow 1
SELECT 	protocolNetwork FROM Flows INNER JOIN Traces ON Traces.traceID=Flows.traceID WHERE traceName="arboc" AND flowID=1;


 */


class TraceDbManager
{
public:

	/**
	 * Constructor of the Trace database manager.
	 * It retrieve requested data form the database.
	 */
	TraceDbManager(std::string databaseFile);

	/**
	 * Destructor.
	 */
	virtual ~TraceDbManager();

	/**
	 *
	 * @param traceName
	 * @param field
	 * @param data
	 * @return
	 */
	std::string getTraceData(std::string traceName, std::string field,
			std::string& data);

	/**
	 *
	 * @param traceName
	 * @param field
	 * @param data
	 * @return
	 */
	int getTraceData(std::string traceName, std::string field, int& data);

	/**
	 *
	 * @param traceName
	 * @param field
	 * @param data
	 */
	uint getNumberOfFlows(std::string traceName);

	/**
	 *
	 * @param traceName
	 * @param flowID
	 * @param field
	 * @param data
	 * @return
	 */
	std::string getFlowData(std::string traceName, int flowID,
			std::string field, std::string& data);

	/**
	 *
	 * @param traceName
	 * @param flowID
	 * @param field
	 * @param data
	 * @return
	 */
	int getFlowData(std::string traceName, int flowID,
			std::string field, int& data);

	/**
	 *
	 * @param traceName
	 * @param flowID
	 * @param field
	 * @param dataList
	 * @return
	 */
	int getFlowPktData(std::string traceName, int flowID,
			std::string field, std::list<int>& dataList);

	/**
	 *
	 * @param traceName
	 * @param flowID
	 * @param field
	 * @param dataList
	 * @return
	 */
	int getFlowPktData(std::string traceName, int flowID,
			std::string field, std::list<double>& dataList);

	/**
	 *
	 * @param traceName
	 * @param flowID
	 * @param field
	 * @param dataList
	 * @return
	 */
	int getFlowPktData(std::string traceName, int flowID,
			std::string field, std::list<std::string>& dataList);
private:

	// members

	DatabaseSqlite3 m_db;
	std::string flowTable = "Flows";
	std::string traceTable = "Traces";
	std::string packetTable = "Packets";

	// private methods
	int check_if_trace_exists_or_not_empty(std::string traceName);


};



#endif /* TRACEDBMANAGER_H_ */
