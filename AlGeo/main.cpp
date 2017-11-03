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

void outputmanual() {
    cout << endl << "Input commands available:" << endl << endl;
    cout << "translate <dx> <dy>" << endl;
    cout << "dilate <k>" << endl;
    cout << "rotate <deg> <a> <b>" << endl;
    cout << "reflect <param>" << endl;
    cout << "shear <param> <k>" << endl;
    cout << "stretch <param> <k>" << endl;
    cout << "custom <a> <b> <c> <d>" <<endl;
    cout << "multiple <n>" << endl;
    cout << "reset" << endl;
    cout << "exit" << endl << endl;
}

void welcomescreen() {
    cout << "  ________  ___       ________  _______   ________          ________  ________  _______   ________   ________  ___           " << endl;
    cout << " |\\   __  \\|\\  \\     |\\   ____\\|\\  ___ \\ |\\   __  \\        |\\   __  \\|\\   __  \\|\\  ___ \\ |\\   ___  \\|\\   ____\\|\\  \\          " << endl;
    cout << " \\ \\  \\|\\  \\ \\  \\    \\ \\  \\___|\\ \\   __/|\\ \\  \\|\\  \\       \\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\         " << endl;
    cout << "  \\ \\   __  \\ \\  \\    \\ \\  \\  __\\ \\  \\_|/_\\ \\  \\\\\\  \\       \\ \\  \\\\\\  \\ \\   ____\\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\        " << endl;
    cout << "   \\ \\  \\ \\  \\ \\  \\____\\ \\  \\|\\  \\ \\  \\_|\\ \\ \\  \\\\\\  \\       \\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\____   " << endl;
    cout << "    \\ \\__\\ \\__\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\       \\ \\_______\\ \\__\\    \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ " << endl;
    cout << "     \\|__|\\|__|\\|_______|\\|_______|\\|_______|\\|_______|        \\|_______|\\|__|     \\|_______|\\|__| \\|__|\\|_______|\\|_______| " << endl;
    
    cout << "by" << endl << "13516062" << endl << "13516096" << endl << endl << endl;
}

void input(int n){
    int idx = 1;
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
        else if ((int) i % 150 == 0) glLineWidth (2.0);
        else glLineWidth (0.2);
        drawline (-h/2, float(i), (float) h/2, float(i));
    }
    
    for (float i = -w/2; i < w/2; i +=50)
    {
        if ((int) i == 0) glLineWidth (3.5);
        else if ((int) i % 150 == 0) glLineWidth (2.0);
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

void shear(string inparam, string ink) {
    double k=0;
    stringstream masukan(ink);
    masukan >> k;
    
    if (inparam == "x") {
        for(int i=0; i<n_vertice; i++) {
            xhasil[i] += k*yhasil[i];
        }
    }
    else if (inparam == "y") {
        for(int i=0; i<n_vertice; i++) {
            yhasil[i] += k*xhasil[i];
        }
    }
}

void stretch(string inparam, string ink) {
    double k=0;
    stringstream masukan(ink);
    masukan >> k;
    
    if (inparam == "x") {
        for(int i=0; i<n_vertice; i++) {
            xhasil[i] *= k;
        }
    }
    else if(inparam == "y") {
        for(int i=0; i<n_vertice; i++) {
            yhasil[i] *= k;
        }
    }
}

void custom(string ina, string inb, string inc, string ind) {
    double a=0,b=0,c=0,d=0;
    stringstream masukan1(ina);
    masukan1 >> a;
    stringstream masukan2(inb);
    masukan2 >> b;
    stringstream masukan3(inc);
    masukan3 >> c;
    stringstream masukan4(ind);
    masukan4 >> d;
    
    for(int i=0; i<n_vertice; i++) {
        temp = xhasil[i];
        xhasil[i] = xhasil[i]*a + yhasil[i]*b;
        yhasil[i] = temp*c + yhasil[i]*d;
    }
}

void reset() {
    for(int i=0; i<n_vertice; i++) {
        xhasil[i] = xawal[i];
        yhasil[i] = yawal[i];
    }
}


void insertfactor() {
    for(int i=0; i<n_vertice; i++) {
        factorx[i] = (xhasil[i]-x[i])/((double)res);
        factory[i] = (yhasil[i]-y[i])/((double)res);
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

void readyanimate() {
    reps = res;
    finish_animate = false;
    insertfactor();
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
            readyanimate();
        }
        else if(input_operator == "dilate") {
            cin >> param1;
            dilate(param1);
            readyanimate();
        }
        else if(input_operator == "rotate") {
            cin >> param1 >> param2 >> param3;
            rotatevertex(xhasil, yhasil, param1, param2, param3);
            readyrotate();
        }
        else if(input_operator == "shear") {
            cin >> param1 >> param2;
            shear(param1,param2);
            readyanimate();
        }
        else if(input_operator == "stretch") {
            cin >> param1 >> param2;
            stretch(param1,param2);
            readyanimate();
        }
        else if(input_operator == "custom") {
            cin >> param1 >> param2 >> param3 >> param4;
            custom(param1,param2,param3,param4);
            readyanimate();
        }
        else if(input_operator == "reset") {
            reset();
            readyanimate();
        }
        else if(input_operator == "exit") {
            exit(0);
        }
        else if(input_operator == "0") {
            outputmanual();
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
    welcomescreen();
    printf("Input Total Vertices : "); scanf("%d",&n_vertice);
    input(n_vertice);
    cout<<"\nPress 0 for info\n";
    readyanimate();
    draw();
    glutReshapeFunc(handleResize);
    //glutKeyboardFunc(key_back);
    glutMainLoop();
    return 0;
}
