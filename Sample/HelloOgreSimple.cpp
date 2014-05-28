# include <GL/glut.h>
#include <stdio.h>
# include <stdlib.h>
#include "OgreSimpleRoot.h"
#include "GLRenderSystem.h"
#include "SceneManager.h"
#include "Camera.h"

OgreSimple::OgreSimpleRoot *gRoot = NULL;
OgreSimple::Camera * gCamera = NULL;
OgreSimple::Vector3 gPosition(0,1.5,0);
OgreSimple::Vector3 gAtPosition(0,1.5,-3);

OgreSimple::Vector2 gLastMouse;
float gDetalX=0;
float gDetalY=0;
bool gIsMove=false;

void init ( void )
{
    gRoot = new OgreSimple::OgreSimpleRoot();
#ifdef WIN32
    gRoot->setResourcePath("E:/WorkSpace/OgreSimple/Sample/Resources");
#else
    gRoot->setResourcePath("/home/nf/WorkSpace/OgreSimple/Sample/Resources");
#endif
    OgreSimple::GLRenderSystem *rs = new OgreSimple::GLRenderSystem();
    gRoot->setRenderSystem(rs);
    gRoot->initialise();
    OgreSimple::SceneManager* scene = gRoot->createSceneManager();
    scene->LoadSceneFile();
    gCamera = gRoot->createCamera();
    gCamera->SetPosition(OgreSimple::Vector3(0, 1.5, 0));
    gCamera->SetLookAt(OgreSimple::Vector3(0, 1.5, 1));
    //cam->SetUp(OgreSimple::Vector3(0, 1, 0));
}

void display ( void )
{
    //printf("====================\n");
    gRoot->renderScene();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
     gRoot->setSurfaceSize(w, h);
}


void keyboard ( unsigned char key, int x, int y)
{
     switch (key)
     {
     case 'w':
        gCamera->Walk(0.1);
        break;
     case 's':
        gCamera->Walk(-0.1);
		break;
     case 'a':
        gCamera->Strafe(0.1);
	break;
     case 'd':
        gCamera->Strafe(-0.1);
		break;
     case 'e':
        gCamera->Pitch(0.1);
	break;
     case 'q':
        gCamera->Pitch(-0.1);
        break;
     case GLUT_KEY_PAGE_UP:
        gCamera->Fly(0.1);
        break;
     case 27:
        exit ( 0 );
        break;
     }
}

void MouseEventCall(int button,int state,int x,int y)
{
    if ( state==GLUT_DOWN&& button==GLUT_RIGHT_BUTTON )
    {
        gLastMouse.x = x;
        gLastMouse.y = y;
        gIsMove = true;
    }else if (state==GLUT_UP && button==GLUT_RIGHT_BUTTON)
    {
        gIsMove = false;
		gDetalX = 0;
		gDetalY = 0;
    }
}

void MouseMoveCall(int x, int y)
{
    if(gIsMove)
    {
        OgreSimple::Vector2 curMouse(x,y);
        float units = 0.001;
        int offx  = curMouse.x - gLastMouse.x;
        int  offy  = curMouse.y - gLastMouse.y;

        float fPercentOfNew = 1.0f / 2;
        float fPercentOfOld = 1.0f - fPercentOfNew;

        gDetalX = gDetalX * fPercentOfOld + offx * fPercentOfNew;
        gDetalY = gDetalY * fPercentOfOld + offy * fPercentOfNew;
		
        // Æ«º½
        gCamera->Yaw( units * gDetalX );

        // ¸©Ñö
        gCamera->Pitch( units * gDetalY );
        gLastMouse = curMouse;
    }


}


int main(int argc, char** argv)
{
    glutInit (&argc, argv);

     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

     glutInitWindowSize (1280, 720);

     glutInitWindowPosition (100, 100);

     glutCreateWindow ( argv [0] );

     init();

     glutDisplayFunc ( display );
     glutIdleFunc(display);

     glutReshapeFunc ( reshape );

     glutKeyboardFunc ( keyboard );
     glutMotionFunc (MouseMoveCall);
	 glutMouseFunc (MouseEventCall);


     glutMainLoop( );
     return 0;
}
