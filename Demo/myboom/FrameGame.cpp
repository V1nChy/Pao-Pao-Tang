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


int map[HEIGHT][WIDTH];//地图信息
int giftMap[HEIGHT][WIDTH];///道具信息
bool begin;//开始准备状态
bool end;//结束状态
struct Role *role1, *role2;

Paopao paopao;
GameOutput Output;
DataProcess Process;
AI Ai;

HDC bufHdc;//图像缓存
HWND hGame, hMain;

int win, x, y, GameStytle,Ani=1500;


void EnterGame(int stytle)
{
	GameStytle = stytle;
	Process.GameStart();//初始化角色，地图，道具,泡泡
	begin = true;
	end = false;
	win = -1;

	//隔一段时间执行一件事，发送WM_TIMER
	SetTimer(hGame, 1, 20, TimerProc);//窗口绘制
	SetTimer(hGame, 2, 30, TimerProc);//人物
	SetTimer(hGame, 3, 83, TimerProc);//泡泡
	SetTimer(hGame, 4, 30, TimerProc);//爆炸处理
	SetTimer(hGame, 5, 20, TimerProc);//人工智能

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

						CreateWindow("BUTTON", "单人游戏",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 100, 125, 50, hwnd, (HMENU)10001,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "双人游戏",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							550, 200, 125, 50, hwnd, (HMENU)10002,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "游戏帮助",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 300, 125, 50, hwnd, (HMENU)10003,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						CreateWindow("BUTTON", "退出游戏",
							WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							600, 450, 125, 50, hwnd, (HMENU)10004,
							(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

						return 0;

	}

	case WM_COMMAND: {
						
						 if (LOWORD(wp) == 10001 && HIWORD(wp) == BN_CLICKED)
						 {

							 hGame = CreateWindow(_T("GameWindow"), _T("泡泡堂—单人游戏"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

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

							 hGame = CreateWindow(_T("GameWindow"), _T("泡泡堂—双人游戏"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

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
							 HWND hHelp = CreateWindow(_T("HelpWindow"), _T("泡泡堂—游戏帮助"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,

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
	PAINTSTRUCT		ps;		//该结构体包含了某应用程序用来绘制它所拥有的窗口客户区所需要的信息
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

		case WM_CREATE://创建按钮
		{
			CreateWindow("BUTTON", "返回菜单",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  650, 555, 130, 35, hwnd, (HMENU)10005,(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
					return 0;
		}break;

		case WM_COMMAND://激活按钮
		{
			if (LOWORD(wparam) == 10005 && HIWORD(wparam) == BN_CLICKED)
			{
				DestroyWindow(hwnd);
			}
					return 0;
		}break;

		case WM_PAINT: //更新画面
		{
			 hdc = GetDC(hwnd);
			 hdc = BeginPaint(hwnd, &ps);// 指定窗口进行绘图工作的准备
			 EndPaint(hwnd, &ps);//指定窗口的绘画过程结束
					return 0;
		}break;

		case WM_KEYDOWN://按下键
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
					//方向键多个一起按时的处理
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
					//方向键多个一起按时的处理
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
		
		case WM_KEYUP://键盘按键放起
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

						CreateWindow("BUTTON", "返回菜单",
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
		case 1://绘制游戏画面
			Output.Paint(hdc,bufHdc);break;
		case 2://游戏开始与结束的动画数据处理
		if (begin)//登场
		{
			role1->state++;
			role2->state++;
			if (role1->state >= BEGINSTATE + 60)//登场动画时间
			{
				begin = false;
				role1->state = 1;
				role2->state = 1;
				win = 0;
			}

		}
		else if (end)//死亡后胜利一方画面
		{
			if (role1 != NULL)
			{
				if (role1->state < ENDSTATE)
				{
					role1->state = ENDSTATE;
				}
				else if (role1->state > ENDSTATE + 72)
				{
					//重新开始了
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
		else//游戏数据更新
		{
			if (role1 != NULL)
				Process.DealRole(map, role1, role1->Active_keystate);
			if (role2 != NULL)
				Process.DealRole(map, role2, role2->Active_keystate);
		}
		break;

		case 3://游戏泡泡处理
		{
			  struct Popo *temp;
			  temp = paopao.get_popo();
			  while (temp != NULL)
			  {
				  if (temp->life >= POPOLIFE)
				  {
					  //加上泡泡爆炸产生的数据代码
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

		//爆炸泡泡与道具的动态变化
		case 4:
		{
			  for (int i = 0; i<WIDTH; i++)
			  for (int j = 0; j<HEIGHT; j++)
			  {
				  switch (map[j][i])
				  {
					//道具状态的动态处理
						case GIFT1:
						case GIFT2:
						case GIFT3:
						case GIFT4:
						case GIFT5:
						case GIFT6:
						case GIFT7:
						case GIFT8:giftMap[j][i] = (giftMap[j][i] + 1) % 18;break;
					//爆炸柱结束

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
				  //爆炸泡泡的动态处理
				  if (map[j][i] > 100)
					  map[j][i]++;

					Ani = (Ani + 1) % 4500;
			  }
		}
		break;
		//游戏角色2（人工智能）的自处理
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

	ZeroMemory(&wc, sizeof(wc));//只是将指定的内存块清零
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainProc;
	wc.hInstance = hInst;
	wc.lpszClassName = _T("MainWindow");
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&wc);
	//注册  MainWindow

	wc.lpszClassName = _T("GameWindow");
	wc.lpfnWndProc = GameProc;
	RegisterClass(&wc);
	//注册  GameWindow

	wc.lpszClassName = _T("HelpWindow");
	wc.lpfnWndProc = HelpProc;
	RegisterClass(&wc);
	//注册  GameWindow

	x = ((GetSystemMetrics(SM_CXSCREEN) / 2) - 400); //x居中
	y = ((GetSystemMetrics(SM_CYSCREEN) / 2) - 315); //y居中

	//主窗口
	HWND hMain = CreateWindow(_T("MainWindow"), _T("泡泡堂"), WS_OVERLAPPEDWINDOW,

		x, y, 800, 630, NULL, NULL, hInst, 0);

	//子窗口信息
	hGame = CreateWindow(_T("GameWindow"), _T("泡泡堂"), WS_OVERLAPPEDWINDOW,

		x, y, 800, 630, NULL, NULL, hInst, 0);

	HDC imageDC;//位图信息
	HBITMAP bmp;//画图用
	HDC hdc = GetDC(hGame);//检索显示设备上下文环境的句柄
	bufHdc = CreateCompatibleDC(hdc);//创建一个与指定设备兼容的内存设备上下文环境
	imageDC = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc, 800, 600); //该函数创建与指定的设备环境相关的设备兼容的位图。
	SelectObject(bufHdc, bmp);//选择一对象到指定的设备上下文环境中
	Output.InitFile(hdc, imageDC);//初始化,加载图片
	//子窗口

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