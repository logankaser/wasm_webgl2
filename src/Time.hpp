#pragma once

#include <chrono>

class	Time
{
private:

	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _delta;
	double _totalTime;
	double _deltaTime;

public:

	Time();

	void Fix();
	void Reset();
	double Total();
	double Delta();
};
