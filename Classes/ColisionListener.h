//
//  ColisionListener.h
//  bornrace
//
//  Created by Thalisson Christiano de Almeida on 17/04/13.
//
//

#include "SpermGun.h"

class ColisionListener : public  b2ContactListener {

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void EspermicidaXCompetidorON(Espermicida* esp, Competidor* comp);
	void EspermicidaXCompetidorOFF(Espermicida* esp, Competidor* comp);
	void DiafragmaColision(Diafragma* diaf);
	void ItemXCompetidor(Item* item, Competidor* comp);
	void ItemXCompetidorOFF(Item* item, Competidor* comp);
};