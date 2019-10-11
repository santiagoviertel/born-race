//
//  Sensorable.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 18/04/13.
//
//

#define SENSORABLE_ESPERMICIDA  1
#define SENSORABLE_COMPETIDOR  2
#define SENSORABLE_DIAFRAGMA 4
#define SENSORABLE_ITEM 8

#include <iostream>

class Sensorable {

private:
	int sensorID;
	void* obj;

public:
	Sensorable(int sID, void* objeto);
	int getSensorableID();
	void* getObj();
};