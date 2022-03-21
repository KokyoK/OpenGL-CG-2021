#include "Loader.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "Util.hpp"
using namespace std;

string objName;
Loader::Loader(string filename)
{
    objName = filename;
    filename = rootpath + filename;
    // read material
    fstream fmat;
    string line;
    
    fmat.open(filename+".mtl", ios::in);
    if (!fmat.is_open()){
        cout << "Something Went Wrong When Opening Matfiles" << endl;
    }
    while (!fmat.eof()){
        getline(fmat, line);
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        line = line.append(tailMark);
        for (int i = 0; i < line.length(); i++) {
            
            char ch = line[i];
            if (ch != ' ') {
                
                ans+=ch;
            }
            else {
                parameters.push_back(ans);
                ans = "";
            }
        }
        
        
        if (parameters[0] == "newmtl") {    // save new material
            matNameList.push_back(parameters[1]);
            matTexList.push_back("none");
        }
        else if (parameters[0] == "Kd") {    // save new material
            vector<GLfloat>kd;
            for(int i = 1; i < parameters.size(); i++){
                kd.push_back(atof(parameters[i].c_str()));
            }
            matKd.push_back(kd);
        }
        else if (parameters[0] == "Ks") {
            vector<GLfloat>ks;
            for(int i = 1; i < parameters.size(); i++){
                ks.push_back(atof(parameters[i].c_str()));
            }
            matKs.push_back(ks);
        }
        else if (parameters[0] == "Ka") {
            vector<GLfloat>ka;
            for(int i = 1; i < parameters.size(); i++){
                ka.push_back(atof(parameters[i].c_str()));
            }
            matKa.push_back(ka);
        }
        else if (parameters[0] == "Ns") {
            matNs.push_back(atof(parameters[1].c_str()));
        }
        else if (parameters[0] == "map_Kd") {
            // modify last item (ensure length)
            matTexList[matTexList.size()-1] = parameters[1].substr(0, (parameters[1].size() - 1));
        }
        
    }
    
    fstream fobj;
    GLint fidx = 0;
    fobj.open(filename+".obj", ios::in);
    string haveTexture = "false";
    if (!fobj.is_open()){
        cout << "Something Went Wrong When Opening Objfiles" << endl;
    }
    
    while (!fobj.eof()){
        
        getline(fobj, line);
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        line = line.append(tailMark);
        // seperate line by space
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];
            if (ch != ' ') {
                ans+=ch;
            }
            else {
                parameters.push_back(ans);
                ans = "";
            }
        }
        
        if (parameters[0] == "usemtl"){
            // go to name list find material idx, push add to list
            GLint matIdx = 0;
            for (int j  = 0; j< matNameList.size(); j++){
                if (matNameList[j] == parameters[1]){
                    matIdx = j;
                    fAreaMatIdx.push_back(matIdx);
                    // check whether current material have texture
                    if (matTexList[j] != "none"){
                        haveTexture = "true";
                    }else{
                        haveTexture = "false";
                    }
                    break;
                }
            }
            fAreaIdx.push_back(fidx);
        }
        
        else if (parameters[0] == "v") {
            vector<GLfloat>Point;
            for (int i = 1; i < 4; i++) {
                GLfloat xyz = atof(parameters[i].c_str());
                Point.push_back(xyz);
            }
            
            vSets.push_back(Point);
        }
        else if (parameters[0] == "f") {
            vector<GLint>vIndexSets;
            vector<GLint>vTexIndexSets;
            for (int i = 1; i < parameters.size(); i++){
                string x = parameters[i];
                string ans = "";
                int readcount = 0;
                for (int j = 0; j < x.length(); j++) {
                    char ch = x[j];
                    if (ch != '/') {
                        ans += ch;
                    }else  {     // ch == '/'
                        GLint index = atof(ans.c_str());
                        if (index  == 0){
                            index = 1;
                        }
                        if (readcount == 0){        // read 1st paramenter: vertex id
                            vIndexSets.push_back(index - 1);
                        }else if(readcount == 1){   // read 2nd paramenter: face texture id
                            vTexIndexSets.push_back(index - 1);
                        }else if(readcount == 2){   // read 3rd paramenter: face
                            vTexIndexSets.push_back(index - 1);
                        }
                        ans = "";
                        readcount += 1;
                        
                    }
                }
            }
            fidx = fidx+1;
            fSets.push_back(vIndexSets);
            ftSets.push_back(vTexIndexSets);
            
        }
        else if (parameters[0] == "vn") {
            vector<GLfloat>vnValueSets;
            for (int i = 1; i < 4; i++) {
                GLfloat vnxyz = atof(parameters[i].c_str());
                vnValueSets.push_back(vnxyz);
            }
            vnSets.push_back(vnValueSets);
        }
        
        else if (parameters[0] == "vt") {
            vector<GLfloat>vtValueSets;
            for (int i = 1; i < 3; i++) {
                GLfloat vtxy = atof(parameters[i].c_str());
                vtValueSets.push_back(vtxy);
            }
            vtSets.push_back(vtValueSets);
        }
    }
    fobj.close();
}




