/*
 * TinsFlow.cpp
 *
 *  Created on: 3 de out de 2017
 *      Author: anderson
 */

#include "TinsFlow.h"

TinsFlow::TinsFlow()
{
	// nothing to do
}

TinsFlow::~TinsFlow()
{
	// nothing to do
}

int TinsFlow::server(const std::string& netInterface)
{
	PLOG_WARN << "TODO: libtins server. Now exiting.";
	return (0);
}

void TinsFlow::flowGenerate(const counter& flowId, const time_sec& onTime,
		const uint& npackets, const uint& nbytes,
		const std::string& netInterface)
{

	uint npackets_mode1 = (uint) this->getNpacketsMode1();
	uint npackets_mode2 = (uint) this->getNpacketsMode2();
	uint packetSize_mode1 = (uint) this->getPacketSizeModelMode1(0).param1();
	uint packetSize_mode2 = (uint) this->getPacketSizeModelMode2(0).param1();

	PLOG_DEBUG << "[flowId:" << flowId << "] -> " << "onTime:" << onTime
						<< " npackets:" << npackets << " netInterface:"
						<< netInterface;
	PLOG_DEBUG << "[flowId:" << flowId << "] -> " << "npackets_mode1"
						<< npackets_mode1 << " npackets_mode2:"
						<< npackets_mode2;

	this->sendPackets(flowId, getLinkProtocol(), getNetworkProtocol(),
			getTransportProtocol(), getApplicationProtocol(), getMacSrcAddr(),
			getMacDstAddr(), getNetworkSrcAddr(), getNetworkDstAddr(),
			getNetworkTtl(), getTransportSrcPort(), getTransportDstPort(),
			npackets_mode1, packetSize_mode1, netInterface);
	this->sendPackets(flowId, getLinkProtocol(), getNetworkProtocol(),
			getTransportProtocol(), getApplicationProtocol(), getMacSrcAddr(),
			getMacDstAddr(), getNetworkSrcAddr(), getNetworkDstAddr(),
			getNetworkTtl(), getTransportSrcPort(), getTransportDstPort(),
			npackets_mode2, packetSize_mode2, netInterface);
}

