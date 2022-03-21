//
//  BellTower.hpp
//  cg-cw
//
//  Created by 何宇婷 on 2021/11/8.
//

#ifndef BellTower_hpp
#define BellTower_hpp

#include <stdio.h>

#endif /* BellTower_hpp */
#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Loader.hpp"

class BellTower :
    public DisplayableObject,
    public Animation
{
public:
    BellTower();
    ~BellTower(){};

    void Display();
    void Update(const double& deltaTime);

private:

//    void DrawCube(float x, float y, float z);            // function to draw a unit cube over the origin
    void DrawRoof();
    void DrawTopWindowLayer();
    void DrawTopWindow();
    void DrawSubRoof();
    
    void DrawBellLayer();
    void DrawSubRoofConnection();
    void DrawSideWindow();
    void DrawClock();
    void DrawCircle();
    
    void DrawBalconyLayer();
    void DrawBalcony();
    void DrawBalconyPillar();
    void DrawDownsideBar();
    
    void DrawBottomLayer();
    void DrawBottomWindow();
    void DrawBottomSide();

    void DrawFloor();

    int keyframe;               // variable to track which keyframe we are on
    float time;                 // variable to store the current time the animation has run for
    float animateRotation;      // variable to track the current amount of rotation steps
    float animateTranslation;   // variable to track the current amount of translation steps
    
    Loader *clock;
    Loader *minute;
    Loader *hour;

};

