#include "MyScene.h"


#include "Loader.hpp"

#include "model/BellTower.hpp"
#include "model/Firework.hpp"
#include "model/Stage.hpp"
#include "model/Piano.hpp"
#include "model/Sky.hpp"


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	
}

void MyScene::Initialise()
{



    
    glClearColor(0,0,0, 1);
   
    glScalef(0.5, 0.5, 0.5);
//
    BellTower *bt = new BellTower();
	bt->size(2.0f);
	AddObjectToScene(bt);

    Stage *stage = new Stage();
    stage->size(2.0f);
    AddObjectToScene(stage);
//
    Firework *f = new Firework();
    f->size(1.0f);
    AddObjectToScene(f);

    Piano *piano = new Piano();
    piano->size(1.0f);
    AddObjectToScene(piano);

    Sky *sky = new Sky();
    sky->size(33.0f);
    AddObjectToScene(sky);
    



}


void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}
