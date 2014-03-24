#include "windows.h"  
#include "stdio.h"
#include "GL/gl.h"
#include "OgreSimpleRoot.h"
#include "GLRenderSystem.h"
#include "SceneManager.h"
  
HINSTANCE g_hInstance=NULL;
HGLRC hRC=NULL;
HDC hDC=NULL;  
OgreSimple::OgreSimpleRoot *gRoot = NULL;
BOOL Register(char* pszClassName);  
HWND Create(char* pszClassName,char* pszWndName);  
VOID  Display(HWND hWnd);  
VOID MessageLoop(); 
void CreateContext(HWND hWnd);


void ReSizeGLScene(int width, int height)
{
 if (height==0)
 {
 height=1;
 }
 gRoot->setSurfaceSize(width, height);
 
}
/************************************************************************/  
/* 窗口消息处理函数(此函数为回调函数)                       */  
/************************************************************************/  
LRESULT CALLBACK WindowsProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)  
{  
    switch( nMsg )  
    {  
        case WM_SYSCOMMAND:  //收到的消息为关闭窗口的消息,则使用PostQuitMessage函数发送消息,是消息循环结束,程序退出.  
            if( SC_CLOSE == wParam )  
            {  
                PostQuitMessage( 0 );  
            }  
            break;  
		case WM_SIZE:
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); 
			break;
    }  
    return DefWindowProc(hWnd,nMsg,wParam,lParam);  
}  
  
/************************************************************************/  
/* 程序入口函数,由操作系统来调用                                        */  
/************************************************************************/  
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,char* pszCmd,int nShowCmd)  
{  
    gRoot = new OgreSimple::OgreSimpleRoot();
	
    g_hInstance=hInstance;    
    Register("MyClass");  //注册窗口类  
    HWND hWnd=Create("MyClass","OgreSimple"); //创建窗口  
    Display(hWnd);  //更新并显示窗口  
	CreateContext(hWnd);
	
	
	OgreSimple::GLRenderSystem *rs = new OgreSimple::GLRenderSystem();
	gRoot->setRenderSystem(rs);
	OgreSimple::SceneManager* scene = gRoot->createSceneManager();
	
    MessageLoop();  //进入消息循环,直到收到   PostQuitMessage(0)函数发来的消息,GetMessage函数才会返回False,程序会立即返回并且结束;  
    return 0;  
}  
  
/************************************************************************/  
/* 注册窗口类                                                         */  
/************************************************************************/  
BOOL Register(char* pszClassName)  
{  
    WNDCLASSEX wce = { 0 };  
    wce.cbSize        = sizeof( wce );  
    wce.style         = CS_HREDRAW|CS_VREDRAW;  
    wce.lpfnWndProc   = WindowsProc;  
    wce.hIcon         = NULL;  
    wce.hCursor       = NULL;  
    wce.hIconSm       = NULL;  
    wce.hbrBackground = (HBRUSH)(COLOR_WINDOW);  
    wce.hInstance     = g_hInstance;  
    wce.cbClsExtra    = 100;  
    wce.cbWndExtra    = 100;  
    wce.lpszMenuName  = NULL;  
    wce.lpszClassName = pszClassName;  
    ATOM nAtom = RegisterClassEx( &wce );  
    if( 0 == nAtom ){return FALSE;}  
    return TRUE;  
}  
/************************************************************************/  
/* 创建窗口                                                             */  
/************************************************************************/  
HWND Create(char* pszClassName,char* pszWndName)  
{  
    HWND hWnd = CreateWindowEx( WS_EX_CLIENTEDGE,   
        pszClassName, pszWndName,  
        WS_OVERLAPPEDWINDOW,   
        CW_USEDEFAULT, CW_USEDEFAULT,  
        CW_USEDEFAULT, CW_USEDEFAULT,  
        NULL, NULL, g_hInstance, NULL );  
    return hWnd;  
}  
/************************************************************************/  
/* 更新并显示窗口                                                        */  
/************************************************************************/  
VOID  Display(HWND hWnd)  
{  
    UpdateWindow(hWnd);  
    ShowWindow(hWnd,SW_SHOW);  
}  
/************************************************************************/  
/* 消息循环(循环处理消息)                                              */  
/************************************************************************/  
VOID MessageLoop()  
{  
    MSG msg={0};  
    while(GetMessage(&msg,NULL,0,0))  
    {  
		gRoot->renderScene();
		SwapBuffers(hDC);
        DispatchMessage(&msg);  
    }  
}  

void CreateContext(HWND hWnd)
{
	int PixelFormat;  // 保存查找匹配的结果
	static PIXELFORMATDESCRIPTOR pfd={ sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0};
	if (!(hDC=GetDC(hWnd)))                                                      //取得设备描述表了么?
	{
	  printf("error get DC");
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))                             // Windows 找到相应的象素格式了吗?
	{
		printf("error get PixelFormat");													 
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))                                   // 能够设置象素格式么?
	{
		printf("error get SetPixelFormat");														   
	}
	if (!(hRC=wglCreateContext(hDC)))                                           // 能否取得着色描述表?
	{
	  printf("error get wglCreateContext");	
	}
	if(!wglMakeCurrent(hDC,hRC))                                               // 尝试激活着色描述表
	{
	  printf("error get wglMakeCurrent");
	}
	
}
