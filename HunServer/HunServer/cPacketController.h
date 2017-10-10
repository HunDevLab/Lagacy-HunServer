#pragma once
class cClientManager;
class cPacketController : public Singleton<cPacketController>
{
public:
	cPacketController();
	~cPacketController();
public:
	void SendPacket(int client, char* packet);
	void ProcessPacket(int id, unsigned char* packet);

	sc_login_res_packet ProcessLoginPacket(int id, cs_login_req_packet* reqPacket);


	// ������ ��Ŷ ó�� �Լ�
	void SendConnectPlayer(int from, int to);
	std::mutex mLock;
private:
	cClientManager* mClientManager;
};

