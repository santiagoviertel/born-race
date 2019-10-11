#include "Engine.h"
#include "Constantes.h"

//Aceleracoes
#define ACELERACAO_FACIL 2
#define ACELERACAO_MEDIO 3
#define ACELERACAO_DIFICIL 4

//Velocidades maximas na corrida
#define VELOCIDADE_MAXIMA_FACIL 4
#define VELOCIDADE_MAXIMA_MEDIO 6
#define VELOCIDADE_MAXIMA_DIFICIL 8

//Modificadores sobre o efeito da velocidade e aceleracao
#define MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA 0.25
#define MODIFICADOR_AUMENTO_VELOCIDADE_DNA 1.5
#define MODIFICADOR_AUMENTO_ACELERACAO_ITEM_VITAMINA 2
#define MODIFICADOR_AUMENTO_VELOCIDADE_ITEM_VITAMINA 1

//Velocidades para rotação da roda dianteira
#define VELOCIDADE_MAXIMA_VOLANTE_SETAS 3.5
#define VELOCIDADE_MAXIMA_VOLANTE_ACELEROMETRO 10

//Tempos para animacao provocada pela velocidade
#define TEMPO_FRAME_CORPO_VEL_BAIXA 0.14
#define TEMPO_FRAME_CORPO_VEL_NORMAL 0.10
#define TEMPO_FRAME_CORPO_VEL_ALTA 0.05
#define TEMPO_FRAME_CAUDA 0.05

//Velocidades para animar mais rápido quando a velocidade é maior
#define VELOCIDADE_PARADO_CORPO (0.01*VELOCIDADE_MAXIMA_FACIL)*(0.01*VELOCIDADE_MAXIMA_FACIL)
#define VELOCIDADE_BAIXA_CORPO (0.357*VELOCIDADE_MAXIMA_FACIL)*(0.357*VELOCIDADE_MAXIMA_FACIL)
#define VELOCIDADE_NORMAL_CORPO (0.714*VELOCIDADE_MAXIMA_FACIL)*(0.714*VELOCIDADE_MAXIMA_FACIL)

//Variaveis fisicas
#define GRAVIDADE 10.0
#define COEFICIENTE_ATRITO_ESTATICO 0.72
#define COEFICIENTE_ATRITO_DINAMICO 0.65
#define AMPLITUDE_DISTRIBUICAO_NORMAL_FORCA_ATRITO 30

//Status do jogador
#define STATUS_NORMAL 0
#define STATUS_REDUCAOVELOCIDADE 1
#define STATUS_INVERSAOCONTROLE 2
#define STATUS_AUMENTOVELOCIDADE 4
#define STATUS_INVENCIVEL 8
#define STATUS_AUTO 16
#define STATUS_PARALISADO 32

