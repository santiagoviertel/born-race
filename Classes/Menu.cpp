#include "Engine.h"
#include "Constantes.h"

#include "GUI/CCScrollView/CCScrollView.h"

int Menu::state;
Menu* Menu::sharedMenu;
bool Menu::Championship::championship;
int Menu::Championship::tela;
int Menu::Championship::copa;
int Menu::Championship::pista;
int Menu::Championship::pontuacao[5];
int Menu::Championship::personagens[5];

bool Menu::init() {
	if(!CCLayer::init())
		return false;
	Menu::sharedMenu = this;
	return true;
}

void Menu::beginGame() {
	Menu::paraOpening();
}

void Menu::paraOpening() {
	Menu::state = OPENING;
	Menu::paraMainMenu();
}

void Menu::paraMainMenu() {
	int qtdOpcoes = 6;
	CCString *tela = new CCString("Main Menu");
	CCString **labels = new CCString*[6];
	labels[0] = new CCString("New Game");
	labels[1] = new CCString("Instructions");
	labels[2] = new CCString("Records");
	labels[3] = new CCString("Options");
	labels[4] = new CCString("About");
	labels[5] = new CCString("Shop");
	SEL_MenuHandler selectors[6] = {
			menu_selector(Menu::paraNewGame),
			menu_selector(Menu::paraInstructions),
			menu_selector(Menu::paraRecords),
			menu_selector(Menu::paraOptions),
			menu_selector(Menu::paraAbout),
			menu_selector(Menu::paraShop)};
	SEL_MenuHandler voltar = menu_selector(Menu::paraExit);
	Menu::state = MAINMENU;
	Menu::criaTela1(tela,qtdOpcoes,labels,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels[2];
	delete labels[3];
	delete labels[4];
	delete labels[5];
	delete labels;
	delete tela;
}

void Menu::paraInstructions() {
	int qtdOpcoes = 2;
	CCString *tela = new CCString("Instructions");
	CCString **labels = new CCString*[2];
	labels[0] = new CCString("Rules");
	labels[1] = new CCString("Commands");
	SEL_MenuHandler selectors[2] = {
			menu_selector(Menu::paraRules),
			menu_selector(Menu::paraCommands)};
	SEL_MenuHandler voltar = menu_selector(Menu::paraMainMenu);
	Menu::state = INSTRUCTIONS;
	Menu::criaTela1(tela,qtdOpcoes,labels,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels;
	delete tela;
}

void Menu::paraRecords() {

}

void Menu::paraRules() {

}

void Menu::paraCommands() {

}

void Menu::paraOptions() {

}

void Menu::paraAbout() {

}

void Menu::paraShop() {

}

void Menu::paraNewGame() {
	int qtdOpcoes = 5;
	CCString *tela = new CCString("New Game");
	CCString **imagens = new CCString*[5];
	imagens[0] = new CCString("personagens/Mike.png");
	imagens[1] = new CCString("personagens/Sammy.png");
	imagens[2] = new CCString("personagens/Tommy.png");
	imagens[3] = new CCString("personagens/Beth.png");
	imagens[4] = new CCString("personagens/Rhino.png");
	CCString **labels = new CCString*[5];
	labels[0] = new CCString("Mike");
	labels[1] = new CCString("Sammy");
	labels[2] = new CCString("Tommy");
	labels[3] = new CCString("Beth");
	labels[4] = new CCString("Rhino");
	SEL_MenuHandler selectors[5] = {
			menu_selector(Menu::selecaoPersonagemMike),
			menu_selector(Menu::selecaoPersonagemSammy),
			menu_selector(Menu::selecaoPersonagemTommy),
			menu_selector(Menu::selecaoPersonagemBeth),
			menu_selector(Menu::selecaoPersonagemRhino)};
	SEL_MenuHandler voltar = menu_selector(Menu::paraMainMenu);
	Menu::state = NEWGAME;
	Menu::criaTela2(tela,qtdOpcoes,imagens,labels,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels[2];
	delete labels[3];
	delete labels[4];
	delete labels;
	delete imagens[0];
	delete imagens[1];
	delete imagens[2];
	delete imagens[3];
	delete imagens[4];
	delete imagens;
	delete tela;
}

void Menu::paraGameMode() {
	int qtdOpcoes = 2;
	CCString *tela = new CCString("Game Mode");
	CCString **labels = new CCString*[2];
	labels[0] = new CCString("Championship");
	labels[1] = new CCString("Time Trial");
	SEL_MenuHandler selectors[2] = {
			menu_selector(Menu::selecaoCopa),
			menu_selector(Menu::selecaoTimeTrial)};
	SEL_MenuHandler voltar = menu_selector(Menu::paraNewGame);
	Menu::state = GAMEMODE;
	Menu::criaTela1(tela,qtdOpcoes,labels,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels;
	delete tela;
}

void Menu::paraSelectCup() {
	int qtdOpcoes = 5;
	CCString *tela = new CCString("Select Cup");
	CCString **imagens = new CCString*[5];
	imagens[0] = new CCString("pistas/Epididimo.png");
	imagens[1] = new CCString("pistas/Uretra.png");
	imagens[2] = new CCString("pistas/Utero.png");
	imagens[3] = new CCString("pistas/Ovario.png");
	imagens[4] = new CCString("pistas/Camisinha.png");
	CCString **labels = new CCString*[5];
	labels[0] = new CCString("Epididymis Cup");
	labels[1] = new CCString("Urethra Cup");
	labels[2] = new CCString("Uterus Cup");
	labels[3] = new CCString("Ovary Cup");
	labels[4] = new CCString("Condom Cup");
	int classificacoes[5] = {3,2,1,0,0};
	SEL_MenuHandler selectors[5] = {
			menu_selector(Menu::selecaoCopaEpididymis),
			menu_selector(Menu::selecaoCopaUrethra),
			menu_selector(Menu::selecaoCopaUterus),
			menu_selector(Menu::selecaoCopaOvary),
			menu_selector(Menu::selecaoCopaCondom)};
	SEL_MenuHandler voltar = menu_selector(Menu::paraGameMode);
	Menu::state = SELECTCUP;
	Menu::criaTela3(tela,qtdOpcoes,imagens,labels,classificacoes,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels[2];
	delete labels[3];
	delete labels[4];
	delete labels;
	delete imagens[0];
	delete imagens[1];
	delete imagens[2];
	delete imagens[3];
	delete imagens[4];
	delete imagens;
	delete tela;
}

void Menu::paraSelectTrack() {
	int qtdOpcoes = 4;
	CCString *tela = new CCString("Select Track");
	CCString **imagens = new CCString*[4];
	CCString **labels = new CCString*[4];
	SEL_MenuHandler selectors[4];
	if(Menu::Championship::copa==EPIDIDYMIS) {
		imagens[0] = new CCString("pistas/Epididimo1.png");
		imagens[1] = new CCString("pistas/Epididimo2.png");
		imagens[2] = new CCString("pistas/Epididimo3.png");
		imagens[3] = new CCString("pistas/Epididimo4.png");
		labels[0] = new CCString("Head");
		labels[1] = new CCString("Body");
		labels[2] = new CCString("Tail");
		labels[3] = new CCString("Duct");
		selectors[0] = menu_selector(Menu::selecaoPistaEpididymis1);
		selectors[1] = menu_selector(Menu::selecaoPistaEpididymis2);
		selectors[2] = menu_selector(Menu::selecaoPistaEpididymis3);
		selectors[3] = menu_selector(Menu::selecaoPistaEpididymis4);
	} else if(Menu::Championship::copa==URETHRA) {
		imagens[0] = new CCString("pistas/Uretra1.png");
		imagens[1] = new CCString("pistas/Uretra2.png");
		imagens[2] = new CCString("pistas/Uretra3.png");
		imagens[3] = new CCString("pistas/Uretra4.png");
		labels[0] = new CCString("Prostatic");
		labels[1] = new CCString("Bulbar");
		labels[2] = new CCString("Penile");
		labels[3] = new CCString("Opening");
		selectors[0] = menu_selector(Menu::selecaoPistaUrethra1);
		selectors[1] = menu_selector(Menu::selecaoPistaUrethra2);
		selectors[2] = menu_selector(Menu::selecaoPistaUrethra3);
		selectors[3] = menu_selector(Menu::selecaoPistaUrethra4);
	} else if(Menu::Championship::copa==UTERUS) {
		imagens[0] = new CCString("pistas/Utero1.png");
		imagens[1] = new CCString("pistas/Utero2.png");
		imagens[2] = new CCString("pistas/Utero3.png");
		imagens[3] = new CCString("pistas/Utero4.png");
		labels[0] = new CCString("Subserosal");
		labels[1] = new CCString("Intramural");
		labels[2] = new CCString("Submucosal");
		labels[3] = new CCString("Pedunculated");
		selectors[0] = menu_selector(Menu::selecaoPistaUterus1);
		selectors[1] = menu_selector(Menu::selecaoPistaUterus2);
		selectors[2] = menu_selector(Menu::selecaoPistaUterus3);
		selectors[3] = menu_selector(Menu::selecaoPistaUterus4);
	} else if(Menu::Championship::copa==OVARY) {
		imagens[0] = new CCString("pistas/Ovario1.png");
		imagens[1] = new CCString("pistas/Ovario2.png");
		imagens[2] = new CCString("pistas/Ovario3.png");
		imagens[3] = new CCString("pistas/Ovario4.png");
		labels[0] = new CCString("Primary Follicles");
		labels[1] = new CCString("Secondary Follicles");
		labels[2] = new CCString("Corpus Luteum");
		labels[3] = new CCString("Ovulation");
		selectors[0] = menu_selector(Menu::selecaoPistaOvary1);
		selectors[1] = menu_selector(Menu::selecaoPistaOvary2);
		selectors[2] = menu_selector(Menu::selecaoPistaOvary3);
		selectors[3] = menu_selector(Menu::selecaoPistaOvary4);
	} else {
		imagens[0] = new CCString("pistas/Camisinha1.png");
		imagens[1] = new CCString("pistas/Camisinha2.png");
		imagens[2] = new CCString("pistas/Camisinha3.png");
		imagens[3] = new CCString("pistas/Camisinha4.png");
		labels[0] = new CCString("Basic");
		labels[1] = new CCString("Flavoured");
		labels[2] = new CCString("Colorful");
		labels[3] = new CCString("Fragance");
		selectors[0] = menu_selector(Menu::selecaoPistaCondom1);
		selectors[1] = menu_selector(Menu::selecaoPistaCondom2);
		selectors[2] = menu_selector(Menu::selecaoPistaCondom3);
		selectors[3] = menu_selector(Menu::selecaoPistaCondom4);
	}
	SEL_MenuHandler voltar = menu_selector(Menu::paraSelectCup);
	Menu::state = SELECTTRACK;
	Menu::criaTela5(tela,qtdOpcoes,imagens,labels,selectors,voltar);
	delete labels[0];
	delete labels[1];
	delete labels[2];
	delete labels[3];
	delete labels;
	delete imagens[0];
	delete imagens[1];
	delete imagens[2];
	delete imagens[3];
	delete imagens;
	delete tela;
}

void Menu::paraConfirmationScreenTimeTrial() {
	CCString *tela = new CCString("Time Trial");
	CCString *imagemCopa;
	CCString *imagemPista;
	CCString *nomeCopa;
	CCString *nomePista;
	if(Menu::Championship::copa==EPIDIDYMIS) {
		imagemCopa = new CCString("pistas/Epididimo.png");
		nomeCopa = new CCString("Epididymis Cup");
	}
	else if(Menu::Championship::copa==URETHRA) {
		imagemCopa = new CCString("pistas/Uretra.png");
		nomeCopa = new CCString("Urethra Cup");
	}
	else if(Menu::Championship::copa==UTERUS) {
		imagemCopa = new CCString("pistas/Utero.png");
		nomeCopa = new CCString("Uterus Cup");
	}
	else if(Menu::Championship::copa==OVARY) {
		imagemCopa = new CCString("pistas/Ovario.png");
		nomeCopa = new CCString("Ovary Cup");
	}
	else {
		imagemCopa = new CCString("pistas/Camisinha.png");
		nomeCopa = new CCString("Condom Cup");
	}
	if(Menu::Championship::pista==EPIDIDYMIS_TRACK_1) {
		imagemPista = new CCString("pistas/Epididimo1.png");
		nomePista = new CCString("Head");
	} else if(Menu::Championship::pista==EPIDIDYMIS_TRACK_2) {
		imagemPista = new CCString("pistas/Epididimo2.png");
		nomePista = new CCString("Body");
	} else if(Menu::Championship::pista==EPIDIDYMIS_TRACK_3) {
		imagemPista = new CCString("pistas/Epididimo3.png");
		nomePista = new CCString("Tail");
	} else if(Menu::Championship::pista==EPIDIDYMIS_TRACK_4) {
		imagemPista = new CCString("pistas/Epididimo4.png");
		nomePista = new CCString("Duct");
	} else if(Menu::Championship::pista==URETHRA_TRACK_1) {
		imagemPista = new CCString("pistas/Uretra1.png");
		nomePista = new CCString("Prostatic");
	} else if(Menu::Championship::pista==URETHRA_TRACK_2) {
		imagemPista = new CCString("pistas/Uretra2.png");
		nomePista = new CCString("Bulbar");
	} else if(Menu::Championship::pista==URETHRA_TRACK_3) {
		imagemPista = new CCString("pistas/Uretra3.png");
		nomePista = new CCString("Penile");
	} else if(Menu::Championship::pista==URETHRA_TRACK_4) {
		imagemPista = new CCString("pistas/Uretra4.png");
		nomePista = new CCString("Opening");
	} else if(Menu::Championship::pista==UTERUS_TRACK_1) {
		imagemPista = new CCString("pistas/Utero1.png");
		nomePista = new CCString("Subserosal");
	} else if(Menu::Championship::pista==UTERUS_TRACK_2) {
		imagemPista = new CCString("pistas/Utero2.png");
		nomePista = new CCString("Intramural");
	} else if(Menu::Championship::pista==UTERUS_TRACK_3) {
		imagemPista = new CCString("pistas/Utero3.png");
		nomePista = new CCString("Submucosal");
	} else if(Menu::Championship::pista==UTERUS_TRACK_4) {
		imagemPista = new CCString("pistas/Utero4.png");
		nomePista = new CCString("Pedunculated");
	} else if(Menu::Championship::pista==OVARY_TRACK_1) {
		imagemPista = new CCString("pistas/Ovario1.png");
		nomePista = new CCString("Primary Follicles");
	} else if(Menu::Championship::pista==OVARY_TRACK_2) {
		imagemPista = new CCString("pistas/Ovario2.png");
		nomePista = new CCString("Secondary Follicles");
	} else if(Menu::Championship::pista==OVARY_TRACK_3) {
		imagemPista = new CCString("pistas/Ovario3.png");
		nomePista = new CCString("Corpus Luteum");
	} else if(Menu::Championship::pista==OVARY_TRACK_4) {
		imagemPista = new CCString("pistas/Ovario4.png");
		nomePista = new CCString("Ovulation");
	} else if(Menu::Championship::pista==CONDOM_TRACK_1) {
		imagemPista = new CCString("pistas/Camisinha1.png");
		nomePista = new CCString("Basic");
	} else if(Menu::Championship::pista==CONDOM_TRACK_2) {
		imagemPista = new CCString("pistas/Camisinha2.png");
		nomePista = new CCString("Flavoured");
	} else if(Menu::Championship::pista==CONDOM_TRACK_3) {
		imagemPista = new CCString("pistas/Camisinha3.png");
		nomePista = new CCString("Colorful");
	} else {
		imagemPista = new CCString("pistas/Camisinha4.png");
		nomePista = new CCString("Fragance");
	}
	int classificacao = 2;
	SEL_MenuHandler adiante = menu_selector(Menu::paraGameplayTimeTrial);
	SEL_MenuHandler voltar = menu_selector(Menu::paraSelectTrack);
	Menu::state = CONFIRMATIONSCREENTIMETRIAL;
	Menu::criaTela6(tela,imagemCopa,nomeCopa,classificacao,imagemPista,nomePista,NULL,adiante,voltar);
	delete nomePista;
	delete nomeCopa;
	delete imagemPista;
	delete imagemCopa;
	delete tela;
}

void Menu::paraConsumableItens() {

}

void Menu::paraGameplayTimeTrial() {
	Menu::state = GAMEPLAYTIMETRIAL;
	removeAllChildren();
	Engine::changeToGame(Menu::Championship::pista,Menu::Championship::personagens,1,0,DIFICULDADE_FACIL,0);
}

void Menu::paraPauseTimeTrial() {

}

void Menu::paraGameOverTimeTrial() {

}

void Menu::paraChampionship() {
	static int posicoes[5];
	int personagens[5];
	int pontuacao[5];
	int pontosGanhos[5];
	int pista;
	bool inicioCorrida;
	SEL_MenuHandler adiante;
	SEL_MenuHandler desistir;
	Menu::state = CHAMPIONSHIP;
	if(Menu::Championship::tela==0) {
		posicoes[0] = 0;
		posicoes[1] = 1;
		posicoes[2] = 2;
		posicoes[3] = 3;
		posicoes[4] = 4;
		Menu::Championship::tela = 3;
	}
	personagens[posicoes[0]] = Menu::Championship::personagens[0];
	personagens[posicoes[1]] = Menu::Championship::personagens[1];
	personagens[posicoes[2]] = Menu::Championship::personagens[2];
	personagens[posicoes[3]] = Menu::Championship::personagens[3];
	personagens[posicoes[4]] = Menu::Championship::personagens[4];
	pontuacao[posicoes[0]] = Menu::Championship::pontuacao[0];
	pontuacao[posicoes[1]] = Menu::Championship::pontuacao[1];
	pontuacao[posicoes[2]] = Menu::Championship::pontuacao[2];
	pontuacao[posicoes[3]] = Menu::Championship::pontuacao[3];
	pontuacao[posicoes[4]] = Menu::Championship::pontuacao[4];
	if(Menu::Championship::tela==1) {
		pontosGanhos[0] = 0;
		pontosGanhos[1] = 0;
		pontosGanhos[2] = 0;
		pontosGanhos[3] = 0;
		pontosGanhos[4] = 0;
		pista = ((Menu::Championship::pista-1)%4) + 1;
		inicioCorrida = false;
		adiante = menu_selector(Menu::paraChampionship);
		desistir = menu_selector(Menu::paraMainMenu);
		Menu::criaTela4(personagens,posicoes[0],pontuacao,pontosGanhos,pista,adiante,inicioCorrida,desistir);
		Menu::Championship::tela++;
	} else if(Menu::Championship::tela==2) {
		pontosGanhos[0] = 10;
		pontosGanhos[1] = 7;
		pontosGanhos[2] = 5;
		pontosGanhos[3] = 3;
		pontosGanhos[4] = 1;
		pista = ((Menu::Championship::pista-1)%4) + 1;
		inicioCorrida = false;
		adiante = menu_selector(Menu::paraChampionship);
		desistir = menu_selector(Menu::paraMainMenu);
		Menu::criaTela4(personagens,posicoes[0],pontuacao,pontosGanhos,pista,adiante,inicioCorrida,desistir);
		Menu::Championship::pontuacao[0] += pontosGanhos[posicoes[0]];
		Menu::Championship::pontuacao[1] += pontosGanhos[posicoes[1]];
		Menu::Championship::pontuacao[2] += pontosGanhos[posicoes[2]];
		Menu::Championship::pontuacao[3] += pontosGanhos[posicoes[3]];
		Menu::Championship::pontuacao[4] += pontosGanhos[posicoes[4]];
		pontosGanhos[0] = Menu::Championship::pontuacao[0];
		pontosGanhos[1] = Menu::Championship::pontuacao[1];
		pontosGanhos[2] = Menu::Championship::pontuacao[2];
		pontosGanhos[3] = Menu::Championship::pontuacao[3];
		pontosGanhos[4] = Menu::Championship::pontuacao[4];
		Menu::ordenaCompetidores(posicoes,pontosGanhos);
		Menu::Championship::pista++;
		Menu::Championship::tela++;
	} else {
		pontosGanhos[0] = 0;
		pontosGanhos[1] = 0;
		pontosGanhos[2] = 0;
		pontosGanhos[3] = 0;
		pontosGanhos[4] = 0;
		inicioCorrida = true;
		if((Menu::Championship::pontuacao[0]+
				Menu::Championship::pontuacao[1]+
				Menu::Championship::pontuacao[2]+
				Menu::Championship::pontuacao[3]+
				Menu::Championship::pontuacao[4])<104) {
			pista = ((Menu::Championship::pista-1)%4) + 1;
			adiante = menu_selector(Menu::paraChampionship);
		}
		else {
			pista = 0;
			adiante = menu_selector(Menu::paraMainMenu);
		}
		desistir = menu_selector(Menu::paraMainMenu);
		Menu::criaTela4(personagens,posicoes[0],pontuacao,pontosGanhos,pista,adiante,inicioCorrida,desistir);
		Menu::Championship::tela = 1;
	}
}

void Menu::paraConfirmationScreenChampionship() {
	CCString *tela = new CCString("Championship");
	CCString *imagemCopa;
	CCString *nomeCopa;
	CCString *labelsTracks[4];
	if(Menu::Championship::copa==EPIDIDYMIS) {
		imagemCopa = new CCString("pistas/Epididimo.png");
		nomeCopa = new CCString("Epididymis Cup");
		labelsTracks[0] = new CCString("Head");
		labelsTracks[1] = new CCString("Body");
		labelsTracks[2] = new CCString("Tail");
		labelsTracks[3] = new CCString("Duct");
	}
	else if(Menu::Championship::copa==URETHRA) {
		imagemCopa = new CCString("pistas/Uretra.png");
		nomeCopa = new CCString("Urethra Cup");
		labelsTracks[0] = new CCString("Prostatic");
		labelsTracks[1] = new CCString("Bulbar");
		labelsTracks[2] = new CCString("Penile");
		labelsTracks[3] = new CCString("Opening");
	}
	else if(Menu::Championship::copa==UTERUS) {
		imagemCopa = new CCString("pistas/Utero.png");
		nomeCopa = new CCString("Uterus Cup");
		labelsTracks[0] = new CCString("Subserosal");
		labelsTracks[1] = new CCString("Intramural");
		labelsTracks[2] = new CCString("Submucosal");
		labelsTracks[3] = new CCString("Pedunculated");
	}
	else if(Menu::Championship::copa==OVARY) {
		imagemCopa = new CCString("pistas/Ovario.png");
		nomeCopa = new CCString("Ovary Cup");
		labelsTracks[0] = new CCString("Primary Follicles");
		labelsTracks[1] = new CCString("Secondary Follicles");
		labelsTracks[2] = new CCString("Corpus Luteum");
		labelsTracks[3] = new CCString("Ovulation");
	}
	else {
		imagemCopa = new CCString("pistas/Camisinha.png");
		nomeCopa = new CCString("Condom Cup");
		labelsTracks[0] = new CCString("Basic");
		labelsTracks[1] = new CCString("Flavoured");
		labelsTracks[2] = new CCString("Colorful");
		labelsTracks[3] = new CCString("Fragance");
	}
	int classificacao = 2;
	SEL_MenuHandler adiante = menu_selector(Menu::paraChampionship);
	SEL_MenuHandler voltar = menu_selector(Menu::selecaoCopa);
	Menu::state = CONFIRMATIONSCREENCHAMPIONSHIP;
	Menu::criaTela6(tela,imagemCopa,nomeCopa,classificacao,NULL,NULL,labelsTracks,adiante,voltar);
	delete labelsTracks[0];
	delete labelsTracks[1];
	delete labelsTracks[2];
	delete labelsTracks[3];
	delete nomeCopa;
	delete imagemCopa;
	delete tela;
}

void Menu::paraScoreScreen() {

}

void Menu::paraGameplayChampionship() {

}

void Menu::paraPauseChampionship() {

}

void Menu::paraGameOverChampionship() {

}

void Menu::paraFinalPlayer() {

}

void Menu::paraExit() {
	Engine::getSharedEngine()->closeApp();
}

void Menu::criaTela1(CCString *nomeTela,int qtdOpcoes,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar) {
	int i;
	char tela;
	char caminho[40];
	char caminho1[40];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Voltar_Fundo.png");

	CCMenu* menuVol = CCMenu::create();
	CCMenuItemImage* vol = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	vol->setScale((0.18*ht)/vol->getContentSize().height);
	vol->setPosition(ccp(0.5*wt - vol->boundingBox().size.width/2,0.5*ht - vol->boundingBox().size.height/2));
	menuVol->addChild(vol);

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	CCLabelTTF *labelTela = CCLabelTTF::create(nomeTela->getCString(),myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	cocos2d::extension::CCScrollView* sv = cocos2d::extension::CCScrollView::create();
	sv->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	sv->setViewSize(CCSize(wt,ht));

	CCMenu* menu = CCMenu::create();
	sv->setContainer(menu);

	sprintf(caminho+11,"Ovulo.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Ovulo_Fundo.png");

	CCMenuItemImage* mi;
	ccColor3B cor;
	cor.r = 109;
	cor.g = 36;
	cor.b = 36;

	int larg = qtdOpcoes*1.2*(0.5*ht);
	int inicio = 0.6*(0.5*ht);
	if(larg<wt) {
		inicio += (wt-larg)/2;
		larg = wt;
	}
	for(i=0;i<qtdOpcoes;i++) {
		mi = CCMenuItemImage::create(caminho,caminho1,this,selectors[i]);
		mi->setScale((0.5*ht)/mi->getContentSize().height);
		mi->setPosition(ccp(inicio + i*1.2*(0.5*ht),0));
		CCLabelTTF *l = CCLabelTTF::create(labels[i]->getCString(),myriadProBold,tamanhoFonte);
		l->setColor(cor);
		l->setScale(1/mi->getScale());
		l->setPosition(ccp(mi->getContentSize().width/2,mi->getContentSize().height/2));
		mi->addChild(l);
		menu->addChild(mi);
	}

	sv->setContentSize(CCSize(larg,mi->boundingBox().size.height));
	sv->setContentOffset(ccp(0,0.1*ht + mi->boundingBox().size.height/2));

	CCLabelTTF *labelCeuGames = CCLabelTTF::create("Céu Games - 2014",myriadProBold,tamanhoFonte*0.5);
	labelCeuGames->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+labelCeuGames->boundingBox().size.height/2));

	removeAllChildren();
	addChild(background);
	addChild(logo);
	addChild(menuVol);
	addChild(labelTela);
	addChild(sv);
	addChild(labelCeuGames);
}

void Menu::criaTela2(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar) {
	int i;
	char tela;
	char caminho[40];
	char caminho1[40];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Voltar_Fundo.png");

	CCMenu* menuVol = CCMenu::create();
	CCMenuItemImage* vol = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	vol->setScale((0.18*ht)/vol->getContentSize().height);
	vol->setPosition(ccp(0.5*wt - vol->boundingBox().size.width/2,0.5*ht - vol->boundingBox().size.height/2));
	menuVol->addChild(vol);

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	CCLabelTTF *labelTela = CCLabelTTF::create(nomeTela->getCString(),myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	cocos2d::extension::CCScrollView* sv = cocos2d::extension::CCScrollView::create();
	sv->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	sv->setViewSize(CCSize(wt,ht));

	CCMenu* menu = CCMenu::create();
	sv->setContainer(menu);

	CCMenuItemImage *mi;
	ccColor3B cor;
	cor.r = 109;
	cor.g = 36;
	cor.b = 36;

	int larg = qtdOpcoes*1.2*(0.5*ht);
	int inicio = 0.6*(0.5*ht);
	if(larg<wt) {
		inicio += (wt-larg)/2;
		larg = wt;
	}
	for(i=0;i<qtdOpcoes;i++) {
		sprintf(caminho+11,"%s",imagens[i]->getCString());
		mi = CCMenuItemImage::create(caminho,caminho,this,selectors[i]);
		mi->setScale((0.4*ht)/mi->getContentSize().height);
		mi->setPosition(ccp(inicio + i*1.2*(0.5*ht),0.08*ht));
		CCLabelTTF *l = CCLabelTTF::create(labels[i]->getCString(),myriadProBold,0.6*tamanhoFonte);
		l->setScale(1/mi->getScale());
		l->setPosition(ccp(mi->getContentSize().width/2,-0.04*ht));
		mi->addChild(l);
		menu->addChild(mi);
	}

	sv->setContentSize(CCSize(larg,mi->boundingBox().size.height));
	sv->setContentOffset(ccp(0,0.1*ht + mi->boundingBox().size.height/2));

	CCLabelTTF *labelCeuGames = CCLabelTTF::create("Céu Games - 2014",myriadProBold,tamanhoFonte*0.5);
	labelCeuGames->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+labelCeuGames->boundingBox().size.height/2));

	removeAllChildren();
	addChild(background);
	addChild(logo);
	addChild(menuVol);
	addChild(labelTela);
	addChild(sv);
	addChild(labelCeuGames);
}

void Menu::criaTela3(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,int *classificacoes,SEL_MenuHandler *selectors,SEL_MenuHandler voltar) {
	int i,j;
	char tela;
	char caminho[40];
	char caminho1[40];
	char caminho2[40];
	char caminho3[40];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Voltar_Fundo.png");

	CCMenu* menuVol = CCMenu::create();
	CCMenuItemImage* vol = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	vol->setScale((0.18*ht)/vol->getContentSize().height);
	vol->setPosition(ccp(0.5*wt - vol->boundingBox().size.width/2,0.5*ht - vol->boundingBox().size.height/2));
	menuVol->addChild(vol);

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	CCLabelTTF *labelTela = CCLabelTTF::create(nomeTela->getCString(),myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	cocos2d::extension::CCScrollView* sv = cocos2d::extension::CCScrollView::create();
	sv->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	sv->setViewSize(CCSize(wt,ht));

	CCMenu* menu = CCMenu::create();
	sv->setContainer(menu);

	CCMenuItemImage *mi;
	ccColor3B cor;
	cor.r = 109;
	cor.g = 36;
	cor.b = 36;

	int larg = qtdOpcoes*1.2*(0.5*ht);
	int inicio = 0.6*(0.5*ht);
	if(larg<wt) {
		inicio += (wt-larg)/2;
		larg = wt;
	}
	sprintf(caminho+11,"Ranking_Copa.png");
	sprintf(caminho2,caminho);
	sprintf(caminho2+11,"Estrela.png");
	sprintf(caminho3,caminho);
	sprintf(caminho3+11,"Estrela_Preta.png");
	for(i=0;i<qtdOpcoes;i++) {
		mi = CCMenuItemImage::create(caminho,caminho,this,selectors[i]);
		mi->setScale((0.4*ht)/mi->getContentSize().height);
		mi->setPosition(ccp(inicio + i*1.2*(0.5*ht),0.08*ht));
		sprintf(caminho1+11,"%s",imagens[i]->getCString());
		CCSprite *pista = CCSprite::create(caminho1);
		pista->setScale((0.22*ht)/(pista->getContentSize().height*mi->getScale()));
		pista->setPosition(ccp(mi->getContentSize().width/2,0.613*mi->getContentSize().height));
		mi->addChild(pista);
		for(j=0;j<3;j++) {
			CCSprite *estrelas;
			if(j<classificacoes[i])
				estrelas = CCSprite::create(caminho2);
			else
				estrelas = CCSprite::create(caminho3);
			estrelas->setScale((0.06*ht)/(estrelas->getContentSize().height*mi->getScale()));
			estrelas->setPosition(ccp((0.262+j*0.238)*mi->getContentSize().width,0.15*mi->getContentSize().height));
			mi->addChild(estrelas);
		}
		CCLabelTTF *l = CCLabelTTF::create(labels[i]->getCString(),myriadProBold,0.6*tamanhoFonte);
		l->setScale(1/mi->getScale());
		l->setPosition(ccp(mi->getContentSize().width/2,-0.04*ht));
		mi->addChild(l);
		menu->addChild(mi);
	}

	sv->setContentSize(CCSize(larg,mi->boundingBox().size.height));
	sv->setContentOffset(ccp(0,0.1*ht + mi->boundingBox().size.height/2));

	CCLabelTTF *labelCeuGames = CCLabelTTF::create("Céu Games - 2014",myriadProBold,tamanhoFonte*0.5);
	labelCeuGames->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+labelCeuGames->boundingBox().size.height/2));

	removeAllChildren();
	addChild(background);
	addChild(logo);
	addChild(menuVol);
	addChild(labelTela);
	addChild(sv);
	addChild(labelCeuGames);
}

void Menu::criaTela4(int personagens[5],int jogador,int pontosAtual[5],int pontosGanhos[5],int corrida,SEL_MenuHandler adiante,bool inicioCorrida,SEL_MenuHandler voltar) {
	int i;
	char tela;
	char caminho[40];
	char caminho1[40];
	char label[21];
	char pontuacao[5][7];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	sprintf(caminho+11,"Fundo_Janela.png");
	CCSprite* windowBackground = CCSprite::create(caminho);
	windowBackground->setPosition(background->getPosition());
	windowBackground->setScale(background->getScale());

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	sprintf(label,"Championship:",corrida);
	if(corrida>0)
		sprintf(label+13," Race %i",corrida);
	CCLabelTTF *labelTela = CCLabelTTF::create(label,myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	CCLabelTTF ***tabela = new CCLabelTTF**[5];
	int aux = 0;
	for(i=0;i<5;i++) {
		tabela[i] = new CCLabelTTF*[2];
		if(pontosGanhos[i]>0)
			sprintf(pontuacao[i],"%i(+%i)",pontosAtual[i],pontosGanhos[i]);
		else
			sprintf(pontuacao[i],"%i",pontosAtual[i]);
		tabela[i][0] = CCLabelTTF::create(NOMES[personagens[i]],myriadProBold,tamanhoFonte);
		tabela[i][0]->setAnchorPoint(ccp(0,0.5));
		tabela[i][1] = CCLabelTTF::create(pontuacao[i],myriadProBold,tamanhoFonte);
		tabela[i][1]->setAnchorPoint(ccp(1,0.5));
		if(i==jogador) {
			ccColor3B cor;
			cor.r = 255;
			cor.g = 255;
			cor.b = 0;
			tabela[i][0]->setColor(cor);
			tabela[i][1]->setColor(cor);
		}
		if(tabela[i][0]->boundingBox().size.width+tabela[i][1]->boundingBox().size.width>aux)
			aux = tabela[i][0]->boundingBox().size.width + tabela[i][1]->boundingBox().size.width;
	}

	CCMenu* menu = CCMenu::create();
	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+17,"_Fundo.png");
	CCMenuItemImage *btVoltar = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	btVoltar->setScale((0.18*ht)/btVoltar->getContentSize().height);
	btVoltar->setPosition(ccp(-0.4*wt,0));
	menu->addChild(btVoltar);
	if(inicioCorrida) {
		sprintf(caminho+11,"Iniciar.png");
		sprintf(caminho1,"%s",caminho);
		sprintf(caminho1+18,"_Fundo.png");
	} else {
		sprintf(caminho+11,"Avancar.png");
		sprintf(caminho1,"%s",caminho);
		sprintf(caminho1+18,"_Fundo.png");
	}
	CCMenuItemImage *btAvancar = CCMenuItemImage::create(caminho,caminho1,this,adiante);
	btAvancar->setScale((0.18*ht)/btAvancar->getContentSize().height);
	if(!inicioCorrida)
		btAvancar->setRotation(180);
	btAvancar->setPosition(ccp(0.4*wt,0));
	menu->addChild(btAvancar);

	removeAllChildren();
	addChild(background);
	addChild(windowBackground);
	addChild(logo);
	addChild(labelTela);
	for(i=0;i<5;i++) {
		tabela[i][0]->setPosition(ccp((wt-aux)/2 - 0.1*wt,ht/2 - i*ht*0.1));
		addChild(tabela[i][0]);
		tabela[i][1]->setPosition(ccp((wt+aux)/2 + 0.1*wt,ht/2 - i*ht*0.1));
		addChild(tabela[i][1]);
		delete tabela[i];
	}
	delete tabela;
	addChild(menu);
}

void Menu::criaTela5(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar) {
	int i,j;
	char tela;
	char caminho[40];
	char caminho1[40];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Voltar_Fundo.png");

	CCMenu* menuVol = CCMenu::create();
	CCMenuItemImage* vol = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	vol->setScale((0.18*ht)/vol->getContentSize().height);
	vol->setPosition(ccp(0.5*wt - vol->boundingBox().size.width/2,0.5*ht - vol->boundingBox().size.height/2));
	menuVol->addChild(vol);

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	CCLabelTTF *labelTela = CCLabelTTF::create(nomeTela->getCString(),myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	cocos2d::extension::CCScrollView* sv = cocos2d::extension::CCScrollView::create();
	sv->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	sv->setViewSize(CCSize(wt,ht));

	CCMenu* menu = CCMenu::create();
	sv->setContainer(menu);

	CCMenuItemImage *mi;
	ccColor3B cor;
	cor.r = 109;
	cor.g = 36;
	cor.b = 36;

	int larg = qtdOpcoes*1.2*(0.5*ht);
	int inicio = 0.6*(0.5*ht);
	if(larg<wt) {
		inicio += (wt-larg)/2;
		larg = wt;
	}
	sprintf(caminho+11,"Ranking_Copa.png");
	for(i=0;i<qtdOpcoes;i++) {
		mi = CCMenuItemImage::create(caminho,caminho,this,selectors[i]);
		mi->setScale((0.4*ht)/mi->getContentSize().height);
		mi->setPosition(ccp(inicio + i*1.2*(0.5*ht),0.08*ht));
		sprintf(caminho1+11,"%s",imagens[i]->getCString());
		CCSprite *pista = CCSprite::create(caminho1);
		pista->setScale((0.22*ht)/(pista->getContentSize().height*mi->getScale()));
		pista->setPosition(ccp(mi->getContentSize().width/2,0.613*mi->getContentSize().height));
		mi->addChild(pista);
		CCLabelTTF *l = CCLabelTTF::create(labels[i]->getCString(),myriadProBold,0.6*tamanhoFonte);
		l->setScale(1/mi->getScale());
		l->setPosition(ccp(mi->getContentSize().width/2,-0.04*ht));
		mi->addChild(l);
		menu->addChild(mi);
	}

	sv->setContentSize(CCSize(larg,mi->boundingBox().size.height));
	sv->setContentOffset(ccp(0,0.1*ht + mi->boundingBox().size.height/2));

	CCLabelTTF *labelCeuGames = CCLabelTTF::create("Céu Games - 2014",myriadProBold,tamanhoFonte*0.5);
	labelCeuGames->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+labelCeuGames->boundingBox().size.height/2));

	removeAllChildren();
	addChild(background);
	addChild(logo);
	addChild(menuVol);
	addChild(labelTela);
	addChild(sv);
	addChild(labelCeuGames);
}

void Menu::criaTela6(CCString *nomeTela,CCString *imagemCup,CCString *labelCup,int classificacao,CCString *imagemTrack,CCString *labelTrack,CCString **labelsTracks,SEL_MenuHandler adiante,SEL_MenuHandler voltar) {
	int i;
	char tela;
	char caminho[40];
	char caminho1[40];
	switch(Engine::getTamanhoTela()) {
	case TELA_1:
		tela = '1';
		break;
	case TELA_2:
		tela = '2';
		break;
	case TELA_3:
		tela = '3';
		break;
	case TELA_4:
		tela = '4';
		break;
	}
	sprintf(caminho,"tela%c/menu/Logo.png",tela);
	CCSprite* logo = CCSprite::create(caminho);
	sprintf(caminho+11,"Fundo.png");
	CCSprite* background = CCSprite::create(caminho);
	float por;
	float ht = CCDirector::sharedDirector()->getWinSize().height;
	float wt = CCDirector::sharedDirector()->getWinSize().width;
	float hi = background->boundingBox().size.height;
	float wi = background->boundingBox().size.width;
	if(ht/wt<hi/wi)
		por = wt/wi;
	else
		por = ht/hi;
	background->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+ht/2));
	background->setScale(por);

	por = (0.3*ht)/logo->boundingBox().size.height;
	logo->setScale(por);
	logo->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(ht-logo->boundingBox().size.height/2)));

	CCMenu* menu = CCMenu::create();
	sprintf(caminho+11,"Voltar.png");
	sprintf(caminho1,"%s",caminho);
	sprintf(caminho1+11,"Voltar_Fundo.png");
	CCMenuItemImage* vol = CCMenuItemImage::create(caminho,caminho1,this,voltar);
	vol->setScale((0.18*ht)/vol->getContentSize().height);
	vol->setPosition(ccp(0.5*wt - vol->boundingBox().size.width/2,0.5*ht - vol->boundingBox().size.height/2));
	menu->addChild(vol);
	if(!labelsTracks) {
		sprintf(caminho+11,"Iniciar.png");
		sprintf(caminho1,"%s",caminho);
		sprintf(caminho1+11,"Iniciar_Fundo.png");
	} else {
		sprintf(caminho+11,"Avancar.png");
		sprintf(caminho1,"%s",caminho);
		sprintf(caminho1+11,"Avancar_Fundo.png");
	}
	CCMenuItemImage* ava = CCMenuItemImage::create(caminho,caminho1,this,adiante);
	if(labelsTracks)
		ava->setRotation(180);
	ava->setScale((0.18*ht)/ava->getContentSize().height);
	ava->setPosition(ccp(0.3*wt,-0.25*ht));
	menu->addChild(ava);

