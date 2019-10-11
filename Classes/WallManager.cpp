#include "Mundo.h"

int WallManager::gid_branco;
int WallManager::gid_completo;
int WallManager::gid_esq_sup_meio;
int WallManager::gid_dir_sup_meio;
int WallManager::gid_esq_inf_meio;
int WallManager::gid_dir_inf_meio;
int WallManager::gid_dir_inf_inic;
int WallManager::gid_esq_inf_inic;
int WallManager::gid_dir_sup_inic;
int WallManager::gid_esq_sup_inic;
int WallManager::gid_dir;
int WallManager::gid_esq;
int WallManager::gid_sup;
int WallManager::gid_inf;
b2Body** WallManager::esq_sup_meio;
b2Body** WallManager::dir_sup_meio;
b2Body** WallManager::esq_inf_meio;
b2Body** WallManager::dir_inf_meio;
b2Body** WallManager::dir_inf_inic;
b2Body** WallManager::esq_inf_inic;
b2Body** WallManager::dir_sup_inic;
b2Body** WallManager::esq_sup_inic;
b2Body** WallManager::dir;
b2Body** WallManager::esq;
b2Body** WallManager::sup;
b2Body** WallManager::inf;
int** WallManager::paredesPosicionadas;
CCTMXLayer* WallManager::pista;
int WallManager::qtdJogadores;
int WallManager::tileWidth;
int WallManager::tileHeight;

