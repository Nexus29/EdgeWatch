#pragma once
#include "Observer.hpp"
#include <vector>

class EventManager {
	public:
		void subscribe(IObserver* observer);
		void notify(const AlertEvent& event);

	private:
		std::vector<IObserver*> observers;
};
