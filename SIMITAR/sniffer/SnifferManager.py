from Sniffer import Sniffer as Sniffer
from EasySqlite import Database
from termcolor import colored
import time
import logging


class SnifferManager:
    @staticmethod
    def new(database_name='trace.db', trace_name='trace-name', trace_type='live', target_name='eth0', comment='',
            live_timeout=10, verbose=True, logfile_path='.'):
        #logging.debug("database_name:, "+database_name+"trace_name:, "+trace_name+"trace_type:, "+trace_type+
        #              "target_name:, "+target_name+"comment:, "+comment+":, "+"live_timeout:, "+str(live_timeout)+
        #              "verbose:, "+str(verbose)+"logfile_path:, "+logfile_path)
        if trace_type != 'live' and trace_type != 'pcap':
            print(colored("Error: Invalid trace type argument: " + trace_type, 'red'))
            exit()
        # Create Database if not exists ################################################################################
        db = Database(database_name)
        db.query("""
            CREATE TABLE if not exists Traces (
                traceID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                traceName varchar NOT NULL UNIQUE,
                captureDate text NOT NULL,
                captureType varchar NOT NULL,
                captureTarget varchar NOT NULL,
                commentaries text NOT NULL
            );
        """)
        db.query("""
            CREATE TABLE if not exists Flows (
                flowID integer NOT NULL,
                protocolLink varchar NOT NULL,
                protocolNetwork varchar NOT NULL,
                protocolTransport varchar NOT NULL,
                macSrc varchar NOT NULL,
                macDst varchar NOT NULL,
                netSrc varchar NOT NULL,
                netDst varchar NOT NULL,
                portSrc integer NOT NULL,
                portDst integer NOT NULL,
                traceID integer NOT NULL,
                -- FK
                constraint flows_fk foreign key (traceID) references Traces(traceID),
                -- PK
                constraint flows_pk primary key (traceID, flowID)
            );
        """)
        db.query("""
            CREATE TABLE if not exists Packets (
                seq integer NOT NULL,
                arrivalTime varchar NOT NULL,
                pktSize integer NOT NULL,
                ttl integer NOT NULL,
                winSize integer NOT NULL,
                flowID integer NOT NULL,
                traceID integer NOT NULL,
                -- PK
                constraint packets_pk primary key (traceID, flowID, seq),
                -- FK
                constraint packets_fk foreign key (traceID, flowID) references Flows(traceID, flowID)
            );
        """)
        trace_columns = 'traceName, captureDate, captureType, captureTarget, commentaries'
        # Create trace new table #######################################################################################
        trace_data = [
            (trace_name, str(time.strftime("%H:%M:%S") + ", " + time.strftime("%d/%m/%Y")), trace_type, target_name,
             comment)]
        try:
            db.write(table='Traces', columns=trace_columns, data=trace_data)
        except:
            print( colored("Trace name " + trace_name + " already exist.", 'red') )
            print( colored("\tTry another name.", 'green'))
            db.close()
            exit()
        # Sniff packets ################################################################################################
        trace_id = db.get_where(table='Traces', thecolumns='traceID', where_clause='traceName="' + trace_name + '"')[0][
            0]
        theSniffer = Sniffer(captureMethod=trace_type, captureTarget=target_name, liveTimeout=live_timeout,
                             traceID=trace_id, logfile_path=logfile_path)
        theSniffer.start(verbose=verbose)
        # Save on database #############################################################################################
        db.write(table='Flows', columns=theSniffer.flows_properties_names(), data=theSniffer.listFlowsProperties())
        db.write(table='Packets', columns=theSniffer.packets_properties_names(),
                 data=theSniffer.listPacketsProperties())
        db.close()

    @staticmethod
    def rm(database_name='trace.db', trace_name='trace-name'):
        db = Database(database_name)
        is_id_int = False
        try:
            trace_id = \
                db.get_where(table='Traces', thecolumns='traceID', where_clause='traceName="' + trace_name + '"')[0][
                    0]
            is_id_int = isinstance(trace_id, int)
        except IndexError:  # there was no trace ID, do nothing was returned
            SnifferManager.__no_trace_error(trace_name)
            db.close()
            return

        if is_id_int:
            where_constraint = 'traceID=' + str(trace_id)
            db.delete(table='Traces', where=where_constraint)
            db.delete(table='Flows', where=where_constraint)
            db.delete(table='Packets', where=where_constraint)
            db.close()
        else:
            SnifferManager.__no_trace_error(trace_name)
            db.close()
            return

    @staticmethod
    def list(database_name='trace.db'):
        db = Database(database_name)
        #db.print_info('Traces')
        db.print_table('Traces')
        #db.print('Flows')
        # db.print('Packets')
        db.close()

    @staticmethod
    def __no_trace_error(trace_name):
        print( colored('Error: There is no trace called ' + trace_name + 'stored in the local database', 'red'))
        print( colored('\tTry: `sniffer-cli.py --list` to show all avaliable traces.', 'green'))


if __name__ == '__main__':
    # Debug options
    trace_name = 't10'
    # target_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
    target_name = 'wlp6s0'
    trace_type = 'live'
    # trace_type = 'pcap'
    live_timeout = 3
    rm_trace_name = 't1'
    #SnifferManager.new(database_name='trace.db', trace_name=trace_name, trace_type=trace_type, target_name=target_name,
    #                   live_timeout=live_timeout, verbose=True)
    #SnifferManager.rm(database_name='trace.db', trace_name=rm_trace_name)
    SnifferManager.list(database_name='trace.db')

    db = Database(database_name='trace.db')
    # npackets from a trace select max(seq) from Packets where traceId=1;
    # npackets from select max(flowId)+1 from Flows where traceID=1;

    db.cursor.execute('')
