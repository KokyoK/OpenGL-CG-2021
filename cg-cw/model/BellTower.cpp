//
//  BellTower.cpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/8.
//
#define GL_SILENCE_DEPRECATION
#include "BellTower.hpp"
#include "Util.hpp"
#include "Loader.hpp"
#include <cmath>



// initialize variables
BellTower::BellTower() : keyframe(-1), time(0.0), animateRotation(0.0), animateTranslation(0.0){
    this->clock = new Loader("clock");
    this->minute = new Loader("minute");
    this->hour = new Loader("hour");
}

// update belltower
void BellTower::Update(const double& deltaTime)
{
    time += static_cast<float>(deltaTime);
}

// Draw the BellTower
void BellTower::Display()
{
    
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glScalef(5, 5, 5);
    
    DrawRoof();
    DrawTopWindowLayer();
    DrawBellLayer();
    DrawBalconyLayer();
    DrawBottomLayer();
    
    // draw clock
    DrawClock();
    
    glPopAttrib();
    glPopMatrix();
}


// in Bell Layer
void BellTower::DrawClock(){
    
    glPushMatrix();
    
    glTranslated(0, 40, 20);
    glScalef(0.5, 0.5, 0.5);
    clock->Draw();
    
    glPushMatrix();
    glRotated(-time* 36, 0,0,1);
    minute->Draw();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(-time* 3, 0,0,1);
    hour->Draw();
    glPopMatrix();
    
    glPopMatrix();
}




void BellTower::DrawRoof(){
    glPushMatrix();
    
    // 四棱锥
    glPushMatrix();
    glTranslated(0, 100, 0);
    glColor3ub(169, 169, 169);
    DrawCube(42.5, 0.1, 42.5); // bottom surface of pyramid
    glRotated(-90, 1, 0, 0);
    glRotated(45, 0, 0, 1);
    glColor3ub(7, 26, 40); //dark blue
    GLUquadricObj *roof = gluNewQuadric();
    gluCylinder(roof, 30, 0, 20, 4, 1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3ub(169, 169, 169);
    glTranslated(0, 98, 0);
    DrawCube(40.5, 0.5, 40.5); // cube layer 1
    glTranslated(0, -0.5, 0);
    DrawCube(40.5, 0.5, 40.5); // cube layer 2
    
    
    glRotated(45, 0, 1, 0);
    glRotated(90, 1, 0, 0);
    //    glRotated(45, 0, 1, 0);
    GLUquadricObj *downLayer = gluNewQuadric(); // upside down pyramid
    gluCylinder(downLayer, 27.5, 0, 27.5, 4, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 95, 0);
    DrawCube(38, 0.5, 38); // cube layer 3
    glPopMatrix();
    
    glPopMatrix();
}


void BellTower::DrawTopWindowLayer(){ //bottom at 54.5
    glPushMatrix();
    
    // 2 square layer
    glPushMatrix();
    glTranslated(0, 94.5, 0);
    DrawCube(33, 4, 34);
    glTranslated(0, -2, 0);
    DrawCube(36, 4, 36);
    glPopMatrix();
    
    // top window layer body
    glPushMatrix();
    glTranslated(0, 83, 0);
    DrawCube(34, 40, 34); // bottom at 63
    glPopMatrix();
    
    // windows
    glPushMatrix();
    glTranslated(0, 87, 0);
    
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 18);
        glScalef(0.8, 0.8, 1);
        DrawTopWindow();
        glPopMatrix();
    }
    glPopMatrix();
    
    // bottom layer
    glPushMatrix();
    glTranslated(0, 62.5, 0);
    DrawCube(40, 1, 40); // bottom at 61.5
    glPopMatrix();
    
    // 4 sub roofs
    glPushMatrix();
    glTranslated(0, 66, 0);
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glScalef(0.8, 0.3, 0.8);
        glTranslated(0, 0, 23);
        DrawSubRoof();
        glPopMatrix();
    }
    glPopMatrix();
    
    
    glPopMatrix();
}

