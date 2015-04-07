#pragma once

#include "AccelerometerParser.h"
#include "Accelerometer.h"

#include <StringUtils.h>
#include <Arduino.h>

#include <iostream>
#include <thread>
#include <Item.h>

AccelerometerParser::AccelerometerParser(std::string portName):
	Arduino(portName),
	forced(false),
	firstPing(true),
	canUpdate(true),
	accumlator("")
{
	//Make sure our buffer is clear
    PurgeComm(hSerial, PURGE_RXABORT); 
	PurgeComm(hSerial, PURGE_TXABORT);
	PurgeComm(hSerial, PURGE_RXCLEAR);
	PurgeComm(hSerial, PURGE_TXCLEAR);
}

AccelerometerParser::~AccelerometerParser(){
	delete t;
	while(accelerometers.size() > 0){
		delete accelerometers.back();
		accelerometers.pop_back();
	}
}

Accelerometer * AccelerometerParser::addAccelerometer(){
	accelerometers.push_back(new Accelerometer(this));
	return accelerometers.back();
}

void AccelerometerParser::getData(AccelerometerParser * _parser){
	//while(_parser->IsConnected() && _parser->status.cbInQue > 20) {
	//	char * buffer = new char[20];
	//	int numRead = _parser->ReadData(buffer, _parser->status.cbInQue);
	//}
	while(_parser->IsConnected()) {
		char ping[1] = {'1'};
		_parser->WriteData(ping, 1);
		bool dataRead = false;
		if(_parser->firstPing) {
			//ClearCommError(_parser->hSerial, &_parser->errors, &_parser->status);
		}
		if(_parser->status.cbInQue > 0){
			char * buffer = new char[37];
			int numRead = _parser->ReadData(buffer, 37);
			_parser->accumlator += buffer;
			std::string src = getLatestData(_parser->accumlator);
			if(src.size() >= LINE_SIZE - 1){
				_parser->accumlator.clear();
				dataRead = true;
				_parser->firstPing = false;
				for(unsigned long int i = 0; i < _parser->accelerometers.size(); ++i){
					//char * src = buffer + (i*9) + 1;
					char x[4];
					char y[4];
					char z[4];
						
					x[0] = src[0];
					x[1] = src[1];
					x[2] = src[2];
					x[3] = '\0';
						
					y[0] = src[3];
					y[1] = src[4];
					y[2] = src[5];
					y[3] = '\0';
						
					z[0] = src[6];
					z[1] = src[7];
					z[2] = src[8];
					z[3] = '\0';

					_parser->accelerometers.at(i)->lx = _parser->accelerometers.at(i)->x;
					_parser->accelerometers.at(i)->ly = _parser->accelerometers.at(i)->y;
					_parser->accelerometers.at(i)->lz = _parser-> accelerometers.at(i)->z;
					_parser->accelerometers.at(i)->x = atoi(x);
					_parser->accelerometers.at(i)->y = atoi(y);
					_parser->accelerometers.at(i)->z = atoi(z);
					_parser->accelerometers.at(i)->update(&vox::step);
				}
				//if(_parser->status.cbInQue > 0){
				//	char * buff = new char[_parser->status.cbInQue];
				//	_parser->ReadData(buff, _parser->status.cbInQue);
				//	delete buff;
				//}
				//_parser->canUpdate = true;
				//break;
			}
		}
		//}/*else if(_parser->status.cbInQue > LINE_SIZE){
			//char * buff = new char[_parser->status.cbInQue];
			//_parser->ReadData(buff, _parser->status.cbInQue);
			//delete buff;
			/*if(_parser->status.cbInQue > 0){
				char * buff = new char[_parser->status.cbInQue];
				_parser->ReadData(buff, _parser->status.cbInQue);
				delete buff;
			}*/
			//_parser->canUpdate = true;
			//break;
		//}
	}		
}


void AccelerometerParser::update(Step* _step){
	Arduino::update(_step);
	if(canUpdate) {
		//if(firstPing) {
		//	char ping[1] = {'1'};
		//	WriteData(ping, 1);
		//}
		canUpdate = false;
		t = new std::thread(getData, this);
		t->detach();
	}
}

std::string AccelerometerParser::getLatestData(std::string _acc){

	for(unsigned long int i = _acc.size() - 1; i >= 0; --i) {
		if(_acc.at(i) == ':') {
			if(_acc.size() - i >= LINE_SIZE) {
				return _acc.substr(i + 1, LINE_SIZE - 1);
			}
		}
	}

	return "";
}
