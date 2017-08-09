#pragma once
class cClientInfo
{
public:
	cClientInfo();
	virtual ~cClientInfo();
	SOCKET				GetSocket();
	OverlappedEx		GetRecvOverEx();
	SRWLOCK				GetSRWLock();
	int					GetId();
	bool				GetIsUse();
	
	void				Initialize();
private:
	SOCKET				mClientSocket;
	OverlappedEx		mRecvOverlappedEx;
	SRWLOCK				mRWLock;
	int					mId;
	bool				mIsUse;
};

