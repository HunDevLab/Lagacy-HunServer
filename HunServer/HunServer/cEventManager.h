#pragma once
class cEventManager : public Singleton<cEventManager>
{
public:
	cEventManager();
	~cEventManager();

	void ResistEvent(int id, int eventType, unsigned long time);
	void ProcessEvent(int id, OverlappedEx* packet);
	
	void PostEventToQueue(cEvent evt);

	//std::vector<cEvent> GetEventVec() { return eventVec; }
//private:
	std::vector<cEvent> eventVec;
	std::mutex eventLock;
};

