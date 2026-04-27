#include "EventManager.hpp"

void EventManager::subscribe(IObserver* observer) {
	observers.push_back(observer);
}

void EventManager::notify(const Alert& event) {
	for (auto* obs : observers) {
		obs->onAlert(event);
	}
}
