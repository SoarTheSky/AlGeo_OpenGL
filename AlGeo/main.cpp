#if defined (__APPLE__)
#include <GLUT/glut.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include "/Users/rama/Desktop/src/stdc++.h"

#elif defined (WIN32)
#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#endif
using namespace std;

int w = 1000, h = 1000, res = 50;
double resdeg = 0;
int n_vertice, reps;
double x[100],y[100],temp;
double xhasil[100], yhasil[100];
double xawal[100], yawal[100];
double factorx[100], factory[100];
bool finish_animate = true;
bool rotation_animate = false;
bool inputted = false;
string input_operator, param1, param2, param3, param4;
bool op1 = false,op2 = false,op3 = false,op4 = false;

void init(int argc, char** argv){
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600); //Window size
    glutCreateWindow("Introduction to OpenGL"); //Create a window
    glEnable(GL_DEPTH_TEST); //Make sure 3D drawing works when one object is in front of another
}

//Called when the window is resized
void handleResize(int w, int h){
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
}

// void key_back(unsigned char key, int x, int y){
//     if (key == 'w') zoom -= 5;
//     else if (key == 'q') zoom += 5;
// }

void updatematrix() {
    for(int i=0; i<n_vertice; i++) {
        x[i] = xhasil[i];
        y[i] = yhasil[i];
    }
}

//void update_shape(){
//    double factor;
//    factor = temp/(res*1.0);
//    for(int i=0;i<n_vertice;i++){
//        x[i]+=factor;
//        y[i]+=factor;
//    }
//    reps--;
//    if(reps <= 0)
//        finish_animate = true;
//}

void input(int n){
    int idx = 1;
    printf("\nInsert\n");
    for(int i = 0; i < n; i++){
        printf("(x%d,y%d) : ",idx,idx); scanf("%lf",&xhasil[i]);
        scanf("%lf",&yhasil[i]);
        idx++;
        xawal[i] = xhasil[i];
        yawal[i] = yhasil[i];
        x[i] = 0;
        y[i] = 0;
    }
}

//Draw coordinate lines
void drawline (float x1, float y1, float x2, float y2)
{
    glBegin (GL_LINES);
    glVertex2f (x1, y1);
    glVertex2f (x2, y2);
    glEnd();
}

void coordinatelines() {
    glClearColor (0, 0, 0, 0);
    glColor3ub (210, 57, 53);
    
    for (int i = -h/2; i < h/2; i +=50)
    {
        if ((int) i == 0) glLineWidth (3.5);
        else if ((int) i % 150 == 0) glLineWidth (1.5);
        else glLineWidth (0.2);
        drawline (-h/2, float(i), (float) h/2, float(i));
    }
    
    for (float i = -w/2; i < w/2; i +=50)
    {
        if ((int) i == 0) glLineWidth (3.5);
        else if ((int) i % 150 == 0) glLineWidth (1.5);
        else glLineWidth (0.2);
        drawline (i, -w/2, i, (float) w/2);
    }
    
}

void update(bool b, bool rot) {
    if ((!b) and (!rot)) {
        if(reps > 0) {
            for(int i=0;i<n_vertice;i++) {
                x[i] += factorx[i];
                y[i] += factory[i];
            }
            reps--;
        }
        else if (reps == 0) {
            updatematrix();
            reps--;
        }
        else {
            finish_animate = true;
        }
    }
}

void translate(double (&x1)[100], double (&y1)[100], string inx, string iny) {
    double dx=0, dy=0;
    stringstream masukan1(inx);
    masukan1 >> dx;
    stringstream masukan2(iny);
    masukan2 >> dy;
    for(int i=0; i<n_vertice; i++) {
        x1[i] = x1[i] + dx;
        y1[i] = y1[i] + dy;
    }
}

void dilate(string in) {
    double d = 0;
    stringstream masukan(in);
    masukan >> d;
    for(int i=0; i<n_vertice; i++) {
        xhasil[i] = xhasil[i]*d;
        yhasil[i] = yhasil[i]*d;
    }
}

void rotatevertex(double (&x1)[100], double (&y1)[100], string indeg, string ina, string inb) {
    double deg=0;
    double temp;
    stringstream masukan1(indeg);
    masukan1 >> deg;
    
    //Radian
    double rad = deg * (3.141592/180);
    
    translate(x1, y1, "-"+ina, "-"+inb);
    for(int i=0; i<n_vertice; i++) {
        temp = x1[i];
        x1[i] = (x1[i]*cos(rad)) - (y1[i]*sin(rad));
        y1[i] = (temp*sin(rad)) + (y1[i]*cos(rad));
    }
    translate(x1, y1, ina,inb);
}

void reset() {
    for(int i=0; i<n_vertice; i++) {
        xhasil[i] = xawal[i];
        yhasil[i] = yawal[i];
    }
}


void insertfactor(bool b) {
    if (!b) {
        for(int i=0; i<n_vertice; i++) {
            factorx[i] = (xhasil[i]-x[i])/((double)res);
            factory[i] = (yhasil[i]-y[i])/((double)res);
        }
    }
}

void animaterotate (bool b, bool rot) {
    if ((!b) and (rot)) {
        if(reps > 0) {
            rotatevertex(x, y, to_string(resdeg), param2, param3);
            reps--;
        }
        else if (reps == 0) {
            updatematrix();
            reps--;
        }
        else {
            finish_animate = true;
            rotation_animate = false;
            resdeg = 0;
        }
    }
}

void readyanimate(bool b) {
    reps = res;
    finish_animate = false;
    insertfactor(b);
}

void readyrotate() {
    double deg;
    stringstream masukkan(param1);
    masukkan >> deg;
    reps = res;
    finish_animate = false;
    rotation_animate = true;
    resdeg = deg/((double)res);
}

//Draws the 3D scene
void shapes(){
    //Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    
    glLoadIdentity();
    glOrtho(-w*0.5,w*0.5,-h*0.5,h*0.5, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
    coordinatelines();
    
    glBegin(GL_POLYGON);
        for(int i=0;i<n_vertice;i++){
            glVertex2f(x[i],y[i]);
        }
    glEnd();
    
    if(finish_animate) {
        cin >> input_operator;
        if(input_operator == "translate") {
            cin >> param1 >> param2;
            translate(xhasil, yhasil,param1,param2);
            readyanimate(false);
        }
        else if(input_operator == "dilate") {
            cin >> param1;
            dilate(param1);
            readyanimate(false);
        }
        else if(input_operator == "rotate") {
            cin >> param1 >> param2 >> param3;
            rotatevertex(xhasil, yhasil, param1, param2, param3);
            readyrotate();
        }
        else if(input_operator == "reset") {
            reset();
            readyanimate(false);
        }
        else {
            cout<<"Masukkan salah\n";
        }
    }
    
    animaterotate(finish_animate,rotation_animate);
    update(finish_animate,rotation_animate);

    glutSwapBuffers();
}

void draw(){
    glutDisplayFunc(shapes);
    glutIdleFunc(shapes);
}

int main(int argc, char** argv) {
    init(argc, argv); //Initialize rendering
    printf("Total Vertices : "); scanf("%d",&n_vertice);
    input(n_vertice);
    cout<<"\nPress 0 for info\n";
    readyanimate(false);
    draw();
    glutReshapeFunc(handleResize);
    //glutKeyboardFunc(key_back);
    glutMainLoop();
    return 0;
}
