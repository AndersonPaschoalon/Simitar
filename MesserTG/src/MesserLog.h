/*
 * MesserLog.h
 *
 *  Created on: 29 de abr de 2017
 *      Author: anderson
 */

#ifndef MESSERLOG_H_
#define MESSERLOG_H_

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PropertyConfigurator.hh>

/**
	FATAL -> the program cant run
	ALERT -> A serious bug
	CRIT -> It should not happen
	ERROR -> a predictable error, execution program is interrupted
	WARN -> an error, but it can run correctelly
	NOTICE -> crictical execution information
	INFO -> important execution information
	DEBUG -> trivial execution information
**/

/**
 * Log onfiguration file
 */
#define LOG_PROPERTIES_FILE "src/log4cpp-config.properties"

/**
 * Logfile has a global loglevel defined here
 */
#define LOGFILE_LOGLEVEL DEBUG

/**
 * Log module init
 */
#define MESSER_LOG_INIT(priority_console) log4cpp::PropertyConfigurator::configure(LOG_PROPERTIES_FILE);\
	log4cpp::Category& console__ = log4cpp::Category::getInstance("console");\
	log4cpp::Category& logfile__ = log4cpp::Category::getInstance("logfile");\
	logfile__.setPriority(log4cpp::Priority::LOGFILE_LOGLEVEL);\
	console__.setPriority(log4cpp::Priority::priority_console);\

/**
 * Console loglevel used by the the macro MESSER_LOG_START()
 */
#define GLOBAL_LOG_LEVEL ERROR

/**
 * Equivalent to MESSER_LOG_INIT(), but with no argument
 */
#define MESSER_LOG_START() MESSER_LOG_INIT(GLOBAL_LOG_LEVEL);

/**
 * Destructor macro of logs
 */
#define MESSER_LOG_END() log4cpp::Category::shutdown();


#define MESSER_NOTSET(fmt, args...) logfile__.notset(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.notset(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_DEBUG(fmt, args...) logfile__.debug(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.debug(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_INFO(fmt, args...) logfile__.info(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.info(fmt, __PRETTY_FUNCTION__ ,##args, __FILE__);\

#define MESSER_NOTICE(fmt, args...) logfile__.notice(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.notice(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_WARN(fmt, args...) logfile__.warn(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.warn(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_ERROR(fmt, args...) logfile__.error(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.error(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_CRIT(fmt, args...) logfile__.crit(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.crit(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_ALERT(fmt, args...) logfile__.alert(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.alert(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_FATAL(fmt, args...) logfile__.fatal(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.fatal(fmt, __PRETTY_FUNCTION__ ,##args);\

#define MESSER_EMERG(fmt, args...) logfile__.emerg(fmt, __PRETTY_FUNCTION__ ,##args);\
	console__.emerg(fmt, __PRETTY_FUNCTION__ ,##args);\




#endif /* MESSERLOG_H_ */
