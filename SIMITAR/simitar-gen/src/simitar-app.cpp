#include <iostream>
#include <string>
#include <algorithm>
#include <tclap/CmdLine.h>
#include <PlogMacros.h>
#include <NetworkTrace.h>
#include <DummyFlow.h>
#include <Defines.h>
#include <Protocol.h>
#include <SimitarWorkspace.h>

/**
 * Print an error message if the input argument is an invalid balue
 * @param arg input CLI argument
 * @param arg_name argument name
 * @param expected_values message with expected values
 */
void cli_error_messege(std::string arg, std::string arg_name,
		std::string expected_values_msg);

/**
 * Check if the CLI input argument is a valid value
 * @param val input CLI argument.
 * @param expectedVals vector with valid CLI arguments.
 * @return
 */
bool cli_check_val(std::string val, std::vector<std::string> expectedVals);

/**
 * Erros list:
 *  #-1: invalid mode (client/server)
 *  #-2: exception parsing commandline
 */
int main(int argc, char** argv)
{
	/// Modes
    ///none = 0,   //!< none
    ///fatal = 1,  //!< fatal: error, program cant continue and is terminated
    ///error = 2,  //!< error: error, but can still run
    ///warning = 3,//!< warning: strange state, probably error, but can still run
    ///info = 4,   //!< info: execution important info
    ///debug = 5,  //!< debug: used for debug
    ///verbose = 6 //!< verbose: just keep track of what is being done
	PLOG_INIT(warning);
	try
	{
		///
		/// CLI parser
		///

		// program description
		char progDescription[] = "SIMITAR dummy-flow component.";
		// version information
		char version[CHAR_BUFFER];
		SimitarWorkspace workspace = SimitarWorkspace();
		std::string str_version = workspace.version_tag() + ":"
				+ workspace.version_name();
		strcpy(version, str_version.c_str());

		// comamnd line parsing
		TCLAP::CmdLine cmd(progDescription, ' ', version);
		TCLAP::ValueArg<std::string> mode_arg("m", "mode",
				"Operation mode, as a client or a server", false, "client",
				"string");
		TCLAP::ValueArg<std::string> tool_arg("t", "tool",
				"Tool used to generate the traffic", true, "", "string");
		TCLAP::ValueArg<std::string> in_arg("x", "xml",
				"Compact Trace Descriptor XML. They are salved at data/xml/ directory.",
				true, "", "string");
		TCLAP::ValueArg<std::string> dst_list_arg("d", "dst-list-ip",
				"Text file in CSV format containing a list of desired destinations of IP and MAC adresses, used as servers, in the client mode. These destinations are addressed to the flows in a ring-oriented way.",
				false, "", "string");
		TCLAP::ValueArg<std::string> dst_server_arg("p", "dst-ip",
				"Instead of a textfile, defines a single server destination IP address in the command line.",
				false, "", "string");
		TCLAP::ValueArg<std::string> eth_arg("e", "ether",
				"Ethernet interface to send the traffic, as provided by the command `ifconfig`.",
				true, "", "string");

		cmd.add(mode_arg);
		cmd.add(tool_arg);
		cmd.add(in_arg);
		cmd.add(dst_list_arg);
		cmd.add(dst_server_arg);
		cmd.add(eth_arg);

		cmd.parse(argc, argv);

		std::string mode = mode_arg.getValue();
		std::string tool = tool_arg.getValue();
		std::string input_xml = in_arg.getValue();
		std::string dst_list_file = dst_list_arg.getValue();
		std::string dst_ip_str = dst_server_arg.getValue();
		std::string eth_interface = eth_arg.getValue();
		bool flag_dst_list_file = (dst_list_file == "") ? false : true;
		bool flag_dst_ip_str = (dst_ip_str == "") ? false : true;

		if (!cli_check_val(mode,
		{ "client", "server" }))
		{
			cli_error_messege(mode, "mode", "client, server");
			exit(ERROR_INVALID_ASSIGNMENT);
		}

		///
		/// Actual execution
		///

		if (!cli_check_val(tool,
		{ "dummy", "iperf", "ditg", "tins", "libtins", "ostinato" }))
		{
			cli_error_messege(tool, "tool",
					"dummy, iperf, ditg, tins, libtins, ostinato");
			exit(ERROR_INVALID_ASSIGNMENT);
		}

		NetworkTrace traceCdt = NetworkTrace(input_xml, tool);

		// change IPs if --dst-list-ip or --dst-ip options are provided
		if (flag_dst_list_file == true)
		{
			PLOG_DEBUG << "traceCdt.clientServerIps(" << dst_list_file.c_str()
								<< ", " << eth_interface.c_str() << ")";

			traceCdt.clientServerIps(dst_list_file.c_str(),
					eth_interface.c_str(), true);
		}
		else if (flag_dst_ip_str == true)
		{
			PLOG_DEBUG << "traceCdt.clientServerIps(" << dst_ip_str.c_str()
								<< ", " << eth_interface.c_str() << ")";

			traceCdt.clientServerIps(dst_ip_str.c_str(), "",
					eth_interface.c_str());
		}

		if (mode == "server")
		{
			PLOG_VERBOSE << " execution of traceCdt.server()";
			traceCdt.server(eth_interface);
		}
		else
		{
			PLOG_VERBOSE << " execution of traceCdt.exec()";
			traceCdt.exec(eth_interface);
		}

	} catch (TCLAP::ArgException &e)  // catch any exceptions
	{
		PLOG_ERROR << ERRORMSG_INVALID_ASSIGNMENT << "dummy-flow Error: "
							<< e.error() << " for arg " << e.argId()
							<< std::endl;
		exit(ERROR_INVALID_ASSIGNMENT);
	}

	return (0);
}

void cli_error_messege(std::string arg, std::string arg_name,
		std::string expected_values_msg)
{
	PLOG_ERROR << ERRORMSG_INVALID_ASSIGNMENT
						<< "trace-analyzer Error: invalid argument " << arg
						<< " for " << arg_name << ". Expected "
						<< expected_values_msg << ". Use --help for help.";
}

bool cli_check_val(std::string val, std::vector<std::string> expectedVals)
{
	uint m = expectedVals.size();

	for (uint i = 0; i < m; i++)
		if (val == expectedVals[i])
			return (true);

	return (false);
}

