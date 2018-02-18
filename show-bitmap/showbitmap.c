#include <windows.h>
#include <stdio.h>

#define MSG(m) {\
	MessageBoxA(NULL,m,NULL,MB_OK);}

//ウィンドウハンドル
HWND hwnd;
//インスタンスハンドル
HINSTANCE hinst;

//ウィンドウ横幅
#define WIDTH 500
#define HEIGHT 300



LRESULT CALLBACK WinProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	HDC hdc;

	//ビットマップハンドル
	static HBITMAP hb;

	PAINTSTRUCT ps;
	
	//ビットマップ構造体
	static BITMAP bp;

	//縦、横
	static int width,height;

	//メモリデバイスコンテキスト
	static HDC mhdc;

	switch(msg){
		case WM_DESTROY:
			//ビットマップハンドルを削除
			DeleteObject(hb);
			//メモリデバイスコンテキストを破棄
			DeleteDC(mhdc);

			PostQuitMessage(0);
			return 0;

		case WM_CREATE:
			
			//ファイル読み込み
			hb=LoadBitmap(hinst,"FILENAME");


			//画像サイズ取得
			GetObject(hb,sizeof(BITMAP),&bp);
			width=bp.bmWidth;
			height=bp.bmHeight;

			//メモリデバイスコンテキストを作成
			mhdc = CreateCompatibleDC(NULL);

			
			//メモリデバイスコンテキストにビットマップを設定
			SelectObject(mhdc,hb);


		case WM_PAINT:

			hdc = BeginPaint(hwnd,&ps);

			//描画
			BitBlt(hdc,0,0,width,height,mhdc,0,0,SRCCOPY);

			EndPaint(hwnd,&ps);



			return 0;

		
	}
	return DefWindowProc(hwnd,msg,wp,lp);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	MSG msg;
	WNDCLASS wc;

	wc.style=CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc=WinProc;
	wc.cbClsExtra=wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hCursor=wc.hIcon=NULL;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName="test";
	wc.lpszMenuName=NULL;
	
	if(!RegisterClass(&wc)){
		MSG("クラスの登録失敗");
		return -1;
	}

	
	//インスタンスハンドル
	hinst=hInstance;

	hwnd=CreateWindowA("test","テストウィンドウ",WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0,0,400,400,NULL,NULL,hInstance,NULL);


	if(hwnd==NULL){
		MSG("ウィンドウ作成失敗");
		return -1;
	}


	//エラーチェック用変数
	int check;

	while(check=GetMessage(&msg,NULL,0,0)){
		if(check==-1){
			break;
		}
		DispatchMessage(&msg);
	}

	//クラス解放
	UnregisterClass("test",hinst);

	return 0;

}
