//
//  Firework.cpp
//  cg-cw
//
//  Created by Yuting HE on 2021/11/15.

#include <math.h>

#define GL_SILENCE_DEPRECATION
#include "Firework.hpp"
#define GRAVITY 9.8



Firework::Firework():
keyframe(-1),
total_time(0.0),
time(0.0),
rise_time(0.0),
burst_time(0.0),
fireworkCount(0),
burst_height(0.0),
status(0),
velocity(),
h_pos(){
    p_num = 15000;
    // initialize firebox
    this->firebox = new Loader("env/firebox");
    this->dangertxt = new Loader("env/dangertxt");

    // initialize the y axis velocity
    this->velocity = new float *[p_num];
    this->h_pos = new float *[p_num];
    for (int p = 0; p < p_num; p++){
        this->velocity[p] = new float [3];
        this->h_pos[p] = new float [3];
        this->velocity[p][1] = 120;
    }
}

void Firework::Update(const double& deltaTime)
{
    total_time += static_cast<float>(deltaTime);    // never goes to 0
    time += static_cast<float>(deltaTime);
    rise_time += static_cast<float>(deltaTime); // 先加着，下面会归零
    burst_time += static_cast<float>(deltaTime);
    
    if (time >=3  && status == 0){
        if (keyframe != 1  ) {
            rise_time = 0;
            keyframe = 1;
            status = 1;     // 静止 to 上升
        }
    }
    else if (time >= 7  && status == 1){    // before burst point
        if (keyframe != 2) //保证只进一次 更新random速度
        {
            burst_time = 0;
            
            if (fireworkCount % typeCount == 0){
                mapUpdateV();
            }else if(fireworkCount % typeCount == 1){
                randomUpdateV();
            }else if(fireworkCount % typeCount == 2){
                unncUpdateV();
            }else if(fireworkCount % typeCount == 3){
                crayonUpdateV();
            }else if(fireworkCount % typeCount == 4){
                numUpdateV();
            }
            
            status = 2;
            keyframe = 2;
        }
    }else if (time >= 15 && status == 2){          // particle prepared to disapear
        if (keyframe != 3)
        {
            status = 3;
            keyframe = 3;
        }
    }else if (time >= 15 && status == 3){          // all turn to 0, back to initial state
        if (keyframe != 0)  // ensure only enter once, update the random speed
        {
            status = 0;
            keyframe = 0;
            time = 0;
            rise_time = 0;
            burst_time = 0;
            fireworkCount += 1;
            for (int p = 0; p < p_num; p++){
                velocity[p][0] = 0;
                velocity[p][1] = 120;
                velocity[p][2] = 0;
                h_pos[p][0] =  h_pos[p][1] = h_pos[p][2] = 0;
                
            }
            
        }
    }
}

// show firework and bind it with lights
void Firework::Display()
{
    
    // Always push before making any changes
    glPushMatrix();
    
    glTranslated(0, -155, 400);
    glPushMatrix();
    glRotated(total_time*20, 0, 1, 0);
    dangertxt->Draw();
    glPopMatrix();
    // draw firebox
    firebox->Draw();
    
    glTranslated(0, 100, 0);
    // draw firework
    if (status == 0){   // wait
        
    }else if(status == 1){      // rise
        rise();
    }else if(status == 2){      //show firework
        updatePos();
    }else if(status == 3){
        //   returnBack();
    }
    
    if (status != 3){
        
        for (int p = 0; p < p_num; p++){
            glPushMatrix();
            glTranslated(h_pos[p][0], h_pos[p][1], h_pos[p][2]);
            float alpha = -(float)255/64 * burst_time * burst_time + 255;
            if (fireworkCount % typeCount == 0){
                glColor4ub(255, rand()%180, rand()%150,alpha);     // map
            }else if(fireworkCount % typeCount == 1){
                glColor4ub(255, rand()%180, rand()%50, alpha);     // normal
            }else if(fireworkCount % typeCount == 2){
                glColor4ub(rand()%50, rand()%180, 255,alpha);     // unnc
            }else if(fireworkCount % typeCount == 3){
                glColor4ub(rand()%50, rand()%180, 255,alpha);     // crayon
            }else if(fireworkCount % typeCount == 4){
                glColor4ub(255, rand()%180, rand()%50, alpha);      //  2022
            }
            
            DrawCube(4, 4, 4);
            glPopMatrix();
        }
    }
    
    
    // update lightning effect
    glEnable(GL_LIGHTING);
    if (status == 0){   // wait
        GLfloat ambience[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat diffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat specular[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat position[] = {1.0f, 1.0f*time + 1.0f, 1.0f, 0.0f};
        
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT2, GL_POSITION, position);
        glEnable(GL_LIGHT2);
    }else if(status == 1){      // rise
        float s = time * 0.025 + 0.125;             // y = 0.1x -1
        
        GLfloat ambience[] = {s, s, s, 1.0f};
        GLfloat diffuse[] = {s, s, s, 1.0f};
        GLfloat specular[] = {s, s, s, 1.0f};
        GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f};
        
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT2, GL_POSITION, position);
        glEnable(GL_LIGHT2);
        
    }else if(status == 2){      //show firework
        float s = -(float)0.00625 * pow((time -7.5 ),2)+0.6;
        GLfloat ambience[] = {s, s, s, 1.0f};
        GLfloat diffuse[] = {s, s, s, 1.0f};
        GLfloat specular[] = {s, s, s, 1.0f};
        GLfloat position[] = {1.0f, 1.0f, 1.0f, 0.0f};
        
        
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT2, GL_POSITION, position);
        glEnable(GL_LIGHT2);
        
    }else if(status == 3){
        //            returnBack();
    }
    
    glPopMatrix();
    
}

