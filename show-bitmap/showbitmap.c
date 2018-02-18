#include <windows.h>
#include <stdio.h>

#define MSG(m) {\
	MessageBoxA(NULL,m,NULL,MB_OK);}

//�E�B���h�E�n���h��
HWND hwnd;
//�C���X�^���X�n���h��
HINSTANCE hinst;

//�E�B���h�E����
#define WIDTH 500
#define HEIGHT 300



LRESULT CALLBACK WinProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
	HDC hdc;

	//�r�b�g�}�b�v�n���h��
	static HBITMAP hb;

	PAINTSTRUCT ps;
	
	//�r�b�g�}�b�v�\����
	static BITMAP bp;

	//�c�A��
	static int width,height;

	//�������f�o�C�X�R���e�L�X�g
	static HDC mhdc;

	switch(msg){
		case WM_DESTROY:
			//�r�b�g�}�b�v�n���h�����폜
			DeleteObject(hb);
			//�������f�o�C�X�R���e�L�X�g��j��
			DeleteDC(mhdc);

			PostQuitMessage(0);
			return 0;

		case WM_CREATE:
			
			//�t�@�C���ǂݍ���
			hb=LoadBitmap(hinst,"FILENAME");


			//�摜�T�C�Y�擾
			GetObject(hb,sizeof(BITMAP),&bp);
			width=bp.bmWidth;
			height=bp.bmHeight;

			//�������f�o�C�X�R���e�L�X�g���쐬
			mhdc = CreateCompatibleDC(NULL);

			
			//�������f�o�C�X�R���e�L�X�g�Ƀr�b�g�}�b�v��ݒ�
			SelectObject(mhdc,hb);


		case WM_PAINT:

			hdc = BeginPaint(hwnd,&ps);

			//�`��
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
		MSG("�N���X�̓o�^���s");
		return -1;
	}

	
	//�C���X�^���X�n���h��
	hinst=hInstance;

	hwnd=CreateWindowA("test","�e�X�g�E�B���h�E",WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0,0,400,400,NULL,NULL,hInstance,NULL);


	if(hwnd==NULL){
		MSG("�E�B���h�E�쐬���s");
		return -1;
	}


	//�G���[�`�F�b�N�p�ϐ�
	int check;

	while(check=GetMessage(&msg,NULL,0,0)){
		if(check==-1){
			break;
		}
		DispatchMessage(&msg);
	}

	//�N���X���
	UnregisterClass("test",hinst);

	return 0;

}
