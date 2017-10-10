#pragma once
class cPacketController : public Singleton<cPacketController>
{
public:
	cPacketController();
	~cPacketController();
public:
	void SendPacket(int client, char* packet);
	void ProcessPacket(int id, unsigned char* packet);
	std::mutex mLock;
};

