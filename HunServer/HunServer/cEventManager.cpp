#include "stdafx.h"
#include "cEventManager.h"


cEventManager::cEventManager()
{
	eventVec.reserve(MONSTER_MAX_COUNT);
}

cEventManager::~cEventManager()
{
}

void cEventManager::ResistEvent(int id, int eventType, unsigned long time) {
	eventLock.lock();
	std::cout << "ResistEvent IN" << std::endl;
	cEvent evt;
	evt.SetEvent(id, eventType, time);
	eventVec.push_back(evt);
	eventLock.unlock();
}
void cEventManager::ProcessEvent(int id, OverlappedEx* packet) {
	std::cout << "ProcessEvent IN" << std::endl;
	OverlappedEx* overEx = reinterpret_cast<OverlappedEx*>(packet);
	switch (overEx->mEventType) {
		case MonsterEvent::MOVE:
		{
			std::cout <<id <<  "번 몬스터 Event MOVE Switch문 안으로 들어옴" << std::endl;
			ResistEvent(id, MonsterEvent::MOVE, 1000 + GetTickCount());
		}
		break;
		case MonsterEvent::SPAWN:
		{

		}
		break;
		default:
		{
			std::cout << "잘못된 이벤트 타입 처리문이 들어왔습니다." << std::endl;
		}
		break;
	}
}

void cEventManager::PostEventToQueue(cEvent evt) {
	std::cout << "PostEventToQueue IN" << std::endl;
	cIocpManager* pIocpManager = cIocpManager::getInstance();
	
	OverlappedEx* postEx = new OverlappedEx;
	postEx->mIoType = IOType::IO_POST;
	postEx->mEventType = evt.getType();
	ZeroMemory(&postEx->mOverlapped, sizeof(WSAOVERLAPPED));
	PostQueuedCompletionStatus(pIocpManager->GetCompletionPort(), 1, evt.getId(), reinterpret_cast<LPOVERLAPPED>(postEx));
	
}