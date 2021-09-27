#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include<wx/wx.h>
#endif
#include <string.h>

int board[3][3];
int player; //qual é o jogador da vez?
int turnCounter;//contador de rodadas
int victorious;//quem ganhou?

void initBoard();
int checkBoard();

void initBoard() {


	int i, j;

	player = 1;
	turnCounter = 0;
	victorious = 0;

	for (i = 0;i < 3;i++) {
		for (j = 0;j < 3;j++) {
			board[i][j] = 0;
		}
	}

}


int checkBoard() {

	int i, j, p1, p2;
	
	//verificar linhas
	for (i = 0;i < 3;i++) {
		p1 = 0;
		p2 = 0;
		for (j = 0;j < 3;j++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}

	//verificar colunas
	for (j = 0; j < 3;j++) {
		p1 = 0;
		p2 = 0;
		for (i = 0;i < 3;i++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}
	//Diagona principal
	p1 = 0;
	p2 = 0;
	for (i = 0;i < 3;i++) {
		if (board[i][i] == 1) p1++;
		else if (board[i][i] == 2) p2++;
	}
	if (p1 == 3) {
		return 1;
	}
	else if (p2 == 3) {
		return 2;
	}
	//Diagonal segundaria
	p1 = 0;
	p2 = 0;
	j = 2;
	for (i = 0;i < 3;i++) {
		if (board[i][j] == 1) p1++;
		else if (board[i][j] == 2) p2++;
		j--;
	}
	if (p1 == 3) {
		return 1;
	}
	else if (p2 == 3) {
		return 2;
	}
	//se ninguém ganhou
	return 0;
}


class ticTecToe : public wxApp {
public:
	virtual bool OnInit();
};
class MainFrame: public wxFrame{
public:
	MainFrame();
protected:
	//Menus
	wxMenuBar* m_meinMenuBar;
	wxMenu* m_menuGame;
	wxMenu* m_menuHelp;
	//Botoes
	wxButton* m_btnUpLeft;
	wxButton* m_btnUpMid; 
	wxButton* m_btnUpRight;

	wxButton* m_btnMidLeft;
	wxButton* m_btnMidMid;
	wxButton* m_btnMidRight;

	wxButton* m_btnLowLeft;
	wxButton* m_btnLowMid;
	wxButton* m_btnLowRight;

	wxStatusBar* m_statusBar;

	char m_msgStatusBar[200];
private:
	void EnableGrid();
	void DisableGrid();
	void EndGame();

	//Ação dos menus
	void OnNewGame(wxCommandEvent& event);
	void OnSair(wxCommandEvent& event);
	void OnSobre(wxCommandEvent& event);
	//Ação dos botões
	void OnUpLeftClick(wxCommandEvent& event);
	void OnUpMidClick(wxCommandEvent& event);
	void OnUpRightClick(wxCommandEvent& event);

	void OnMidLeftClick(wxCommandEvent& event);
	void OnMidMidClick(wxCommandEvent& event);
	void OnMidRightClick(wxCommandEvent& event);

	void OnLowLeftClick(wxCommandEvent& event);
	void OnLowMidClick(wxCommandEvent& event);
	void OnLowRightClick(wxCommandEvent& event);
	//Ação entrada encima do botão
	void OnUpLeftEnterWindow(wxCommandEvent& event);
	void OnUpMidEnterWindow(wxCommandEvent& event);
	void OnUpRightEnterWindow(wxCommandEvent& event);

	void OnMidLeftEnterWindow(wxCommandEvent& event);
	void OnMidMidEnterWindow(wxCommandEvent& event);
	void OnMidRightEnterWindow(wxCommandEvent& event);

	void OnLowLeftEnterWindow(wxCommandEvent& event);
	void OnLowMidEnterWindow(wxCommandEvent& event);
	void OnLowRightEnterWindow(wxCommandEvent& event);
	//Ação de Sáida do botão
	void OnUpLeftLeaveWindow(wxCommandEvent& event);
	void OnUpMidLeaveWindow(wxCommandEvent& event);
	void OnUpRightLeaveWindow(wxCommandEvent& event);

	void OnMidLeftLeaveWindow(wxCommandEvent& event);
	void OnMidMidLeaveWindow(wxCommandEvent& event);
	void OnMidRightLeaveWindow(wxCommandEvent& event);

	void OnLowLeftLeaveWindow(wxCommandEvent& event);
	void OnLowMidLeaveWindow(wxCommandEvent& event);
	void OnLowRightLeaveWindow(wxCommandEvent& event);
};
bool ticTecToe::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show();

	initBoard();

	return true;
}
enum {
	ID_Sobre=3
};
enum {
	ID_Sair = 2
};
enum {
	ID_NewGame = 1
};
//Construtor 
MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Jogo da velha") {
	this->SetSizeHints(720, 720);
	m_meinMenuBar = new wxMenuBar(0);
	m_menuGame = new wxMenu();
	m_menuHelp = new wxMenu();

	m_meinMenuBar->Append(m_menuGame, "Jogo");
	m_meinMenuBar->Append(m_menuHelp, "Ajuda");

	m_menuGame->Append(ID_NewGame, "&Inicio de Jogo\tCtrl-N", "Ao clicar o jogo se inicializa");
	m_menuGame->AppendSeparator();
	m_menuGame->Append(ID_Sair, "&Sair", "Ao clicar o jogo se enserra");
	m_menuHelp->Append(ID_Sobre, "&Sobre", "Informaçoes sobre a criação do jogo");

	wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, FALSE);

	this->SetMenuBar(m_meinMenuBar);

	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(500, 500);
	//Botões De cima
	m_btnUpLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpLeft->SetFont(font);
	gBoard->Add(m_btnUpLeft, 0, wxALL | wxEXPAND, 5);

	m_btnUpMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpMid->SetFont(font);
	gBoard->Add(m_btnUpMid, 0, wxALL | wxEXPAND, 5);

	m_btnUpRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpRight->SetFont(font);
	gBoard->Add(m_btnUpRight, 0, wxALL | wxEXPAND, 5);

	//Botoes do Meio
	m_btnMidLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidLeft->SetFont(font);
	gBoard->Add(m_btnMidLeft, 0, wxALL | wxEXPAND, 5);

	m_btnMidMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidMid->SetFont(font);
	gBoard->Add(m_btnMidMid, 0, wxALL | wxEXPAND, 5);

	m_btnMidRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidRight->SetFont(font);
	gBoard->Add(m_btnMidRight, 0, wxALL | wxEXPAND, 5);

	//Botoes de Baixo
	m_btnLowLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowLeft->SetFont(font);
	gBoard->Add(m_btnLowLeft, 0, wxALL | wxEXPAND, 5);

	m_btnLowMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowMid->SetFont(font);
	gBoard->Add(m_btnLowMid, 0, wxALL | wxEXPAND, 5);

	m_btnLowRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowRight->SetFont(font);
	gBoard->Add(m_btnLowRight, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(gBoard);
	this->Layout();

	m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Center(wxBOTH);

	DisableGrid();
	SetStatusText("Clik em Novo Jogo Para iniciar uma nova partida!");



	Bind(wxEVT_MENU, &MainFrame::OnNewGame, this, ID_NewGame);
	Bind(wxEVT_MENU, &MainFrame::OnSobre, this, ID_Sobre);	
	Bind(wxEVT_MENU, &MainFrame::OnSair, this, ID_Sair);

	m_btnUpLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnUpLeftClick), NULL, this);
	m_btnUpMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnUpMidClick), NULL, this);
	m_btnUpRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnUpRightClick), NULL, this);

	m_btnMidLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnMidLeftClick), NULL, this);
	m_btnMidMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnMidMidClick), NULL, this);
	m_btnMidRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnMidRightClick), NULL, this);

	m_btnLowLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnLowLeftClick), NULL, this);
	m_btnLowMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnLowMidClick), NULL, this);
	m_btnLowRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnLowRightClick), NULL, this);
	
	//saida e entra dos botoes
	m_btnUpLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpLeftEnterWindow), NULL, this);
	m_btnUpMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpMidEnterWindow), NULL, this);
	m_btnUpRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpRightEnterWindow), NULL, this);

	m_btnMidLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidLeftEnterWindow), NULL, this);
	m_btnMidMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidMidEnterWindow), NULL, this);
	m_btnMidRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidRightEnterWindow), NULL, this);

	m_btnLowLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowLeftEnterWindow), NULL, this);
	m_btnLowMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowMidEnterWindow), NULL, this);
	m_btnLowRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowRightEnterWindow), NULL, this);
	//.
	m_btnUpLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpLeftLeaveWindow), NULL, this);
	m_btnUpMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpMidLeaveWindow), NULL, this);
	m_btnUpRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnUpRightLeaveWindow), NULL, this);

	m_btnMidLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidLeftLeaveWindow), NULL, this);
	m_btnMidMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidMidLeaveWindow), NULL, this);
	m_btnMidRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnMidRightLeaveWindow), NULL, this);

	m_btnLowLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowLeftLeaveWindow), NULL, this);
	m_btnLowMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowMidLeaveWindow), NULL, this);
	m_btnLowRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnLowRightLeaveWindow), NULL, this);
}