void Firework::rise(){
    for (int p = 0; p < p_num; p++){
        h_pos[p][1] = velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time;
    }
}



void Firework::randomUpdateV(){
    
    for (int p = 0; p < p_num; p++){
        float r1 = rand()%360 * M_PI / 180;
        float r2 = rand()%150;  // control explosion coverage
        burst_height = h_pos[p][1] = (velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time);
        velocity[p][1] = rand()%300 - 50;
        velocity[p][0] = r2 * sin(r1) ;
        velocity[p][2] = r2 * cos(r1) ;
    }
}

void Firework::numUpdateV(){
    p_num = (int)p2022.size();
    //    cout <<  << endl;
    float trans_period = 8;
    burst_time = 0;
    for (int p = 0; p < p_num; p++){
        burst_height = h_pos[p][1] = (velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time);
        velocity[p][0] = (float)(p2022[p][0] - h_pos[p][0]) / trans_period;
        velocity[p][1] = (float)(p2022[p][1] - h_pos[p][1]) / trans_period;
        velocity[p][2] = (float)(p2022[p][2] - h_pos[p][2]) / trans_period;
    }
}

void Firework::unncUpdateV(){
    p_num = (int)punnc.size();
    float trans_period = 8;
    burst_time = 0;
    for (int p = 0; p < p_num; p++){
        burst_height = h_pos[p][1] = (velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time);
        velocity[p][0] = (float)(punnc[p][0] - h_pos[p][0]) / trans_period;
        velocity[p][1] = (float)(punnc[p][1] - h_pos[p][1]) / trans_period;
        velocity[p][2] = (float)(punnc[p][2] - h_pos[p][2]) / trans_period;
    }
}

void Firework::mapUpdateV(){
    p_num = (int)pmonster.size();
    float trans_period = 8;
    burst_time = 0;
    for (int p = 0; p < p_num; p++){
        burst_height = h_pos[p][1] = (velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time);
        velocity[p][0] = (float)(pmonster[p][0] - h_pos[p][0]) / trans_period;
        velocity[p][1] = (float)(pmonster[p][1] - h_pos[p][1]) / trans_period;
        velocity[p][2] = (float)(pmonster[p][2] - h_pos[p][2]) / trans_period;
    }
}



void Firework::crayonUpdateV(){
    p_num = (int)pxx.size();
    float trans_period = 8;
    burst_time = 0;
    for (int p = 0; p < p_num; p++){
        burst_height = h_pos[p][1] = (velocity[p][1] * rise_time - 0.5 * GRAVITY * rise_time * rise_time);
        velocity[p][0] = (float)(pxx[p][0] - h_pos[p][0]) / trans_period;
        velocity[p][1] = (float)(pxx[p][1] - h_pos[p][1]) / trans_period;
        velocity[p][2] = (float)(pxx[p][2] - h_pos[p][2]) / trans_period;
    }
}


void Firework::updatePos(){
    glPushMatrix();
    
    for (int p = 0; p < p_num; p++){
        h_pos[p][1] = velocity[p][1] * burst_time -  0.5 * GRAVITY * burst_time * burst_time;
        h_pos[p][1] += burst_height;
        
        h_pos[p][0] = velocity[p][0] * burst_time;
        h_pos[p][2] = velocity[p][2] * burst_time;
    }
    glPopMatrix();
}






