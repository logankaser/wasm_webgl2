#include "Time.hpp"

Time::Time()
{
	_startTime = std::chrono::high_resolution_clock::now();
	_delta = _startTime;
	_totalTime = 0;
	_deltaTime = -1;
}

void	Time::Fix()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = currentTime - _startTime;
	auto elapsedDeltaTime = currentTime - _delta;

	_totalTime = std::chrono::duration<double>(elapsedTime).count();

	if (_deltaTime != -1)
		_deltaTime = std::chrono::duration<double>(elapsedDeltaTime).count();
	else
		_deltaTime = 0;

	_delta = std::chrono::high_resolution_clock::now();
}

void	Time::Reset()
{
	_startTime = std::chrono::high_resolution_clock::now();
	_delta = _startTime;
	_totalTime = 0;
	_deltaTime = -1;
}

double	Time::Total()
{
	return _totalTime;
}

double	Time::Delta()
{
	return _deltaTime;
}
