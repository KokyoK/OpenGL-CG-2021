#include <stdio.h>
#include "DisplayableObject.h"
#include "Animation.h"
#include "Loader.hpp"
#define mNum 12

class Piano :
public DisplayableObject,
public Animation
{
public:
    ~Piano(){};
    Piano();

    void Display();
    void Update(const double& deltaTime);
    
    
    
private:
    void DrawPiano();
    void DrawMusic();
    
    int keyframe;
    float time;
    
    Loader *piano;
    Loader *music[mNum];

};