#ifdef __MACH__
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[15] = "MyriadPro-Bold";
#else
	float tamanhoFonte = 0.75*0.1*ht;
	char myriadProBold[26] = "fontes/MyriadPro-Bold.ttf";
#endif

	CCLabelTTF *labelTela = CCLabelTTF::create(nomeTela->getCString(),myriadProBold,tamanhoFonte);
	labelTela->setPosition(ccp(Engine::getSharedEngine()->getPositionX()+wt/2,Engine::getSharedEngine()->getPositionY()+(0.64*ht)));

	CCLabelTTF *cup = CCLabelTTF::create("Cup",myriadProBold,tamanhoFonte);
	cup->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.2*wt),Engine::getSharedEngine()->getPositionY()+(0.55*ht)));
	sprintf(caminho+11,"Ranking_Copa.png");
	CCSprite *rankingFundo1 = CCSprite::create(caminho);
	rankingFundo1->setScale((0.4*ht)/rankingFundo1->getContentSize().height);
	rankingFundo1->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.2*wt),Engine::getSharedEngine()->getPositionY()+(0.3*ht)));
	sprintf(caminho1+11,"%s",imagemCup->getCString());
	CCSprite *imagemCopa = CCSprite::create(caminho1);
	imagemCopa->setScale((0.22*ht)/imagemCopa->getContentSize().height);
	imagemCopa->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.2*wt),Engine::getSharedEngine()->getPositionY() + rankingFundo1->getPositionY() + 0.113*rankingFundo1->boundingBox().size.height));
	sprintf(caminho+11,"Estrela.png");
	sprintf(caminho1+11,"Estrela_Preta.png");
	CCSprite *estrelas[3];
	for(i=0;i<3;i++) {
		if(i<classificacao)
			estrelas[i] = CCSprite::create(caminho);
		else
			estrelas[i] = CCSprite::create(caminho1);
		estrelas[i]->setScale((0.06*ht)/(estrelas[i]->getContentSize().height));
		estrelas[i]->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.2*wt) - rankingFundo1->boundingBox().size.width/2 + (0.262+i*0.238)*rankingFundo1->boundingBox().size.width,Engine::getSharedEngine()->getPositionY() + rankingFundo1->getPositionY() - 0.35*rankingFundo1->boundingBox().size.height));
	}
	CCLabelTTF *cupName = CCLabelTTF::create(labelCup->getCString(),myriadProBold,0.6*tamanhoFonte);
	cupName->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.2*wt),Engine::getSharedEngine()->getPositionY()+(0.06*ht)));

	CCLabelTTF *track;
	CCSprite *rankingFundo2;
	CCSprite *imagemPista;
	CCLabelTTF *trackName;
	CCLabelTTF *nomesPistas[4];
	if(!labelsTracks) {
		track = CCLabelTTF::create("Track",myriadProBold,tamanhoFonte);
		track->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt),Engine::getSharedEngine()->getPositionY()+(0.55*ht)));
		sprintf(caminho+11,"Ranking_Copa.png");
		rankingFundo2 = CCSprite::create(caminho);
		rankingFundo2->setScale((0.4*ht)/rankingFundo2->getContentSize().height);
		rankingFundo2->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt),Engine::getSharedEngine()->getPositionY()+(0.3*ht)));
		sprintf(caminho1+11,"%s",imagemTrack->getCString());
		imagemPista = CCSprite::create(caminho1);
		imagemPista->setScale((0.22*ht)/imagemPista->getContentSize().height);
		imagemPista->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt),Engine::getSharedEngine()->getPositionY() + rankingFundo2->getPositionY() + 0.113*rankingFundo2->boundingBox().size.height));
		trackName = CCLabelTTF::create(labelTrack->getCString(),myriadProBold,0.6*tamanhoFonte);
		trackName->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt),Engine::getSharedEngine()->getPositionY()+(0.06*ht)));
	} else {
		track = CCLabelTTF::create("Tracks",myriadProBold,tamanhoFonte);
		track->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt),Engine::getSharedEngine()->getPositionY()+(0.55*ht)));
		int x,maior=0;
		for(i=0;i<4;i++) {
			nomesPistas[i] = CCLabelTTF::create(labelsTracks[i]->getCString(),myriadProBold,0.8*tamanhoFonte);
			nomesPistas[i]->setAnchorPoint(ccp(0,0.5));
			if(nomesPistas[i]->boundingBox().size.width>maior)
				maior = nomesPistas[i]->boundingBox().size.width;
		}
		for(i=0;i<4;i++)
			nomesPistas[i]->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.5*wt) - maior/2,Engine::getSharedEngine()->getPositionY() + (0.45*ht) - i*nomesPistas[i]->boundingBox().size.height));
	}

	CCLabelTTF *labelAreYou = CCLabelTTF::create("Are you",myriadProBold,tamanhoFonte);
	labelAreYou->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.8*+wt),Engine::getSharedEngine()->getPositionY()+(0.55*ht)));
	CCLabelTTF *labelReady = CCLabelTTF::create("Ready?",myriadProBold,tamanhoFonte);
	labelReady->setPosition(ccp(Engine::getSharedEngine()->getPositionX() + (0.8*+wt),Engine::getSharedEngine()->getPositionY()+(0.45*ht)));

	removeAllChildren();
	addChild(background);
	addChild(logo);
	addChild(menu);
	addChild(labelTela);
	addChild(cup);
	addChild(rankingFundo1);
	addChild(imagemCopa);
	for(i=0;i<3;i++)
		addChild(estrelas[i]);
	addChild(cupName);
	addChild(track);
	if(labelsTracks==NULL) {
		addChild(rankingFundo2);
		addChild(imagemPista);
		addChild(trackName);
	} else {
		for(i=0;i<4;i++)
			addChild(nomesPistas[i]);
	}
	addChild(labelAreYou);
	addChild(labelReady);
}

