#include "stdafx.h"
#include "cClientInfo.h"


cClientInfo::cClientInfo()
{
	mRecvOverlappedEx.wsabuf.buf = mRecvOverlappedEx.IOCPbuf;
	mRecvOverlappedEx.wsabuf.len = MAX_BUFF_SIZE;
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
void cClientInfo::Initialize()
{
	mRecvOverlappedEx.wsabuf.buf = mRecvOverlappedEx.IOCPbuf;
	mRecvOverlappedEx.wsabuf.len = MAX_BUFF_SIZE;
	InitializeSRWLock(&mRWLock);
	mIsUse = false;
	mId = 0;
}