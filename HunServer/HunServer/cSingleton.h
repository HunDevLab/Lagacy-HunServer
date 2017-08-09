#pragma once
#include "stdafx.h"

template <typename T>
class Singleton {
public:
	static T* getInstance() {
		if (instance == nullptr) {
			instance = std::make_shared<T>();
		}
		return instance.get();
	}
	void releaseInstance() {
		instance.reset();
		instance = nullptr;
	}
private:
	static std::shared_ptr<T> instance;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instance;