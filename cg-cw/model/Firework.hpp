//
//  Firework.hpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.
//
#include <assimp/scene.h>
#ifndef Firework_hpp
#define Firework_hpp

#include <stdio.h>

#endif /* Firework_hpp */

//#define p_num 2462
#include "Util.hpp"
#include "Loader.hpp"
#include "PointLoader.hpp"
#include "DisplayableObject.h"
#include "Animation.h"

class Firework :
public DisplayableObject,
public Animation
{
public:
    ~Firework(){};
    Firework();

    void Display();
    void Update(const double& deltaTime);
    
    
    
private:
    void rise();

    
    void updatePos();
    
    // functions to update velocity
    void randomUpdateV();
    void numUpdateV();
    void unncUpdateV();
    void mapUpdateV();
    void xiaohuiUpdateV();
    void crayonUpdateV();
    
    int fireworkCount;
    int typeCount = 5;
    int keyframe;               // variable to track which keyframe we are on
    int status;
    int p_num;
    

    float total_time;
    float time;
    float rise_time;
    float burst_time;
    float burst_height;
    
    Loader *firebox;
    Loader *dangertxt;
    
    vector<vector<GLfloat>> p2022 = GetPointsPosition("points/year");
    vector<vector<GLfloat>> punnc = GetPointsPosition("points/unnc");
    vector<vector<GLfloat>> pmonster = GetPointsPosition("points/map");
    vector<vector<GLfloat>> pxiaohui = GetPointsPosition("points/xiaohui");
    vector<vector<GLfloat>> pxx = GetPointsPosition("points/xx2");

    float **h_pos;
    float **velocity;
};