void Menu::selecaoPersonagemTommy() {
	Menu::Championship::personagens[0] = TOMMY;
	Menu::paraGameMode();
}

void Menu::selecaoPersonagemSammy() {
	Menu::Championship::personagens[0] = SAMMY;
	Menu::paraGameMode();
}

void Menu::selecaoPersonagemRhino() {
	Menu::Championship::personagens[0] = RHINO;
	Menu::paraGameMode();
}

void Menu::selecaoPersonagemMike() {
	Menu::Championship::personagens[0] = MIKE;
	Menu::paraGameMode();
}

void Menu::selecaoPersonagemBeth() {
	Menu::Championship::personagens[0] = BETH;
	Menu::paraGameMode();
}

void Menu::selecaoCopa() {
	Menu::Championship::championship = true;
	Menu::paraSelectCup();
}

void Menu::selecaoTimeTrial() {
	Menu::Championship::championship = false;
	Menu::paraSelectCup();
}

void Menu::selecaoCopaEpididymis() {
	Menu::Championship::copa = EPIDIDYMIS;
	if(Menu::Championship::championship) {
		Menu::Championship::pista = Menu::Championship::copa;
		Menu::Championship::pontuacao[0] = 0;
		Menu::Championship::tela = 0;
		Menu::embaralhaCompetidores();
		Menu::paraConfirmationScreenChampionship();
	}
	else
		Menu::paraSelectTrack();
}