void WallManager::create(CCTMXLayer* p,int qtd) {
	int i;
	WallManager::gid_branco = 0;
	WallManager::gid_completo = p->getTileSet()->m_uFirstGid;
	WallManager::gid_esq_sup_meio = WallManager::gid_completo + 1;
	WallManager::gid_dir_sup_meio = WallManager::gid_esq_sup_meio + 1;
	WallManager::gid_esq_inf_meio = WallManager::gid_dir_sup_meio + 1;
	WallManager::gid_dir_inf_meio = WallManager::gid_esq_inf_meio + 1;
	WallManager::gid_dir_inf_inic = WallManager::gid_dir_inf_meio + 1;
	WallManager::gid_esq_inf_inic = WallManager::gid_dir_inf_inic + 1;
	WallManager::gid_dir_sup_inic = WallManager::gid_esq_inf_inic + 1;
	WallManager::gid_esq_sup_inic = WallManager::gid_dir_sup_inic + 1;
	WallManager::gid_dir = WallManager::gid_esq_sup_inic + 1;
	WallManager::gid_esq = WallManager::gid_dir + 1;
	WallManager::gid_sup = WallManager::gid_esq + 1;
	WallManager::gid_inf = WallManager::gid_sup + 1;
	b2BodyDef wallDefEsqSupMeio;
	b2Vec2 vsEsqSupMeio[4];
	b2ChainShape wallEdgeEsqSupMeio;
	b2FixtureDef wallShapeDefEsqSupMeio;
	b2BodyDef wallDefDirSupMeio;
	b2Vec2 vsDirSupMeio[4];
	b2ChainShape wallEdgeDirSupMeio;
	b2FixtureDef wallShapeDefDirSupMeio;
	b2BodyDef wallDefEsqInfMeio;
	b2Vec2 vsEsqInfMeio[4];
	b2ChainShape wallEdgeEsqInfMeio;
	b2FixtureDef wallShapeDefEsqInfMeio;
	b2BodyDef wallDefDirInfMeio;
	b2Vec2 vsDirInfMeio[4];
	b2ChainShape wallEdgeDirInfMeio;
	b2FixtureDef wallShapeDefDirInfMeio;
	b2BodyDef wallDefDirInfInic;
	b2Vec2 vsDirInfInic[2];
	b2EdgeShape wallEdgeDirInfInic;
	b2FixtureDef wallShapeDefDirInfInic;
	b2BodyDef wallDefEsqInfInic;
	b2Vec2 vsEsqInfInic[2];
	b2EdgeShape wallEdgeEsqInfInic;
	b2FixtureDef wallShapeDefEsqInfInic;
	b2BodyDef wallDefDirSupInic;
	b2Vec2 vsDirSupInic[2];
	b2EdgeShape wallEdgeDirSupInic;
	b2FixtureDef wallShapeDefDirSupInic;
	b2BodyDef wallDefEsqSupInic;
	b2Vec2 vsEsqSupInic[2];
	b2EdgeShape wallEdgeEsqSupInic;
	b2FixtureDef wallShapeDefEsqSupInic;
	b2BodyDef wallDefDir;
	b2Vec2 vsDir[2];
	b2EdgeShape wallEdgeDir;
	b2FixtureDef wallShapeDefDir;
	b2BodyDef wallDefEsq;
	b2Vec2 vsEsq[2];
	b2EdgeShape wallEdgeEsq;
	b2FixtureDef wallShapeDefEsq;
	b2BodyDef wallDefSup;
	b2Vec2 vsSup[2];
	b2EdgeShape wallEdgeSup;
	b2FixtureDef wallShapeDefSup;
	b2BodyDef wallDefInf;
	b2Vec2 vsInf[2];
	b2EdgeShape wallEdgeInf;
	b2FixtureDef wallShapeDefInf;
	WallManager::qtdJogadores = qtd;
	WallManager::esq_sup_meio = new b2Body*[3*qtd];
	WallManager::dir_sup_meio = new b2Body*[3*qtd];
	WallManager::esq_inf_meio = new b2Body*[3*qtd];
	WallManager::dir_inf_meio = new b2Body*[3*qtd];
	WallManager::dir_inf_inic = new b2Body*[3*qtd];
	WallManager::esq_inf_inic = new b2Body*[3*qtd];
	WallManager::dir_sup_inic = new b2Body*[3*qtd];
	WallManager::esq_sup_inic = new b2Body*[3*qtd];
	WallManager::dir = new b2Body*[3*qtd];
	WallManager::esq = new b2Body*[3*qtd];
	WallManager::sup = new b2Body*[3*qtd];
	WallManager::inf = new b2Body*[3*qtd];
	wallDefEsqSupMeio.type = b2_staticBody;
	wallDefEsqSupMeio.position.Set(-1,-1);
	vsEsqSupMeio[0].Set(0.60,0.00);
	vsEsqSupMeio[1].Set(0.58,0.75);
	vsEsqSupMeio[2].Set(1.44,1.32);
	vsEsqSupMeio[3].Set(1.92,1.34);
	wallEdgeEsqSupMeio.CreateChain(vsEsqSupMeio,4);
	wallShapeDefEsqSupMeio.shape = &wallEdgeEsqSupMeio;
	wallDefDirSupMeio.type = b2_staticBody;
	wallDefDirSupMeio.position.Set(-1,-1);
	vsDirSupMeio[0].Set(0.00,1.34);
	vsDirSupMeio[1].Set(0.52,1.38);
	vsDirSupMeio[2].Set(1.25,0.77);
	vsDirSupMeio[3].Set(1.31,0.00);
	wallEdgeDirSupMeio.CreateChain(vsDirSupMeio,4);
	wallShapeDefDirSupMeio.shape = &wallEdgeDirSupMeio;
	wallDefEsqInfMeio.type = b2_staticBody;
	wallDefEsqInfMeio.position.Set(-1,-1);
	vsEsqInfMeio[0].Set(0.60,1.92);
	vsEsqInfMeio[1].Set(0.71,1.02);
	vsEsqInfMeio[2].Set(1.63,0.50);
	vsEsqInfMeio[3].Set(1.92,0.56);
	wallEdgeEsqInfMeio.CreateChain(vsEsqInfMeio,4);
	wallShapeDefEsqInfMeio.shape = &wallEdgeEsqInfMeio;
	wallDefDirInfMeio.type = b2_staticBody;
	wallDefDirInfMeio.position.Set(-1,-1);
	vsDirInfMeio[0].Set(0.00,0.56);
	vsDirInfMeio[1].Set(0.90,0.77);
	vsDirInfMeio[2].Set(1.31,1.15);
	vsDirInfMeio[3].Set(1.31,1.92);
	wallEdgeDirInfMeio.CreateChain(vsDirInfMeio,4);
	wallShapeDefDirInfMeio.shape = &wallEdgeDirInfMeio;
	wallDefDirInfInic.type = b2_staticBody;
	wallDefDirInfInic.position.Set(-1,-1);
	vsDirInfInic[0].Set(1.31,0.00);
	vsDirInfInic[1].Set(1.92,0.56);
	wallEdgeDirInfInic.Set(vsDirInfInic[0],vsDirInfInic[1]);
	wallShapeDefDirInfInic.shape = &wallEdgeDirInfInic;
	wallDefEsqInfInic.type = b2_staticBody;
	wallDefEsqInfInic.position.Set(-1,-1);
	vsEsqInfInic[0].Set(0.00,0.56);
	vsEsqInfInic[1].Set(0.60,0.00);
	wallEdgeEsqInfInic.Set(vsEsqInfInic[0],vsEsqInfInic[1]);
	wallShapeDefEsqInfInic.shape = &wallEdgeEsqInfInic;
	wallDefDirSupInic.type = b2_staticBody;
	wallDefDirSupInic.position.Set(-1,-1);
	vsDirSupInic[0].Set(1.31,1.92);
	vsDirSupInic[1].Set(1.92,1.34);
	wallEdgeDirSupInic.Set(vsDirSupInic[0],vsDirSupInic[1]);
	wallShapeDefDirSupInic.shape = &wallEdgeDirSupInic;
	wallDefEsqSupInic.type = b2_staticBody;
	wallDefEsqSupInic.position.Set(-1,-1);
	vsEsqSupInic[0].Set(0.00,1.34);
	vsEsqSupInic[1].Set(0.60,1.92);
	wallEdgeEsqSupInic.Set(vsEsqSupInic[0],vsEsqSupInic[1]);
	wallShapeDefEsqSupInic.shape = &wallEdgeEsqSupInic;
	wallDefDir.type = b2_staticBody;
	wallDefDir.position.Set(-1,-1);
	vsDir[0].Set(1.31,1.92);
	vsDir[1].Set(1.31,0.00);
	wallEdgeDir.Set(vsDir[0],vsDir[1]);
	wallShapeDefDir.shape = &wallEdgeDir;
	wallDefEsq.type = b2_staticBody;
	wallDefEsq.position.Set(-1,-1);
	vsEsq[0].Set(0.60,1.92);
	vsEsq[1].Set(0.60,0.00);
	wallEdgeEsq.Set(vsEsq[0],vsEsq[1]);
	wallShapeDefEsq.shape = &wallEdgeEsq;
	wallDefSup.type = b2_staticBody;
	wallDefSup.position.Set(-1,-1);
	vsSup[0].Set(0.00,1.34);
	vsSup[1].Set(1.92,1.34);
	wallEdgeSup.Set(vsSup[0],vsSup[1]);
	wallShapeDefSup.shape = &wallEdgeSup;
	wallDefInf.type = b2_staticBody;
	wallDefInf.position.Set(-1,-1);
	vsInf[0].Set(0.00,0.56);
	vsInf[1].Set(1.92,0.56);
	wallEdgeInf.Set(vsInf[0],vsInf[1]);
	wallShapeDefInf.shape = &wallEdgeInf;
	for(i=0;i<3*qtd;i+=1) {
		WallManager::esq_sup_meio[i] = Mundo::getb2World()->CreateBody(&wallDefEsqSupMeio);
		WallManager::esq_sup_meio[i]->CreateFixture(&wallShapeDefEsqSupMeio);
		WallManager::dir_sup_meio[i] = Mundo::getb2World()->CreateBody(&wallDefDirSupMeio);
		WallManager::dir_sup_meio[i]->CreateFixture(&wallShapeDefDirSupMeio);
		WallManager::esq_inf_meio[i] = Mundo::getb2World()->CreateBody(&wallDefEsqInfMeio);
		WallManager::esq_inf_meio[i]->CreateFixture(&wallShapeDefEsqInfMeio);
		WallManager::dir_inf_meio[i] = Mundo::getb2World()->CreateBody(&wallDefDirInfMeio);
		WallManager::dir_inf_meio[i]->CreateFixture(&wallShapeDefDirInfMeio);
		WallManager::dir_inf_inic[i] = Mundo::getb2World()->CreateBody(&wallDefDirInfInic);
		WallManager::dir_inf_inic[i]->CreateFixture(&wallShapeDefDirInfInic);
		WallManager::esq_inf_inic[i] = Mundo::getb2World()->CreateBody(&wallDefEsqInfInic);
		WallManager::esq_inf_inic[i]->CreateFixture(&wallShapeDefEsqInfInic);
		WallManager::dir_sup_inic[i] = Mundo::getb2World()->CreateBody(&wallDefDirSupInic);
		WallManager::dir_sup_inic[i]->CreateFixture(&wallShapeDefDirSupInic);
		WallManager::esq_sup_inic[i] = Mundo::getb2World()->CreateBody(&wallDefEsqSupInic);
		WallManager::esq_sup_inic[i]->CreateFixture(&wallShapeDefEsqSupInic);
		WallManager::dir[i] = Mundo::getb2World()->CreateBody(&wallDefDir);
		WallManager::dir[i]->CreateFixture(&wallShapeDefDir);
		WallManager::esq[i] = Mundo::getb2World()->CreateBody(&wallDefEsq);
		WallManager::esq[i]->CreateFixture(&wallShapeDefEsq);
		WallManager::sup[i] = Mundo::getb2World()->CreateBody(&wallDefSup);
		WallManager::sup[i]->CreateFixture(&wallShapeDefSup);
		WallManager::inf[i] = Mundo::getb2World()->CreateBody(&wallDefInf);
		WallManager::inf[i]->CreateFixture(&wallShapeDefInf);
	}
	WallManager::pista = p;
	WallManager::tileWidth = WallManager::pista->tileAt(ccp(0,0))->boundingBox().size.width;
	WallManager::tileHeight = WallManager::pista->tileAt(ccp(0,0))->boundingBox().size.height;
	WallManager::paredesPosicionadas = new int*[36*qtd];
	for(i=0;i<36*qtd;i++) {
		WallManager::paredesPosicionadas[i] = new int[2];
		WallManager::paredesPosicionadas[i][0] = -1;
		WallManager::paredesPosicionadas[i][1] = -1;
	}
}

