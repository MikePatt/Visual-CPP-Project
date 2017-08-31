#pragma once
#include "stdafx.h"
#include "TicTacToeGame.h"

// constructor
TicTacToeGame::TicTacToeGame()
{
}

// destructor that deletes created objects
TicTacToeGame::~TicTacToeGame()
{
	DeleteObject(this->BLUE);
	DeleteObject(this->RED);
	DeleteObject(this->PURPLE);
	DestroyIcon(IcPlayer1);
	DestroyIcon(IcPlayer2);
}
// gets the dimensions of the game board
BOOL TicTacToeGame::GetGameBoardRect(HWND hWnd, RECT * pRect)
{
	RECT rc;
	if (GetClientRect(hWnd, &rc))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		pRect->left = (width - CELL_SIZE * 3) / 2;
		pRect->top = (height - CELL_SIZE * 3) / 2;
		pRect->right = pRect->left + CELL_SIZE * 3;
		pRect->bottom = pRect->top + CELL_SIZE * 3;
		return TRUE;
	}

	SetRectEmpty(pRect);
	return FALSE;
}

// draws the game board
void TicTacToeGame::DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// returns the index of the cell 
INT TicTacToeGame::GetBoxNumber(HWND hWnd, int xPos, int yPos)
{
	RECT rc;
	POINT pt = { xPos, yPos };
	if (GetGameBoardRect(hWnd, &rc))
	{
		if (PtInRect(&rc, pt))
		{
			//Normalize Location Values
			xPos -= rc.left;
			yPos -= rc.top;

			int column = xPos / CELL_SIZE;
			int row = yPos / CELL_SIZE;
			return row * 3 + column;
		}
	}
	return -1;
}

// gets the dimensions of the cell
BOOL TicTacToeGame::GetCellRect(HWND hWnd, int index, RECT * pRect)
{
	SetRectEmpty(pRect);
	if (index >= 0 && index <= 8)
	{
		RECT rcBoard;
		if (GetGameBoardRect(hWnd, &rcBoard))
		{
			int x = index % 3;
			int y = index / 3;
			pRect->left = (rcBoard.left + CELL_SIZE * x) + 1;
			pRect->right = pRect->left + CELL_SIZE - 1;
			pRect->top = (rcBoard.top + CELL_SIZE * y) + 1;
			pRect->bottom = pRect->top + CELL_SIZE - 1;
			return TRUE;
		}
	}
	return FALSE;
}

// checks if there is a winner
INT TicTacToeGame::CheckWin(int winCells[3], int winCellSize)
{
	//ways a player can win
	int cellWins[] = { 0,1,2, 0,3,6, 0,4,8, 1,4,7, 2,4,6, 2,5,8, 3,4,5, 6,7,8 };
	//check to see if player has got three in a line
	for (int i = 0; i < ARRAYSIZE(cellWins); i += 3)
	{
		if (UsedBoxes[cellWins[i]] && CheckEqual(UsedBoxes[cellWins[i]], UsedBoxes[cellWins[i + 1]], UsedBoxes[cellWins[i + 2]]))
		{
			for (int j = 0; j < winCellSize; j++)
			{
				winCells[j] = cellWins[i + j];
			}
			return UsedBoxes[cellWins[i]];
		}
	}
	// checks to see if theres a draw
	for (int i = 0; i < 9; i++)
	{
		if (!UsedBoxes[i])
			break;
		else if (i == 8)
			return 3;
	}
	return 0;
}

// checks if three ints are equal
BOOL TicTacToeGame::CheckEqual(int a, int b, int c)
{
	if (a == b && b == c)
		return TRUE;
	return FALSE;
}