Competidor::Competidor(int personagem,CCPoint largada,float direction,int vitaminas) {
	Competidor::status = STATUS_NORMAL;
	Competidor::colisao = 0;
	Competidor::vitaminas = vitaminas;
	CCArray* sequenciaFramesCorpo1 = CCArray::create();
	CCArray* sequenciaFramesCorpo2 = CCArray::create();
	CCArray* sequenciaFramesCorpo3 = CCArray::create();
	b2Vec2 verticesCorpo[6];
	b2CircleShape cabeca;
	CCPoint ancoraCorpo;
	float desvioCauda;
	switch(personagem) {
	case TOMMY:
		break;
	case SAMMY:
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy02.png"));
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy05.png"));
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy02.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy03.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy02.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy05.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy06.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy05.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy02.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy03.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy04.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy03.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy02.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy05.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy06.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy07.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy06.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy05.png"));
		sequenciaFramesCorpo3->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Sammy01.png"));
		verticesCorpo[0].Set(0.09,-0.09);
		verticesCorpo[1].Set(-0.1,-0.09);
		verticesCorpo[2].Set(-0.32,-0.31);
		verticesCorpo[3].Set(-0.14,-0.71);
		verticesCorpo[4].Set(0.13,-0.71);
		verticesCorpo[5].Set(0.31,-0.31);
		cabeca.m_radius = 0.37;
		cabeca.m_p.Set(0.0,0.25);
		ancoraCorpo = ccp(0.5,0.63);
		desvioCauda = 0.8*Mundo::getPTMRatio();
		Competidor::spriteCorpo = CCSprite::createWithSpriteFrameName("Sammy01.png");
		break;
	case RHINO:
		break;
	case MIKE:
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike02.png"));
		sequenciaFramesCorpo1->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike01.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike02.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike03.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike02.png"));
		sequenciaFramesCorpo2->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Mike01.png"));
		sequenciaFramesCorpo3 = sequenciaFramesCorpo2;
		verticesCorpo[0].Set(0.19,-0.12);
		verticesCorpo[1].Set(-0.19,-0.12);
		verticesCorpo[2].Set(-0.47,-0.3);
		verticesCorpo[3].Set(-0.24,-0.87);
		verticesCorpo[4].Set(0.23,-0.87);
		verticesCorpo[5].Set(0.47,-0.3);
		cabeca.m_radius = 0.49;
		cabeca.m_p.Set(0.0,0.33);
		ancoraCorpo = ccp(0.5,0.53);
		desvioCauda = 0.87*Mundo::getPTMRatio();
		Competidor::spriteCorpo = CCSprite::createWithSpriteFrameName("Mike01.png");
		break;
	case BETH:
		break;
	case YONG:
		break;
	case BRIAN:
		break;
	case CARLINHOS:
		break;
	case MARY:
		break;
	case JACK:
		break;
	case KELLY:
		break;
	case LEON:
		break;
	case MONKY:
		break;
	}

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	Competidor::desvioNariz = Mundo::getPTMRatio()*(cabeca.m_p.y + cabeca.m_radius);
	b2Vec2 desvioLargada = b2Vec2(0.0f,cabeca.m_p.y + cabeca.m_radius);
	desvioLargada.x = -desvioLargada.y*sin(direction);
	desvioLargada.y = desvioLargada.y*cos(direction);
	bodyDef.position = b2Vec2(largada.x/Mundo::getPTMRatio() - desvioLargada.x,largada.y/Mundo::getPTMRatio() - desvioLargada.y);
	bodyDef.angle = direction;
	bodyDef.userData = new Sensorable(SENSORABLE_COMPETIDOR,this);
	Competidor::geometriaCorpo = Mundo::getb2World()->CreateBody(&bodyDef);

	b2PolygonShape corpo;
	corpo.Set(verticesCorpo,6);
	float densidade = 1.0f;
	Competidor::geometriaCorpo->CreateFixture(&corpo,densidade);
	Competidor::geometriaCorpo->CreateFixture(&cabeca,densidade);

	Competidor::spriteCorpo->setAnchorPoint(ancoraCorpo);
	Competidor::spriteCorpo->setPosition(ccp(Competidor::geometriaCorpo->GetWorldCenter().x*Mundo::getPTMRatio(),Competidor::geometriaCorpo->GetWorldCenter().y*Mundo::getPTMRatio()));
	Competidor::spriteCorpo->setRotation(-((Competidor::geometriaCorpo->GetAngle()*180.0f)/M_PI));
	SpriteSource::addChild(Competidor::spriteCorpo,CAMADA_2);
	Competidor::spriteCauda = CCSprite::createWithSpriteFrameName("Cauda1.png");
	Competidor::spriteCauda->setAnchorPoint(ccp(0.5,1.0 + desvioCauda/Competidor::spriteCauda->boundingBox().size.height));
	Competidor::spriteCauda->setPosition(Competidor::spriteCorpo->getPosition());
	Competidor::spriteCauda->setRotation(Competidor::spriteCorpo->getRotation());
	SpriteSource::addChild(Competidor::spriteCauda,CAMADA_3);

	b2Vec2 pos = b2Vec2(0.0f,0.4f);
	float aux = pos.x;
	pos.x = pos.x*cos(direction) - pos.y*sin(direction);
	pos.y = aux*sin(direction) + pos.y*cos(direction);
	b2BodyDef frontWheelDef;
	frontWheelDef.type = b2_dynamicBody;
	frontWheelDef.position = Competidor::geometriaCorpo->GetWorldCenter();
	frontWheelDef.position.operator+=(pos);
	frontWheelDef.angle = direction;
	Competidor::rodaDianteira = Mundo::getb2World()->CreateBody(&frontWheelDef);

	b2PolygonShape frontWheelShape;
	frontWheelShape.SetAsBox(0.05f,0.15f);
	Competidor::rodaDianteira->CreateFixture(&frontWheelShape,densidade);

	b2RevoluteJointDef frontJointDef;
	frontJointDef.Initialize(Competidor::geometriaCorpo,Competidor::rodaDianteira,Competidor::rodaDianteira->GetWorldCenter());
	frontJointDef.enableMotor = true;
	frontJointDef.maxMotorTorque = 100;
	Competidor::juntaRodaDianteira = static_cast<b2RevoluteJoint*>(Mundo::getb2World()->CreateJoint(&frontJointDef));
	Competidor::velocidadeRotacao = 0.0f;

	pos = b2Vec2(0,-0.4);
	aux = pos.x;
	pos.x = pos.x*cos(direction) - pos.y*sin(direction);
	pos.y = aux*sin(direction) + pos.y*cos(direction);
	b2BodyDef rearWheelDef;
	rearWheelDef.type = b2_dynamicBody;
	rearWheelDef.position = Competidor::geometriaCorpo->GetWorldCenter();
	rearWheelDef.position.operator+=(pos);
	rearWheelDef.angle = direction;
	Competidor::rodaTraseira = Mundo::getb2World()->CreateBody(&rearWheelDef);

	b2PolygonShape rearWheelShape;
	rearWheelShape.SetAsBox(0.05,0.15);
	Competidor::rodaTraseira->CreateFixture(&rearWheelShape,densidade);

	b2PrismaticJointDef rearJointDef;
	rearJointDef.Initialize(Competidor::geometriaCorpo,Competidor::rodaTraseira,Competidor::rodaTraseira->GetWorldCenter(),b2Vec2(1,0));
	rearJointDef.enableLimit = true;
	rearJointDef.lowerTranslation = 0;
	rearJointDef.upperTranslation = 0;
	Competidor::juntaRodaTraseira = static_cast<b2PrismaticJoint*>(Mundo::getb2World()->CreateJoint(&rearJointDef));

	Competidor::velocidadeRotacao = 0;
	Competidor::inicializaVariaveisFisicas();

	Competidor::velAnimacao = Competidor::VelocidadeAnimacao::create();
	Engine::getSharedEngine()->addChild(Competidor::velAnimacao);
	Competidor::velAnimacao->setVars(Competidor::spriteCorpo,Competidor::spriteCauda,Competidor::geometriaCorpo,sequenciaFramesCorpo1,sequenciaFramesCorpo2,sequenciaFramesCorpo3);
}

