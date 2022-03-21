//
//  PointLoader.hpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/29.
//


#define GL_SILENCE_DEPRECATION

#pragma once
#include "DisplayableObject.h"
#include "Animation.h"

#include <stdio.h>
#include <GLUT/glut.h>

#include <vector>
#include <string>
using namespace std;

class PointLoader:
public DisplayableObject,
public Animation
{
public:

    PointLoader(string filename);
    vector<vector<GLfloat>> GetPoints();
    void Display();
    void Update(const double& deltaTime);

private:
    vector<vector<GLfloat>>vSets;

};



