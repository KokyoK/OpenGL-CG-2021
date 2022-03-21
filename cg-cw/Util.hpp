//
//  Util.hpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/16.
//
#pragma once
#include <string>
#include <iostream>
#include "model/PointLoader.hpp"
using namespace std;



void DrawCube(float x, float y, float z);
const string rootpath = "/Users/krisiney/Desktop/CG/cg-cw/cg-cw/Objects/";
vector<vector<GLfloat>> GetPointsPosition(string filename);




    
// -----------------------------------------
const int YEAR_NUM = 2462;

//PointLoader *loader2022;
//PointLoader *loaderUNNC = new PointLoader("points/unnc");

//vector<vector<GLfloat>> p2022 = loader2022->GetPoints();
