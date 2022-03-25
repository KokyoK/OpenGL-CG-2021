#define GL_SILENCE_DEPRECATION


#include "DisplayableObject.h"
#include "Animation.h"
#include <stdio.h>
#include <GL/glut.h> 
#include <vector>
#include <string>
using namespace std;

class Loader:
public DisplayableObject,
public Animation
{
public:

    Loader(string filename);
    //void Init();
    void Draw();

    void Display();
    void Update(const double& deltaTime);

private:
    vector<string>matNameList;
    vector<vector<GLfloat>>matKd;
    vector<vector<GLfloat>>matKs;
    vector<vector<GLfloat>>matKa;
    vector<GLfloat>matNs;
    vector<string>matTexList;

    vector<GLint>fAreaIdx; 
    vector<GLint>fAreaMatIdx;

    vector<vector<GLfloat>>vSets;
    vector<vector<GLint>>fSets;
    vector<vector<GLint>>ftSets;
    vector<vector<GLfloat>>vnSets;
    vector<vector<GLfloat>>vtSets;
};



