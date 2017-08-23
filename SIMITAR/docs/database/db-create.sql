CREATE TABLE if not exists Traces (
    traceID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    traceName varchar NOT NULL UNIQUE,
    captureDate text NOT NULL,
    captureType varchar NOT NULL,
    captureTarget varchar NOT NULL,
    commentaries text NOT NULL
);
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

