#pragma once
#include "Observer.hpp"

class AlertLogger : public IObserver {
	public:
		void onAlert(const Alert& event) override;
};
