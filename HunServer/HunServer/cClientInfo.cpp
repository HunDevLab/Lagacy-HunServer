#include "stdafx.h"
#include "cClientInfo.h"


cClientInfo::cClientInfo()
{
	mRecvOverlappedEx.mCurrPacketSize = 0;
	mRecvOverlappedEx.mIoType = IOType::IO_RECV;
	mRecvOverlappedEx.mPrevReceived = 0;
	ZeroMemory(&mRecvOverlappedEx.mOverlapped, sizeof(WSAOVERLAPPED));
	mRecvOverlappedEx.mWsaBuf.buf = mRecvOverlappedEx.IOCPbuf;
	mRecvOverlappedEx.mWsaBuf.len = MAX_BUFF_SIZE;
	InitializeSRWLock(&mRWLock);
	mIsUse = false;
	mId = 0;
}


cClientInfo::~cClientInfo()
{
}
SOCKET cClientInfo::GetSocket()
{
	return mClientSocket;
}
OverlappedEx cClientInfo::GetRecvOverEx()
{
	return mRecvOverlappedEx;
}
SRWLOCK	cClientInfo::GetSRWLock()
{
	return mRWLock;
}
int cClientInfo::GetId()
{
	return mId;
}
bool cClientInfo::GetIsUse()
{
	return mIsUse;
}

WSABUF* cClientInfo::GetRecvOverExWsabuf()
{
	return &mRecvOverlappedEx.mWsaBuf;
}
OVERLAPPED* cClientInfo::GetRecvOverExOverlapped()
{
	return &mRecvOverlappedEx.mOverlapped;
}
void cClientInfo::SetIsUse(bool isUsed)
{
	mIsUse = isUsed;
}
void cClientInfo::SetId(int id)
{
	mId = id;
}
void cClientInfo::SetSocket(SOCKET socket)
{
	mClientSocket = socket;
}
void cClientInfo::SetCurrPacketSize(int size)
{
	mRecvOverlappedEx.mCurrPacketSize = size;
}
void cClientInfo::SetPrevPacketSize(int size)
{
	mRecvOverlappedEx.mPrevReceived = size;
}
void cClientInfo::resetClient()
{

	mRecvOverlappedEx.mCurrPacketSize = 0;
	mRecvOverlappedEx.mIoType = IOType::IO_RECV;
	mRecvOverlappedEx.mPrevReceived = 0;
	ZeroMemory(&mRecvOverlappedEx.mOverlapped, sizeof(WSAOVERLAPPED));
	mRecvOverlappedEx.mWsaBuf.buf = mRecvOverlappedEx.IOCPbuf;
	mRecvOverlappedEx.mWsaBuf.len = MAX_BUFF_SIZE;
	InitializeSRWLock(&mRWLock);
	mIsUse = false;
	mId = 0;
	mClientSocket = NULL;
}