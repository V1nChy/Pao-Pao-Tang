#include <windows.h> 
#include <windowsx.h> 
#include <commctrl.h> 
#include <tchar.h> 

#include "stdafx.h"
#include"FrameGame.h"
#include "AI.h"
#include"Paopao.h"
#include"DataProcess.h"
#include"GameOutput.h"

#pragma comment(lib, "user32.lib") 
#pragma comment(lib, "gdi32.lib") 
#pragma comment(lib, "comctl32.lib") 


int map[HEIGHT][WIDTH];//��ͼ��Ϣ
int giftMap[HEIGHT][WIDTH];///������Ϣ
bool begin;//��ʼ׼��״̬
bool end;//����״̬
struct Role *role1, *role2;

Paopao paopao;
GameOutput Output;
DataProcess Process;
AI Ai;

HDC bufHdc;//ͼ�񻺴�
HWND hGame, hMain;

int win, x, y, GameStytle,Ani=1500;


void EnterGame(int stytle)
{
	GameStytle = stytle;
	Process.GameStart();//��ʼ����ɫ����ͼ������,����
	begin = true;
	end = false;
	win = -1;

	//��һ��ʱ��ִ��һ���£�����WM_TIMER
	SetTimer(hGame, 1, 20, TimerProc);//���ڻ���
	SetTimer(hGame, 2, 30, TimerProc);//����
	SetTimer(hGame, 3, 83, TimerProc);//����
	SetTimer(hGame, 4, 30, TimerProc);//��ը����
	SetTimer(hGame, 5, 20, TimerProc);//�˹�����

	ShowWindow(hGame, SW_SHOWNORMAL);
	ShowWindow(hMain, SW_HIDE);
	UpdateWindow(hGame);



	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) > 0) {

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}
}


LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp)