void Competidor::updateAccelerometer(float p) {
	Competidor::velocidadeRotacao = -p;
}

void Competidor::turnRight() {
	Competidor::velocidadeRotacao = -ANGULO_MAXIMO_VOLANTE;
}

void Competidor::turnLeft() {
	Competidor::velocidadeRotacao = ANGULO_MAXIMO_VOLANTE;
}

void Competidor::dontTurn() {
	Competidor::velocidadeRotacao = 0.0f;
}

void Competidor::startRace() {
	switch(Mundo::getDificuldade()) {
	case DIFICULDADE_FACIL:
		Competidor::aceleracao = ACELERACAO_FACIL;
		Competidor::velocidade_maxima = VELOCIDADE_MAXIMA_FACIL;
		break;
	case DIFICULDADE_MEDIO:
		Competidor::aceleracao = ACELERACAO_MEDIO;
		Competidor::velocidade_maxima = VELOCIDADE_MAXIMA_MEDIO;
		break;
	case DIFICULDADE_DIFICIL:
		Competidor::aceleracao = ACELERACAO_DIFICIL;
		Competidor::velocidade_maxima = VELOCIDADE_MAXIMA_DIFICIL;
		break;
	}
	if(Competidor::vitaminas&VITAMINA_ACELERACAO)
		Competidor::aceleracao += MODIFICADOR_AUMENTO_ACELERACAO_ITEM_VITAMINA;
	if(Competidor::vitaminas&VITAMINA_VELOCIDADE)
		Competidor::velocidade_maxima += MODIFICADOR_AUMENTO_VELOCIDADE_ITEM_VITAMINA;

	Competidor::forcaAceleracaoMaxima = (Competidor::geometriaCorpo->GetMass() + Competidor::rodaDianteira->GetMass() + Competidor::rodaTraseira->GetMass())*Competidor::aceleracao;
	Competidor::velAnimacao->startRace();
}

