#pragma once
struct OverlappedEx {
	WSAOVERLAPPED overlapped;
	WSABUF	wsabuf;
	bool	is_send;
	char IOCPbuf[MAX_BUFF_SIZE];
	unsigned char PacketBuf[MAX_PACKET_SIZE];
	int     curr_packet_size;
	int     prev_received;
};