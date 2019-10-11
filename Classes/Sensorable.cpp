//
//  Sensorable.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 18/04/13.
//
//

#include "Sensorable.h"

Sensorable::Sensorable(int sID, void* objeto) {
	Sensorable::obj = objeto;
	Sensorable::sensorID = sID;
}

int Sensorable::getSensorableID() {
	return Sensorable::sensorID;
}

void* Sensorable::getObj() {
	return Sensorable::obj;
}