#pragma once
enum IOType {
	IO_SEND,
	IO_RECV,
	IO_RECV_ZERO,
	IO_ACCEPT,
	IO_POST,
	IO_NONE,
};
struct OverlappedEx {
	WSAOVERLAPPED mOverlapped;
	WSABUF	mWsaBuf;
	IOType	mIoType;
	char IOCPbuf[MAX_BUFF_SIZE];
	unsigned char mPacketBuf[MAX_PACKET_SIZE];
	int     mCurrPacketSize;
	int     mPrevReceived;
	int		mEventType;
};
