/*
 * Protocol.h
 *
 *  Created on: 5 de abr de 2017
 *      Author: anderson
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#include <string.h>
#include <iostream>

//#include "Defines.h"
#include "RegressionTests.h"
//#include "MesserLog.h"
//#define LOG_LEVEL INFO
#define LOG_LEVEL INFO
#define PROTOCOL_STR_SIZE 15

enum protocol_enum
{
	PROTOCOL__NULL,    //!< No valid protocol setted
	// Link layer protocols
	PROTOCOL__ETHERNET,    //!< Ethernet protocol
	//Network layer protocols
	PROTOCOL__IPV4,    //!< IPv4 network protocol
	PROTOCOL__IPV6,    //!< IPv6 network protocol
	PROTOCOL__ARP,     //!< ARP protocol
	PROTOCOL__ICMP,    //!< ICMP network protocol
	PROTOCOL__ICMPV6,  //!< ICMPv6 network protocol
	// Transport layer protocols
	PROTOCOL__TCP,     //!< TCP transport protocol
	PROTOCOL__UDP,     //!< UDP transport protocol
	PROTOCOL__DCCP,    //!< DCCP protocol
	PROTOCOL__GRE,     //!< GRE protocol
	PROTOCOL__SCTP,    //!< SCTP protocol
	// Application layer protocols
	PROTOCOL__HTTP,    //!< HTTP application protocol
	PROTOCOL__HTTPS,   //!< HTTPS application protocol
	PROTOCOL__SNMP,    //!< SNMP application protocol
	PROTOCOL__SMTP,    //!< SMTP application protocol
	PROTOCOL__FTP,     //!< FTP application protocol
	PROTOCOL__BGP,     //!< BGP protocol
	PROTOCOL__DHCP,    //!< DHCP application protocol
	PROTOCOL__DNS,     //!< DNS application protocol
	PROTOCOL__SSH,     //!< SSH application protocol
	PROTOCOL__Telnet,  //!< Telnet application protocol
	PROTOCOL__TACACS  //!< TACACS application protocol

};

typedef protocol_enum protocol;

typedef unsigned short int protocol_code;

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

const char STR__ARP[] = "ARP";
const char STR__BGP[] = "BGP";
const char STR__DCCP[] = "DCCP";
const char STR__DHCP[] = "DHCP";
const char STR__DNS[] = "DNS";
const char STR__ETHERNET[] = "ETHERNET";
const char STR__FTP[] = "FTP";
const char STR__GRE[] = "GRE";
const char STR__HTTP[] = "HTTP";
const char STR__HTTPS[] = "HTTPS";
const char STR__ICMP[] = "ICMP";
const char STR__ICMPV6[] = "ICMPV6";
const char STR__IPV4[] = "IPV4";
const char STR__IPV6[] = "IPV6";
const char STR__SCTP[] = "SCTP";
const char STR__SMTP[] = "SMTP";
const char STR__SNMP[] = "SNMP";
const char STR__SSH[] = "SSH";
const char STR__TACACS[] = "TACACS";
const char STR__TCP[] = "TCP";
const char STR__Telnet[] = "Telnet";
const char STR__UDP[] = "UDP";
const char STR__NULL[] = "NULL";

class Protocol
{
public:
	/**
	 * @brief Default constructor
	 */
	Protocol()
	{
		m_prot = PROTOCOL__NULL;
	}

	/**
	 * @brief Destructor
	 */
	virtual ~Protocol()
	{
	}

	Protocol(const protocol& proto)
	{
		m_prot = proto;
	}
	Protocol(const char* proto)
	{
		m_prot = cstr2protocol(proto);
	}
	Protocol(const protocol_code& pcode)
	{
		m_prot = code2protocol(pcode);
	}
	Protocol& operator=(const Protocol& rhs) noexcept
	{
		//MESSER_LOG_INIT(LOG_LEVEL);

		if (this != &rhs)
		{
			m_prot = rhs.m_prot;
		}
		else
		{
			//MESSER_ALERT(
			//		"Attempted assignment of a StochasticModelFit object to itself :: m_prot=%d  @<%s, %s>",
			//		m_prot);
			std::cerr
					<< "Attempted assignment of a StochasticModelFit object to itself"
					<< std::endl;

		}

		//MESSER_LOG_END();
		return (*this);
	}

	protocol get()
	{
		return (m_prot);
	}
	void get(char* vetc) const
	{
		protocol2cstr(m_prot, vetc);
	}

	void print()
	{
		std::cout << str() << std::endl;
	}

	string str()
	{
		char cstr[20];
		protocol2cstr(m_prot, cstr);
		return (string(cstr));
	}

	void regression_tests()
	{
		RegressionTests rt = RegressionTests();

		rt.printHeader("class Protocol");
		rt.printTestResult("Get Protocol", test_get_protocol());
		rt.printTestResult("Get Protocol Char", test_get_char());

	}

