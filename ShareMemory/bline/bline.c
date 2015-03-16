#include <windows.h>
#include "bline.h"

int WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
     return TRUE ;
}
/*---------------------------�s��shared�ܼƪ��禡------------------*/
/*�]���ŧi��shared���ܼƥu����bDLL�����ϥΡA�ҥH������{�����ø��
  �һݪ�apt�}�C�令�ϥΦbDLL���ŧi���ܼ�point�A�P��DrawBezier�]���A
  �ݭnapt���Ѽ�*/
EXPORT void CALLBACK SetPoint (POINT apt[])		
{
	int count;
	for (count = 0; count < 4; count++) {
		point[count].x = apt[count].x;
		point[count].y = apt[count].y;
	}
}
/*---------------------------�ۭqø�Ϩ禡------------------------*/
EXPORT void CALLBACK DrawBezier (HDC hdc)
{
	PolyBezier (hdc, point, 4) ;			//�I�sGDI32.DLL�����禡ø�s�������u
	MoveToEx (hdc, point[0].x, point[0].y, NULL) ;	//�q���ɺ����u�̥����}�l�e�@�����u
	LineTo   (hdc, point[1].x, point[1].y) ;		//��ƹ�����̫�Q���U�ɪ���m
	MoveToEx (hdc, point[2].x, point[2].y, NULL) ;	//�q���ɺ����u�̥k���}�l�e�@�����u
	LineTo   (hdc, point[3].x, point[3].y) ;		//��ƹ��k��̫�Q���U�ɪ���m
}