void Competidor::inicializaVariaveisFisicas() {
	float md,mt;
	float x = sqrt(
			(pow(Competidor::geometriaCorpo->GetWorldCenter().x-Competidor::rodaTraseira->GetWorldCenter().x,2) + pow(Competidor::geometriaCorpo->GetWorldCenter().y-Competidor::rodaTraseira->GetWorldCenter().y,2))
			/(pow(Competidor::rodaDianteira->GetWorldCenter().x-Competidor::rodaTraseira->GetWorldCenter().x,2) + pow(Competidor::rodaDianteira->GetWorldCenter().y-Competidor::rodaTraseira->GetWorldCenter().y,2)));
	md = x*Competidor::geometriaCorpo->GetMass();
	mt = Competidor::geometriaCorpo->GetMass() - md;
	md += Competidor::rodaDianteira->GetMass();
	mt += Competidor::rodaTraseira->GetMass();
	Competidor::impulsoPerpendicularMaximoDianteira = AMPLITUDE_DISTRIBUICAO_NORMAL_FORCA_ATRITO/(GRAVIDADE*COEFICIENTE_ATRITO_ESTATICO*md*sqrt(2*M_PI));
	Competidor::impulsoPerpendicularMaximoTraseira = AMPLITUDE_DISTRIBUICAO_NORMAL_FORCA_ATRITO/(GRAVIDADE*COEFICIENTE_ATRITO_ESTATICO*mt*sqrt(2*M_PI));
	Competidor::velocidadePerpendicularMaximaDianteira = Competidor::impulsoPerpendicularMaximoDianteira/md;
	Competidor::velocidadePerpendicularMaximaTraseira = Competidor::impulsoPerpendicularMaximoTraseira/mt;
	Competidor::forcaAtritoDinamicoDianteira = COEFICIENTE_ATRITO_DINAMICO*GRAVIDADE*md;
	Competidor::forcaAtritoDinamicoTraseira = COEFICIENTE_ATRITO_DINAMICO*GRAVIDADE*mt;
	Competidor::velocidadePerpendicularAnteriorDianteira = 0.0f;
	Competidor::velocidadePerpendicularAnteriorTraseira = 0.0f;
}

void Competidor::aplicaForcasAtritoPerpendicularesDianteira() {
	b2Vec2 vetorLocal = Competidor::rodaDianteira->GetWorldVector(b2Vec2(1,0));
	b2Vec2 velocidade = Competidor::rodaDianteira->GetLinearVelocity();
	float vp = vetorLocal.x*velocidade.x + vetorLocal.y*velocidade.y;
	/*Aplica Impulso Linear E inicia a derrapagem*/
	/*Se a velocidade perpendicular passou da máxima permitida E*/
	/*Se a roda iniciou velocidade OU inverteu o sentido da velocidade derrapando ou nao*/
	if(abs(vp)>=Competidor::velocidadePerpendicularMaximaDianteira&&((vp<0.0f&&Competidor::velocidadePerpendicularAnteriorDianteira>=0.0f)||(vp>0.0f&&Competidor::velocidadePerpendicularAnteriorDianteira<=0.0f))) {
		if(vp>0.0f)
			Competidor::rodaDianteira->ApplyLinearImpulse(b2Vec2(-Competidor::impulsoPerpendicularMaximoDianteira*vetorLocal.x,-Competidor::impulsoPerpendicularMaximoDianteira*vetorLocal.y),Competidor::rodaDianteira->GetWorldCenter());
		else
			Competidor::rodaDianteira->ApplyLinearImpulse(b2Vec2(Competidor::impulsoPerpendicularMaximoDianteira*vetorLocal.x,Competidor::impulsoPerpendicularMaximoDianteira*vetorLocal.y),Competidor::rodaDianteira->GetWorldCenter());
		Competidor::velocidadePerpendicularAnteriorDianteira = vp;
	}
	/*Zera a velocidade perpendicular*/
	/*Se não estava derrapando OU*/
	/*Se inverteu o sentido da velocidade*/
	if(Competidor::velocidadePerpendicularAnteriorDianteira==0.0f||(vp<0.0f&&Competidor::velocidadePerpendicularAnteriorDianteira>0.0f)||(vp>0.0f&&Competidor::velocidadePerpendicularAnteriorDianteira<0.0f)) {
		velocidade.x -= vp*vetorLocal.x;
		velocidade.y -= vp*vetorLocal.y;
		Competidor::rodaDianteira->SetLinearVelocity(velocidade);
		Competidor::velocidadePerpendicularAnteriorDianteira = 0.0f;
	}
	/*Aplica forca de atrito dinamico*/
	/*Se ele já está derrapando*/
	if(Competidor::velocidadePerpendicularAnteriorDianteira!=0.0f) {
		if(vp>0.0f)
			Competidor::rodaDianteira->ApplyForceToCenter(b2Vec2(-Competidor::forcaAtritoDinamicoDianteira*vetorLocal.x,-Competidor::forcaAtritoDinamicoDianteira*vetorLocal.y));
		else
			Competidor::rodaDianteira->ApplyForceToCenter(b2Vec2(Competidor::forcaAtritoDinamicoDianteira*vetorLocal.x,Competidor::forcaAtritoDinamicoDianteira*vetorLocal.y));
		Competidor::velocidadePerpendicularAnteriorDianteira = vp;
	}
}

