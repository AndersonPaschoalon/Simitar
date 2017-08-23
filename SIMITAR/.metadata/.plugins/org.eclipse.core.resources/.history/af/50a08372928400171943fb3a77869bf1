/*
 * ConstantsDeinition.h
 *
 *  Created on: 4 de jul de 2016
 *      Author: apaschoalon
 */

#ifndef DEFINES_H_
#define DEFINES_H_
//#include <string>
using namespace std;

#include <plog/Init.h>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>

/**
Alguns tutoriais importantes:
Select ao inves de sleep:
http://stackoverflow.com/questions/3125645/why-use-select-instead-of-sleep
Current time thread safe:
http://stackoverflow.com/questions/3220224/is-the-gettimeofday-function-thread-safe-in-linux
http://stackoverflow.com/questions/18348383/time-related-functions-and-multiple-threads
http://stackoverflow.com/questions/10894504/is-there-any-stdchrono-thread-safety-guaranty-even-with-multicore-context
http://stackoverflow.com/questions/3220224/is-the-gettimeofday-function-thread-safe-in-linux
http://en.cppreference.com/w/cpp/chrono/system_clock/now
 */

#define DEBUG_NetworkTrace_writeToFile 1

/**
 * Length of a standard C string vector
 */
#define CHAR_SMALL_BUFFER 50
#define CHAR_BUFFER 120
#define CHAR_MEDIUM_BUFFER 500
#define CHAR_LARGE_BUFFER 1000
#define CHAR_HUGE_BUFFER 10000

/**
 * Macro for  \f$ 10^6 \f$.
 */
#define MEGA_POWER 1000000


/**
 * Port number type
 */
typedef unsigned int port_number;

/**
 * Time to live type
 */
typedef unsigned short int ttl_val;

/**
 * Time type
 */
typedef double time_sec;

/**
 * Packet size type
 */
typedef double packet_size;

/**
 * Kbytes type
 */
typedef long int kbytes;

/**
 * Counter type
 */
typedef unsigned int counter;


/**
 *
 */
const time_sec DEFAULT_FILE_CUT_TIME = 0.1;

/**
 *
 */
const time_sec DEFAULT_SESSION_CUT_TIME = 30;

/**
 * Cut value for packet size modes distributions. A value smaller than
 * PACKET_SIZE_MODE_CUT_VALUE belongs to the first mode, and a larger to the
 * second mode.
 */
const int PACKET_SIZE_MODE_CUT_VALUE = 500;

/**
 * Max valid value for a port number
 */
const port_number MAX_TRANSPORT_PORT_NUMBER = 65535;

// FATAL -> the program cant run
// ALERT -> A serious bug
// CRIT -> It should not happen
// ERROR -> a predictable error, execution program is interrupted
// WARN -> an error, but it can run correctelly
// NOTICE -> crictical execution information
// INFO -> important execution information
// DEBUG -> trivial execution information

//#define NO_MODEL "no-model-selected"
// Debug defines
//#define DEBUG 1 // basic debug
//#define DEBUG_DataProcessor_calculate_loop 1
//#define DEBUG_DataProcessor_calculate 1
//#define DEBUG_NetworkFlow 1
//#define DEBUG_flowThread 1
//#define DEBUG_DatabaseInterface 1
//#define DEBUG_NetworkTrace_exec 1
//#define DEBUG_DataProcessor_interArrival 1
//#define DEBUG_StochasticModelFit 1
//#define DEBUG_DummyFlow 1

//Misc
//#define TEST_FUNCTIONS 1 //execute regression testes
//#define HLINE "----------"
//#define TAB "::"

/*******************************************************************************
 * Defines
 ******************************************************************************/



//Math

//Stochastic Models
/*
 #define WEIBULL "weibull"
 #define NORMAL "normal"
 #define EXPONENTIAL "exponential"
 #define EXPONENTIAL_MEAN "exponential-mean"
 #define EXPONENTIAL_MEAN "exponential"
 #define EXPONENTIAL_LINEAR_REGRESSION "exponential-linear-regression"
 #define EXPONENTIAL_LINEAR_REGRESSION "exponential"
 #define PARETO "pareto"
 #define PARETO_LINEAR_REGRESSION "pareto-linear-regression"
 #define PARETO_MAXIMUM_LIKEHOOD "pareto-maximum-likehood"
 #define CAUCHY "cauchy"
 #define CONSTANT  "constant"
 */
//test
/*
 const string WEIBULL = "weibull";
 const string NORMAL = "normal";
 const string EXPONENTIAL_MEAN = "exponential";
 const string EXPONENTIAL_LINEAR_REGRESSION = "exponential";
 const string EXPONENTIAL = "exponential";
 const string PARETO_LINEAR_REGRESSION = "pareto";
 const string PARETO_MAXIMUM_LIKEHOOD = "pareto";
 const string PARETO = "pareto";
 const string CAUCHY = "cauchy";
 const string CONSTANT = "constant";
 const string NO_MODEL = "no-model-selected";
 */
/**
 *
 */
//test
//#define NUMBER_OF_MODELS 8
/**
 *
 */