private:
	protocol m_prot;

	void protocol2cstr(const protocol& proto, char* cstr_proto) const
	{

		if (proto == PROTOCOL__ARP)
		{
			strcpy(cstr_proto, STR__ARP);
		}
		else if (proto == PROTOCOL__BGP)
		{
			strcpy(cstr_proto, STR__BGP);
		}
		else if (proto == PROTOCOL__DCCP)
		{
			strcpy(cstr_proto, STR__DCCP);
		}
		else if (proto == PROTOCOL__DHCP)
		{
			strcpy(cstr_proto, STR__DHCP);
		}
		else if (proto == PROTOCOL__DNS)
		{
			strcpy(cstr_proto, STR__DNS);
		}
		else if (proto == PROTOCOL__ETHERNET)
		{
			strcpy(cstr_proto, STR__ETHERNET);
		}
		else if (proto == PROTOCOL__FTP)
		{
			strcpy(cstr_proto, STR__FTP);
		}
		else if (proto == PROTOCOL__GRE)
		{
			strcpy(cstr_proto, STR__GRE);
		}
		else if (proto == PROTOCOL__HTTP)
		{
			strcpy(cstr_proto, STR__HTTP);
		}
		else if (proto == PROTOCOL__HTTPS)
		{
			strcpy(cstr_proto, STR__HTTPS);
		}
		else if (proto == PROTOCOL__ICMP)
		{
			strcpy(cstr_proto, STR__ICMP);
		}
		else if (proto == PROTOCOL__ICMPV6)
		{
			strcpy(cstr_proto, STR__ICMPV6);
		}
		else if (proto == PROTOCOL__IPV4)
		{
			strcpy(cstr_proto, STR__IPV4);
		}
		else if (proto == PROTOCOL__IPV6)
		{
			strcpy(cstr_proto, STR__IPV6);
		}
		else if (proto == PROTOCOL__SCTP)
		{
			strcpy(cstr_proto, STR__SCTP);
		}
		else if (proto == PROTOCOL__SMTP)
		{
			strcpy(cstr_proto, STR__SMTP);
		}
		else if (proto == PROTOCOL__SNMP)
		{
			strcpy(cstr_proto, STR__SNMP);
		}
		else if (proto == PROTOCOL__SSH)
		{
			strcpy(cstr_proto, STR__SSH);
		}
		else if (proto == PROTOCOL__TACACS)
		{
			strcpy(cstr_proto, STR__TACACS);
		}
		else if (proto == PROTOCOL__TCP)
		{
			strcpy(cstr_proto, STR__TCP);
		}
		else if (proto == PROTOCOL__Telnet)
		{
			strcpy(cstr_proto, STR__Telnet);
		}
		else if (proto == PROTOCOL__UDP)
		{
			strcpy(cstr_proto, STR__UDP);
		}
		else // proto == PROTOCOL__NULL or invalid_proto
		{
			strcpy(cstr_proto, STR__NULL);

		}

	}

	protocol cstr2protocol(const char* cstr_proto) const
	{

		protocol proto;

		if (strcmp("ARP", cstr_proto) == 0)
		{
			proto = PROTOCOL__ARP;
		}
		else if (strcmp("BGP", cstr_proto) == 0)
		{
			proto = PROTOCOL__BGP;
		}
		else if (strcmp("DCCP", cstr_proto) == 0)
		{
			proto = PROTOCOL__DCCP;
		}
		else if (strcmp("DHCP", cstr_proto) == 0)
		{
			proto = PROTOCOL__DHCP;
		}
		else if (strcmp("DNS", cstr_proto) == 0)
		{
			proto = PROTOCOL__DNS;
		}
		else if (strcmp("ETHERNET", cstr_proto) == 0)
		{
			proto = PROTOCOL__ETHERNET;
		}
		else if (strcmp("FTP", cstr_proto) == 0)
		{
			proto = PROTOCOL__FTP;
		}
		else if (strcmp("GRE", cstr_proto) == 0)
		{
			proto = PROTOCOL__GRE;
		}
		else if (strcmp("HTTP", cstr_proto) == 0)
		{
			proto = PROTOCOL__HTTP;
		}
		else if (strcmp("HTTPS", cstr_proto) == 0)
		{
			proto = PROTOCOL__HTTPS;
		}
		else if (strcmp("ICMP", cstr_proto) == 0)
		{
			proto = PROTOCOL__ICMP;
		}
		else if (strcmp("ICMPV6", cstr_proto) == 0)
		{
			proto = PROTOCOL__ICMPV6;
		}
		else if (strcmp("IPV4", cstr_proto) == 0)
		{
			proto = PROTOCOL__IPV4;
		}
		else if (strcmp("IPV6", cstr_proto) == 0)
		{
			proto = PROTOCOL__IPV6;
		}
		else if (strcmp("SCTP", cstr_proto) == 0)
		{
			proto = PROTOCOL__SCTP;
		}
		else if (strcmp("SMTP", cstr_proto) == 0)
		{
			proto = PROTOCOL__SMTP;
		}
		else if (strcmp("SNMP", cstr_proto) == 0)
		{
			proto = PROTOCOL__SNMP;
		}
		else if (strcmp("SSH", cstr_proto) == 0)
		{
			proto = PROTOCOL__SSH;
		}
		else if (strcmp("TACACS", cstr_proto) == 0)
		{
			proto = PROTOCOL__TACACS;
		}
		else if (strcmp("TCP", cstr_proto) == 0)
		{
			proto = PROTOCOL__TCP;
		}
		else if (strcmp("Telnet", cstr_proto) == 0)
		{
			proto = PROTOCOL__Telnet;
		}
		else if (strcmp("UDP", cstr_proto) == 0)
		{
			proto = PROTOCOL__UDP;
		}
		else if (strcmp("NULL", cstr_proto) == 0) // proto ==  or invalid_proto
		{
			proto = PROTOCOL__NULL;
		}
		else //invalid_proto
		{
			proto = PROTOCOL__NULL;
		}

		return (proto);
	}

	protocol code2protocol(const protocol_code& pcode) const
	{
		protocol proto;

		if (pcode == IPV4_CODE)
		{
			proto = PROTOCOL__IPV4;
		}
		else if (pcode == ARP_CODE)
		{
			proto = PROTOCOL__ARP;
		}

		else if (pcode == ARP_CODE_REV)
		{
			proto = PROTOCOL__ARP;
		}
		else if (pcode == IPV6_CODE)
		{
			proto = PROTOCOL__IPV6;
		}
		else if (pcode == ICMP_CODE)
		{
			proto = PROTOCOL__ICMP;
		}

		else if (pcode == TCP_CODE)
		{
			proto = PROTOCOL__TCP;
		}
		else if (pcode == UDP_CODE)
		{
			proto = PROTOCOL__UDP;
		}
		else if (pcode == DCCP_CODE)
		{
			proto = PROTOCOL__DCCP;
		}
		else if (pcode == GRE_CODE)
		{
			proto = PROTOCOL__GRE;
		}
		else if (pcode == ICMPV6_CODE)
		{
			proto = PROTOCOL__ICMPV6;
		}
		else if (pcode == SCTP_CODE)
		{
			proto = PROTOCOL__SCTP;
		}
		else
		{
			proto = PROTOCOL__NULL;
		}
		return (proto);
	}

	bool test_get_protocol()
	{
		char pc1[] = "ARP";
		char pc2[] = "TCP";
		char pc3[] = "UDP";
		char pc4[] = "IPV4";
		char pc5[] = "IPV6";
		char pc6[] = "ICMP";
		char pc7[] = "ICMPV6";
		char pc8[] = "HTTP";
		char pc9[] = "FTP";
		char pc10[] = "SCTP";
		char pc11[] = "DCCP";
		char pc12[] = "Blind Guardian";

		Protocol p1 = Protocol(pc1);
		Protocol p2 = Protocol(pc2);
		Protocol p3 = Protocol(pc3);
		Protocol p4 = Protocol(pc4);
		Protocol p5 = Protocol(pc5);
		Protocol p6 = Protocol(pc6);
		Protocol p7 = Protocol(pc7);
		Protocol p8 = Protocol(pc8);
		Protocol p9 = Protocol(pc9);
		Protocol p10 = Protocol(pc10);
		Protocol p11 = Protocol(pc11);
		Protocol p12 = Protocol(pc12);

		if (p1.get() != PROTOCOL__ARP)
			return (false);
		if (p2.get() != PROTOCOL__TCP)
			return (false);
		if (p3.get() != PROTOCOL__UDP)
			return (false);
		if (p4.get() != PROTOCOL__IPV4)
			return (false);
		if (p5.get() != PROTOCOL__IPV6)
			return (false);
		if (p6.get() != PROTOCOL__ICMP)
			return (false);
		if (p7.get() != PROTOCOL__ICMPV6)
			return (false);
		if (p8.get() != PROTOCOL__HTTP)
			return (false);
		if (p9.get() != PROTOCOL__FTP)
			return (false);
		if (p10.get() != PROTOCOL__SCTP)
			return (false);
		if (p11.get() != PROTOCOL__DCCP)
			return (false);
		if (p12.get() != PROTOCOL__NULL)
			return (false);

		return (true);
	}
	bool test_get_char()
	{
		char protChar[PROTOCOL_STR_SIZE];

		char pc1[] = "ARP";
		char pc2[] = "TCP";
		char pc3[] = "UDP";
		char pc4[] = "IPV4";
		char pc5[] = "IPV6";
		char pc6[] = "ICMP";
		char pc7[] = "ICMPV6";
		char pc8[] = "HTTP";
		char pc9[] = "FTP";
		char pc10[] = "SCTP";
		char pc11[] = "DCCP";
		char pc12[] = "NULL";

		Protocol p1 = Protocol(PROTOCOL__ARP);
		Protocol p2 = Protocol(PROTOCOL__TCP);
		Protocol p3 = Protocol(PROTOCOL__UDP);
		Protocol p4 = Protocol(PROTOCOL__IPV4);
		Protocol p5 = Protocol(PROTOCOL__IPV6);
		Protocol p6 = Protocol(PROTOCOL__ICMP);
		Protocol p7 = Protocol(PROTOCOL__ICMPV6);
		Protocol p8 = Protocol(PROTOCOL__HTTP);
		Protocol p9 = Protocol(PROTOCOL__FTP);
		Protocol p10 = Protocol(PROTOCOL__SCTP);
		Protocol p11 = Protocol(PROTOCOL__DCCP);
		Protocol p12 = Protocol(PROTOCOL__NULL);

		Protocol ppp = Protocol(PROTOCOL__ARP);

		p1.print();

		p1.get(protChar);
		if (strcmp(protChar, pc1) != 0)
			return (false);
		p2.get(protChar);
		if (strcmp(protChar, pc2) != 0)
			return (false);
		p3.get(protChar);
		if (strcmp(protChar, pc3) != 0)
			return (false);
		p4.get(protChar);
		if (strcmp(protChar, pc4) != 0)
			return (false);
		p5.get(protChar);
		if (strcmp(protChar, pc5) != 0)
			return (false);
		p6.get(protChar);
		if (strcmp(protChar, pc6) != 0)
			return (false);
		p7.get(protChar);
		if (strcmp(protChar, pc7) != 0)
			return (false);
		p8.get(protChar);
		if (strcmp(protChar, pc8) != 0)
			return (false);
		p9.get(protChar);
		if (strcmp(protChar, pc9) != 0)
			return (false);
		p10.get(protChar);
		if (strcmp(protChar, pc10) != 0)
			return (false);
		p11.get(protChar);
		if (strcmp(protChar, pc11) != 0)
			return (false);
		p12.get(protChar);
		if (strcmp(protChar, pc12) != 0)
			return (false);

		return (true);

	}
};

/*
 class Protocol
 {
 public:
 Protocol();
 virtual ~Protocol();
 Protocol(const protocol& proto);
 Protocol(const char* proto);
 Protocol(const protocol_code& pcode);
 Protocol& operator=(const Protocol& other) noexcept;

 protocol get();
 void get(char* vetc);
 void print();
 void regression_tests();

 private:
 char m_prot_char[CHAR_BUFFER];
 protocol m_prot;
 bool test_get_protocol();
 bool test_get_char();
 };
 */

#endif /* PROTOCOL_H_ */