void Competidor::aplicaForcasAtritoPerpendicularesTraseira() {
	b2Vec2 vetorLocal = Competidor::rodaTraseira->GetWorldVector(b2Vec2(1,0));
	b2Vec2 velocidade = Competidor::rodaTraseira->GetLinearVelocity();
	float vp = vetorLocal.x*velocidade.x + vetorLocal.y*velocidade.y;
	/*Aplica Impulso Linear E inicia a derrapagem*/
	/*Se a velocidade perpendicular passou da máxima permitida E*/
	/*Se a roda iniciou velocidade OU inverteu o sentido da velocidade derrapando ou nao*/
	if(abs(vp)>=Competidor::velocidadePerpendicularMaximaTraseira&&((vp<0.0f&&Competidor::velocidadePerpendicularAnteriorTraseira>=0.0f)||(vp>0.0f&&Competidor::velocidadePerpendicularAnteriorTraseira<=0.0f))) {
		if(vp>0.0f)
			Competidor::rodaTraseira->ApplyLinearImpulse(b2Vec2(-Competidor::impulsoPerpendicularMaximoTraseira*vetorLocal.x,-Competidor::impulsoPerpendicularMaximoTraseira*vetorLocal.y),Competidor::rodaTraseira->GetWorldCenter());
		else
			Competidor::rodaTraseira->ApplyLinearImpulse(b2Vec2(Competidor::impulsoPerpendicularMaximoTraseira*vetorLocal.x,Competidor::impulsoPerpendicularMaximoTraseira*vetorLocal.y),Competidor::rodaTraseira->GetWorldCenter());
		Competidor::velocidadePerpendicularAnteriorTraseira = vp;
	}
	/*Zera a velocidade perpendicular*/
	/*Se não estava derrapando OU*/
	/*Se inverteu o sentido da velocidade*/
	if(Competidor::velocidadePerpendicularAnteriorTraseira==0.0f||(vp<0.0f&&Competidor::velocidadePerpendicularAnteriorTraseira>0.0f)||(vp>0.0f&&Competidor::velocidadePerpendicularAnteriorTraseira<0.0f)) {
		velocidade.x -= vp*vetorLocal.x;
		velocidade.y -= vp*vetorLocal.y;
		Competidor::rodaTraseira->SetLinearVelocity(velocidade);
		Competidor::velocidadePerpendicularAnteriorTraseira = 0.0f;
	}
	/*Aplica forca de atrito dinamico*/
	/*Se ele já está derrapando*/
	if(Competidor::velocidadePerpendicularAnteriorTraseira!=0.0f) {
		if(vp>0.0f)
			Competidor::rodaTraseira->ApplyForceToCenter(b2Vec2(-Competidor::forcaAtritoDinamicoTraseira*vetorLocal.x,-Competidor::forcaAtritoDinamicoTraseira*vetorLocal.y));
		else
			Competidor::rodaTraseira->ApplyForceToCenter(b2Vec2(Competidor::forcaAtritoDinamicoTraseira*vetorLocal.x,Competidor::forcaAtritoDinamicoTraseira*vetorLocal.y));
		Competidor::velocidadePerpendicularAnteriorTraseira = vp;
	}
}

