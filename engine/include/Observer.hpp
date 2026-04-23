#pragma once
#include "Alert.hpp"

class IObserver {
	public:
		virtual void onAlert(const AlertEvent& event) = 0;
		virtual ~IObserver() = default;
};