/*
typedef enum stochastic_functions_enum
{
	WEIBULL,                      //!< WEIBULL
	NORMAL,                       //!< NORMAL
	EXPONENTIAL,                  //!< EXPONENTIAL
	EXPONENTIAL_MEAN,             //!< EXPONENTIAL_MEAN
	EXPONENTIAL_LINEAR_REGRESSION,            //!< EXPONENTIAL_LINEAR_REGRESSION
	PARETO,                       //!< PARETO
	PARETO_LINEAR_REGRESSION,     //!< PARETO_LINEAR_REGRESSION
	PARETO_MAXIMUM_LIKEHOOD,      //!< PARETO_MAXIMUM_LIKEHOOD
	CAUCHY,                       //!< CAUCHY
	CONSTANT,                     //!< CONSTANT
	SINGLE_PACKET,                //!< SINGLE_PACKET
	NO_MODEL                      //!< NO_MODEL
} stochastic_functions;
*/
/**
 *
 */
/*
typedef enum information_criterion_enum
{
	AIC, BIC
} information_criterion;
*/
/*
 * TODO
 * The data obeys a Constant distribution (regular time intervals), equal to
 * the max of the original data value
 */
//#define CONSTANT_MAX "constant-max"

/*
 * TODO
 * The data obeys a Constant distribution (regular time intervals), equal to
 * the minimum of the original data value
 */
//#define CONSTANT_MIN "constant-min"

/**
 * No model selected, this means there is no data to evaluate any stochastic
 * model. In case on interarrival that means that there are just a packet,
 * file or session to be executed. In case of packet size this means that
 * there isn't any packet on that mode
 */

/*******************************************************************************
 * Types
 ******************************************************************************/

/**
 *
 */
/*
 enum protocol_enum
 {
 PROTOCOL__NULL,    //!< PROTOCOL__NULL
 // Link layer protocols
 PROTOCOL__ETHERNET,    //!< PROTOCOL__ETHERNET
 //Network layer protocols
 PROTOCOL__IPV4,    //!< PROTOCOL__IPV4
 PROTOCOL__IPV6,    //!< PROTOCOL__IPV6
 PROTOCOL__ARP,     //!< PROTOCOL__ARP
 PROTOCOL__ICMP,    //!< PROTOCOL__ICMP
 PROTOCOL__ICMPV6,  //!< PROTOCOL__ICMPV6
 // Transport layer protocols
 PROTOCOL__TCP,     //!< PROTOCOL__TCP
 PROTOCOL__UDP,     //!< PROTOCOL__UDP
 PROTOCOL__DCCP,    //!< PROTOCOL__DCCP
 PROTOCOL__GRE,     //!< PROTOCOL__GRE
 PROTOCOL__SCTP,    //!< PROTOCOL__SCTP
 // Application layer protocols
 PROTOCOL__HTTP,    //!< ok
 PROTOCOL__HTTPS,   //!< ok
 PROTOCOL__SNMP,    //!< PROTOCOL__SMTP
 PROTOCOL__SMTP,    //!< PROTOCOL__SMTP
 PROTOCOL__FTP,     //!< ok
 PROTOCOL__BGP,     //!< ok
 PROTOCOL__DHCP,    //!< ok
 PROTOCOL__DNS,     //!< ok
 PROTOCOL__SSH,     //!< ok
 PROTOCOL__Telnet,  //!< ok
 PROTOCOL__TACACS  //!< ok

 };
 */

/**
 *
 */
//typedef protocol_enum protocol;
/**
 *
 */

/**
 *
 */
//typedef unsigned short int protocol_code;
/**
 *
 */
//typedef unsigned short int stochastic_model;



/*******************************************************************************
 * Constants
 ******************************************************************************/



/*

 const protocol_code IPV4_CODE = 2048;


 const protocol_code ARP_CODE = 2054;


 const protocol_code ARP_CODE_REV = 2056;


 const protocol_code IPV6_CODE = 34525;


 const protocol_code ICMP_CODE = 1;


 const protocol_code TCP_CODE = 6;


 const protocol_code UDP_CODE = 17;


 const protocol_code DCCP_CODE = 33;


 const protocol_code GRE_CODE = 47;


 const protocol_code ICMPV6_CODE = 58;


 const protocol_code SCTP_CODE = 132;

 */


// Log macros
#define PLOG_INIT() plog::RollingFileAppender<plog::CsvFormatter> fileAppender("MultiAppender.csv", 8000, 3); \
		plog::ColorConsoleAppender<plog::TxtFormatter> colorConsoleAppender; \
		plog::init(plog::debug, &colorConsoleAppender).addAppender(&fileAppender);

#define PLOG_CONF(LogFileName, LogFileMaxSize, NLogFiles) plog::RollingFileAppender<plog::CsvFormatter> fileAppender(LogFileName, LogFileMaxSize, NLogFiles); \
		plog::ColorConsoleAppender<plog::TxtFormatter> colorConsoleAppender; \
		plog::init(plog::debug, &colorConsoleAppender).addAppender(&fileAppender);

#define PLOG_NONE LOG_NONE  << "[" << __FILE__ << "] "
#define PLOG_FATAL LOG_FATAL  << "[" << __FILE__ << "] "
#define PLOG_ERROR LOG_ERROR  << "[" << __FILE__ << "] "
#define PLOG_WARN LOG_WARNING  << "[" << __FILE__ << "] "
#define PLOG_INFO LOG_INFO  << "[" << __FILE__ << "] "
#define PLOG_DEBUG LOG_DEBUG  << "[" << __FILE__ << "] "
#define PLOG_VERBOSE LOG_VERBOSE  << "[" << __FILE__ << "] "



#endif /* DEFINES_H_ */