void Competidor::update(float dt) {
	float maxVelMod = 1.0f;
	if(Competidor::status&STATUS_REDUCAOVELOCIDADE) {
		maxVelMod = MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA;
	}
	if(Competidor::status&STATUS_AUMENTOVELOCIDADE) {
		maxVelMod *= MODIFICADOR_AUMENTO_VELOCIDADE_DNA;
		Competidor::dnaTimer -= dt;
		if(Competidor::dnaTimer<=0) {
			Competidor::removerEfeito_AumentoVelocidade();
		}
	}
	if(Competidor::status&STATUS_INVENCIVEL) {
		Competidor::testosteronaTimer -= dt;
		if(Competidor::testosteronaTimer<=0) {
			Competidor::removerEfeito_Invencibilidade();
		}
	}
	if(Competidor::status&STATUS_AUTO) {
		Competidor::autoTimer -= dt;
		if(Competidor::autoTimer<=0) {
			Competidor::removerEfeito_direcaoAutomatica();
		}
	}
	if(Competidor::status&STATUS_PARALISADO){
		Competidor::paralisiaTimer -= dt;
		if(Competidor::paralisiaTimer<=0){
			Competidor::removerEfeito_Paralisia();
		}
	}

	Competidor::aplicaForcasAtritoPerpendicularesDianteira();
	Competidor::aplicaForcasAtritoPerpendicularesTraseira();
	Competidor::spriteCorpo->setPosition(ccp(Competidor::geometriaCorpo->GetWorldCenter().x*Mundo::getPTMRatio(),Competidor::geometriaCorpo->GetWorldCenter().y*Mundo::getPTMRatio()));
	Competidor::spriteCorpo->setRotation(-((Competidor::geometriaCorpo->GetAngle()*180.0f)/M_PI));
	Competidor::spriteCauda->setPosition(Competidor::spriteCorpo->getPosition());
	Competidor::spriteCauda->setRotation(Competidor::spriteCorpo->getRotation());

	float mspeed = Competidor::velocidadeRotacao - Competidor::juntaRodaDianteira->GetJointAngle();
	if(Engine::getSharedEngine()->isAccelerometerEnabled())
		Competidor::juntaRodaDianteira->SetMotorSpeed(mspeed*VELOCIDADE_MAXIMA_VOLANTE_ACELEROMETRO);
	else
		Competidor::juntaRodaDianteira->SetMotorSpeed(mspeed*VELOCIDADE_MAXIMA_VOLANTE_SETAS);
	b2Vec2 vel = Competidor::rodaDianteira->GetLinearVelocity();
	b2Vec2 vetorDirecao = Competidor::rodaDianteira->GetWorldVector(b2Vec2(0,1));
	if(Competidor::status&STATUS_AUMENTOVELOCIDADE) {
		Competidor::rodaDianteira->ApplyForceToCenter(Competidor::rodaDianteira->GetWorldVector(b2Vec2(0,Competidor::forcaAceleracaoMaxima*((maxVelMod*Competidor::velocidade_maxima)/2))));
	}
	else {
		float velocidade = vel.x*vetorDirecao.x + vel.y*vetorDirecao.y;
		Competidor::rodaDianteira->ApplyForceToCenter(Competidor::rodaDianteira->GetWorldVector(b2Vec2(0,Competidor::forcaAceleracaoMaxima*((maxVelMod*Competidor::velocidade_maxima-velocidade)/2))));
	}
}

CCSprite* Competidor::getSprite() {
	return Competidor::spriteCorpo;
}

b2Body* Competidor::getBody() {
	return Competidor::geometriaCorpo;
}

b2Body* Competidor::getFrontWheel() {
	return Competidor::rodaDianteira;
}

void Competidor::getPontoNariz(int* p) {
	b2Vec2 vet = Competidor::geometriaCorpo->GetWorldVector(b2Vec2(0,1));
	p[0] = Competidor::spriteCorpo->getPositionX() + vet.x*Competidor::desvioNariz;
	p[1] = Competidor::spriteCorpo->getPositionY() + vet.y*Competidor::desvioNariz;
}