wxIMPLEMENT_APP(ticTecToe);


void MainFrame::EnableGrid() {
//Abilitar botões
	m_btnUpLeft->Enable();
	m_btnUpMid->Enable();
	m_btnUpRight->Enable();
	m_btnMidLeft->Enable();
	m_btnMidMid->Enable();
	m_btnMidRight->Enable();
	m_btnLowLeft->Enable();
	m_btnLowMid->Enable();
	m_btnLowRight->Enable();
//Deixa os botões sem informações
	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");
	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");
	m_btnLowLeft->SetLabelText("");
	m_btnLowMid->SetLabelText("");
	m_btnLowRight->SetLabelText("");

}

void MainFrame::DisableGrid() {
	//Desabilita botões
	m_btnUpLeft->Disable();
	m_btnUpMid->Disable();
	m_btnUpRight->Disable();
	m_btnMidLeft->Disable();
	m_btnMidMid->Disable();
	m_btnMidRight->Disable();
	m_btnLowLeft->Disable();
	m_btnLowMid->Disable();
	m_btnLowRight->Disable();
	//Deixa os botões sem informações
	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");
	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");
	m_btnLowLeft->SetLabelText("");
	m_btnLowMid->SetLabelText("");
	m_btnLowRight->SetLabelText("");

}