{

	switch (uMsg) {

	case WM_CLOSE:

		DestroyWindow(hwnd);

		return 0;

	case WM_NCDESTROY:

		PostQuitMessage(0);

		return 0;

	case WM_PAINT: {

					   PAINTSTRUCT ps;

					   HDC dc = BeginPaint(hwnd, &ps);

					   Output.PaintMain(dc,bufHdc);

					   EndPaint(hwnd, &ps);

					   return 0;

	}

	case WM_CREATE: {

						CreateWindow("BUTTON", "������Ϸ",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 100, 125, 50, hwnd, (HMENU)10001,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "˫����Ϸ",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							550, 200, 125, 50, hwnd, (HMENU)10002,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "��Ϸ����",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 300, 125, 50, hwnd, (HMENU)10003,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "�˳���Ϸ",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 450, 125, 50, hwnd, (HMENU)10004,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						return 0;

	}

	case WM_COMMAND: {
						
						 if (LOWORD(wp) == 10001 && HIWORD(wp) == BN_CLICKED)
						 {

							 hGame = CreateWindow(_T("GameWindow"), _T("�����á�������Ϸ"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

								 x, y, 800, 630, NULL, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);


							 EnableWindow(hwnd, FALSE);
							 EnterGame(1);


							 ShowWindow(hwnd, SW_SHOWNA);
							 InvalidateRect(hwnd, NULL, TRUE);
							 EnableWindow(hwnd, TRUE);
							 SetFocus(hwnd);
							
						 }
						 else if (LOWORD(wp) == 10002 && HIWORD(wp) == BN_CLICKED)
						 {

							 hGame = CreateWindow(_T("GameWindow"), _T("�����á�˫����Ϸ"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

								 x, y, 800, 630, NULL, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);


							 EnableWindow(hwnd, FALSE);
							 EnterGame(2);


							 ShowWindow(hwnd, SW_SHOWNA);
							 InvalidateRect(hwnd, NULL, TRUE);
							 EnableWindow(hwnd, TRUE);
							 SetFocus(hwnd);

						 }
						 else if (LOWORD(wp) == 10003 && HIWORD(wp) == BN_CLICKED)
						 {
							 HWND hHelp = CreateWindow(_T("HelpWindow"), _T("�����á���Ϸ����"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

								 x, y, 800, 630, NULL, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 0);
							 
							 EnableWindow(hwnd, FALSE);
							 ShowWindow(hHelp, SW_SHOWNORMAL);
							 ShowWindow(hMain, SW_HIDE);
							 UpdateWindow(hHelp);

							 MSG msg;

							 while (GetMessage(&msg, 0, 0, 0) > 0) {

								 TranslateMessage(&msg);

								 DispatchMessage(&msg);

							 }
							 ShowWindow(hwnd, SW_SHOWNA);
							 InvalidateRect(hwnd, NULL, TRUE);
							 EnableWindow(hwnd, TRUE);
							 SetFocus(hwnd);
						 }
						 else if (LOWORD(wp) == 10004 && HIWORD(wp) == BN_CLICKED)
						 {
							 PostQuitMessage(0);
						 }
						 ShowWindow(hwnd, SW_SHOW);
						 PlaySound("..\\Debug\\sound\\main.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
						 return 0;

	}

	default:

		return DefWindowProc(hwnd, uMsg, wp, lp);

	}

}


LRESULT CALLBACK GameProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT		ps;		//�ýṹ�������ĳӦ�ó���������������ӵ�еĴ��ڿͻ�������Ҫ����Ϣ
	HDC				hdc;

	switch (uMsg) 
	{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
					 return(0);
		} break;

		case WM_NCDESTROY:
		{
			PostQuitMessage(0);
					return 0;
		}break;

		case WM_CREATE://������ť
		{
			CreateWindow("BUTTON", "���ز˵�",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  650, 555, 130, 35, hwnd, (HMENU)10005,(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					return 0;
		}break;

		case WM_COMMAND://���ť
		{
			if (LOWORD(wparam) == 10005 && HIWORD(wparam) == BN_CLICKED)
			{
				DestroyWindow(hwnd);
			}
					return 0;
		}break;

		case WM_PAINT: //���»���
		{
			 hdc = GetDC(hwnd);
			 hdc = BeginPaint(hwnd, &ps);// ָ�����ڽ��л�ͼ������׼��
			 EndPaint(hwnd, &ps);//ָ�����ڵĻ滭���̽���
					return 0;
		}break;

		case WM_KEYDOWN://���¼�
		{
			if (role1 != NULL && role1->Auto == false)
			{
				if (int(wparam) == VK_SPACE)
					role1->addPopo = true;
				else if ((int)wparam == VK_W || (int)wparam == VK_S || (int)wparam == VK_A || (int)wparam == VK_D)
				{
					switch ((int)wparam)
					{
						case VK_W:role1->direction = UP;break;
						case VK_S:role1->direction = DOWN;break;
						case VK_A:role1->direction = LEFT;break;
						case VK_D:role1->direction = RIGHT;break;
					}
					//��������һ��ʱ�Ĵ���
					role1->keyState[role1->direction] = true;
					for (int i = 0; i<4; i++)
					{
						if (i != role1->direction)
							role1->keyState[i] = false;
					}
					role1->Active_keystate = true;
				}
			}
			if (role2 != NULL && role2->Auto == false)
			{
				if (int(wparam) == VK_NUMPAD0)
					role2->addPopo = true;
				else if ((int)wparam == VK_UP || (int)wparam == VK_DOWN || (int)wparam == VK_LEFT || (int)wparam == VK_RIGHT)
				{
					switch ((int)wparam)
					{
						case VK_UP:role2->direction = UP;break;
						case VK_DOWN:role2->direction = DOWN;break;
						case VK_LEFT:role2->direction = LEFT;break;
						case VK_RIGHT:role2->direction = RIGHT;break;
					}
					//��������һ��ʱ�Ĵ���
					role2->keyState[role2->direction] = true;
					for (int i = 0; i<4; i++)
					{
						if (i != role2->direction)
							role2->keyState[i] = false;
					}
					role2->Active_keystate = true;
				}
			}
		}break;
		
		case WM_KEYUP://���̰�������
		{
			if (role1 != NULL && role1->Auto == false)
			{
				if ((int)wparam == VK_W || (int)wparam == VK_S || (int)wparam == VK_A || (int)wparam == VK_D)
				{
					switch ((int)wparam)
					{
						case VK_W:role1->keyState[UP] = false;break;
						case VK_S:role1->keyState[DOWN] = false;break;
						case VK_A:role1->keyState[LEFT] = false;break;
						case VK_D:role1->keyState[RIGHT] = false;break;
					}
					bool flag = true;
					for (int i = 0; i<4; i++)
					{
						if (role1->keyState[i] == true)
						{
							flag = false;
							break;
						}
					}
					if (flag)
						role1->Active_keystate = false;
				}
			}


			if (role2 != NULL && role2->Auto == false)
			{
				if ((int)wparam == VK_UP || (int)wparam == VK_DOWN || (int)wparam == VK_LEFT || (int)wparam == VK_RIGHT)
				{
					switch ((int)wparam)
					{
						case VK_UP:role2->keyState[UP] = false;break;
						case VK_DOWN:role2->keyState[DOWN] = false;break;
						case VK_LEFT:role2->keyState[LEFT] = false;break;
						case VK_RIGHT:role2->keyState[RIGHT] = false;break;
					}
					bool flag = true;
					for (int i = 0; i<4; i++)
					{
						if (role2->keyState[i] == true)
						{
							flag = false;
							break;
						}
					}
					if (flag)
						role2->Active_keystate = false;
				}
			}
		}break;

		default:break;
	}

	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}


LRESULT CALLBACK HelpProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp)

{

	switch (uMsg) {

	case WM_CLOSE:

		DestroyWindow(hwnd);

		return 0;

	case WM_NCDESTROY:

		PostQuitMessage(0);

		return 0;

	case WM_PAINT: {

					   PAINTSTRUCT ps;

					   HDC dc = BeginPaint(hwnd, &ps);

					   Output.PaintHelp(dc, bufHdc);

					   EndPaint(hwnd, &ps);

					   return 0;

	}

	case WM_CREATE: {

						CreateWindow("BUTTON", "���ز˵�",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							630, 60, 125, 50, hwnd, (HMENU)10006,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						return 0;

	}

	case WM_COMMAND: {

						 if (LOWORD(wp) == 10006 && HIWORD(wp) == BN_CLICKED)
						 {
							 DestroyWindow(hwnd);
						 }
						 return 0;

	}

	default:

		return DefWindowProc(hwnd, uMsg, wp, lp);

	}

}


void CALLBACK TimerProc(HWND hwnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	HDC hdc;
	hdc = GetDC(hwnd);

	switch (nTimerid)
	{
		case 1://������Ϸ����
			Output.Paint(hdc,bufHdc);break;
		case 2://��Ϸ��ʼ������Ķ������ݴ���
		if (begin)//�ǳ�
		{
			role1->state++;
			role2->state++;
			if (role1->state >= BEGINSTATE + 60)//�ǳ�����ʱ��
			{
				begin = false;
				role1->state = 1;
				role2->state = 1;
				win = 0;
			}

		}
		else if (end)//������ʤ��һ������
		{
			if (role1 != NULL)
			{
				if (role1->state < ENDSTATE)
				{
					role1->state = ENDSTATE;
				}
				else if (role1->state > ENDSTATE + 72)
				{
					//���¿�ʼ��
					end = false;
					Process.GameStart();
					begin = true;
				}
				else
					role1->state++;
			}
			else if (role2 != NULL)
			{
				if (role2->state < ENDSTATE)
				{
					role2->state = ENDSTATE;
				}
				else if (role2->state > ENDSTATE + 72)
				{
					end = false;
					Process.GameStart();
					begin = true;
				}
				else
					role2->state++;
			}
			else
			{
				if (win++ > 72)
				{
					end = false;
					Process.GameStart();
					begin = true;
				}
			}

		}
		else//��Ϸ���ݸ���
		{
			if (role1 != NULL)
				Process.DealRole(map, role1, role1->Active_keystate);
			if (role2 != NULL)
				Process.DealRole(map, role2, role2->Active_keystate);
		}
		break;

		case 3://��Ϸ���ݴ���
		{
			  struct Popo *temp;
			  temp = paopao.get_popo();
			  while (temp != NULL)
			  {
				  if (temp->life >= POPOLIFE)
				  {
					  //�������ݱ�ը���������ݴ���
					  paopao.DealExPopo(temp->x, temp->y);
				  }
				  else
				  {
					  temp->life++;
				  }

				  temp = temp->next;
			  }
		}
		break;

		//��ը��������ߵĶ�̬�仯
		case 4:
		{
			  for (int i = 0; i<WIDTH; i++)
			  for (int j = 0; j<HEIGHT; j++)
			  {
				  switch (map[j][i])
				  {
					//����״̬�Ķ�̬����
						case GIFT1:
						case GIFT2:
						case GIFT3:
						case GIFT4:
						case GIFT5:
						case GIFT6:
						case GIFT7:
						case GIFT8:giftMap[j][i] = (giftMap[j][i] + 1) % 18;break;
					//��ը������

						case EXPLOSIONCENTRE + 7:
						case EXPLOSIONUP + 13:
						case EXPLOSIONDOWN + 13:
						case EXPLOSIONLEFT + 13:
						case EXPLOSIONRIGHT + 13:
							map[j][i] = SANDGROUND;
							if (role1->immunex == i && role1->immuney == j)
							{
								role1->immunex = -1; role1->immuney = -1;
							}
							if (role2->immunex == i && role2->immuney == j)
							{
								role2->immunex = -1; role2->immuney = -1;
							}break;
						default:
							 break;
				  }
				  //��ը���ݵĶ�̬����
				  if (map[j][i] > 100)
					  map[j][i]++;

					Ani = (Ani + 1) % 4500;
			  }
		}
		break;
		//��Ϸ��ɫ2���˹����ܣ����Դ���
		case 5:
		{
			  /*if (role1->Auto)
				  AutoProcess(role1, role2);*/
			  if (role2->Auto)
				  Ai.AutoProcess(role2, role1);
		}break;
		default:
			break;
	}

	ReleaseDC(hwnd, hdc);
}


int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR szCmd, INT nShow)

{

	InitCommonControls();

	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));//ֻ�ǽ�ָ�����ڴ������
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainProc;
	wc.hInstance = hInst;
	wc.lpszClassName = _T("MainWindow");
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wc);
	//ע��  MainWindow

	wc.lpszClassName = _T("GameWindow");
	wc.lpfnWndProc = GameProc;
	RegisterClass(&wc);
	//ע��  GameWindow

	wc.lpszClassName = _T("HelpWindow");
	wc.lpfnWndProc = HelpProc;
	RegisterClass(&wc);
	//ע��  GameWindow

	x = ((GetSystemMetrics(SM_CXSCREEN) / 2) - 400); //x����
	y = ((GetSystemMetrics(SM_CYSCREEN) / 2) - 315); //y����

	//������
	HWND hMain = CreateWindow(_T("MainWindow"), _T("������"), WS_OVERLAPPEDWINDOW,

		x, y, 800, 630, NULL, NULL, hInst, 0);

	//�Ӵ�����Ϣ
	hGame = CreateWindow(_T("GameWindow"), _T("������"), WS_OVERLAPPEDWINDOW,

		x, y, 800, 630, NULL, NULL, hInst, 0);

	HDC imageDC;//λͼ��Ϣ
	HBITMAP bmp;//��ͼ��
	HDC hdc = GetDC(hGame);//������ʾ�豸�����Ļ����ľ��
	bufHdc = CreateCompatibleDC(hdc);//����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
	imageDC = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc, 800, 600); //�ú���������ָ�����豸������ص��豸���ݵ�λͼ��
	SelectObject(bufHdc, bmp);//ѡ��һ����ָ�����豸�����Ļ�����
	Output.InitFile(hdc, imageDC);//��ʼ��,����ͼƬ
	//�Ӵ���

	ShowWindow(hMain, SW_SHOWNORMAL);
	UpdateWindow(hMain);


	PlaySound("..\\Debug\\sound\\main.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) > 0) {

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}



	return msg.wParam;

}