void WallManager::posicionaParedes(CCRect r,int jogador) {
	int i,j;
	CCPoint p,p1 = r.origin;
	CCPoint p2 = r.origin;
	p1.x = (int)((p1.x+r.size.width)/WallManager::tileWidth);
	p1.y = (int)((WallManager::pista->boundingBox().size.height-p1.y-r.size.height)/WallManager::tileHeight);
	p2.x = (int)(p2.x/WallManager::tileWidth);
	p2.y = (int)((WallManager::pista->boundingBox().size.height-p2.y)/WallManager::tileHeight);
	for(i=p2.x;i<=p1.x;i++)
		for(j=p1.y;j<=p2.y;j++)
			WallManager::adicionaParede(p1,p2,ccp(i,j),jogador);
}

void WallManager::adicionaParede(CCPoint p1,CCPoint p2,CCPoint p,int jog) {
	int gid = WallManager::pista->tileGIDAt(p);
	int posParedes = (gid-WallManager::gid_esq_sup_meio)*3;
	if(gid!=WallManager::gid_branco&&gid!=WallManager::gid_completo&&!WallManager::buscaParede(p,jog,posParedes))
		WallManager::reposicionaParede(p1,p2,p,gid,jog,posParedes);
}

bool WallManager::buscaParede(CCPoint p,int jog,int posParedes) {
	int i,in=36*jog+posParedes,fim=36*jog+posParedes+3;
	for(i=in;i<fim;i+=1)
		if(p.x==WallManager::paredesPosicionadas[i][0]&&p.y==WallManager::paredesPosicionadas[i][1])
			return true;
	return false;
}

