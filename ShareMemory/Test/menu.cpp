#include <windows.h>
#include "resource.h"
#include "bline.h"

/*---------------------------全域宣告----------------------------*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

/*---------------------------程式啟始函式------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)	
{
/*宣告變數名稱及型態*/
	static TCHAR szAppName[] = TEXT ("Bezier") ;			//字串，用來當視窗的名稱	
	HWND	    	hwnd ;						//用來存放視窗實體代號
	MSG		msg ;						//用來存放從系統取得的訊息(message)
	WNDCLASS	wndclass ;					//視窗類別的實體(instance)
/*設定視窗基本資料*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;			//視窗的樣式
	wndclass.lpfnWndProc = WndProc ;				//處理視窗訊息的函式
	wndclass.cbClsExtra = 0 ;					//不知道
	wndclass.cbWndExtra = 0 ;					//不知道
	wndclass.hInstance = hInstance ;				//視窗實體代號
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;		//圖示(Icon)的代號
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;		//游標(Cusor)代號
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;//背景顏色(畫刷)
	wndclass.lpszMenuName  = szAppName ;					//視窗選單的實體代號
	wndclass.lpszClassName = szAppName ;				//視窗名稱
/*向OS註冊這個視窗類別*/
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, 					//訊息盒實體代號
				TEXT ("Program requires Windows NT!"), 	//訊息盒內容文字
				szAppName, 				//訊息盒名稱
				MB_ICONERROR) ;				//訊息盒風格
		return 0 ;
	}
/*建立(create)這個視窗*/	
	hwnd = CreateWindow (szAppName, 		//視窗名稱
				TEXT ("Bezier Splines"),//視窗的標題字串
				WS_OVERLAPPEDWINDOW, 	//視窗的風格
				CW_USEDEFAULT, 		//視窗左上角位置(x)
				CW_USEDEFAULT, 		//視窗左上角位置(y)
				CW_USEDEFAULT, 		//視窗寬度
				CW_USEDEFAULT,		//視窗高度
				NULL, 			//父視窗實體代號
				NULL, 			//選單的實體代號
				hInstance, 		//本身的視窗代號
				NULL) ;			//creation parameters(不知道)
/*在螢幕上顯示這個視窗*/
	ShowWindow (hwnd, iCmdShow) ;
/*畫出這個視窗的Clinent Area*/
	UpdateWindow (hwnd) ;
/*建立訊息處理迴圈*/
	while (GetMessage (&msg, NULL, 0, 0)) {	//向訊息佇列取得訊息
		TranslateMessage (&msg) ;	//
		DispatchMessage (&msg) ;	//
	}
	return msg.wParam ;
}
/*---------------------------訊息處理函式------------------------*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szAppName[] = TEXT ("Bezier") ;			//字串，用來當視窗的名稱
	static POINT 	apt[4] ;		//建立四個點的位置(x,y)
	HDC		hdc ;			//用來存放DC的實體代號
	int		cxClient, cyClient ;	//用來存放視窗Client Area大小
	PAINTSTRUCT  	ps ;			//用來存放繪圖資訊
	HMENU	hMenu;

	switch (message)
	{
	case WM_COMMAND :
		hMenu = GetMenu (hwnd);
		switch (LOWORD(wParam)) {
		case ID_OPEN :
			MessageBox (NULL,TEXT ("Open!"),szAppName,MB_OK) ;
			return 0;
		}
/*視窗產生*/
	case WM_CREATE:
	return 0;
/*視窗大小被改變*/
	case WM_SIZE:
		cxClient = LOWORD (lParam) ;	//從lParam取得新視窗寬度
		cyClient = HIWORD (lParam) ;	//從lParam取得新視窗高度
		apt[0].x = cxClient / 4 ;	//依新的視窗高度調整四個點的位置
		apt[0].y = cyClient / 2 ;	//
		apt[1].x = cxClient / 2 ;	//
		apt[1].y = cyClient / 4 ;	//
		apt[2].x = cxClient / 2 ;	//
		apt[2].y = 3 * cyClient / 4 ;	//
		apt[3].x = 3 * cxClient / 4 ;	//
		apt[3].y =	cyClient / 2 ;	//
		SetPoint(apt);
		//因為WM_SIZE訊息會觸發WM_PAINT訊息，所以視窗會再做一次重繪
		return 0 ;
/*滑鼠左鍵被按下*/
	case WM_LBUTTONDOWN:
/*滑鼠右鍵被按下*/
	case WM_RBUTTONDOWN:
/*滑鼠移動*/
	case WM_MOUSEMOVE:
	/*如果滑鼠的左鍵或右鍵被按下*/
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
			hdc = GetDC (hwnd) ;				//取得DC實體代號
	/*清除原來的曲線*/
			SelectObject (hdc, GetStockObject (WHITE_PEN)) ;//設定畫刷顏色為白色
			DrawBezier (hdc) ;				//依apt陣列中所存的數值繪貝賽爾曲線
	/*設定滑鼠左鍵控制的部份*/
			if (wParam & MK_LBUTTON)
			{
				apt[1].x = LOWORD (lParam) ;//從lParam的下半部取得x座標
				apt[1].y = HIWORD (lParam) ;//從lParam的上半部取得y座標
				SetPoint(apt);
			}
	/*設定滑鼠左鍵控制的部份*/
			if (wParam & MK_RBUTTON)
			{
				apt[2].x = LOWORD (lParam) ;//從lParam的下半部取得x座標
				apt[2].y = HIWORD (lParam) ;//從lParam的上半部取得y座標
				SetPoint(apt);
			}
	/*繪新的曲線*/
			SelectObject (hdc, GetStockObject (BLACK_PEN)) ;//設定畫刷顏色為黑色
			DrawBezier (hdc) ;				//依apt陣列中所存的數值繪貝賽爾曲線
			ReleaseDC (hwnd, hdc) ;				//釋放DC實體
		}
		return 0 ;
/*視窗重繪*/
	case WM_PAINT:
		InvalidateRect (hwnd, NULL, TRUE) ;	//取得重繪區域(矩形)		
		hdc = BeginPaint (hwnd, &ps) ;		//取得DC代號，並給與繪圖資訊
		//SetPoint(apt);//此處不可呼叫，否則將導致記憶體不共用，原因不知
		DrawBezier (hdc) ;			//依apt陣列中所存的數值繪貝賽爾曲線		
		EndPaint (hwnd, &ps) ;			//釋放DC實體
		return 0 ;
/*結束視窗程式*/
	case WM_DESTROY:
		PostQuitMessage (0) ;//在訊息佇列中插入一個WM_QUIT的訊息，程式結束
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

