#pragma once
class TicTacToeGame
{
	public:
		static const int CELL_SIZE = 100;						// size of the cells
		HBRUSH RED = CreateSolidBrush(RGB(255, 0, 0));			// colors created for game
		HBRUSH BLUE = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH PURPLE = CreateSolidBrush(RGB(55, 0, 71));
		HICON IcPlayer1, IcPlayer2;
		INT UsedBoxes[9] = { 0 };								// sees if boxes were used
		INT WinCells[3] = { 0 };								// sees which cells won
		INT PlayerTurn = 1;										// who has the turn
		INT PlayerWon = 0;										// who won the game

		

														//Global Functions
		BOOL GetGameBoardRect(HWND, RECT *);			// get rectangle of the 
		BOOL GetCellRect(HWND, int, RECT *);			// get the rectangle of the cell
		BOOL CheckEqual(int, int, int);					// see if boxes contain same value;

		INT CheckWin(int[3], int);						// check to see if anyone won game
		INT GetBoxNumber(HWND, int, int);				// get index location of the box used
		void DrawLine(HDC, int, int, int, int);			// draw lines in window
		void DrawIconCentered(HDC, RECT *, HICON);		// draw icon centered into the cell
		void StartNewGame(HWND, int);
		void DrawLabels(HWND, HDC, HICON, HICON);
		void DrawTurn(HWND, HDC);

		TicTacToeGame();
		~TicTacToeGame();
};