Competidor::~Competidor() {
	Engine::getSharedEngine()->removeChild(Competidor::velAnimacao,true);
	Mundo::getb2World()->DestroyJoint(Competidor::juntaRodaTraseira);
	Mundo::getb2World()->DestroyBody(Competidor::rodaTraseira);
	Mundo::getb2World()->DestroyJoint(Competidor::juntaRodaDianteira);
	Mundo::getb2World()->DestroyBody(Competidor::rodaDianteira);
	SpriteSource::removeChild(Competidor::spriteCauda);
	SpriteSource::removeChild(Competidor::spriteCorpo);
	Mundo::getb2World()->DestroyBody(Competidor::geometriaCorpo);
}

bool Competidor::VelocidadeAnimacao::init() {
	if(!CCLayer::init())
		return false;
	return true;
}

void Competidor::VelocidadeAnimacao::setVars(CCSprite* spCorpo,CCSprite* spCauda,b2Body* corpo,CCArray* sequenciaFramesCorpo1,CCArray* sequenciaFramesCorpo2,CCArray* sequenciaFramesCorpo3) {
	VelocidadeAnimacao::intervalo = 0.0f;
	VelocidadeAnimacao::spriteCorpo = spCorpo;
	VelocidadeAnimacao::spriteCauda = spCauda;
	VelocidadeAnimacao::geometriaCorpo = corpo;
	CCAnimation *anim = CCAnimation::createWithSpriteFrames(sequenciaFramesCorpo1,TEMPO_FRAME_CORPO_VEL_BAIXA);
	VelocidadeAnimacao::animacaoCorpoVelBaixa = CCAnimate::create(anim);
	VelocidadeAnimacao::animacaoCorpoVelBaixa->retain();
	anim = CCAnimation::createWithSpriteFrames(sequenciaFramesCorpo2,TEMPO_FRAME_CORPO_VEL_NORMAL);
	VelocidadeAnimacao::animacaoCorpoVelNormal = CCAnimate::create(anim);
	VelocidadeAnimacao::animacaoCorpoVelNormal->retain();
	anim = CCAnimation::createWithSpriteFrames(sequenciaFramesCorpo3,TEMPO_FRAME_CORPO_VEL_ALTA);
	VelocidadeAnimacao::animacaoCorpoVelAlta = CCAnimate::create(anim);
	VelocidadeAnimacao::animacaoCorpoVelAlta->retain();

	CCArray* sequenciaFramesCauda = CCArray::create();
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda2.png"));
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda3.png"));
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda4.png"));
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda3.png"));
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda2.png"));
	sequenciaFramesCauda->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Cauda1.png"));
	anim = CCAnimation::createWithSpriteFrames(sequenciaFramesCauda,TEMPO_FRAME_CAUDA);
	VelocidadeAnimacao::animacaoCauda = CCAnimate::create(anim);
	VelocidadeAnimacao::animacaoCauda->retain();
}

void Competidor::VelocidadeAnimacao::startRace() {
	VelocidadeAnimacao::updateAnimacaoCorpo();
	VelocidadeAnimacao::updateAnimacaoCauda();
	schedule(schedule_selector(VelocidadeAnimacao::updateAnimacaoCauda),VelocidadeAnimacao::animacaoCauda->getDuration());
}

void Competidor::VelocidadeAnimacao::updateAnimacaoCorpo() {
	float aux,velocidade = VelocidadeAnimacao::geometriaCorpo->GetLinearVelocity().LengthSquared();
	if(velocidade<VELOCIDADE_PARADO_CORPO)
		aux = 0.1;
	else if(velocidade<VELOCIDADE_BAIXA_CORPO) {
		aux = VelocidadeAnimacao::animacaoCorpoVelBaixa->getDuration();
		VelocidadeAnimacao::spriteCorpo->runAction(static_cast<CCAction*>(VelocidadeAnimacao::animacaoCorpoVelBaixa->copy()->autorelease()));
	}
	else if(velocidade<VELOCIDADE_NORMAL_CORPO) {
		aux = VelocidadeAnimacao::animacaoCorpoVelNormal->getDuration();
		VelocidadeAnimacao::spriteCorpo->runAction(static_cast<CCAction*>(VelocidadeAnimacao::animacaoCorpoVelNormal->copy()->autorelease()));
	}
	else {
		aux = VelocidadeAnimacao::animacaoCorpoVelAlta->getDuration();
		VelocidadeAnimacao::spriteCorpo->runAction(static_cast<CCAction*>(VelocidadeAnimacao::animacaoCorpoVelAlta->copy()->autorelease()));
	}
	if(aux!=VelocidadeAnimacao::intervalo) {
		VelocidadeAnimacao::intervalo = aux;
		schedule(schedule_selector(VelocidadeAnimacao::updateAnimacaoCorpo),VelocidadeAnimacao::intervalo);
	}
}

