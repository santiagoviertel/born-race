//
//  ColisionListener.cpp
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 17/04/13.
//
//

#include "ColisionListener.h"

void ColisionListener::BeginContact(b2Contact* contact) {
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	if(bodyUserData1 && bodyUserData2) {
		Sensorable* b1 = static_cast<Sensorable*>(bodyUserData1);
		Sensorable* b2 = static_cast<Sensorable*>(bodyUserData2);
		if(b1->getSensorableID()==SENSORABLE_COMPETIDOR && b2->getSensorableID()==SENSORABLE_ESPERMICIDA) {
			EspermicidaXCompetidorON(static_cast<Espermicida*>(b2->getObj()), static_cast<Competidor*>(b1->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_ESPERMICIDA && b2->getSensorableID()==SENSORABLE_COMPETIDOR) {
			EspermicidaXCompetidorON(static_cast<Espermicida*>(b1->getObj()), static_cast<Competidor*>(b2->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_COMPETIDOR && b2->getSensorableID()==SENSORABLE_ITEM) {
			ItemXCompetidor(static_cast<Item*>(b2->getObj()), static_cast<Competidor*>(b1->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_ITEM && b2->getSensorableID()==SENSORABLE_COMPETIDOR) {
			ItemXCompetidor(static_cast<Item*>(b1->getObj()), static_cast<Competidor*>(b2->getObj()));
		}
	}
}

void ColisionListener::EndContact(b2Contact* contact) {
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	if(bodyUserData1 && bodyUserData2) {
		Sensorable* b1 = static_cast<Sensorable*>(bodyUserData1);
		Sensorable* b2 = static_cast<Sensorable*>(bodyUserData2);
		if(b1->getSensorableID()==SENSORABLE_COMPETIDOR && b2->getSensorableID()==SENSORABLE_ESPERMICIDA) {
			EspermicidaXCompetidorOFF(static_cast<Espermicida*>(b2->getObj()), static_cast<Competidor*>(b1->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_ESPERMICIDA && b2->getSensorableID()==SENSORABLE_COMPETIDOR) {
			EspermicidaXCompetidorOFF(static_cast<Espermicida*>(b1->getObj()), static_cast<Competidor*>(b2->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_COMPETIDOR && b2->getSensorableID()==SENSORABLE_DIAFRAGMA) {
			DiafragmaColision(static_cast<Diafragma*>(b2->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_DIAFRAGMA && b2->getSensorableID()==SENSORABLE_COMPETIDOR) {
			DiafragmaColision(static_cast<Diafragma*>(b1->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_COMPETIDOR && b2->getSensorableID()==SENSORABLE_ITEM) {
			ItemXCompetidorOFF(static_cast<Item*>(b2->getObj()), static_cast<Competidor*>(b1->getObj()));
		}
		else if(b1->getSensorableID()==SENSORABLE_ITEM && b2->getSensorableID()==SENSORABLE_COMPETIDOR) {
			ItemXCompetidorOFF(static_cast<Item*>(b1->getObj()), static_cast<Competidor*>(b2->getObj()));
		}
	}
}

void ColisionListener::EspermicidaXCompetidorON(Espermicida* esp, Competidor* comp) {
	esp->aplicarEfeito(comp);
}

void ColisionListener::EspermicidaXCompetidorOFF(Espermicida* esp, Competidor* comp) {
	esp->removerEfeito(comp);
}

void ColisionListener::DiafragmaColision(Diafragma* diaf) {
	diaf->tocarSom();
}

void ColisionListener::ItemXCompetidor(Item* item, Competidor* comp) {
	item->aplicarEfeito(comp);
	comp->adicionarColisao();
}

void ColisionListener::ItemXCompetidorOFF(Item* item, Competidor* comp) {
	comp->removerColisao();
}