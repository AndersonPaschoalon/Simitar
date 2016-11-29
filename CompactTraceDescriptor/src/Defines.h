/*
 * ConstantsDeinition.h
 *
 *  Created on: 4 de jul de 2016
 *      Author: apaschoalon
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
//Math
#define MEGA_POWER 1000000

//Stochastic Models
#define WEIBULL "weibull"
#define NORMAL "normal"
#define EXPONENTIAL_MEAN "exponential-mean"
#define EXPONENTIAL_LINEAR_REGRESSION "exponential-linear-regression"
#define PARETO_LINEAR_REGRESSION "pareto-linear-regression"
#define PARETO_MAXIMUM_LIKEHOOD "pareto-maximum-likehood"
#define CAUCHY "cauchy"
#define CONSTANT  "constant"
#define NO_MODEL "no-model-selected"

// Debug defines
//#define DEBUG 1 // basic debug
//#define DEBUG_DataProcessor_calculate_loop 1
//#define DEBUG_DataProcessor_calculate 1
//#define DEBUG_NetworkFlow 1
//#define DEBUG_flowThread 1
//#define DEBUG_DatabaseInterface 1
//#define DEBUG_NetworkTrace_exec 1
#define DEBUG_DataProcessor_interArrival 1

//Misc
#define TEST_FUNCTIONS 1 //execute regression testes
#define HLINE "----------"
#define TAB "::"

/*******************************************************************************
 * Types
 ******************************************************************************/
typedef unsigned short int protocol;
typedef unsigned short int protocol_code;
typedef unsigned short int stochastic_model;
typedef unsigned int port_number;

/*******************************************************************************
 * Constants
 ******************************************************************************/
//packet analysis features
const double FILE_CUT_TIME = 0.1;
const double SESSION_CUT_TIME = 30;
const int PACKET_SIZE_MODE_CUT_VALUE = 500;

//protocols
const protocol PROTOCOL__NULL = 0;
const protocol PROTOCOL__ETHERNET = 1;
const protocol PROTOCOL__IPV4 = 2;
const protocol PROTOCOL__IPV6 = 3;
const protocol PROTOCOL__ARP = 4;
const protocol PROTOCOL__ICMP = 5;
const protocol PROTOCOL__ICMPV6 = 6;
const protocol PROTOCOL__TCP = 7;
const protocol PROTOCOL__UDP = 8;
const protocol PROTOCOL__DCCP = 9;
const protocol PROTOCOL__GRE = 10;
const protocol PROTOCOL__SCTP = 11;
const protocol PROTOCOL__HTTP = 12;
const protocol PROTOCOL__HTML = 13;
const protocol PROTOCOL__SMTP = 14;

//Protocol code
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

//Port number
const port_number MAX_TRANSPORT_PORT_NUMBER = 65535;

#endif /* DEFINES_H_ */
