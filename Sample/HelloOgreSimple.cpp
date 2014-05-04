# include <GL/glut.h>
# include <stdlib.h>
#include "OgreSimpleRoot.h"
#include "GLRenderSystem.h"
#include "SceneManager.h"
#include "Camera.h"

OgreSimple::OgreSimpleRoot *gRoot = NULL;

/* 初始化材料属性、光源属性、光照模型，打开深度缓冲区 */
void init ( void )
{
    gRoot = new OgreSimple::OgreSimpleRoot();
    OgreSimple::GLRenderSystem *rs = new OgreSimple::GLRenderSystem();
    gRoot->setRenderSystem(rs);
    gRoot->initialise();
    OgreSimple::SceneManager* scene = gRoot->createSceneManager();
    scene->LoadSceneFile();
    OgreSimple::Camera * cam = gRoot->createCamera();
    cam->SetPosition(OgreSimple::Vector3(0, 0, 3));
    cam->SetLookAt(OgreSimple::Vector3(0, 0, 0));
    cam->SetUp(OgreSimple::Vector3(0, 1, 0));
}

/*调用GLUT函数，绘制一个球*/
void display ( void )
{
    gRoot->renderScene();
}

/* 定义GLUT的reshape函数，w、h分别是当前窗口的宽和高*/
void reshape (int w, int h)
{
     gRoot->setSurfaceSize(w, h);
}


/* 定义对键盘的响应函数 */
void keyboard ( unsigned char key, int x, int y)
{
     /*按Esc键退出*/
     switch (key)
     {
         case 27:
         exit ( 0 );
         break;
     }
}


int main(int argc, char** argv)
{
     /* GLUT环境初始化*/
    glutInit (&argc, argv);
     /* 显示模式初始化 */
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     /* 定义窗口大小 */
     glutInitWindowSize (1280, 720);
     /* 定义窗口位置 */
     glutInitWindowPosition (100, 100);
    /* 显示窗口，窗口标题为执行函数名 */
     glutCreateWindow ( argv [ 0 ] );
     /* 调用OpenGL初始化函数 */
     init ( );
     /* 注册OpenGL绘图函数 */
     glutDisplayFunc ( display );
     /* 注册窗口大小改变时的响应函数 */
     glutReshapeFunc ( reshape );
     /* 注册键盘响应函数 */
    glutKeyboardFunc ( keyboard );
     /* 进入GLUT消息循环，开始执行程序 */
     glutMainLoop( );
     return 0;
}
