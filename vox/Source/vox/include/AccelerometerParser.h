#pragma once
#include <vector>

#include "Arduino.h"

#define LINE_SIZE 37

namespace std{
	class thread;
}

class Accelerometer;

class AccelerometerParser : public Arduino{
public:
	bool forced;
	bool firstPing;
	bool canUpdate;

	std::thread * t;

	std::string accumlator;

	explicit AccelerometerParser(std::string portName);
	~AccelerometerParser();

	Accelerometer *  addAccelerometer();

	static void getData(AccelerometerParser * _parser);
	virtual void update(Step * _step) override;

	static std::string getLatestData(std::string _acc);

private:
	std::vector<Accelerometer *> accelerometers;
};