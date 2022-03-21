//
//  Clock.hpp
//  cg-cw
//
//  Created by 何宇婷 on 2021/11/29.
//


#define GL_SILENCE_DEPRECATION


#include "DisplayableObject.h"
#include "Animation.h"


//#include "GL/glut.h"
//#include "GL/glew.h"
//#include "OpenGL/OpenGL.h"

#pragma once
#include <stdio.h>
#include <GLUT/glut.h>

#include <vector>
#include <string>
using namespace std;

class Clock:
public DisplayableObject,
public Animation
{
public:

    Clock(string filename);
    //void Init();
    void Draw();
    
    void Display();
    void Update(const double& deltaTime);

private:

    //GLint lastFrameTime;
    //GLint animationLastingTime;

    vector<string>matNameList;
    vector<vector<GLfloat>>matKd;
    vector<vector<GLfloat>>matKs;
    vector<vector<GLfloat>>matKa;
    vector<GLfloat>matNs;
    
    
    vector<GLint>fAreaIdx; // 第几个f要变材质
    vector<GLint>fAreaMatIdx; //要变的材质是第几个
    
    vector<vector<GLfloat>>vSets;
    vector<vector<GLint>>fSets;
    vector<vector<GLfloat>>vnSets;
    vector<vector<GLfloat>>vtSets;
    


};



