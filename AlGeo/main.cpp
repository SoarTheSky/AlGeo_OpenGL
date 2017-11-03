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

int w = 1000, h = 1000, res = 1000;
int n_vertice, reps;
double x[100],y[100],temp;
double xawal[100], yawal[100];
bool finish_animate = true;

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

void update_shape(){
    double factor;
    factor = temp/(res*1.0);
    for(int i=0;i<n_vertice;i++){
        x[i]+=factor;
        y[i]+=factor;
    }
    reps--;
    if(reps <= 0)
        finish_animate = true;
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

    for (int i = -h; i < h; i +=50)
    {
        if ((int) i % 300 == 0) glLineWidth (2.5);
        else if ((int) i % 150 == 0) glLineWidth (1.5);
        else glLineWidth (0.2);
        drawline (-w, float(i), (float) w, float(i));
    }

    for (float i = -w; i < w; i +=50)
    {
        if ((int) i % 300 == 0) glLineWidth (2.5);
        else if ((int) i % 150 == 0) glLineWidth (1.5);
        else glLineWidth (0.2);
        drawline (i, -h, i, (float) h);
    }
    
}

//Draws the 3D scene
void shapes(){
    //Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective

    glLoadIdentity();
    glOrtho(-w*1.0,w*1.0,-h*1.0,h*1.0, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
    coordinatelines();
    
    glBegin(GL_POLYGON);
    for(int i=0;i<n_vertice;i++){
        glVertex2f(x[i],y[i]);
    }
    glEnd();

    glutSwapBuffers();

    if(finish_animate){
        scanf("%lf",&temp);
        finish_animate = false;
        reps = res;
    }
    update_shape();
}

void draw(){
    glutDisplayFunc(shapes);
    glutIdleFunc(shapes);
}

void input(int n){
    int idx = 1;
    printf("\nInsert\n");
    for(int i = 0; i < n; i++){
        printf("(x%d,y%d) : ",idx,idx); scanf("%lf",&x[i]);
                                        scanf("%lf",&y[i]);
        idx++;
        xawal[i] = x[i];
        yawal[i] = y[i];
    }
}

int main(int argc, char** argv) {
    init(argc, argv); //Initialize rendering
    printf("Total Vertices : "); scanf("%d",&n_vertice);
    input(n_vertice);
    draw();
    glutReshapeFunc(handleResize);
    //glutKeyboardFunc(key_back);
    glutMainLoop(); 
    return 0; 
}