void WallManager::reposicionaParede(CCPoint p1,CCPoint p2,CCPoint p,int gid,int jog,int posParedes) {
	int i,in=36*jog+posParedes,fim=36*jog+posParedes+3;
	b2Vec2 pos;
	for(i=in;i<fim;i+=1)
		if(WallManager::paredesPosicionadas[i][0]<p2.x||WallManager::paredesPosicionadas[i][0]>p1.x
				||WallManager::paredesPosicionadas[i][1]<p1.y||WallManager::paredesPosicionadas[i][1]>p2.y)
			break;
	WallManager::paredesPosicionadas[i][0] = p.x;
	WallManager::paredesPosicionadas[i][1] = p.y;
	i -= in;
	i += 3*jog;
	pos.x = p.x*1.92;
	pos.y = (WallManager::pista->getLayerSize().height-p.y-1)*1.92;
	if(gid==WallManager::gid_esq_sup_meio)
		WallManager::esq_sup_meio[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_dir_sup_meio)
		WallManager::dir_sup_meio[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_esq_inf_meio)
		WallManager::esq_inf_meio[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_dir_inf_meio)
		WallManager::dir_inf_meio[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_dir_inf_inic)
		WallManager::dir_inf_inic[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_esq_inf_inic)
		WallManager::esq_inf_inic[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_dir_sup_inic)
		WallManager::dir_sup_inic[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_esq_sup_inic)
		WallManager::esq_sup_inic[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_dir)
		WallManager::dir[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_esq)
		WallManager::esq[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_sup)
		WallManager::sup[i]->SetTransform(pos,0.0);
	else if(gid==WallManager::gid_inf)
		WallManager::inf[i]->SetTransform(pos,0.0);
}

