#include <windows.h>
#include "bline.h"

int WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
     return TRUE ;
}
/*---------------------------存取shared變數的函式------------------*/
/*因為宣告成shared的變數只能夠在DLL之中使用，所以必須把程式實際繪圖
  所需的apt陣列改成使用在DLL中宣告的變數point，同時DrawBezier也不再
  需要apt的參數*/
EXPORT void CALLBACK SetPoint (POINT apt[])		
{
	int count;
	for (count = 0; count < 4; count++) {
		point[count].x = apt[count].x;
		point[count].y = apt[count].y;
	}
}
/*---------------------------自訂繪圖函式------------------------*/
EXPORT void CALLBACK DrawBezier (HDC hdc)
{
	PolyBezier (hdc, point, 4) ;			//呼叫GDI32.DLL中的函式繪製貝爾曲線
	MoveToEx (hdc, point[0].x, point[0].y, NULL) ;	//從貝賽爾曲線最左側開始畫一條直線
	LineTo   (hdc, point[1].x, point[1].y) ;		//到滑鼠左鍵最後被按下時的位置
	MoveToEx (hdc, point[2].x, point[2].y, NULL) ;	//從貝賽爾曲線最右側開始畫一條直線
	LineTo   (hdc, point[3].x, point[3].y) ;		//到滑鼠右鍵最後被按下時的位置
}