void Menu::selecaoCopaUrethra() {
	Menu::Championship::copa = URETHRA;
	if(Menu::Championship::championship) {
		Menu::Championship::pista = Menu::Championship::copa;
		Menu::Championship::pontuacao[0] = 0;
		Menu::Championship::tela = 0;
		Menu::embaralhaCompetidores();
		Menu::paraConfirmationScreenChampionship();
	}
	else
		Menu::paraSelectTrack();
}

void Menu::selecaoCopaUterus() {
	Menu::Championship::copa = UTERUS;
	if(Menu::Championship::championship) {
		Menu::Championship::pista = Menu::Championship::copa;
		Menu::Championship::pontuacao[0] = 0;
		Menu::Championship::tela = 0;
		Menu::embaralhaCompetidores();
		Menu::paraConfirmationScreenChampionship();
	}
	else
		Menu::paraSelectTrack();
}

void Menu::selecaoCopaOvary() {
	Menu::Championship::copa = OVARY;
	if(Menu::Championship::championship) {
		Menu::Championship::pista = Menu::Championship::copa;
		Menu::Championship::pontuacao[0] = 0;
		Menu::Championship::tela = 0;
		Menu::embaralhaCompetidores();
		Menu::paraConfirmationScreenChampionship();
	}
	else
		Menu::paraSelectTrack();
}

