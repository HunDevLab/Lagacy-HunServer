#pragma once
class cEvent
{
public:
	cEvent();
	~cEvent();

	int getId() { return objId; }
	int getType() { return type; }
	int getWakeTime() { return wakeTime; }

	void SetEvent(int paraId, int paraType, unsigned long paraWakeTime);
	
private:
	int objId;
	int type;
	unsigned long wakeTime;
};

