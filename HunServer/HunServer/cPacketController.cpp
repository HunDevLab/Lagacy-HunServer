#include "stdafx.h"
#include "cPacketController.h"


cPacketController::cPacketController()
{
	mClientManager = cClientManager::getInstance();
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
		gLock.lock();
		auto reqPacket = reinterpret_cast<cs_login_req_packet*>(packet);
		auto resPacket = ProcessLoginPacket(id,reqPacket);
		gLock.unlock();
		SendPacket(id, reinterpret_cast<char*>(&resPacket));
		break;
	}
	case CS_LOGIN_RES_FIN:
	{
		for (int i = 0; i < mClientManager->GetUserCount(); ++i) {
			for (int j = 0; j < mClientManager->GetUserCount(); ++j) {
				if(i!=j) {
					SendConnectPlayer(i, j);
				}
			}
		}
	}
	break;
	/*case CS_ATTACK:
	{
	std::cout << "CS_ATTACK_PACKET 진입" << std::endl;
	sc_packet_attack atkPacket;
	atkPacket.Exp = 100;
	atkPacket.hp = 10;
	atkPacket.LevelupExp = 1000;
	atkPacket.size = sizeof(sc_packet_attack);
	atkPacket.type = SC_ATTACK_OK;
	std::cout << "서버로부터 SC_ATTACK_OK packet 전송" << std::endl;
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
		std::cout << "패킷타입이 잘 못 들어왔습니다. " << std::endl;
		break;
	}
}
// 패킷 처리 관련 함수
sc_login_res_packet cPacketController::ProcessLoginPacket(int id, cs_login_req_packet* reqPacket)
{
	
	
	std::cout << "CS_LOGIN_REQ Packet 처리 부분 진입" << std::endl;
	auto player = mClientManager->FindPlayerById(id);
	sc_login_res_packet resPacket;
	resPacket.type = SC_LOGIN_RES;
	resPacket.size = sizeof(sc_login_res_packet);
	resPacket.id = player->GetId();
	resPacket.hp = player->GetHp();
	resPacket.xpos = player->GetXPos();
	resPacket.ypos = player->GetYPos();
	resPacket.zpos = player->GetZPos();
	return resPacket;
	/*std::cout << "SC_LOGIN_RES Packet을 " << id << "에게 보냄" << std::endl;*/
}
void cPacketController::SendConnectPlayer(int from, int to)
{
	gLock.lock();
	auto fromPlayer = mClientManager->FindPlayerById(from);
	sc_put_player_packet packet;

	packet.id = fromPlayer->GetId();
	packet.xpos = fromPlayer->GetXPos();
	packet.ypos = fromPlayer->GetYPos();
	packet.zpos = fromPlayer->GetZPos();
	packet.hp = fromPlayer->GetHp();
	packet.size = sizeof(sc_put_player_packet);
	packet.type = SC_PUT_PLAYER;
	if(from == to) {
		std::cout << from << "번 유저가 자기 자신의 접속을 알립니다." << std::endl;
	}
	else {
		std::cout << from << "번 유저가 " << to << "번 유저에게 접속을 알립니다." << std::endl;
	}
	gLock.unlock();
	SendPacket(to, reinterpret_cast<char*>(&packet));
}