// draws the player labels
void TicTacToeGame::DrawLabels(HWND hWnd, HDC hdc, HICON hIcon1, HICON hIcon2)
{
	RECT G_RECT;
	const WCHAR wcPlayer1[] = L"Player 1:";
	const WCHAR wcPlayer2[] = L"Player 2:";
	GetGameBoardRect(hWnd, &G_RECT);
	G_RECT.bottom = G_RECT.top;
	G_RECT.top -= 52;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 255));
	DrawText(hdc, wcPlayer1, lstrlen(wcPlayer1), &G_RECT, DT_LEFT);
	DrawIcon(hdc, G_RECT.left + lstrlen(wcPlayer1), G_RECT.top + 16, hIcon1);
	SetTextColor(hdc, RGB(255, 0, 0));
	DrawIcon(hdc, G_RECT.right - lstrlen(wcPlayer2) * 5, G_RECT.top + 16, hIcon2);
	DrawText(hdc, wcPlayer2, lstrlen(wcPlayer2), &G_RECT, DT_RIGHT);
	return;
}

// draws which player has the turn
void TicTacToeGame::DrawTurn(HWND hWnd, HDC hdc)
{
	RECT G_RECT;
	static const WCHAR wcPlayer1[] = L"Player 1's Turn";
	static const WCHAR wcPlayer2[] = L"Player 2's Turn";
	static const WCHAR wcPlayWon1[] = L"Player 1 is the Winner!";
	static const WCHAR wcPlayWon2[] = L"Player 2 is the Winner!";
	static const WCHAR wcPlayDraw[] = L"Its a Draw!!";
	GetGameBoardRect(hWnd, &G_RECT);
	G_RECT.top = G_RECT.bottom;
	G_RECT.bottom += 20;
	FillRect(hdc, &G_RECT, PURPLE);
	SetBkColor(hdc, RGB(55, 0, 71));
	SetTextColor(hdc, RGB(255, 255, 255));
	switch (PlayerWon)
	{
		case 0:
			if (PlayerTurn == 1)
				DrawText(hdc, wcPlayer1, lstrlen(wcPlayer1), &G_RECT, DT_CENTER);
			else if (PlayerTurn == 2)
				DrawText(hdc, wcPlayer2, lstrlen(wcPlayer2), &G_RECT, DT_CENTER);
			break;
		case 1:
			DrawText(hdc, wcPlayWon1, lstrlen(wcPlayWon1), &G_RECT, DT_CENTER);
			break;
		case 2:
			DrawText(hdc, wcPlayWon2, lstrlen(wcPlayWon2), &G_RECT, DT_CENTER);
			break;
		case 3:
			DrawText(hdc, wcPlayDraw, lstrlen(wcPlayDraw), &G_RECT, DT_CENTER);
			break;
		default:
			break;
		}
		return;
}

// ensures the icons are in the center of the cell
void TicTacToeGame::DrawIconCentered(HDC hdc, RECT * pRect, HICON hIcon)
{
	if (pRect != NULL)
	{
		ICONINFO ii;
		int iconWidth;
		int iconHeight;
		//
		// get height and width of icon
		//
		if (GetIconInfo(hIcon, &ii))
		{
			BITMAP bm;
			if (GetObject(ii.hbmMask, sizeof(bm), &bm))
			{
				iconWidth = bm.bmWidth;
				iconHeight = ii.hbmColor ? bm.bmHeight : 0;
			}
		}

		int left = (pRect->left + (pRect->right - pRect->left) / 2) - iconWidth / 2;
		int top = (pRect->top + (pRect->bottom - pRect->top) / 2) - iconHeight / 2;

		DeleteObject(ii.hbmMask);
		DeleteObject(ii.hbmColor);
		DrawIcon(hdc, left, top, hIcon);
	}
}

// starts new game based on whether a player has won or if in the middle of a new game
void TicTacToeGame::StartNewGame(HWND hWnd, int loc)
{
	int choice = MessageBox(hWnd, (loc == 0) ? L"Are You Sure You Want to Start New Game?" : L"Do You Wish to Play Again?", L"New Game", MB_YESNO | MB_ICONQUESTION);
	if (IDYES == choice)
	{
		ZeroMemory(UsedBoxes, sizeof(UsedBoxes));
		ZeroMemory(WinCells, sizeof(WinCells));
		PlayerTurn = 1;
		PlayerWon = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}
	return;
}
