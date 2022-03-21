//
//  Util.cpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/16.
//
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include "Util.hpp"
#include <GLUT/glut.h>

void DrawCube(float x, float y, float z)
{
    glPushMatrix();
    glScalef(x, y, z);
    glutSolidCube(1);
    glPopMatrix();
}

vector<vector<GLfloat>> GetPointsPosition(string filename){
    PointLoader *ploader = new PointLoader(filename);
    return ploader->GetPoints();
}