void WallManager::release() {
	int i;
	for(i=0;i<36*WallManager::qtdJogadores;i++)
		delete WallManager::paredesPosicionadas[i];
	for(i=0;i<3*WallManager::qtdJogadores;i+=1) {
		Mundo::getb2World()->DestroyBody(WallManager::esq_sup_meio[i]);
		Mundo::getb2World()->DestroyBody(WallManager::dir_sup_meio[i]);
		Mundo::getb2World()->DestroyBody(WallManager::esq_inf_meio[i]);
		Mundo::getb2World()->DestroyBody(WallManager::dir_inf_meio[i]);
		Mundo::getb2World()->DestroyBody(WallManager::dir_inf_inic[i]);
		Mundo::getb2World()->DestroyBody(WallManager::esq_inf_inic[i]);
		Mundo::getb2World()->DestroyBody(WallManager::dir_sup_inic[i]);
		Mundo::getb2World()->DestroyBody(WallManager::esq_sup_inic[i]);
		Mundo::getb2World()->DestroyBody(WallManager::dir[i]);
		Mundo::getb2World()->DestroyBody(WallManager::esq[i]);
		Mundo::getb2World()->DestroyBody(WallManager::sup[i]);
		Mundo::getb2World()->DestroyBody(WallManager::inf[i]);
	}
	delete WallManager::paredesPosicionadas;
	delete WallManager::esq_sup_meio;
	delete WallManager::dir_sup_meio;
	delete WallManager::esq_inf_meio;
	delete WallManager::dir_inf_meio;
	delete WallManager::dir_inf_inic;
	delete WallManager::esq_inf_inic;
	delete WallManager::dir_sup_inic;
	delete WallManager::esq_sup_inic;
	delete WallManager::dir;
	delete WallManager::esq;
	delete WallManager::sup;
	delete WallManager::inf;
}