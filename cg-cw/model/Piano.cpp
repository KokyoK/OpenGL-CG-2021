//
//  Piano.cpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/29.
//
#define GL_SILENCE_DEPRECATION
#include "Piano.hpp"
#include <math.h>
#include "Util.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;




// MAKE SURE WE INITIALISE OUR VARIABLES
//float velocity[] ={0,0,0};
Piano::Piano():
keyframe(-1),
time(0.0){
    this->piano = new Loader("piano/piano");
    for (int i = 0; i < mNum; i++){
        this->music[i] = new Loader("piano/music"+ to_string(i%6+1));
    }
}



void Piano::Update(const double& deltaTime)
{
    time += static_cast<float>(deltaTime);
    
}


void Piano::Display()
{
    // Always push before making any changes
    glPushMatrix();
    glTranslated(200, 0, 0);
    DrawPiano();
    glPopMatrix();
}

void Piano::DrawPiano(){
    glTranslated(0, -150, 500);
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    piano->Draw();
    glPopMatrix();
    glTranslated(10, 270,-70);

    DrawMusic();
}


void Piano::DrawMusic(){
    for (int i = 0; i < mNum; i++){
        glPushMatrix();
        glRotated(30*i, 0, 1, 0);
        glTranslated(0, 0, 150);
        
        // dynamic animation
        glTranslated(0, 30*sin(time+i),0);
        glTranslatef(-60 * sin((time)*36*M_PI/180), 0, -60 * cos((time)*36*M_PI/180));
        
        music[i]->Draw();
        glPopMatrix();
    }
}