// in TopWindowLayer
void BellTower::DrawTopWindow(){
    glPushMatrix();
    
    //glass
    glPushMatrix();
    glColor3ub(16, 55, 77);
    glTranslated(0, -4.5, 2);
    DrawCube(8, 8, 1);
    glPopMatrix();
    
    // inner layer
    glPushMatrix();
    for (int i = 0; i < 4; i++){
        glColor3f(0.8, 0.8, 0.8);
        DrawCube(10, 1, 8);
        glTranslated(-4.5, -4.5, 0);
        glRotated(90, 0, 0, 1);
    }
    glPopMatrix();
    
    //outer layer
    glPushMatrix();
    glTranslated(0, 1, 1);
    for (int i = 0; i < 4; i++){
        glColor3f(0.6, 0.6, 0.6);
        DrawCube(12, 1, 10);
        glTranslated(-5.5, -5.5, 0);
        glRotated(90, 0, 0, 1);
        
    }
    glPopMatrix();
    
    glPopMatrix();
}

// in TopWindow Layer
void BellTower::DrawSubRoof(){
    glPushMatrix();
    
    // bottom layer
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslated(0, -10, 4.9);
    DrawCube(20*sqrt(3), 3, 10);
    glPopMatrix();
    
    
    // triangle surface
    glPushMatrix();
    glTranslated(0, 0, 10);
    glScalef(10*sqrt(3), 10*sqrt(3), 10*sqrt(3));
    glTranslated(0, -sqrt(3)/3, 0);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, sqrt(3), 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    
    // triangular prism : side length = 10
    glPushMatrix();
    GLUquadricObj *roof = gluNewQuadric();
    gluCylinder(roof, 20, 20, 10, 3, 1);
    glPopMatrix();
    
    // upper layer 1 (left & right) (from bottom to top)
    glPushMatrix();
    glTranslated(-5*sqrt(3), 5, 6);
    glRotated(60, 0, 0, 1);
    DrawCube(20*sqrt(3), 0.5, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(5*sqrt(3), 5, 6);
    glRotated(-60, 0, 0, 1);
    DrawCube(20*sqrt(3), 0.5, 10);
    glPopMatrix();
    
    // upper layer 2 (left & right)
    glPushMatrix();
    glTranslated(-5*sqrt(3), 5.5, 5.5);
    glRotated(60, 0, 0, 1);
    DrawCube(21*sqrt(3), 1.5, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(5*sqrt(3), 5.5, 5.5);
    glRotated(-60, 0, 0, 1);
    DrawCube(21*sqrt(3), 1.5, 10);
    glPopMatrix();
    
    // upper layer 3 (left & right)
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(-5.4*sqrt(3), 5.9, 6.5);
    glScalef(1,5,1);
    glRotated(20, 0, 0, 1);
    DrawCube(20, 0.4, 10);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslated(5.4*sqrt(3), 5.9, 6.5);
    glScalef(1,5,1);
    glRotated(-20, 0, 0, 1);
    DrawCube(20, 0.4, 10);
    glPopMatrix();
    
    
    
    
    
    glPopMatrix();
}


void BellTower::DrawBellLayer(){
    glPushMatrix();
    glColor3ub(169, 169, 169);
    
    // body height: 40 bottom:20
    glPushMatrix();
    glTranslated(0, 40, 0);
    DrawCube(35, 40, 35);
    glPopMatrix();
    
    glPushMatrix();     // next cube from 0 (for balconay layer)
    DrawCube(35, 40, 35);
    glPopMatrix();
    
    
    // sub roof connection
    glPushMatrix();
    DrawSubRoofConnection();
    glPopMatrix();
    glPushMatrix();
    for (int i=0; i <4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 20);
        glScalef(0.8, 1, 0.3);
        DrawSubRoofConnection();
        glPopMatrix();
    }
    glPopMatrix();
    
    // side windows
    glPushMatrix();
    glTranslated(0, 40, 0);
    for (int i=0; i <4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 18);
        glScalef(0.8, 1, 0.3);
        DrawSideWindow();
        glPopMatrix();
    }
    glPopMatrix();
    
    // clock
    //    glPushMatrix();
    //    glTranslated(0, 40, 0);
    //    for (int i=0; i <4; i++){
    //        glRotated(90, 0, 1, 0);
    //        glPushMatrix();
    //        glTranslated(0, 0, 18);
    //        glScalef(0.8, 1, 0.3);
    //        DrawClock();
    //        glPopMatrix();
    //    }
    //    glPopMatrix();
    //
    
    glPopMatrix();
    
}