void TinsFlow::sendPackets(uint flowID, protocol etherProtocol,
		protocol netProtocol, protocol transportProtocol, protocol application,
		std::string etherSrc, std::string etherDst, std::string netSrc,
		std::string netDst, uint ttlNumber, uint portSrc, uint portDst,
		uint npackets, uint pktSize, std::string networkInterface)
{
	if (npackets == 0)
		return;

	/// Packet crafter
	PDU* flowPkt;
	PacketSender::SocketType socket_type;

	if (transportProtocol == PROTOCOL__TCP)
	{
		pktSize =
				(pktSize < MAX_TCP_PACKET_SIZE) ? pktSize : MAX_TCP_PACKET_SIZE;
	}
	if (etherProtocol == PROTOCOL__ETHERNET)
	{
		if (netProtocol == PROTOCOL__IPV4)
		{
			if (transportProtocol == PROTOCOL__TCP)
			{

				if (application == PROTOCOL__DHCP)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/DHCP/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ TCP(portDst, portSrc) / DHCP()
							/ RawPDU(std::string(pktSize, 'H'));

				}
				else if (application == PROTOCOL__DNS)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/DNS/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ TCP(portDst, portSrc) / DNS()
							/ RawPDU(std::string(pktSize, 'D'));
				}
				else
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/NULL/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ TCP(portDst, portSrc)
							/ RawPDU(std::string(pktSize, 'T'));
				}
				PLOG_DEBUG << "[FlowId:" << flowID << "]: "
									<< "PacketSender::IP_TCP_SOCKET";
				socket_type = PacketSender::IP_TCP_SOCKET;

			}
			else if (transportProtocol == PROTOCOL__UDP)
			{
				if (application == PROTOCOL__DHCP)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/UDP(" << portDst
										<< ", " << portSrc << ")/DHCP/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ UDP(portDst, portSrc) / DHCP()
							/ RawPDU(std::string(pktSize, 'H'));
				}
				else if (application == PROTOCOL__DNS)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/UDP(" << portDst
										<< ", " << portSrc << ")/DNS/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ UDP(portDst, portSrc) / DNS()
							/ RawPDU(std::string(pktSize, 'D'));
				}
				else
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IP(" << netDst << ", "
										<< netSrc << ")" << "/UDP(" << portDst
										<< ", " << portSrc << ")/DNS/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IP(netDst, netSrc)
							/ UDP(portDst, portSrc)
							/ RawPDU(std::string(pktSize, 'U'));
				}
				PLOG_DEBUG << "[FlowId:" << flowID << "]: "
									<< "PacketSender::IP_UDP_SOCKET";
				socket_type = PacketSender::IP_UDP_SOCKET;

			}
			else if (transportProtocol == PROTOCOL__ICMP)
			{
				PLOG_DEBUG << "[FlowId:" << flowID << "]: " << "EthernetII/IP("
									<< netDst << ", " << netSrc << ")"
									<< "/ICMP/DNS/payload:" << pktSize;
				flowPkt = new EthernetII() / IP(netDst, netSrc) / ICMP()
						/ RawPDU(std::string(pktSize, 'I'));
				PLOG_DEBUG << "[FlowId:" << flowID << "]: "
									<< "PacketSender::ICMP_SOCKET";
				socket_type = PacketSender::ICMP_SOCKET;
			}
		}
		else if (netProtocol == PROTOCOL__IPV6)
		{
			if (transportProtocol == PROTOCOL__TCP)
			{
				if (application == PROTOCOL__DHCP)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/DHCP/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ TCP(portDst, portSrc) / DHCP()
							/ RawPDU(std::string(pktSize, 'H'));
				}
				else if (application == PROTOCOL__DNS)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/DNS/payload:"
										<< pktSize;

					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ TCP(portDst, portSrc) / DNS()
							/ RawPDU(std::string(pktSize, 'D'));
				}
				else
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/TCP(" << portDst
										<< ", " << portSrc << ")/NULL/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ TCP(portDst, portSrc)
							/ RawPDU(std::string(pktSize, 'T'));
				}
			}
			else if (transportProtocol == PROTOCOL__UDP)
			{
				if (application == PROTOCOL__DHCP)
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/UDP(" << portDst
										<< ", " << portSrc << ")/DHCP/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ UDP(portDst, portSrc) / DHCP()
							/ RawPDU(std::string(pktSize, 'h'));
				}
				else if (application == PROTOCOL__DNS)
				{

					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/UDP(" << portDst
										<< ", " << portSrc << ")/DNS/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ UDP(portDst, portSrc) / DNS()
							/ RawPDU(std::string(pktSize, 'd'));
				}
				else
				{
					PLOG_DEBUG << "[FlowId:" << flowID << "]: "
										<< "EthernetII/IPv6(" << netDst << ", "
										<< netSrc << ")" << "/NULL(" << portDst
										<< ", " << portSrc << ")/DHCP/payload:"
										<< pktSize;
					flowPkt = new EthernetII() / IPv6(netDst, netSrc)
							/ UDP(portDst, portSrc)
							/ RawPDU(std::string(pktSize, 'u'));
				}
			}
			else if (transportProtocol == PROTOCOL__ICMP)
			{
				PLOG_DEBUG << "[FlowId:" << flowID << "]: " << "EthernetII/IP("
									<< netDst << ", " << netSrc << ")"
									<< "/ICMP/payload:" << pktSize;
				flowPkt = new EthernetII() / IPv6(netDst, netSrc) / ICMPv6()
						/ RawPDU(std::string(pktSize, 'i'));
			}
			PLOG_DEBUG << "[FlowId:" << flowID << "]: "
								<< "PacketSender::IPV6_SOCKET";
			socket_type = PacketSender::IPV6_SOCKET;

		}
		else if (etherProtocol == PROTOCOL__ARP)
		{
			PLOG_DEBUG << "[FlowId:" << flowID << "]: " << "EthernetII/ARP";
			//flowPkt = new ARP() / RawPDU(std::string(pktSize, 'a'));
			flowPkt = new EthernetII() / ARP();
			PLOG_DEBUG << "[FlowId:" << flowID << "]: "
								<< "PacketSender::ARP_SOCKET";
			socket_type = PacketSender::ARP_SOCKET;

		}
		else
		{
			PLOG_DEBUG << "[FlowId:" << flowID << "]: " << "EthernetII/payload:"
								<< pktSize;
			flowPkt = new EthernetII() / RawPDU(std::string(pktSize, 'x'));
			PLOG_DEBUG << "[FlowId:" << flowID << "]: "
								<< "PacketSender::ETHER_SOCKET";
			socket_type = PacketSender::ETHER_SOCKET;
		}
	}

	/// Packet sender
	PacketSender sender;
	NetworkInterface iface(networkInterface);

	try
	{
		sender.open_l2_socket(networkInterface);
		sender.open_l3_socket(socket_type);

		//std::cout << std::endl << "[FlowId:" << flowID << "]: <";
		for (uint i = 0; i < npackets; i++)
		{
			sender.send(*flowPkt, iface);
			//std::cout << i << ", ";
		}
		//std::cout << ">" << endl;
		sender.close_socket(socket_type, networkInterface);

	} catch (Tins::invalid_address &e)
	{
		PLOG_ERROR << ERRORMSG_GENERAL_EXECUTION_ERROR
							<< " Tins::invalid_address: " << e.what();
		PLOG_ERROR << "<Info>" " networkInterface:" << networkInterface
							<< " FlowID:" << flowID << " etherProtocol:"
							<< Protocol(etherProtocol).str() << " netProtocol"
							<< Protocol(netProtocol).str() << " netDst:"
							<< netDst << " netSrc:" << netSrc
							<< " transportProtocol:"
							<< Protocol(transportProtocol).str() << " portDst:"
							<< portDst << " portSrc" << portSrc << " npackets:"
							<< npackets << " pktSize:" << pktSize;

	}
	catch (Tins::invalid_domain_name &e)
	{
		PLOG_ERROR << ERRORMSG_GENERAL_EXECUTION_ERROR
							<< " Tins::invalid_domain_name: " << e.what();

		PLOG_ERROR << "<Info>" " networkInterface:" << networkInterface
							<< " FlowID:" << flowID << " etherProtocol:"
							<< Protocol(etherProtocol).str() << " netProtocol"
							<< Protocol(netProtocol).str() << " netDst:"
							<< netDst << " netSrc:" << netSrc
							<< " transportProtocol:"
							<< Protocol(transportProtocol).str() << " portDst:"
							<< portDst << " portSrc" << portSrc << " npackets:"
							<< npackets << " pktSize:" << pktSize;
	} catch (Tins::invalid_interface &e)
	{
		PLOG_ERROR << ERRORMSG_GENERAL_EXECUTION_ERROR
							<< " Tins::invalid_interface: " << e.what();

		PLOG_ERROR << "<Info>" " networkInterface:" << networkInterface
							<< " FlowID:" << flowID << " etherProtocol:"
							<< Protocol(etherProtocol).str() << " netProtocol"
							<< Protocol(netProtocol).str() << " netDst:"
							<< netDst << " netSrc:" << netSrc
							<< " transportProtocol:"
							<< Protocol(transportProtocol).str() << " portDst:"
							<< portDst << " portSrc" << portSrc << " npackets:"
							<< npackets << " pktSize:" << pktSize;

	} catch (Tins::invalid_packet &e)
	{
		PLOG_ERROR << ERRORMSG_GENERAL_EXECUTION_ERROR
							<< " Tins::invalid_packet: " << e.what();
		PLOG_ERROR << "<Info>" " networkInterface:" << networkInterface
							<< " FlowID:" << flowID << " etherProtocol:"
							<< Protocol(etherProtocol).str() << " netProtocol"
							<< Protocol(netProtocol).str() << " netDst:"
							<< netDst << " netSrc:" << netSrc
							<< " transportProtocol:"
							<< Protocol(transportProtocol).str() << " portDst:"
							<< portDst << " portSrc" << portSrc << " npackets:"
							<< npackets << " pktSize:" << pktSize;
	} catch (Tins::invalid_socket_type &e)
	{
		PLOG_ERROR << ERRORMSG_GENERAL_EXECUTION_ERROR
							<< " Tins::invalid_socket_type: " << e.what();
		PLOG_ERROR << "<Info>" " networkInterface:" << networkInterface
							<< " FlowID:" << flowID << " etherProtocol:"
							<< Protocol(etherProtocol).str() << " netProtocol"
							<< Protocol(netProtocol).str() << " netDst:"
							<< netDst << " netSrc:" << netSrc
							<< " transportProtocol:"
							<< Protocol(transportProtocol).str() << " portDst:"
							<< portDst << " portSrc" << portSrc << " npackets:"
							<< npackets << " pktSize:" << pktSize;
	}

	/// Free memory
	delete flowPkt;
}
