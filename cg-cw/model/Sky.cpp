//
//  Sky.cpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.

#include <math.h>
#define GL_SILENCE_DEPRECATION
#include "Sky.hpp"


#include "Util.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Sky::Sky():
keyframe(-1){
    this->sky = new Loader("env/sky");
}

void Sky::Update(const double& deltaTime)
{
    time += static_cast<float>(deltaTime);
}


void Sky::Display()
{
    // Always push before making any changes
    glPushMatrix();
    glTranslated(250, -180, 1300);
    glScalef(8, 5, 8);
    // Save current style attributes
    sky->Draw();

    glPopMatrix();

}