// in Bell Layer
void BellTower::DrawSubRoofConnection(){
    // sub roof connection 47.5 - 54.5  0.5+3+2+(0.25+1+0.25) top-down
    
    // top layer - 0.5
    glPushMatrix();
    glTranslated(0, 62.25, 0);
    DrawCube(35 , 0.5, 35);
    glPopMatrix();
    
    // trapezoid layer - 3
    glPushMatrix();
    glTranslated(0, 62, 0);
    glRotated(45,0, 1, 0);
    glRotated(90, 1, 0, 0);
    GLUquadricObj *r = gluNewQuadric();
    gluCylinder(r, (float)35/sqrt(2), (float)32.5/sqrt(2), 3, 4, 1);
    glPopMatrix();
    
    // cube layer - 2
    //    glPushMatrix();
    glTranslated(0, 58, 0);
    DrawCube(32.5 , 2, 32.5);
    //    glPopMatrix();
    
    
    glTranslated(0, -0.125, 0);
    DrawCube(33 , 0.25, 33);
    
    glTranslated(0, -0.5, 0);
    DrawCube(30 , 1, 30);
    
    
    glTranslated(0, -0.125, 0);
    DrawCube(33 , 0.25, 33);
}

// in Bell Layer
void BellTower::DrawSideWindow(){
    glPushMatrix();
    
    //glass
    glPushMatrix();
    glColor3ub(16, 55, 77); //window color
    
    DrawCube(15, 40, 5);
    glPopMatrix();
    
    //outer layer
    glPushMatrix();
    
    glColor3f(0.6, 0.6, 0.6);
    
    glPushMatrix();
    glTranslated(-10,0 , 1.5);
    DrawCube(5, 40, 7);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(10,0,1.5);
    DrawCube(5, 40, 8);
    glPopMatrix();
    
    glPopMatrix();
    
    glPopMatrix();
}


void BellTower::DrawCircle()
{
    glPushMatrix();
    for (int i = 0; i < 360; i++) {
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0,0,0);
        glVertex3f(cos((i+1) * M_PI / 180), 0, sin((i+1) * M_PI / 180));
        glVertex3f(cos(i*M_PI/180), 0, sin(i * M_PI / 180));
        glEnd();
    }
    glPopMatrix();
    
    
}

void BellTower::DrawBalconyLayer(){
    glPushMatrix();
    glTranslated(0, 20, 0);
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 30);
        DrawBalcony();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 17, 0);
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(-13, 0, 18);
        DrawDownsideBar();
        glTranslated(26, 0, 0);
        DrawDownsideBar();
        glPopMatrix();
    }
    glPopMatrix();
    
}

