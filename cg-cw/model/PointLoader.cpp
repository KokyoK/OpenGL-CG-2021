//
//  Loader.cpp
//  cg-cw
//
//  Created by YutingHE on 2021/11/29.
//

#include "PointLoader.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "Util.hpp"
using namespace std;

//GLfloat m = 1.0f;

PointLoader::PointLoader(string filename)
{
    filename = rootpath + filename;
    // read material
 
    fstream fobj;
    string line;


    fobj.open(filename+".obj", ios::in);
    //    cout << filename << endl;
    if (!fobj.is_open()){
        cout << "Something Went Wrong When Opening Objfiles" << endl;
    }

    while (!fobj.eof()){

        getline(fobj, line);
        //        cout << line << endl;
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        line = line.append(tailMark);
        //        cout << line << endl;
        for (int i = 0; i < line.length(); i++) { // seperate line by space
            char ch = line[i];
            if (ch != ' ') {
                ans+=ch;
            }
            else {
                parameters.push_back(ans);
                ans = "";
            }
        }



        if (parameters[0] == "v") {                         // store vertex
            vector<GLfloat>Point;
            for (int i = 1; i < 4; i++) {
                GLfloat xyz = atof(parameters[i].c_str());
                Point.push_back(xyz);
            }

            vSets.push_back(Point);
        }
    }

}

vector<vector<GLfloat>> PointLoader::GetPoints(){
    return vSets;
}


void PointLoader::Update(const double& deltaTime)
{}


void PointLoader::Display()
{
    glScalef(0.5, 0.5, 0.5);
    glTranslated(0, -200, 1500);
    glRotated(-90, 0, 1, 0);

}



