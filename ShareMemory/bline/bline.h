#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

/*�ŧi�@�ӦW��shared���϶��A�ح��t��point�o���ܼ�*/
#pragma	data_seg ("shared")			
POINT point[4] = {0,0,0,0,0,0,0,0};//�ܼƻݵ����
#pragma	data_seg ()

/*�i�DLinker�b�o��DLL�ɤ����@�ӦW��shared���϶��A
  ���㦳Ū(R)�B�g(W)�B�P�@��(S)���ݩ�*/
#pragma comment(linker,"/SECTION:shared,RWS")

EXPORT void CALLBACK SetPoint (POINT apt[]) ;
EXPORT void CALLBACK DrawBezier (HDC hdc) ;