void Menu::selecaoCopaCondom() {
	Menu::Championship::copa = CONDOM;
	if(Menu::Championship::championship) {
		Menu::Championship::pista = Menu::Championship::copa;
		Menu::Championship::pontuacao[0] = 0;
		Menu::Championship::tela = 0;
		Menu::embaralhaCompetidores();
		Menu::paraConfirmationScreenChampionship();
	}
	else
		Menu::paraSelectTrack();
}

void Menu::selecaoPistaEpididymis1() {
	Menu::Championship::pista = EPIDIDYMIS_TRACK_1;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaEpididymis2() {
	Menu::Championship::pista = EPIDIDYMIS_TRACK_2;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaEpididymis3() {
	Menu::Championship::pista = EPIDIDYMIS_TRACK_3;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaEpididymis4() {
	Menu::Championship::pista = EPIDIDYMIS_TRACK_4;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUrethra1() {
	Menu::Championship::pista = URETHRA_TRACK_1;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUrethra2() {
	Menu::Championship::pista = URETHRA_TRACK_2;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUrethra3() {
	Menu::Championship::pista = URETHRA_TRACK_3;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUrethra4() {
	Menu::Championship::pista = URETHRA_TRACK_4;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUterus1() {
	Menu::Championship::pista = UTERUS_TRACK_1;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUterus2() {
	Menu::Championship::pista = UTERUS_TRACK_2;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUterus3() {
	Menu::Championship::pista = UTERUS_TRACK_3;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaUterus4() {
	Menu::Championship::pista = UTERUS_TRACK_4;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaOvary1() {
	Menu::Championship::pista = OVARY_TRACK_1;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaOvary2() {
	Menu::Championship::pista = OVARY_TRACK_2;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaOvary3() {
	Menu::Championship::pista = OVARY_TRACK_3;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaOvary4() {
	Menu::Championship::pista = OVARY_TRACK_4;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaCondom1() {
	Menu::Championship::pista = CONDOM_TRACK_1;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaCondom2() {
	Menu::Championship::pista = CONDOM_TRACK_2;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaCondom3() {
	Menu::Championship::pista = CONDOM_TRACK_3;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::selecaoPistaCondom4() {
	Menu::Championship::pista = CONDOM_TRACK_4;
	Menu::paraConfirmationScreenTimeTrial();
}

void Menu::embaralhaCompetidores() {
	int i,j,per,flag;
	int aux = time(NULL);
	for(i=1;i<5;i++) {
		Menu::Championship::pontuacao[i] = 0;
		do {
			srand(aux);
			aux = rand();
			per = aux%QTD_PERSONAGENS;
			flag = 0;
			for(j=0;j<i;j++)
				if(per==Menu::Championship::personagens[j]) {
					j = i;
					flag = 1;
				}
		}while(flag);
		Menu::Championship::personagens[i] = per;
	}
}

void Menu::ordenaCompetidores(int *posicoes,int *pontuacao) {
	int i,j,aux,aux1[5];
	aux1[0] = 0;
	aux1[1] = 1;
	aux1[2] = 2;
	aux1[3] = 3;
	aux1[4] = 4;
	for(i=0;i<4;i++)
		for(j=i+1;j<5;j++)
			if(pontuacao[j]>pontuacao[i]) {
				aux = pontuacao[i];
				pontuacao[i] = pontuacao[j];
				pontuacao[j] = aux;
				aux = aux1[i];
				aux1[i] = aux1[j];
				aux1[j] = aux;
			}
	posicoes[aux1[0]] = 0;
	posicoes[aux1[1]] = 1;
	posicoes[aux1[2]] = 2;
	posicoes[aux1[3]] = 3;
	posicoes[aux1[4]] = 4;
}

Menu* Menu::getSharedMenu() {
	return Menu::sharedMenu;
}