void Loader::Draw(){
    int MatChangeCount = 0;
    GLint texture = -2;     // -2: no texture   -1: get texture error
    for (int i = 0; i < fSets.size(); i++) { // for each face
        // switch material
        if (fAreaIdx.size() > MatChangeCount && fAreaIdx[MatChangeCount] == i ){
            

            
            // color
            glColor3f(matKd[fAreaMatIdx[MatChangeCount]][0], matKd[fAreaMatIdx[MatChangeCount]][1], matKd[fAreaMatIdx[MatChangeCount]][2]);
            
            // diffuse
            GLfloat mat_diffuse[] = { matKd[fAreaMatIdx[MatChangeCount]][0], matKd[fAreaMatIdx[MatChangeCount]][1], matKd[fAreaMatIdx[MatChangeCount]][2], 1.0 };
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            
            // ambient
            GLfloat mat_ambient[] = { matKa[fAreaMatIdx[MatChangeCount]][0], matKa[fAreaMatIdx[MatChangeCount]][1], matKa[fAreaMatIdx[MatChangeCount]][2], 1.0 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            
            // specular
            GLfloat mat_specular[] = { matKs[fAreaMatIdx[MatChangeCount]][0], matKs[fAreaMatIdx[MatChangeCount]][1], matKs[fAreaMatIdx[MatChangeCount]][2], 1.0 };
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            
            GLfloat mat_shininess[] = {matNs[fAreaMatIdx[MatChangeCount]]};
            glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
            
            // get texture
            if (matTexList[fAreaMatIdx[MatChangeCount]] != "none" ){
                string texPath = rootpath + "texture/" + matTexList[fAreaMatIdx[MatChangeCount]];
                texture = Scene::GetTexture(texPath);
            }
            
            MatChangeCount  = MatChangeCount +1;
        }
        
        if (texture != -2 && texture != -1){
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
        
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
      
        
        glBegin(GL_POLYGON);// start drawing
        int pointNum = (int)fSets[i].size();
        GLfloat VN[3];
        // first 3 vertex to calculate normal
        GLfloat SV1[pointNum];
        GLfloat SV2[pointNum];
        GLfloat SV3[pointNum];
        GLfloat points[pointNum][3];
        GLfloat pointsTex[pointNum][2];
        
        
        for(int j = 0 ; j < pointNum; j++){   // for each point
            for (int k = 0; k<3; k++){          // store points
                points[j][k] =  (vSets[(fSets[i])[j]])[k];      // face i, vertex j
            }
            if (texture !=  -1 && texture != -2){
                for (int k = 0; k<2; k++){          // store points texture
                    pointsTex[j][k] =  (vtSets[(ftSets[i])[j]])[k];
                }
            }
        }
        
        
        // calculate normal
        // get vertex index
        GLint firstVertexIndex = (fSets[i])[0];
        GLint secondVertexIndex = (fSets[i])[1];
        GLint thirdVertexIndex = (fSets[i])[2];
        
        SV1[0] = (vSets[firstVertexIndex])[0];
        SV1[1] = (vSets[firstVertexIndex])[1];
        SV1[2] = (vSets[firstVertexIndex])[2];
        
        SV2[0] = (vSets[secondVertexIndex])[0];
        SV2[1] = (vSets[secondVertexIndex])[1];
        SV2[2] = (vSets[secondVertexIndex])[2];
        
        SV3[0] = (vSets[thirdVertexIndex])[0];
        SV3[1] = (vSets[thirdVertexIndex])[1];
        SV3[2] = (vSets[thirdVertexIndex])[2];
        
        GLfloat vec1[3], vec2[3], vec3[3];
        
        //(x2-x1,y2-y1,z2-z1)
        vec1[0] = SV1[0] - SV2[0];
        vec1[1] = SV1[1] - SV2[1];
        vec1[2] = SV1[2] - SV2[2];
        
        //(x3-x2,y3-y2,z3-z2)
        vec2[0] = SV1[0] - SV3[0];
        vec2[1] = SV1[1] - SV3[1];
        vec2[2] = SV1[2] - SV3[2];
        
        //(x3-x1,y3-y1,z3-z1)
        vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
        vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];
        
        GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));
        
        VN[0] = vec3[0] / D;
        VN[1] = vec3[1] / D;
        VN[2] = vec3[2] / D;
        
        
        // draw normal
        glNormal3f(VN[0], VN[1], VN[2]);
        
        // draw current face
        for(int j = 0 ; j < pointNum; j++){   // for each point
            if (texture != -2 && texture != -1){
                glTexCoord2f(pointsTex[j][0], pointsTex[j][1]);
            }
//
//            glDisable(GL_COLOR_MATERIAL);
       
         
            glVertex3f(points[j][0], points[j][1], points[j][2]);

        }
        glEnd();
        
        // unbind
        glBindTexture(GL_TEXTURE_2D, NULL);
        glDisable(GL_TEXTURE_2D);

    }
    
}


void Loader::Update(const double& deltaTime)
{
}


void Loader::Display()
{
    glScalef(0.5, 0.5, 0.5);
    glTranslated(0, -200, 1500);
//    glRotated(-90, 0, 1, 0);
    Draw();
}


