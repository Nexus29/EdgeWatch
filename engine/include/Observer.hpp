#pragma once
#include "Alert.hpp"

class IObserver {
	public:
		virtual void onAlert(const Alert& event) = 0;
		virtual ~IObserver() = default;
};
