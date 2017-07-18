from Sniffer import Sniffer
from EasySqlite import Database
from TrafficRepr import Trace
import time


class SnifferManager:
    @staticmethod
    def new(database_name='trace.db', trace_name='trace-name', trace_type='live', target_name='eth0', comment='',
            live_timeout=10, verbose=True):
        #######################################################################
        # Create Database if not exists
        #######################################################################
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
        # 'traceName, captureDate, captureType, commentaries'
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

        # Debug options
        # trace_name = 't1'
        # target_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
        # target_name = 'enp3s0'
        # trace_type = 'live'
        # trace_type = 'pcap'
        # live_timeout = 10

        #######################################################################
        # Create trace new table
        #######################################################################
        trace_data = [
            (trace_name, str(time.strftime("%H:%M:%S") + ", " + time.strftime("%d/%m/%Y")), trace_type, target_name,
             comment)]
        # record new trace
        try:
            db.write(table='Traces', columns=trace_columns, data=trace_data)
        except:
            print("Trace name " + trace_name + " already exist. Try another.")
            # trace_id = db.get_where(table='Traces', thecolumns='traceID', where_clause='traceName="' + trace_name + '"')
            # print(trace_id)
            db.close()
            exit()

        #######################################################################
        # Sniff packets
        #######################################################################
        trace_id = db.get_where(table='Traces', thecolumns='traceID', where_clause='traceName="' + trace_name + '"')[0][
            0]

        if trace_type == 'live':
            theSniffer = Sniffer(captureMethod='live', captureTarget=target_name, liveTimeout=live_timeout,
                                 traceID=trace_id)
        elif trace_type == 'pcap':
            theSniffer = Sniffer(captureMethod='pcap', captureTarget=target_name, traceID=trace_id)
        else:
            print("Invalid trace type argument: " + trace_type)

        # start capture
        theSniffer.start(verbose=verbose)

        #######################################################################
        # Save on database
        #######################################################################
        # Create flow table
        db.write(table='Flows', columns=theSniffer.flows_properties_names(), data=theSniffer.listFlowsProperties())

        # create packet table
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
        db.print('Traces')
        # db.print('Flows')
        # db.print('Packets')
        db.close()

    @staticmethod
    def __no_trace_error(trace_name):
        print("There is no trace called " + trace_name + " stored in the local database")
        print("Try: `sniffer-cli.py --list` to show all avaliable traces.")


if __name__ == '__main__':
    # Debug options
    trace_name = 't10'
    # target_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
    target_name = 'enp3s0'
    trace_type = 'live'
    # trace_type = 'pcap'
    live_timeout = 10
    rm_trace_name = 't1'
    SnifferManager.new(database_name='trace.db', trace_name=trace_name, trace_type=trace_type, target_name=target_name,
                       live_timeout=live_timeout, verbose=False)
    SnifferManager.rm(database_name='trace.db', trace_name=rm_trace_name)
    SnifferManager.list(database_name='trace.db')