void MainFrame::EndGame() {
	char mensagem[200] = "";
	if (victorious == 0) {
		strcpy(mensagem, "Empate");
	}
	else {
		if (victorious == 1) {
			strcpy(mensagem, "X - Jogador 1 Ganhou!");

		}

		else {
			if (victorious == 2) {
				strcpy(mensagem, "O - Jogador 2 Ganhou!");

			}
		}
	}

	strcat(mensagem, "Deseja Jogar novamente?");
	if (wxMessageBox(mensagem, "Fim de partida!", wxYES_NO | wxICON_INFORMATION) == wxYES) {
		initBoard();
		EnableGrid();
	}
	else {
		Close(TRUE);
	}
}


//ação dos menus
void MainFrame::OnNewGame(wxCommandEvent& event) {
	EnableGrid();
	initBoard();
	SetStatusText("Vez de Jogador 1 Jogar");
}
void MainFrame::OnSair(wxCommandEvent& event) {
	wxMessageBox("O Jogo Será encerrado", "Encerrando o Jogo", wxOK | wxICON_INFORMATION);
	Close(true);
}
void MainFrame::OnSobre(wxCommandEvent& event) {
	wxMessageBox("Meu nome é EVERTON e este é primeiro jogo Criado em Linguam C/C++", "Sobre o Jogo", wxOK | wxICON_INFORMATION);

}

//ações Botões
void MainFrame::OnUpLeftClick(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		board[0][0] = player;
		m_btnUpLeft->Disable();
		if (player == 1) {
			m_btnUpLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnUpMidClick(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		board[0][1] = player;
		m_btnUpMid->Disable();
		if (player == 1) {
			m_btnUpMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnUpRightClick(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		board[0][2] = player;
		m_btnUpRight->Disable();
		if (player == 1) {
			m_btnUpRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnMidLeftClick(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		board[1][0] = player;
		m_btnMidLeft->Disable();
		if (player == 1) {
			m_btnMidLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnMidMidClick(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		board[1][1] = player;
		m_btnMidMid->Disable();
		if (player == 1) {
			m_btnMidMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnMidRightClick(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		board[1][2] = player;
		m_btnMidRight->Disable();
		if (player == 1) {
			m_btnMidRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnLowLeftClick(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		board[2][0] = player;
		m_btnLowLeft->Disable();
		if (player == 1) {
			m_btnLowLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnLowMidClick(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		board[2][1] = player;
		m_btnLowMid->Disable();
		if (player == 1) {
			m_btnLowMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnLowRightClick(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		board[2][2] = player;
		m_btnLowRight->Disable();
		if (player == 1) {
			m_btnLowRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}
void MainFrame::OnUpLeftEnterWindow(wxCommandEvent & event){
	if (m_btnUpLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1){
			strcat(m_msgStatusBar, "X!");
			
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnUpMidEnterWindow(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnUpRightEnterWindow(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}

void MainFrame::OnMidLeftEnterWindow(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnMidMidEnterWindow(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnMidRightEnterWindow(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}

void MainFrame::OnLowLeftEnterWindow(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnLowMidEnterWindow(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnLowRightEnterWindow(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}

void MainFrame::OnUpLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnUpMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnUpRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}

void MainFrame::OnMidLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnMidMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnMidRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}

void MainFrame::OnLowLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnLowMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
void MainFrame::OnLowRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "clik aqui para marcar ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");

		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);

}
