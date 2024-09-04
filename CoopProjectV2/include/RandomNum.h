#pragma once
#include <chrono>
#include <thread>
#include <random>

int GetRandomNum()
{
	const int valueMin = 2;
	const int valueMax = 99;
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 gen(ss);
	std::uniform_int_distribution<> valueDist(valueMin, valueMax);
	int qty = static_cast<int>(valueDist(gen));
	return qty;
}

void Wait(int waitTime)
{
	std::this_thread::sleep_for(std::chrono::seconds(waitTime));
}