// in Balcony layer
void BellTower::DrawBalcony(){ //width = 30
    glPushMatrix();
    //    glTranslated(0, 20, 30);
    
    // left , center, right vertical pillar
    glPushMatrix();
    
    glTranslated(0, 1.5, 0);
    DrawCube(2, 4.5, 1);
    
    glPushMatrix();
    glTranslated(-14.5, 0, 0);
    DrawCube(2, 4.5, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(14.5, 0, 0);
    DrawCube(2, 4.5, 1);
    glPopMatrix();
    
    glPopMatrix();
    
    // center - right bunch pillars
    glPushMatrix();
    glTranslated(2, 0, 0);
    for (int j = 0; j < 5 ; j++ ){
        glPushMatrix();
        glScaled(0.4, 0.17, 0.4);
        DrawBalconyPillar();
        glPopMatrix();
        glTranslated(2.5 ,0, 0);
    }
    glPopMatrix();
    
    // center - left bunch pillars
    glPushMatrix();
    glTranslated(-2, 0, 0);
    for (int j = 0; j < 5 ; j++ ){
        
        glPushMatrix();
        glScaled(0.4, 0.17, 0.4);
        DrawBalconyPillar();
        glPopMatrix();
        glTranslated(-2.5 ,0, 0);
    }
    glPopMatrix();
    
    // left bunch pillars
    glPushMatrix();
    glTranslated(-15, 0, -2);
    for (int j = 0; j < 4 ; j++ ){
        glPushMatrix();
        glScaled(0.4, 0.17, 0.4);
        DrawBalconyPillar();
        glPopMatrix();
        glTranslated(0 ,0, -2.5);
    }
    glPopMatrix();
    
    // right bunch pillars
    glPushMatrix();
    glTranslated(15, 0, -2);
    for (int j = 0; j < 4 ; j++ ){
        glPushMatrix();
        glScaled(0.4, 0.17, 0.4);
        DrawBalconyPillar();
        glPopMatrix();
        glTranslated(0 ,0, -2.5);
    }
    glPopMatrix();
    
    glTranslated(0, 4, 0);
    
    // top long horizontal fence
    glPushMatrix();
    DrawCube(32, 0.5, 1);
    glPopMatrix();
    
    // top short horizontal fences
    glPushMatrix();
    glTranslated(-15, 0, -8);
    DrawCube(2, 0.5, 15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(15, 0, -8);
    DrawCube(2, 0.5, 15);
    glPopMatrix();
    
    
    // bottom chassis
    glPushMatrix();
    glTranslated(0, -4.4, -6);
    DrawCube(32, 0.7, 16);
    
    glTranslated(0, -1, 0);
    DrawCube(29, 2, 15);
    
    glTranslated(0, -1, 0);
    DrawCube(32, 0.8, 18);
    glPopMatrix();
    
    
    glPopMatrix();
    
}


// in Balcony layer
void BellTower::DrawBalconyPillar(){
    glPushMatrix();
    glPushMatrix();
    glScaled(1, 0.7, 1);
    glTranslated(0, -2, 0);
    glRotated(-90, 1, 0, 0);
    GLUquadricObj *p = gluNewQuadric();
    gluCylinder(p, 0.7, 0.7, 35, 50, 1);
    
    glPopMatrix();
    
    glPushMatrix();
    
    glutSolidSphere(1, 100, 10);
    glTranslated(0, 0.8, 0);
    glutSolidSphere(1, 100, 10);
    
    glTranslated(0, 5, 0);
    glutSolidSphere(1, 100, 10);
    glTranslated(0, 0.8, 0);
    glutSolidSphere(1, 100, 10);
    
    glTranslated(0, 8, 0);
    glutSolidSphere(1, 100, 10);
    glTranslated(0, 0.8, 0);
    glutSolidSphere(1, 100, 10);
    
    glTranslated(0, 5, 0);
    glutSolidSphere(1, 100, 10);
    glTranslated(0, 0.8, 0);
    glutSolidSphere(1, 100, 10);
    
    glPopMatrix();
    
    
    
    glPopMatrix();
}

// in Balcony layer
void BellTower::DrawDownsideBar(){
    glPushMatrix();
    
    glPushMatrix();
    glTranslated(2, 0, 0);
    
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 8);
    glVertex3f(0, -6, 8);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -6, 8);
    glVertex3f(0, -7, 6);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -7, 6);
    glVertex3f(0, -9, 4);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -9, 4);
    glVertex3f(0, -11, 3);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -11, 3);
    glVertex3f(0, -16, 2);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -16, 2);
    glVertex3f(0, -16, 0);
    glEnd();
    glPopMatrix();
    
    // reverse side surface
    glPushMatrix();
    glTranslated(-2, 0, 0);
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -6, 8);
    glVertex3f(0, 0, 8);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -7, 6);
    glVertex3f(0, -6, 8);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -9, 4);
    glVertex3f(0, -7, 6);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -11, 3);
    glVertex3f(0, -9, 4);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -16, 2);
    glVertex3f(0, -11, 3);
    
    glVertex3f(0, 0, 0);
    glVertex3f(0, -16, 0);
    glVertex3f(0, -16, 2);
    
    glEnd();
    glPopMatrix();
    
    // draw quads
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-2, 0, 0);
    glVertex3f(-2, 0, 8);
    glVertex3f(2, 0, 8);
    glVertex3f(2, 0, 0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-2, 0, 8);
    glVertex3f(-2, -6, 8);
    glVertex3f(2, -6, 8);
    glVertex3f(2, 0, 8);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, -2, 1);
    glVertex3f(-2, -6, 8);
    glVertex3f(-2, -7, 6);
    glVertex3f(2, -7, 6);
    glVertex3f(2, -6, 8);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 1);
    glVertex3f(-2, -7, 6);
    glVertex3f(-2, -9, 4);
    glVertex3f(2, -9, 4);
    glVertex3f(2, -7, 6);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 2);
    glVertex3f(-2, -9, 4);
    glVertex3f(-2, -11, 3);
    glVertex3f(2, -11, 3);
    glVertex3f(2, -9, 4);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 5);
    glVertex3f(-2, -11, 3);
    glVertex3f(-2, -16, 2);
    glVertex3f(2, -16, 2);
    glVertex3f(2, -11, 3);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-2, -16, 2);
    glVertex3f(-2, -16, 0);
    glVertex3f(2, -16, 0);
    glVertex3f(2, -16, 2);
    glEnd();
    glPopMatrix();
    
    // draw top cube
    glPushMatrix();
    glTranslated(0, -2, 8);
    DrawCube(3, 3, 2);
    
    glTranslated(0, 0, 1);
    DrawCube(2, 2, 1);
    glPopMatrix();
    
    // draw bottom cube
    glPushMatrix();
    glTranslated(0, -17, 0.75);
    DrawCube(4, 2, 1.5);
    
    glTranslated(0, -2, -0.25);
    DrawCube(4, 2, 1);
    glPopMatrix();
    
    
    glPopMatrix();
    
    
    
    
}





