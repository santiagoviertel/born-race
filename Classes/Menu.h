#include "Gameplay.h"

#define OPENING 1
#define MAINMENU 2
#define INSTRUCTIONS 3
#define RECORDS 4
#define RULES 5
#define COMMANDS 6
#define OPTIONS 7
#define ABOUT 8
#define SHOP 9
#define NEWGAME 10
#define GAMEMODE 11
#define SELECTCUP 12
#define SELECTTRACK 13
#define CONFIRMATIONSCREENTIMETRIAL 14
#define CONSUMABLEITENS 15
#define GAMEPLAYTIMETRIAL 16
#define PAUSETIMETRIAL 17
#define GAMEOVERTIMETRIAL 18
#define CHAMPIONSHIP 19
#define CONFIRMATIONSCREENCHAMPIONSHIP 20
#define SCORESCREEN 21
#define GAMEPLAYCHAMPIONSHIP 22
#define PAUSECHAMPIONSHIP 23
#define GAMEOVERCHAMPIONSHIP 24
#define FINALPLAYER 25
#define EXIT 26

class Menu : public CCLayer {

private:
	static int state;
	static Menu* sharedMenu;
	void paraOpening();
	void paraMainMenu();
	void paraInstructions();
	void paraRecords();
	void paraRules();
	void paraCommands();
	void paraOptions();
	void paraAbout();
	void paraShop();
	void paraNewGame();
	void paraGameMode();
	void paraSelectCup();
	void paraSelectTrack();
	void paraConfirmationScreenTimeTrial();
	void paraConsumableItens();
	void paraGameplayTimeTrial();
	void paraPauseTimeTrial();
	void paraGameOverTimeTrial();
	void paraChampionship();
	void paraConfirmationScreenChampionship();
	void paraScoreScreen();
	void paraGameplayChampionship();
	void paraPauseChampionship();
	void paraGameOverChampionship();
	void paraFinalPlayer();
	void paraExit();
	void criaTela1(CCString *nomeTela,int qtdOpcoes,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar);
	void criaTela2(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar);
	void criaTela3(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,int *classificacoes,SEL_MenuHandler *selectors,SEL_MenuHandler voltar);
	void criaTela4(int personagens[5],int jogador,int pontosAtual[5],int pontosGanhos[5],int corrida,SEL_MenuHandler adiante,bool inicioCorrida,SEL_MenuHandler voltar);
	void criaTela5(CCString *nomeTela,int qtdOpcoes,CCString **imagens,CCString **labels,SEL_MenuHandler *selectors,SEL_MenuHandler voltar);
	void criaTela6(CCString *nomeTela,CCString *imagemCup,CCString *labelCup,int classificacao,CCString *imagemTrack,CCString *labelTrack,CCString **labelsTracks,SEL_MenuHandler adiante,SEL_MenuHandler voltar);
	void selecaoPersonagemTommy();
	void selecaoPersonagemSammy();
	void selecaoPersonagemRhino();
	void selecaoPersonagemMike();
	void selecaoPersonagemBeth();
	void selecaoCopa();
	void selecaoTimeTrial();
	void selecaoCopaEpididymis();
	void selecaoCopaUrethra();
	void selecaoCopaUterus();
	void selecaoCopaOvary();
	void selecaoCopaCondom();
	void selecaoPistaEpididymis1();
	void selecaoPistaEpididymis2();
	void selecaoPistaEpididymis3();
	void selecaoPistaEpididymis4();
	void selecaoPistaUrethra1();
	void selecaoPistaUrethra2();
	void selecaoPistaUrethra3();
	void selecaoPistaUrethra4();
	void selecaoPistaUterus1();
	void selecaoPistaUterus2();
	void selecaoPistaUterus3();
	void selecaoPistaUterus4();
	void selecaoPistaOvary1();
	void selecaoPistaOvary2();
	void selecaoPistaOvary3();
	void selecaoPistaOvary4();
	void selecaoPistaCondom1();
	void selecaoPistaCondom2();
	void selecaoPistaCondom3();
	void selecaoPistaCondom4();
	void embaralhaCompetidores();
	void ordenaCompetidores(int *posicoes,int *pontuacao);

public:
	virtual bool init();
	static Menu* getSharedMenu();
	void beginGame();
	CREATE_FUNC(Menu);

	class Championship {

	public:
		static bool championship;
		static int tela;
		static int copa;
		static int pista;
		static int pontuacao[5];
		static int personagens[5];
	};
};