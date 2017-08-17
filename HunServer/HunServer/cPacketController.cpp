#include "stdafx.h"
#include "cPacketController.h"


cPacketController::cPacketController()
{
}


cPacketController::~cPacketController()
{
}
void cPacketController::SendPacket(int client, char* packet)
{
	OverlappedEx* sendEx = new OverlappedEx;
	sendEx->is_send = true;
	ZeroMemory(&sendEx->overlapped, sizeof(WSAOVERLAPPED));
	sendEx->wsabuf.buf = sendEx->IOCPbuf;
	sendEx->wsabuf.len = packet[0];
	memcpy(sendEx->IOCPbuf, packet, packet[0]);
	DWORD iobyte;
	//WSASend(players[client].my_socket, &sendEx->wsabuf, 1,
	//	&iobyte, 0, reinterpret_cast<LPWSAOVERLAPPED>(sendEx), NULL);
}
void cPacketController::ProcessPacket(int id, unsigned char* packet)
{
	switch (packet[1])
	{
	case CS_LOGIN:
	{
		sc_packet_login loginpacket;
		loginpacket.size = sizeof(sc_packet_login);
		loginpacket.type = SC_LOGIN_OK;
		loginpacket.id = id;

		break;
	}
	default:
		break;
	}
}