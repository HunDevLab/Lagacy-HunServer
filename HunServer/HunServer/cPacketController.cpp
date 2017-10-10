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
	auto player = cClientManager::getInstance()->FindPlayerById(client);
	gLock.lock();
	OverlappedEx* sendEx = new OverlappedEx;
	gLock.unlock();
	sendEx->mIoType = IOType::IO_SEND;
	ZeroMemory(&sendEx->mOverlapped, sizeof(WSAOVERLAPPED));
	sendEx->mWsaBuf.buf = sendEx->IOCPbuf;
	sendEx->mWsaBuf.len = packet[0];
	memcpy(sendEx->IOCPbuf, packet, packet[0]);
	DWORD iobyte;

	WSASend(player->GetSocket(), &sendEx->mWsaBuf, 1,
		&iobyte, 0, reinterpret_cast<LPWSAOVERLAPPED>(sendEx), NULL);
}
void cPacketController::ProcessPacket(int id, unsigned char* packet)
{
	auto type = reinterpret_cast<int*>(packet);
	std::cout << "Packet Type : " << type[1] << std::endl;
	switch (type[1])
	{
	case CS_LOGIN_REQ:
	{
		auto reqPacket = reinterpret_cast<cs_login_req_packet*>(packet);

		std::cout << "CS_LOGIN_REQ Packet ó�� �κ� ����" << std::endl;
		std::cout << "ID : " << id << std::endl;

		char tmpId[10] = "akkmh";
		char tmpPw[30] = "audgns01001";

		auto reqId = reqPacket->idString;
		auto reqPw = reqPacket->pwString;

		// ���ڿ��� ��ġ�ϸ� 0�� ��ȯ��
		int idCheck = strcmp(tmpId, reqId);
		int pwCheck = strcmp(tmpPw, reqPw);

		sc_login_res_packet resPacket;
		resPacket.type = SC_LOGIN_RES;
		resPacket.size = sizeof(sc_login_res_packet);

		if (idCheck == 0 && pwCheck == 0) {
			// ���̵�� ��й�ȣ�� ��ġ�ϴ� ���	
			std::cout << "LOGIN ��Ī ����" << std::endl;
			resPacket.isSuccess = true;
		}
		else if (idCheck != 0 || pwCheck != 0) {
			std::cout << "�����ΰ� �߸� �Է��ؼ� Ʋ��.." << std::endl;
			resPacket.isSuccess = false;
			if (idCheck != 0) {
				std::cout << "ID �߸� �Է��ؼ� Ʋ��.." << std::endl;
				resPacket.failReason = FAIL_REASON::ID;
			}
			else {
				std::cout << "PW �߸� �Է��ؼ� Ʋ��.." << std::endl;
				resPacket.failReason = FAIL_REASON::PW;
			}
		}

		std::cout << "SC_LOGIN_RES Packet�� " << id << "���� ����" << std::endl;
		SendPacket(id, reinterpret_cast<char*>(&resPacket));
		break;
	}
	/*case CS_ATTACK:
	{
	std::cout << "CS_ATTACK_PACKET ����" << std::endl;
	sc_packet_attack atkPacket;
	atkPacket.Exp = 100;
	atkPacket.hp = 10;
	atkPacket.LevelupExp = 1000;
	atkPacket.size = sizeof(sc_packet_attack);
	atkPacket.type = SC_ATTACK_OK;
	std::cout << "�����κ��� SC_ATTACK_OK packet ����" << std::endl;
	SendPacket(id, reinterpret_cast<char*>(&atkPacket));
	break;
	}
	case CS_POS:
	{
	auto csPosPacket = reinterpret_cast<cs_packet_pos*>(packet);
	std::cout << "CS_POS_PACKET IN" << std::endl;
	std::cout << "csPosPacket Xpos : " << csPosPacket->x << std::endl;
	std::cout << "csPosPacket Ypos : " << csPosPacket->y << std::endl;
	std::cout << "csPosPacket Zpos : " << csPosPacket->z << std::endl;
	sc_packet_pos posPacket;
	posPacket.x = 12.23f;
	posPacket.y = 0.521f;
	posPacket.z = 5.123f;
	posPacket.id = id;
	posPacket.size = sizeof(sc_packet_pos);
	posPacket.type = SC_POS;
	std::cout << "From Server To Client SC_POS Packet Transfer" << std::endl;
	SendPacket(id, reinterpret_cast<char*>(&posPacket));
	break;
	}*/
	default:
		std::cout << "��ŶŸ���� �� �� ���Խ��ϴ�. " << std::endl;
		break;
	}
}