void BellTower::DrawBottomLayer(){
    glPushMatrix();
    
    // draw windows at 0
    glPushMatrix();
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 18);
        glScalef(1, 2, 1);
        DrawBottomWindow();
        glPopMatrix();
    }
    glPopMatrix();
    
    // draw stage connected to windows
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, -18, 0);
    DrawCube(39, 4, 39);
    
    // draw second bottom and side
    glTranslated(0, -6, 0);
    glColor3f(0.4, 0.4, 0.4);
    DrawCube(44, 8, 44);
    
    
    //    glPushMatrix();
    for (int i = 0; i < 4; i++){
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(0, 0, 23);
        DrawBottomSide();
        glPopMatrix();
    }
    glTranslated(0, -5, 0);
    glColor3f(0.4, 0.4, 0.4);
    DrawCube(58, 2, 58);
    
    glPopMatrix();
    glPopMatrix();
    
}

// in bottom layer
void BellTower::DrawBottomWindow(){
    glPushMatrix();
    //glass
    glPushMatrix();
    glColor3ub(16, 55, 77);
    DrawCube(8, 8, 1);
    glPopMatrix();
    
    // inner layer
    glPushMatrix();
    for (int i = 0; i < 4; i++){
        glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glTranslated(0, 5, 0);
        DrawCube(12, 2, 2);
        glPopMatrix();
        glRotated(90, 0, 0, 1);
    }
    glPopMatrix();
    
    //outer layer
    glPushMatrix();
    for (int i = 0; i < 4; i++){
        glPushMatrix();
        glColor3f(0.6, 0.6, 0.6);
        glTranslated(0, 8, 0);
        DrawCube(20, 4, 4);
        glPopMatrix();
        glRotated(90, 0, 0, 1);
    }
    glPopMatrix();
    
    glPopMatrix();
}

// in bottom layer
void BellTower::DrawBottomSide(){
    
    glPushMatrix();
    
    // center
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    DrawCube(48, 8, 2);
    glPopMatrix();
    
    // top
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslated(0, 3, 1);
    DrawCube(50, 2, 2);
    glPopMatrix();
    
    // bottom
    glPushMatrix();
    glTranslated(0, -3, 1);
    DrawCube(50, 2, 2);
    glPopMatrix();
    
    // corner
    glPushMatrix();
    glTranslated(-24, 0, 1);
    DrawCube(2, 8, 2);
    glPopMatrix();
    
    
    
    
    //    for (int i = 0; i < 4; i++){
    //        glPushMatrix();
    //        glColor3f(0.4, 0.4, 0.4);
    //        glTranslated(0, 3, 0);
    //        DrawCube(4, 2, 2);
    //        glPopMatrix();
    //        glRotated(90, 0, 0, 1);
    //    }
    //    glPopMatrix();
    
    glPopMatrix();
}


