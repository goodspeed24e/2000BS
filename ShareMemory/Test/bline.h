#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

/*宣告一個名為shared的區塊，裏面含有point這個變數*/
#pragma	data_seg ("shared")			
POINT point[4] = {0,0,0,0,0,0,0,0};//變數需給初值
#pragma	data_seg ()

/*告訴Linker在這個DLL檔中有一個名為shared的區塊，
  它具有讀(R)、寫(W)、與共用(S)的屬性*/
#pragma comment(linker,"/SECTION:shared,RWS")

EXPORT void CALLBACK SetPoint (POINT apt[]) ;
EXPORT void CALLBACK DrawBezier (HDC hdc) ;

