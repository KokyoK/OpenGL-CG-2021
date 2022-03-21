
//
//  Stage.hpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>

#endif /* Stage_hpp */

#define RLNum 4         // number of roadlights
#define CNum 4         // number of chairs
#define TNum 6         // number of trees

#include "DisplayableObject.h"
#include "Animation.h"
#include "Loader.hpp"

class Stage :
public DisplayableObject,
public Animation
{
public:
    ~Stage(){};
    Stage();

    void Display();
    void Update(const double& deltaTime);
    
    
    
private:

    
    void DrawFloor();
    void DrawRoadlight();
    void DrawChair();
    void DrawTree();
    void DrawXin();
    

    
    int keyframe;               // variable to track which keyframe we are on
    int status;
    float time;
    

    Loader *lights[RLNum];
    Loader *chairs[CNum];
    Loader *trees[TNum];
    Loader *xin;
};


