# include <GL/glut.h>
#include <stdio.h>
# include <stdlib.h>
#include "OgreSimpleRoot.h"
#include "GLRenderSystem.h"
#include "SceneManager.h"
#include "Camera.h"

OgreSimple::OgreSimpleRoot *gRoot = NULL;
OgreSimple::Camera * gCamera = NULL;

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
    gCamera->SetPosition(OgreSimple::Vector3(0, 1.6, 3));
    gCamera->SetLookAt(OgreSimple::Vector3(0, 0, 0));
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
        gCamera->Walk(1);
        break;
     case 's':
        gCamera->Walk(-1);
	break;
     case 'a':
        gCamera->Yaw(0.1);
	break;
     case 'd':
        gCamera->Yaw(-0.1);
	break;
     case 'e':
        gCamera->Fly(1);
	break;
     case 'q':
        gCamera->Fly(-1);
        break;
     case 27:
        exit ( 0 );
        break;
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

     glutMainLoop( );
     return 0;
}
