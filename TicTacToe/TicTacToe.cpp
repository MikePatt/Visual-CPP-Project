// TicTacToe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windowsx.h>
#include "TicTacToe.h"
#include "TicTacToeGame.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//static const int TTT.CELL_SIZE = 100;				// size of the cells
//HBRUSH BLUE, RED;								// colors created for game
//HBRUSH PURPLE = CreateSolidBrush(RGB(55, 0, 71));
//HICON TTT.IcPlayer1, TTT.IcPlayer2;
//INT TTT.UsedBoxes[9] = { 0 };						// sees if boxes were used
//INT TTT.WinCells[3] = { 0 };						// sees which cells won
//
//
//void TTT.DrawLabels(HWND, HDC, HICON, HICON);
//void TTT.DrawTurn(HWND, HDC);
//
//INT TTT.PlayerTurn = 1;								// who has the turn
//INT TTT.PlayerWon = 0;								// who won the game
//
////Global Functions
//BOOL TTT.GetGameBoardRect(HWND, RECT *);			// get rectangle of the 
//BOOL TTT.GetCellRect(HWND, int, RECT *);			// get the rectangle of the cell
//BOOL CheckEqual(int, int, int);					// see if boxes contain same value;
//
//INT TTT.CheckWin(int[3], int);							// check to see if anyone won game
//INT TTT.GetBoxNumber(HWND, int, int);				// get index location of the box used
//void TTT.DrawLine(HDC, int, int, int, int);			// draw lines in window
//void TTT.DrawIconCentered(HDC, RECT *, HICON);		// draw icon centered into the cell
//void StartNewGame(HWND, int);
TicTacToeGame TTT;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = TTT.PURPLE;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TICTACTOE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND		- process the application menu
//  WM_CREATE		- creates icons
//  WM_LBUTTONDOWN	- handles left button click event
//  WM_PAINT		- Paint the main window
//  WM_DESTROY		- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_CREATE:
		{
			TTT.IcPlayer1 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PLAYER1));
			TTT.IcPlayer2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PLAYER2));
		}
		break;
		case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_NEWGAME:
				{
					TTT.StartNewGame(hWnd, 0);
				}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
		case WM_GETMINMAXINFO:
		{
			MINMAXINFO * pMinMax = (MINMAXINFO*)lParam;
			pMinMax->ptMinTrackSize.x = TTT.CELL_SIZE * 5;
			pMinMax->ptMinTrackSize.y = TTT.CELL_SIZE * 5;
			pMinMax->ptMaxTrackSize.x = TTT.CELL_SIZE * 5;
			pMinMax->ptMaxTrackSize.y = TTT.CELL_SIZE * 5;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int boxNumber = TTT.GetBoxNumber(hWnd, xPos, yPos);

			HDC hdc = GetDC(hWnd);
			if (hdc != NULL)
			{	
				//Get cell dimensions from index
				RECT rcCell;
				if (TTT.GetCellRect(hWnd, boxNumber, &rcCell) && !TTT.PlayerWon) 
				{
					//Fills space at index if nobody already won game and box not used
					if (!TTT.UsedBoxes[boxNumber] && !TTT.PlayerWon)
					{
						//FillRect(hdc, &rcCell, TTT.PlayerTurn == 2 ? RED : BLUE);
						TTT.DrawIconCentered(hdc, &rcCell, (TTT.PlayerTurn == 2) ? TTT.IcPlayer2 : TTT.IcPlayer1);
						TTT.UsedBoxes[boxNumber] = TTT.PlayerTurn;
						TTT.PlayerTurn = (TTT.PlayerTurn == 2 ? 1 : 2);
					}
				}
				
				// Checks to see if anyone won the game and places who won in TTT.PlayerWon variable
				if (TTT.PlayerWon = TTT.CheckWin(TTT.WinCells, ARRAYSIZE(TTT.WinCells)))
				{
					if (TTT.PlayerWon != 3)
					{
						for (int i = 0; i < ARRAYSIZE(TTT.WinCells); i++)
						{
							TTT.GetCellRect(hWnd, TTT.WinCells[i], &rcCell);
							FillRect(hdc, &rcCell, (HBRUSH)GetStockObject(WHITE_BRUSH));
							TTT.DrawIconCentered(hdc, &rcCell, TTT.PlayerWon == 2 ? TTT.IcPlayer2 : TTT.IcPlayer1);
						}
						MessageBox(hWnd, (TTT.PlayerWon == 2) ? L"Player 2 Won!" : L"Player 1 Won!", L"You Win!", MB_OK | MB_ICONINFORMATION);
					}
					else
						MessageBox(hWnd, L"Its a Draw!", L"Draw", MB_OK | MB_ICONINFORMATION);
					TTT.StartNewGame(hWnd, 1);
				}
				TTT.DrawTurn(hWnd, hdc);
				ReleaseDC(hWnd, hdc); 
			}
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			RECT rc;
			if (TTT.GetGameBoardRect(hWnd, &rc))
			{
				FillRect(hdc, &rc, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
				TTT.DrawLabels(hWnd, hdc, TTT.IcPlayer1, TTT.IcPlayer2);
				for(int i = 1; i <= 2; i++)
				{
					//Vertical Lines
					TTT.DrawLine(hdc, (rc.left + TTT.CELL_SIZE * i), rc.top, (rc.left + TTT.CELL_SIZE * i), rc.bottom);

					//Horizontal Lines
					TTT.DrawLine(hdc, rc.left, (rc.top + TTT.CELL_SIZE * i), rc.right, (rc.top + TTT.CELL_SIZE * i));
				}

				//Fill Cells After Refresh
				for (int i = 0; i < ARRAYSIZE(TTT.UsedBoxes); i++)
				{
					if (TTT.UsedBoxes[i] && TTT.GetCellRect(hWnd, i, &rc))
					{
						//FillRect(hdc, &rc, TTT.UsedBoxes[i] == 2 ? RED : BLUE);
						TTT.DrawIconCentered(hdc, &rc, (TTT.UsedBoxes[i]== 2) ? TTT.IcPlayer2 : TTT.IcPlayer1);
					}
				}
			}
			TTT.DrawTurn(hWnd, hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}