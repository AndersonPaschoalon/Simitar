/*
 * ConstantsDeinition.h
 *
 *  Created on: 4 de jul de 2016
 *      Author: apaschoalon
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

#ifndef DEFINES_H_
#define DEFINES_H_

/**
 * Time scale enumeration used by NetworkFlow
 */
typedef enum
{
	milliseconds, seconds
} time_scale;


/**
 * Constants
 */
#define CHAR_SMALL_BUFFER 50
#define CHAR_BUFFER 120
#define CHAR_MEDIUM_BUFFER 500
#define CHAR_LARGE_BUFFER 1000
#define CHAR_HUGE_BUFFER 10000
#define MEGA_POWER 1000000
// version of XML Compact trace description
#define CDT_V2 1


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

const port_number MAX_TRANSPORT_PORT_NUMBER = 65535;

//const unsigned int MAX_TCP_PACKET_SIZE = 1518;
const unsigned int MAX_TCP_PACKET_SIZE = 1000;


#endif /* DEFINES_H_ */
