###############################################################################
# All applications will work relative to this directory. It must be set as 
# the absolute path of the SIMITAR root directory
# This script must be run as:
# source data/config/simitar-workspace-config.sh
###############################################################################
export SIMITAR_WORKSPACE=`pwd`


###############################################################################
# Simitar log dir 
###############################################################################
export SIMITAR_LOG_DIR=${SIMITAR_WORKSPACE}'/data/log/'


###############################################################################
# Test data directory
###############################################################################
export SIMITAR_TEST_DATA_DIR=${SIMITAR_WORKSPACE}'/data/test/'


###############################################################################
# Compact Trace Descriptor XML directory
###############################################################################
export SIMITAR_CTD_XML_DIR=${SIMITAR_WORKSPACE}'/data/xml/'


###############################################################################
# Database version
###############################################################################
export SIMITAR_DATABASE_VERSION='2'

###############################################################################
# Database location and name (V1)
###############################################################################
export SIMITAR_DATABASE_V1=${SIMITAR_WORKSPACE}'/data/db/trace_v1.db'


###############################################################################
# Database location and name (V2)
###############################################################################
#export SIMITAR_DATABASE_V2=${SIMITAR_WORKSPACE}'/data/db/trace.db'
export SIMITAR_DATABASE_V2=${SIMITAR_WORKSPACE}'/data/db/trace2.db'


###############################################################################
# Current Database version
###############################################################################
export SIMITAR_DATABASE=${SIMITAR_DATABASE_V2}


###############################################################################
# Simitar logfile 
###############################################################################
export SIMITAR_LOGFILE=${SIMITAR_LOG_DIR}'simitar.log'


###############################################################################
# Test database
###############################################################################
export SIMITAR_TEST_DATABASE=${SIMITAR_TEST_DATA_DIR}'regressiontests_trace.db'


###############################################################################
# Test IP and MAC file
###############################################################################
export SIMITAR_TEST_IPMAC=${SIMITAR_TEST_DATA_DIR}'ipmac.csv'


###############################################################################
# Test XML CTD default file
###############################################################################
export SIMITAR_TEST_CTD_XML=${SIMITAR_TEST_DATA_DIR}'test-trace.xml'


###############################################################################
# Test copy of XML CTD default file 
###############################################################################
export SIMITAR_TEST_COPY_CTD_XML=${SIMITAR_TEST_DATA_DIR}'copy-test-trace.xml'


###############################################################################
# Test copy of XML CTD default file 
###############################################################################
export SIMITAR_TEST_COPY2_CTD_XML=${SIMITAR_TEST_DATA_DIR}'copy2-test-trace.xml'


###############################################################################
# Interarrival times following exponential distribution
###############################################################################
export SIMITAR_TEST_EXPONENTIAL_TIMES=${SIMITAR_TEST_DATA_DIR}'exp_interarrival_times.txt'


###############################################################################
# Interarrival times following a uniform distribution
###############################################################################
export SIMITAR_TEST_UNIFORM_TIMES=${SIMITAR_TEST_DATA_DIR}'rand_interarrival_times.txt'


###############################################################################
# Changed IPs and MACs Compact Trace Descriptor XML
###############################################################################
export SIMITAR_TEST_CTD_XML_IPMAC=${SIMITAR_TEST_DATA_DIR}'changed-ips-macs-trace.xml'


###############################################################################
# Current version tag
###############################################################################
export SIMITAR_VERSION_TAG='v0.3.3'


###############################################################################
# Current version name
###############################################################################
export SIMITAR_VERSION_NAME='Eulemur fulvus'


###############################################################################
# Lybrary dependencies
###############################################################################
export SIMITAR_LIBS_DEPS='armadillo ITG sqlite3 libboost libblas liblapack openblas sctp log4cpp'


###############################################################################
# Tools dependencies
###############################################################################
export SIMITAR_TOOLS_DEPS='tshark wireshark octave sqlite3 cmake iperf ostinato'


###############################################################################
# Python packages dependencies
###############################################################################
export SIMITAR_PYPACKAGES_DEPS='sqlite3 pyshark rstr numpy fnvhash termcolor'





