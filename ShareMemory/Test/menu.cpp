#include <windows.h>
#include "resource.h"
#include "bline.h"

/*---------------------------����ŧi----------------------------*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

/*---------------------------�{���ҩl�禡------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)	
{
/*�ŧi�ܼƦW�٤Ϋ��A*/
	static TCHAR szAppName[] = TEXT ("Bezier") ;			//�r��A�Ψӷ�������W��	
	HWND	    	hwnd ;						//�ΨӦs���������N��
	MSG		msg ;						//�ΨӦs��q�t�Ψ��o���T��(message)
	WNDCLASS	wndclass ;					//�������O������(instance)
/*�]�w�����򥻸��*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;			//�������˦�
	wndclass.lpfnWndProc = WndProc ;				//�B�z�����T�����禡
	wndclass.cbClsExtra = 0 ;					//�����D
	wndclass.cbWndExtra = 0 ;					//�����D
	wndclass.hInstance = hInstance ;				//��������N��
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;		//�ϥ�(Icon)���N��
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;		//���(Cusor)�N��
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;//�I���C��(�e��)
	wndclass.lpszMenuName  = szAppName ;					//������檺����N��
	wndclass.lpszClassName = szAppName ;				//�����W��
/*�VOS���U�o�ӵ������O*/
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, 					//�T��������N��
				TEXT ("Program requires Windows NT!"), 	//�T�������e��r
				szAppName, 				//�T�����W��
				MB_ICONERROR) ;				//�T��������
		return 0 ;
	}
/*�إ�(create)�o�ӵ���*/	
	hwnd = CreateWindow (szAppName, 		//�����W��
				TEXT ("Bezier Splines"),//���������D�r��
				WS_OVERLAPPEDWINDOW, 	//����������
				CW_USEDEFAULT, 		//�������W����m(x)
				CW_USEDEFAULT, 		//�������W����m(y)
				CW_USEDEFAULT, 		//�����e��
				CW_USEDEFAULT,		//��������
				NULL, 			//����������N��
				NULL, 			//��檺����N��
				hInstance, 		//�����������N��
				NULL) ;			//creation parameters(�����D)
/*�b�ù��W��ܳo�ӵ���*/
	ShowWindow (hwnd, iCmdShow) ;
/*�e�X�o�ӵ�����Clinent Area*/
	UpdateWindow (hwnd) ;
/*�إ߰T���B�z�j��*/
	while (GetMessage (&msg, NULL, 0, 0)) {	//�V�T����C���o�T��
		TranslateMessage (&msg) ;	//
		DispatchMessage (&msg) ;	//
	}
	return msg.wParam ;
}
/*---------------------------�T���B�z�禡------------------------*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szAppName[] = TEXT ("Bezier") ;			//�r��A�Ψӷ�������W��
	static POINT 	apt[4] ;		//�إߥ|���I����m(x,y)
	HDC		hdc ;			//�ΨӦs��DC������N��
	int		cxClient, cyClient ;	//�ΨӦs�����Client Area�j�p
	PAINTSTRUCT  	ps ;			//�ΨӦs��ø�ϸ�T
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
/*��������*/
	case WM_CREATE:
	return 0;
/*�����j�p�Q����*/
	case WM_SIZE:
		cxClient = LOWORD (lParam) ;	//�qlParam���o�s�����e��
		cyClient = HIWORD (lParam) ;	//�qlParam���o�s��������
		apt[0].x = cxClient / 4 ;	//�̷s���������׽վ�|���I����m
		apt[0].y = cyClient / 2 ;	//
		apt[1].x = cxClient / 2 ;	//
		apt[1].y = cyClient / 4 ;	//
		apt[2].x = cxClient / 2 ;	//
		apt[2].y = 3 * cyClient / 4 ;	//
		apt[3].x = 3 * cxClient / 4 ;	//
		apt[3].y =	cyClient / 2 ;	//
		SetPoint(apt);
		//�]��WM_SIZE�T���|Ĳ�oWM_PAINT�T���A�ҥH�����|�A���@����ø
		return 0 ;
/*�ƹ�����Q���U*/
	case WM_LBUTTONDOWN:
/*�ƹ��k��Q���U*/
	case WM_RBUTTONDOWN:
/*�ƹ�����*/
	case WM_MOUSEMOVE:
	/*�p�G�ƹ�������Υk��Q���U*/
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
			hdc = GetDC (hwnd) ;				//���oDC����N��
	/*�M����Ӫ����u*/
			SelectObject (hdc, GetStockObject (WHITE_PEN)) ;//�]�w�e���C�⬰�զ�
			DrawBezier (hdc) ;				//��apt�}�C���Ҧs���ƭ�ø���ɺ����u
	/*�]�w�ƹ����䱱�����*/
			if (wParam & MK_LBUTTON)
			{
				apt[1].x = LOWORD (lParam) ;//�qlParam���U�b�����ox�y��
				apt[1].y = HIWORD (lParam) ;//�qlParam���W�b�����oy�y��
				SetPoint(apt);
			}
	/*�]�w�ƹ����䱱�����*/
			if (wParam & MK_RBUTTON)
			{
				apt[2].x = LOWORD (lParam) ;//�qlParam���U�b�����ox�y��
				apt[2].y = HIWORD (lParam) ;//�qlParam���W�b�����oy�y��
				SetPoint(apt);
			}
	/*ø�s�����u*/
			SelectObject (hdc, GetStockObject (BLACK_PEN)) ;//�]�w�e���C�⬰�¦�
			DrawBezier (hdc) ;				//��apt�}�C���Ҧs���ƭ�ø���ɺ����u
			ReleaseDC (hwnd, hdc) ;				//����DC����
		}
		return 0 ;
/*������ø*/
	case WM_PAINT:
		InvalidateRect (hwnd, NULL, TRUE) ;	//���o��ø�ϰ�(�x��)		
		hdc = BeginPaint (hwnd, &ps) ;		//���oDC�N���A�õ��Pø�ϸ�T
		//SetPoint(apt);//���B���i�I�s�A�_�h�N�ɭP�O���餣�@�ΡA��]����
		DrawBezier (hdc) ;			//��apt�}�C���Ҧs���ƭ�ø���ɺ����u		
		EndPaint (hwnd, &ps) ;			//����DC����
		return 0 ;
/*���������{��*/
	case WM_DESTROY:
		PostQuitMessage (0) ;//�b�T����C�����J�@��WM_QUIT���T���A�{������
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

