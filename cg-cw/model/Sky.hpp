
//
//  Sky.hpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.
//

#ifndef Sky_hpp
#define Sky_hpp

#include <stdio.h>

#endif /* Sky_hpp */


#include "DisplayableObject.h"
#include "Animation.h"
#include "Loader.hpp"

class Sky :
public DisplayableObject,
public Animation
{
public:
    ~Sky(){};
    Sky();

    void Display();
    void Update(const double& deltaTime);
    
    
    
private:

    
    void DrawSky();
   
    

    
    int keyframe;               // variable to track which keyframe we are on
    int status;
    float time;

    Loader *sky;
};


