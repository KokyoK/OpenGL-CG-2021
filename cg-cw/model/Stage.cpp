
//
//  Stage.cpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.

#include <math.h>
#define GL_SILENCE_DEPRECATION
#include "Stage.hpp"

#include "Util.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Stage::Stage():
keyframe(-1){
    // initialize roadlights
    for (int i = 0; i < RLNum; i++){
        this->lights[i] = new Loader("env/roadlight");
    }
    // initialize chairs
    for (int i = 0; i < CNum; i++){
        this->chairs[i] = new Loader("env/chair");
    }
    // initialize trees
    for (int i = 0; i < TNum; i++){
        this->trees[i] = new Loader("env/tree"+to_string(i%3+1));
    }
    // initialize xin
    this->xin = new Loader("xxin");
}

void Stage::Update(const double& deltaTime)
{
    time += static_cast<float>(deltaTime);
}


void Stage::Display()
{

    glPushMatrix();
    DrawFloor();
    glTranslated(0, -150, 0);
    DrawRoadlight();
    DrawChair();
    DrawTree();
    DrawXin();
    glPopMatrix();

}


void Stage::DrawXin(){

    glPushMatrix();
    glTranslated(-300, 20,500);
    glTranslatef(100 * sin((time)*120*M_PI/180), 0, 100 * cos((time)*120*M_PI/180));
    glRotated(120*time, 0, 1, 0);
    glScalef(3, 3, 3);
    xin->Draw();
    glPopMatrix();
}




void Stage::DrawFloor(){
    glPushMatrix();
    glScalef(5, 5, 5);
    glColor3f(0.2, 0.6, 0.2);
    glTranslated(0, -30, 100);
    glPopMatrix();
}

void Stage::DrawRoadlight(){
    glPushMatrix();

    glTranslated(0, 0,500);
    for (int i = 0; i < RLNum; i++){
        glPushMatrix();
        if(i%2 == 0){
            glTranslated(-500, 0,500-200*i);
        }
        else{
            glTranslated(500, 0,500-200*i);
        }
        
        glRotated(90, 0, 1, 0);
        lights[i]->Draw();
        glPopMatrix();
    }
    glPopMatrix();
}

void Stage::DrawChair(){
    glPushMatrix();

    glTranslated(0, 0,500);
    for (int i = 0; i < RLNum; i++){
        glPushMatrix();
        if(i%2 == 0){
            glTranslated(-500, 0,300-200*i);
        }else{
            glTranslated(500, 0,300-200*i);
            glRotated(180, 0, 1, 0);
        }
        chairs[i]->Draw();
        glPopMatrix();
    }
    glPopMatrix();
}


void Stage::DrawTree(){
    for (int i = 0; i < TNum/2; i++){
        glPushMatrix();
        glTranslated(  -600+i*200,0,100 );
        trees[i]->Draw();
        glPopMatrix();
        
        glPushMatrix();
        glTranslated( 600-i*200,0,100 );
        trees[i+(TNum/2)]->Draw();
        glPopMatrix();
    }
}

