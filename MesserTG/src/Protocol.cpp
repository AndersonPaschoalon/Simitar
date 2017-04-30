/*
 * Protocol.cpp
 *
 *  Created on: 5 de abr de 2017
 *      Author: anderson
 */

#include "Protocol.h"
/*
Protocol::Protocol()
{
	m_prot = PROTOCOL__NULL;
	strcpy(m_prot_char, "NULL");
}

Protocol::Protocol(const protocol_code& pcode)
{
	m_prot = PROTOCOL__NULL;
	strcpy(m_prot_char, "NULL");

	if (pcode == IPV4_CODE)
	{
		m_prot = PROTOCOL__IPV4;
		strcpy(m_prot_char, "NULL");
	}
	else if (pcode == ARP_CODE)
	{
		m_prot = PROTOCOL__ARP;
		strcpy(m_prot_char, "ARP");
	}

	else if (pcode == ARP_CODE_REV)
	{
		m_prot = PROTOCOL__ARP;
		strcpy(m_prot_char, "ARP");
	}
	else if (pcode == IPV6_CODE)
	{
		m_prot = PROTOCOL__IPV6;
		strcpy(m_prot_char, "IPV6");
	}
	else if (pcode == ICMP_CODE)
	{
		m_prot = PROTOCOL__ICMP;
		strcpy(m_prot_char, "ICMP");
	}

	else if (pcode == TCP_CODE)
	{
		m_prot = PROTOCOL__TCP;
		strcpy(m_prot_char, "TCP");
	}

	else if (pcode == UDP_CODE)
	{
		m_prot = PROTOCOL__UDP;
		strcpy(m_prot_char, "UDP");
	}

	else if (pcode == DCCP_CODE)
	{
		m_prot = PROTOCOL__DCCP;
		strcpy(m_prot_char, "DCCP");
	}
	else if (pcode == GRE_CODE)
	{
		m_prot = PROTOCOL__GRE;
		strcpy(m_prot_char, "GRE");
	}
	else if (pcode == ICMPV6_CODE)
	{
		m_prot = PROTOCOL__ICMPV6;
		strcpy(m_prot_char, "ICMPV6");
	}
	else if (pcode == SCTP_CODE)
	{
		m_prot = PROTOCOL__SCTP;
		strcpy(m_prot_char, "SCTP");
	}
	else
	{
		m_prot = PROTOCOL__NULL;
		strcpy(m_prot_char, "NULL");
	}

}

Protocol::Protocol(const protocol& proto)
{
	m_prot = proto;

	if (proto == PROTOCOL__ARP)
	{
		strcpy(m_prot_char, "ARP");
	}
	else if (proto == PROTOCOL__BGP)
	{
		strcpy(m_prot_char, "BGP");
	}
	else if (proto == PROTOCOL__DCCP)
	{
		strcpy(m_prot_char, "DCCP");
	}
	else if (proto == PROTOCOL__DHCP)
	{
		strcpy(m_prot_char, "DHCP");
	}
	else if (proto == PROTOCOL__DNS)
	{
		strcpy(m_prot_char, "DNS");
	}
	else if (proto == PROTOCOL__ETHERNET)
	{
		strcpy(m_prot_char, "ETHERNET");
	}
	else if (proto == PROTOCOL__FTP)
	{
		strcpy(m_prot_char, "FTP");
	}
	else if (proto == PROTOCOL__GRE)
	{
		strcpy(m_prot_char, "GRE");
	}
	else if (proto == PROTOCOL__HTTP)
	{
		strcpy(m_prot_char, "HTTP");
	}
	else if (proto == PROTOCOL__HTTPS)
	{
		strcpy(m_prot_char, "HTTPS");
	}
	else if (proto == PROTOCOL__ICMP)
	{
		strcpy(m_prot_char, "ICMP");
	}
	else if (proto == PROTOCOL__ICMPV6)
	{
		strcpy(m_prot_char, "ICMPV6");
	}
	else if (proto == PROTOCOL__IPV4)
	{
		strcpy(m_prot_char, "IPV4");
	}
	else if (proto == PROTOCOL__IPV6)
	{
		strcpy(m_prot_char, "IPV6");
	}
	else if (proto == PROTOCOL__SCTP)
	{
		strcpy(m_prot_char, "SCTP");
	}
	else if (proto == PROTOCOL__SMTP)
	{
		strcpy(m_prot_char, "SMTP");
	}
	else if (proto == PROTOCOL__SNMP)
	{
		strcpy(m_prot_char, "SNMP");
	}
	else if (proto == PROTOCOL__SSH)
	{
		strcpy(m_prot_char, "SSH");
	}
	else if (proto == PROTOCOL__TACACS)
	{
		strcpy(m_prot_char, "TACACS");
	}
	else if (proto == PROTOCOL__TCP)
	{
		strcpy(m_prot_char, "TCP");
	}
	else if (proto == PROTOCOL__Telnet)
	{
		strcpy(m_prot_char, "Telnet");
	}
	else if (proto == PROTOCOL__UDP)
	{
		strcpy(m_prot_char, "UDP");
	}
	else // proto == PROTOCOL__NULL or invalid_proto
	{
		strcpy(m_prot_char, "NULL");
	}

}

Protocol::~Protocol()
{
	// nothing to do
}

Protocol::Protocol(const char* proto)
{
	strcpy(m_prot_char, proto);

	if (strcmp("ARP", proto) == 0)
	{
		m_prot = PROTOCOL__ARP;
	}
	else if (strcmp("BGP", proto) == 0)
	{
		m_prot = PROTOCOL__BGP;
	}
	else if (strcmp("DCCP", proto) == 0)
	{
		m_prot = PROTOCOL__DCCP;
	}
	else if (strcmp("DHCP", proto) == 0)
	{
		m_prot = PROTOCOL__DHCP;
	}
	else if (strcmp("DNS", proto) == 0)
	{
		m_prot = PROTOCOL__DNS;
	}
	else if (strcmp("ETHERNET", proto) == 0)
	{
		m_prot = PROTOCOL__ETHERNET;
	}
	else if (strcmp("FTP", proto) == 0)
	{
		m_prot = PROTOCOL__FTP;
	}
	else if (strcmp("GRE", proto) == 0)
	{
		m_prot = PROTOCOL__GRE;
	}
	else if (strcmp("HTTP", proto) == 0)
	{
		m_prot = PROTOCOL__HTTP;
	}
	else if (strcmp("HTTPS", proto) == 0)
	{
		m_prot = PROTOCOL__HTTPS;
	}
	else if (strcmp("ICMP", proto) == 0)
	{
		m_prot = PROTOCOL__ICMP;
	}
	else if (strcmp("ICMPV6", proto) == 0)
	{
		m_prot = PROTOCOL__ICMPV6;
	}
	else if (strcmp("IPV4", proto) == 0)
	{
		m_prot = PROTOCOL__IPV4;
	}
	else if (strcmp("IPV6", proto) == 0)
	{
		m_prot = PROTOCOL__IPV6;
	}
	else if (strcmp("SCTP", proto) == 0)
	{
		m_prot = PROTOCOL__SCTP;
	}
	else if (strcmp("SMTP", proto) == 0)
	{
		m_prot = PROTOCOL__SMTP;
	}
	else if (strcmp("SNMP", proto) == 0)
	{
		m_prot = PROTOCOL__SNMP;
	}
	else if (strcmp("SSH", proto) == 0)
	{
		m_prot = PROTOCOL__SSH;
	}
	else if (strcmp("TACACS", proto) == 0)
	{
		m_prot = PROTOCOL__TACACS;
	}
	else if (strcmp("TCP", proto) == 0)
	{
		m_prot = PROTOCOL__TCP;
	}
	else if (strcmp("Telnet", proto) == 0)
	{
		m_prot = PROTOCOL__Telnet;
	}
	else if (strcmp("UDP", proto) == 0)
	{
		m_prot = PROTOCOL__UDP;
	}
	else // proto ==  or invalid_proto
	{
		m_prot = PROTOCOL__NULL;
	}

}

Protocol& Protocol::operator=(const Protocol& rhs) noexcept
{
	if (this != &rhs)
	{
		m_prot = rhs.m_prot;
		strcpy(m_prot_char, rhs.m_prot_char);
	}
	else
	{
		cerr << "Attempted assignment of a StochasticModelFit object to itself"
				<< endl;
	}

	return (*this);
}

protocol Protocol::get()
{
	return (m_prot);
}

void Protocol::get(char* vetc)
{
	strcpy(vetc, m_prot_char);
}

void Protocol::print()
{
	cout << "protocol: " << m_prot_char << endl;
}

void Protocol::regression_tests()
{
	RegressionTests rt = RegressionTests();

	rt.printHeader("class Protocol");
	rt.printTestResult("Get Protocol", test_get_protocol());
	rt.printTestResult("Get Protocol Char", test_get_char());
	cout << endl;

	cout << "wait key" << endl;
	string keyin;
	cin >> keyin;
}

bool Protocol::test_get_protocol()
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

bool Protocol::test_get_char()
{
	char protChar[CHAR_BUFFER];

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
*/