void Competidor::VelocidadeAnimacao::updateAnimacaoCauda() {
	VelocidadeAnimacao::spriteCauda->stopAllActions();
	VelocidadeAnimacao::spriteCauda->setFlipX(!VelocidadeAnimacao::spriteCauda->isFlipX());
	VelocidadeAnimacao::spriteCauda->runAction(static_cast<CCAction*>(VelocidadeAnimacao::animacaoCauda->copy()->autorelease()));
}

Competidor::VelocidadeAnimacao::~VelocidadeAnimacao() {
	VelocidadeAnimacao::animacaoCorpoVelBaixa->release();
	VelocidadeAnimacao::animacaoCorpoVelNormal->release();
	VelocidadeAnimacao::animacaoCorpoVelAlta->release();
	VelocidadeAnimacao::animacaoCauda->release();
}

void Competidor::aplicarEfeito_ReducaoVelocidade() {
	if(!(Competidor::status&STATUS_REDUCAOVELOCIDADE)) {
		Competidor::status = Competidor::status|STATUS_REDUCAOVELOCIDADE;
		b2Vec2 velocidadeTraseira = Competidor::rodaTraseira->GetLinearVelocity();
		b2Vec2 velocidadeDianteira = Competidor::rodaDianteira->GetLinearVelocity();
		velocidadeDianteira.x*=MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA;
		velocidadeDianteira.y*=MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA;
		velocidadeTraseira.x*=MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA;
		velocidadeTraseira.y*=MODIFICADOR_REDUCAO_VELOCIDADE_ADESIVO_ESPERMICIDA;
		Competidor::rodaDianteira->SetLinearVelocity(velocidadeDianteira);
		Competidor::rodaTraseira->SetLinearVelocity(velocidadeTraseira);
	}
}

void Competidor::getVetorDiretor(float* p){
    b2Vec2 vet = geometriaCorpo->GetWorldVector(b2Vec2(0,1));
    p[0]=vet.x;
    p[1]=vet.y;
}

void Competidor::removerEfeito_ReducaoVelocidade() {
	Competidor::status = Competidor::status&~(STATUS_REDUCAOVELOCIDADE);
}

void Competidor::aplicarEfeito_AumentoVelocidade() {
	Competidor::status = Competidor::status|STATUS_AUMENTOVELOCIDADE;
	Competidor::dnaTimer = 0.25;
}

void Competidor::removerEfeito_AumentoVelocidade() {
	Competidor::dnaTimer = 0.0;
	Competidor::status = Competidor::status&~(STATUS_AUMENTOVELOCIDADE);
}

void Competidor::aplicarEfeito_Invencibilidade() {
	Competidor::status = Competidor::status|STATUS_INVENCIVEL;
	Competidor::testosteronaTimer = 5.0;
}

void Competidor::removerEfeito_Invencibilidade() {
	Competidor::testosteronaTimer = 0.0;
	Competidor::status = Competidor::status&~(STATUS_INVENCIVEL);
}

void Competidor::aplicarEfeito_direcaoAutomatica() {
	Competidor::status = Competidor::status|STATUS_AUTO;
	Competidor::autoTimer = 5.0;
}

void Competidor::removerEfeito_direcaoAutomatica() {
	Competidor::autoTimer = 0.0;
	Competidor::status = Competidor::status&~(STATUS_AUTO);
}

void Competidor::aplicarEfeito_Paralisia() {
	Competidor::status = Competidor::status|STATUS_PARALISADO;
	Competidor::paralisiaTimer = 1.0;
}

void Competidor::removerEfeito_Paralisia() {
	Competidor::paralisiaTimer = 0.0;
	Competidor::status = Competidor::status&~(STATUS_PARALISADO);
}

void Competidor::removerColisao() {
	Competidor::colisao--;
}

void Competidor::adicionarColisao() {
	Competidor::colisao++;
}

int Competidor::pegarColisaoDeItem() {
	return Competidor::colisao;
}