#include <windows.h>	
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SOIL.h>
#include <GL/GLUT.h>
#include <GL/GLU.h>
#include <math.h>	
#include <time.h>
#include "camera.h"

#define PI 3.14

CCamera Camera;

using namespace std;
double fer=0.8;
double mf=0.1;
double flight=0;
double ajtof1=0, ajtof2=0, ajtof3=0, ajtof4=0, ajtof5=0;

bool menu = false;

//menühöz
void bitmap_output(float x, float y, char *string, void *font) 
{
  int len, i;
  glRasterPos3d(x, y,-1);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
  
}

void help(){
//menü(irányítás)
	glPushMatrix();
	glLoadIdentity();
	bitmap_output(-0.02f, 0.32f, " 'W' Elore",
	GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.30f, " 'A' Fordulas balra",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.28f, " 'S' Hatra",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.26f, " 'D' Fordulas jobb",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.24f, " 'O' Fenyero novelés ",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.22f, " 'L' Fenyero csokkentés ",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.20f, " '1-4' Szekrenyek kinyitasa ",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.18f, " '5' Ajto kinyitasa ",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.16f, " '0' Osszes ajto becsukasa ",
    GLUT_BITMAP_HELVETICA_18);
	bitmap_output(-0.02f, 0.14f, " 'Esc' Leallitas ",
    GLUT_BITMAP_HELVETICA_18);

	glPopMatrix();
	glFlush();
	}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	
}
void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(double)width/(double)height,1.0,200.0);
}

double alpha = 0.0;
int i,db;
double tl;


void cetli(GLfloat forg,GLfloat elt){
	glPushMatrix();
	glColor3f(1,1,1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glNormal3d(0,0,1);
	glTranslated(elt, 2 ,-1.06);
	glRotated(forg,0,0,1);
	glBegin(GL_QUADS);
	glVertex3f(-0.12,-0.12,0);
	glVertex3f(0.12,-0.12,0);
	glVertex3f(0.12,0.12,0);
	glVertex3f(-0.12,0.12,0);
	glEnd();
	glPopMatrix();
}

void polc (GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
	glColor3f(0.5,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_QUADS);
	glNormal3d(0,-1,0);
	glVertex3f(1.75,2,-2);
	glVertex3f(1.8,2,-2);
	glVertex3f(1.8,2,-1);
	glVertex3f(1.75,2,-1);
	glEnd();
//-------------------------------------------------------------------	
	glBegin(GL_QUADS);
	glNormal3d(-1,0,0);
	glVertex3f(1.75,3,-1);
	glVertex3f(1.75,3,-2);
	glVertex3f(1.75,2,-2);
	glVertex3f(1.75,2,-1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(1.75,3,-1);
	glVertex3f(1.75,2,-1);
	glVertex3f(1.8,2,-1);
	glVertex3f(1.8,3,-1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(1,0,0);
	glVertex3f(1.8,3,-2);
	glVertex3f(1.8,3,-1);
	glVertex3f(1.8,2,-1);
	glVertex3f(1.8,2,-2);
	glEnd();
  //baloldal
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-1.75,3,-1);
	glVertex3f(-1.8,3,-1);
	glVertex3f(-1.8,2,-1);
	glVertex3f(-1.75,2,-1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(1,0,0);
	glVertex3f(-1.75,3,-1);
	glVertex3f(-1.75,2,-1);
	glVertex3f(-1.75,2,-2);
	glVertex3f(-1.75,3,-2);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,-1,0);
	glVertex3f(-1.8,2,-2);
	glVertex3f(-1.75,2,-2);
	glVertex3f(-1.75,2,-1);
	glVertex3f(-1.8,2,-1);
	glEnd();
//-------------------------------------------------------------------	
	glBegin(GL_QUADS);
	glNormal3d(-1,0,0);
	glVertex3f(-1.8,3,-1);
	glVertex3f(-1.8,3,-2);
	glVertex3f(-1.8,2,-2);
	glVertex3f(-1.8,2,-1);
	glEnd();
 //lap
	glBegin(GL_QUADS);
	glNormal3d(0,-1,0);
	glVertex3f(-1.75,2.2,-1.95);
	glVertex3f(1.75,2.2,-1.95);
	glVertex3f(1.75,2.2,-1.05);
	glVertex3f(-1.75,2.2,-1.05);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(1.75,2.25,-1.05);
	glVertex3f(-1.75,2.25,-1.05);
	glVertex3f(-1.75,2.2,-1.05);
	glVertex3f(1.75,2.2,-1.05);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,1,0);
	glVertex3f(-1.75,2.25,-1.95);
	glVertex3f(1.75,2.25,-1.95);
	glVertex3f(1.75,2.25,-1.05);
	glVertex3f(-1.75,2.25,-1.05);
	glEnd();
  //hatlap
	glBegin(GL_QUADS);
	glNormal3d(0,-1,0);
	glVertex3f(-1.75,2,-2);
	glVertex3f(1.75,2,-2);
	glVertex3f(1.75,2,-1.95);
	glVertex3f(-1.75,2,-1.95);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(1.75,2.2,-1.95);
	glVertex3f(-1.75,2.2,-1.95);
	glVertex3f(-1.75,2,-1.95);
	glVertex3f(1.75,2,-1.95);
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(1.75,3,-1.95);
	glVertex3f(-1.75,3,-1.95);
	glVertex3f(-1.75,2.2,-1.95);
	glVertex3f(1.75,2.2,-1.95);
	glEnd();
  //elolap
	glBegin(GL_QUADS);
	glNormal3d(0,-1,0);
	glVertex3f(-1.75,2.02,-1.13);
	glVertex3f(1.75,2.02,-1.13);
	glVertex3f(1.75,2.02,-1.07);
	glVertex3f(-1.75,2.02,-1.07);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(1.75,2.2,-1.07);
	glVertex3f(-1.75,2.2,-1.07);
	glVertex3f(-1.75,2.02,-1.07);
	glVertex3f(1.75,2.02,-1.07);
	glEnd();

	glPopMatrix();
}
//asztal
void asztal(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,0,1);
	glColor3f(0.3,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
 //front
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-2, -0.03, 0.5);
	glVertex3f(2, -0.03, 0.5);
	glVertex3f(2, 0.03, 0.5);
	glVertex3f(-2, 0.03, 0.5);
  //top
	glNormal3d(0,1,0);
	glVertex3f(-2, 0.03, 0.5);
	glVertex3f(2, 0.03, 0.5);
	glVertex3f(2, 0.03, -2);
	glVertex3f(-2, 0.03, -2);
  //jobboldal
	glNormal3d(1,0,0);
	glVertex3f(2, -0.03, 0.5);
	glVertex3f(2, -0.03, -2);
	glVertex3f(2, 0.03, -2);
	glVertex3f(2, 0.03, 0.5);
  //baloldal	
	glNormal3d(-1,0,0);
	glVertex3f(-2, -0.03, -2);
	glVertex3f(-2, -0.03, 0.5);
	glVertex3f(-2, 0.03, 0.5);
	glVertex3f(-2, 0.03, -2);
	glEnd();

	glPopMatrix();
}
void a_lab(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();

	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,0,1);
	glColor3f(0.3,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glBegin(GL_QUADS);
	glNormal3d(0,0,1);//front
	glVertex3f(-0.075,-0.03,0);
	glVertex3f(-0.075,-2,0);
	glVertex3f(0.075,-2,0);
	glVertex3f(0.075,-0.03,0);
	
	glNormal3d(0,0,-1);//back
	glVertex3f(-0.075,-0.03,-0.15);
	glVertex3f(0.075,-0.03,-0.15);
	glVertex3f(0.075,-2,-0.15);
	glVertex3f(-0.075,-2,-0.15);
	
	glNormal3d(-1,0,0);//left
	glVertex3f(-0.075,-0.03,0);
	glVertex3f(-0.075,-0.03,-0.15);
	glVertex3f(-0.075,-2,-0.15);
	glVertex3f(-0.075,-2,0);
	
	glNormal3d(1,0,0);//right
	glVertex3f(0.075,-0.03,-0.15);
	glVertex3f(0.075,-0.03,0);
	glVertex3f(0.075,-2,0);
	glVertex3f(0.075,-2,-0.15);
	glEnd();

	glPopMatrix();
}

void agy(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz,GLfloat agy[],GLfloat matrac[]){
	glPushMatrix();
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
	glColor3f(0.3,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, agy);
//háttámla
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glVertex3f(-1.3, -1, 0);
	glVertex3f(1.3, -1, 0);
	glVertex3f(1.3, 0.4, 0);
	glVertex3f(0.9, 0.7, 0);
	glVertex3f(-0.9, 0.7, 0);
	glVertex3f(-1.3, 0.4, 0);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(-1,0,0);
	glVertex3f(-1.3, -1, 0);
	glVertex3f(-1.3, 0.4, 0);
	glVertex3f(-1.3, 0.4, -0.09);
	glVertex3f(-1.3, -1, -0.09);

	glNormal3d(-1,1,0);
	glVertex3f(-1.3, 0.4, -0.09);
	glVertex3f(-1.3, 0.4, 0);
	glVertex3f(-0.9, 0.7, 0);
	glVertex3f(-0.9, 0.7, -0.09);

	glNormal3d(0,1,0);
	glVertex3f(-0.9, 0.7, -0.09);
	glVertex3f(-0.9, 0.7, 0);
	glVertex3f(0.9, 0.7, 0);
	glVertex3f(0.9, 0.7, -0.09);

	glNormal3d(1,1,0);
	glVertex3f(0.9, 0.7, -0.09);
	glVertex3f(0.9, 0.7, 0);
	glVertex3f(1.3, 0.4, 0);
	glVertex3f(1.3, 0.4, -0.09);
	
	glNormal3d(1,0,0);
	glVertex3f(1.3, 0.4, -0.09);
	glVertex3f(1.3, 0.4, 0);
	glVertex3f(1.3, -1, 0);
	glVertex3f(1.3, -1, -0.09);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glVertex3f(1.3, -1, -0.09);
	glVertex3f(-1.3, -1, -0.09);
	glVertex3f(-1.3, 0.4, -0.09);
	glVertex3f(-0.9, 0.7, -0.09);
	glVertex3f(0.9, 0.7, -0.09);
	glVertex3f(1.3, 0.4, -0.09);
	glEnd();
//oldal
	glBegin(GL_QUADS);
	glNormal3d(0,1,0);
	glVertex3f(-1.1, -1, 0);
	glVertex3f(-1.09, -1, 5);
	glVertex3f(-1.09, 0, 5);
	glVertex3f(-1.1, 0, 0);

	glNormal3d(-1,0,0);
	glVertex3f(-1.05, 0, 0);
	glVertex3f(-1.1, 0, 0);
	glVertex3f(-1.1, 0, 5);
	glVertex3f(-1.05, 0, 5);

	glNormal3d(1,0,0);
	glVertex3f(1.1, 0, 5);
	glVertex3f(1.1, -1, 5);
	glVertex3f(1.1, -1, 0);
	glVertex3f(1.1, 0, 0);
	
	glNormal3d(0,1,0);
	glVertex3f(1.1, 0, 0);
	glVertex3f(1.05, 0, 0);
	glVertex3f(1.05, 0, 5);
	glVertex3f(1.1, 0, 5);
	glEnd();
//-------------------------------------------------------------------
	glPushMatrix();
		glBegin(GL_POLYGON);
		glNormal3d(0,0,1);
			for(double i = 0; i < 2 * PI; i += PI / 9) //<-- Change this Value
 				glVertex3f(1+cos(i) * 0.1, sin(i) * 0.1, 5);
			glVertex3f(1,0.1,5);
			glVertex3f(-1,0.1,5);
			for(double i = 0; i < 2 * PI; i += PI / 9) //<-- Change this Value
 				glVertex3f(-1-(cos(i) * 0.1), 0-(sin(i) * 0.1), 5);
			glVertex3f(-1.1,-1,5);
			glVertex3f(1.1,-1,5);
		glEnd();
	glPopMatrix();

//matrac
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrac);
	glColor3f(0.8,0.9,0.9);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_QUADS);
	glNormal3d(-1,0,0);
	glVertex3f(-1.05, 0.1, 0);
	glVertex3f(-1.05, 0, 0);
	glVertex3f(-1.05, 0, 5);
	glVertex3f(-1.05, 0.1, 5);

	glNormal3d(1,0,0);
	glVertex3f(1.05, 0.1, 0);
	glVertex3f(1.05, 0.1, 5);
	glVertex3f(1.05, 0, 5);
	glVertex3f(1.05, 0, 0);

	glNormal3d(0,1,0);
	glVertex3f(-1.05, 0.1, 0);
	glVertex3f(-1.05, 0.1, 5);
	glVertex3f(1.05, 0.1, 5);
	glVertex3f(1.05, 0.1, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}
void kilincs(GLfloat y,GLfloat z,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.9,0.5,0.4);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(y,0,1,0);
	glRotated(z,0,0,1);
//-------------------------------------------------------------------
	glBegin(GL_QUAD_STRIP);
	glNormal3d(-1,0,0);
	glVertex3f(1.8, -0.65, 0.1);
	glVertex3f(1.8, -0.8, 0.1);
	glVertex3f(1.8, -0.55, 0.2);
	glVertex3f(1.8, -0.6, 0.25);
	glVertex3f(1.8, -0.4, 0.2);
	glVertex3f(1.8, -0.35, 0.25);
	glVertex3f(1.8, -0.35, 0.1);
	glVertex3f(1.8, -0.2, 0.1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,-1,1);
	glVertex3f(1.8, -0.8, 0.1);
	glVertex3f(1.9, -0.8, 0.1);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.8, -0.6, 0.25);

	glNormal3d(0,0,1);
	glVertex3f(1.8, -0.6, 0.25);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.8, -0.35, 0.25);

	glNormal3d(0,1,1);
	glVertex3f(1.8, -0.35, 0.25);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.9, -0.2, 0.1);
	glVertex3f(1.8, -0.2, 0.1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUAD_STRIP);
	glNormal3d(1,0,0);
	glVertex3f(1.9, -0.8, 0.1);
	glVertex3f(1.9, -0.65, 0.1);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.9, -0.55, 0.2);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.9, -0.4, 0.2);
	glVertex3f(1.9, -0.2, 0.1);
	glVertex3f(1.9, -0.35, 0.1);
//-------------------------------------------------------------------	
	glEnd();
	glPopMatrix();
}
void kilincs2(GLfloat y,GLfloat z,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.9,0.5,0.4);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx+4, elty ,eltz+0.1);
	glRotated(180+y,0,1,0);
	glRotated(z,0,0,1);
//-------------------------------------------------------------------
	glBegin(GL_QUAD_STRIP);
	glNormal3d(-1,0,0);
	glVertex3f(1.8, -0.65, 0.1);
	glVertex3f(1.8, -0.8, 0.1);
	glVertex3f(1.8, -0.55, 0.2);
	glVertex3f(1.8, -0.6, 0.25);
	glVertex3f(1.8, -0.4, 0.2);
	glVertex3f(1.8, -0.35, 0.25);
	glVertex3f(1.8, -0.35, 0.1);
	glVertex3f(1.8, -0.2, 0.1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUADS);
	glNormal3d(0,-1,1);
	glVertex3f(1.8, -0.8, 0.1);
	glVertex3f(1.9, -0.8, 0.1);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.8, -0.6, 0.25);

	glNormal3d(0,0,1);
	glVertex3f(1.8, -0.6, 0.25);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.8, -0.35, 0.25);

	glNormal3d(0,1,1);
	glVertex3f(1.8, -0.35, 0.25);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.9, -0.2, 0.1);
	glVertex3f(1.8, -0.2, 0.1);
	glEnd();
//-------------------------------------------------------------------
	glBegin(GL_QUAD_STRIP);
	glNormal3d(1,0,0);
	glVertex3f(1.9, -0.8, 0.1);
	glVertex3f(1.9, -0.65, 0.1);
	glVertex3f(1.9, -0.6, 0.25);
	glVertex3f(1.9, -0.55, 0.2);
	glVertex3f(1.9, -0.35, 0.25);
	glVertex3f(1.9, -0.4, 0.2);
	glVertex3f(1.9, -0.2, 0.1);
	glVertex3f(1.9, -0.35, 0.1);
//-------------------------------------------------------------------	
	glEnd();
	glPopMatrix();
}
void ajto(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.4,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
//lap
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(0, 1, 0.1);
	glVertex3f(0, -1, 0.1);
	glVertex3f(2, -1, 0.1);
	glVertex3f(2, 1, 0.1);

	glNormal3d(-1,0,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, -1, 0.1);
	glVertex3f(0, 1, 0.1);

	glNormal3d(1,0,0);
	glVertex3f(2, 1, 0);
	glVertex3f(2, 1, 0.1);
	glVertex3f(2, -1, 0.1);
	glVertex3f(2, -1, 0);

	glNormal3d(0,1,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 0.1);
	glVertex3f(2, 1, 0.1);
	glVertex3f(2, 1, 0);

	glNormal3d(0,-1,0);
	glVertex3f(0, -1, 0.1);
	glVertex3f(0, -1, 0);
	glVertex3f(2, -1, 0);
	glVertex3f(2, -1, 0.1);

	glNormal3d(0,0,-1);
	glVertex3f(2, 1, 0);
	glVertex3f(2, -1, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	
	glPopMatrix();
}

void ajto2(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.4,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
//lap
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(0, 1, 0.1);
	glVertex3f(0, -2.2, 0.1);
	glVertex3f(2, -2.2, 0.1);
	glVertex3f(2, 1, 0.1);

	glNormal3d(-1,0,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, -2.2, 0);
	glVertex3f(0, -2.2, 0.1);
	glVertex3f(0, 1, 0.1);

	glNormal3d(1,0,0);
	glVertex3f(2, 1, 0);
	glVertex3f(2, 1, 0.1);
	glVertex3f(2, -2.2, 0.1);
	glVertex3f(2, -2.2, 0);

	glNormal3d(0,1,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 0.1);
	glVertex3f(2, 1, 0.1);
	glVertex3f(2, 1, 0);

	glNormal3d(0,-1,0);
	glVertex3f(0, -2.2, 0.1);
	glVertex3f(0, -2.2, 0);
	glVertex3f(2, -2.2, 0);
	glVertex3f(2, -2.2, 0.1);

	glNormal3d(0,0,-1);
	glVertex3f(2, 1, 0);
	glVertex3f(2, -2.2, 0);
	glVertex3f(0, -2.2, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	
	glPopMatrix();
}

void kisszekreny(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.6,0.3,0.3);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);

	glBegin(GL_QUADS);
	glNormal3d(1,0,0);
	glVertex3f(-0.9, 0.9, 0);
	glVertex3f(-0.9, -0.9, 0);
	glVertex3f(-0.9, -0.9, -1.5);
	glVertex3f(-0.9, 0.9, -1.5);

	glNormal3d(0,1,0);
	glVertex3f(-0.9, -0.9, -1.5);
	glVertex3f(-0.9, -0.9, 0);
	glVertex3f(0.9, -0.9, 0);
	glVertex3f(0.9, -0.9, -1.5);

	glNormal3d(-1,0,0);
	glVertex3f(0.9, 0.9, -1.5);
	glVertex3f(0.9, -0.9, -1.5);
	glVertex3f(0.9, -0.9, 0);
	glVertex3f(0.9, 0.9, 0);

	glNormal3d(0,-1,0);
	glVertex3f(-0.9, 0.9, 0);
	glVertex3f(-0.9, 0.9, -1.5);
	glVertex3f(0.9, 0.9, -1.5);
	glVertex3f(0.9, 0.9, 0);

//hátlap
	glNormal3d(0,0,1);
	glVertex3f(-0.9, 0.9, -1.5);
	glVertex3f(-0.9, -0.9, -1.5);
	glVertex3f(0.9, -0.9, -1.5);
	glVertex3f(0.9, 0.9, -1.5);
	glEnd();

	glPopMatrix();
}
void nagyszekreny(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.6,0.3,0.3);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);

	glBegin(GL_QUADS);
	glNormal3d(1,0,0);
	glVertex3f(-0.9, 0.9, 0);
	glVertex3f(-0.9, -2.1, 0);
	glVertex3f(-0.9, -2.1, -1.5);
	glVertex3f(-0.9, 0.9, -1.5);

	glNormal3d(0,1,0);
	glVertex3f(-0.9, -2.1, -1.5);
	glVertex3f(-0.9, -2.1, 0);
	glVertex3f(0.9, -2.1, 0);
	glVertex3f(0.9, -2.1, -1.5);

	glNormal3d(-1,0,0);
	glVertex3f(0.9, 0.9, -1.5);
	glVertex3f(0.9, -2.1, -1.5);
	glVertex3f(0.9, -2.1, 0);
	glVertex3f(0.9, 0.9, 0);

	glNormal3d(0,-1,0);
	glVertex3f(-0.9, 0.9, 0);
	glVertex3f(-0.9, 0.9, -1.5);
	glVertex3f(0.9, 0.9, -1.5);
	glVertex3f(0.9, 0.9, 0);

//hátlap
	glNormal3d(0,0,1);
	glVertex3f(-0.9, 0.9, -1.5);
	glVertex3f(-0.9, -2.1, -1.5);
	glVertex3f(0.9, -2.1, -1.5);
	glVertex3f(0.9, 0.9, -1.5);
	glEnd();

	glPopMatrix();
}
void bejaratiajto(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz,GLfloat kilincs[]){
	glPushMatrix();
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
	glColor3f(0.35,0.2,0.2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
//lap
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(0, 2, 0.1);
	glVertex3f(0, -3, 0.1);
	glVertex3f(2.5, -3, 0.1);
	glVertex3f(2.5, 2, 0.1);

	glNormal3d(-1,0,0);
	glVertex3f(0, 2, 0);
	glVertex3f(0, -3, 0);
	glVertex3f(0, -3, 0.1);
	glVertex3f(0, 2, 0.1);

	glNormal3d(1,0,0);
	glVertex3f(2.5, 2, 0);
	glVertex3f(2.5, 2, 0.1);
	glVertex3f(2.5, -3, 0.1);
	glVertex3f(2.5, -3, 0);

	glNormal3d(0,1,0);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 2, 0.1);
	glVertex3f(2.5, 2, 0.1);
	glVertex3f(2.5, 2, 0);

	glNormal3d(0,-1,0);
	glVertex3f(0, -3, 0.1);
	glVertex3f(0, -3, 0);
	glVertex3f(2.5, -3, 0);
	glVertex3f(2.5, -3, 0.1);

	glNormal3d(0,0,-1);
	glVertex3f(2.5, 2, 0);
	glVertex3f(2.5, -3, 0);
	glVertex3f(0, -3, 0);
	glVertex3f(0, 2, 0);
	glEnd();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, kilincs);
	kilincs2(0,90,-1.5,-2,0);

	glPopMatrix();
}
void ajtobuki(GLfloat forg,GLfloat eltx,GLfloat elty,GLfloat eltz,GLfloat light,GLfloat asd2[], GLfloat asd[]){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, asd2);
	glPushMatrix();
	glColor3f(light,light,light);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(forg,0,1,0);
//folyosó padló
	glBegin(GL_QUADS);
	glNormal3d(0,1,0);
	glVertex3f(-6.15, -3, -4);
	glVertex3f(-6.15, -3, 0);
	glVertex3f(6.15, -3, 0);
	glVertex3f(6.15, -3, -4);
//folyosó fal
	glNormal3d(0,0,1);
	glVertex3f(-6.15, 7, -4);
	glVertex3f(-6.15, -3, -4);
	glVertex3f(6.15, -3, -4);
	glVertex3f(6.15, 7, -4);

	glNormal3d(1,0,0);
	glVertex3f(-1.15, 1.9, 0);
	glVertex3f(-1.15, -3, 0);
	glVertex3f(-1.15, -3, -1);
	glVertex3f(-1.15, 1.9, -1);

	glNormal3d(-1,0,0);
	glVertex3f(1.15, 1.9, -1);
	glVertex3f(1.15, -3, -1);
	glVertex3f(1.15, -3, 0);
	glVertex3f(1.15, 1.9, 0);

	glNormal3d(0,-1,0);
	glVertex3f(-1.15, 1.9, 0);
	glVertex3f(-1.15, 1.9, -1);
	glVertex3f(1.15, 1.9, -1);
	glVertex3f(1.15, 1.9, 0);
	glEnd();
	
	glPopMatrix();
	
}

void deszka(GLfloat y, GLfloat z,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.6,0.3,0.3);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(y,0,1,0);
	glRotated(z,0,0,1);

	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-1.5, 0.2, 0);
	glVertex3f(-1.5, -0.2, 0);
	glVertex3f(1.5, -0.2, 0);
	glVertex3f(1.5, 0.2, 0);
	glEnd();

	glPopMatrix();
}
void fdeszka(GLfloat y, GLfloat z,GLfloat eltx,GLfloat elty,GLfloat eltz){
	glPushMatrix();
	glColor3f(0.6,0.3,0.3);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(eltx, elty ,eltz);
	glRotated(y,0,1,0);
	glRotated(z,0,0,1);

	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-1.6, 0.3, 0);
	glVertex3f(-1.6, -0.3, 0);
	glVertex3f(1.6, -0.3, 0);
	glVertex3f(1.6, 0.3, 0);
	glEnd();

	glPopMatrix();
}
void ora (GLfloat y,GLfloat z,GLfloat eltx,GLfloat elty,GLfloat eltz,GLfloat keret[],GLfloat lap[],GLfloat mutato[]){
	glPushMatrix();
	glTranslated(eltx, elty ,eltz);
	glRotated(y,0,1,0);
//keret
	glMaterialfv(GL_FRONT, GL_DIFFUSE, keret);
	glColor3f(0.6,0.8,0.6);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_POLYGON);
	for(double i = 0; i < 2 * PI; i += PI / 10) //<-- Change this Value
 				glVertex3f(cos(i) * 0.3, sin(i) * 0.3, 0);
	glEnd();
//óralap
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lap);
	glColor3f(1,1,1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_POLYGON);
	for(double i = 0; i < 2 * PI; i += PI / 10) //<-- Change this Value
 				glVertex3f(cos(i) * 0.25, sin(i) * 0.25, 0.01);
	glEnd();
//mutatók
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mutato);
	glRotated(z,0,0,1);
	glColor3f(0,0,0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.02);
	glVertex3f(0.24, 0, 0.02);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotated(z/60,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.02);
	glVertex3f(0, 0.2, 0.02);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotated(z/(60*60),0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0.02);
	glVertex3f(0.08, 0.08, 0.02);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void key(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			exit(0);
//forgatás
		case 'a':		
			Camera.RotateY(5.0);
			break;
		case 'd':		
			Camera.RotateY(-5.0);
			break;
		case 'w':		
			if(Camera.GetX()<=4 && Camera.GetX()>=-3 && Camera.GetZ()<=6.5 && Camera.GetZ()>=-0){				
			Camera.MoveForwards( -0.25 ) ;  
				if(Camera.GetX()>4 || Camera.GetX()<-3 || Camera.GetZ()>6.5 || Camera.GetZ()<-0){	
					Camera.MoveForwards( 0.25 ) ;  
				}
			} 
			break;
		case 's':		
			if(Camera.GetX()<=4 && Camera.GetX()>=-3 && Camera.GetZ()<=6.5 && Camera.GetZ()>=-0){	
			Camera.MoveForwards( 0.25 ) ;  
				if(Camera.GetX()>4 || Camera.GetX()<-3 || Camera.GetZ()>6.5 || Camera.GetZ()<-0){
					Camera.MoveForwards( -0.25 ) ;  
				} 
			} 
			break;
		case '1':		
			ajtof1+=2;
			if (ajtof1 > 45)
				ajtof1 -=2;
			break;
		case '2':		
			ajtof2+=2;
			if (ajtof2 > 85)
				ajtof2 -=2;
			break;
		case '3':		
			ajtof3+=2;
			if (ajtof3 > 55)
				ajtof3 -=2;
			break;
		case '4':		
			ajtof4+=2;
			if (ajtof4 > 100)
				ajtof4 -=2;
			break;
		case '5':		
			ajtof5+=2;
			if (ajtof5 >80)
				ajtof5 -=2;
			break;
		case '0':		
			ajtof1=0, ajtof2=0, ajtof3=0, ajtof4=0, ajtof5=0;
			break;
//fényerő
		case 'o':		
			fer +=0.5;
			mf +=0.02;
			if (mf > 0.15)
				mf -=0.02;
			if (fer > 1.5)
				fer -=0.5;
			break;
		case 'l':		
			fer -=0.5;
			mf -=0.02;
			if (mf < -0.6)
				mf +=0.02;
			if (fer < -5)
				fer +=0.5;
			break;
	}
}

void display(void) 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   Camera.Render();
 //menü
   //glDisable(GL_COLOR_MATERIAL);
//fény
	
		
		GLfloat lightColor0[] = {fer-1,fer-1,fer-1,1}; //Color
		GLfloat lightPos0[] = {3, 1, 1,1}; //Positioned
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		/**/float light_diffuse2[]    = { 0.4, 0.4, 0.4, 1.0 }; 
		float light_position2[]  = { 1.0, 3.0, 3.0, 0.0 }; 
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2); 
		glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
		
//material értékek
	GLfloat no_mat[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular2[] = { 0.15, 0.15, 0.15, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 20.0 };
	GLfloat mat_emissionw[] = {0.9, 0.9, 0.9, 0.0};
	GLfloat mat_emissionwajtokeret[] = {0.8, 0.7, 0.7, 0.0};
    GLfloat mat_emission[] = {1, 1, 1, 0.0};
	GLfloat mat_emissionpadlo[] = {0.8,0.8,1, 0.0};
	GLfloat mat_emissiondeszkaszekreny[] = {0.6,0.3,0.3, 0.0};
	GLfloat mat_emissionpolc[] = {0.5,0.2,0.2, 0.0};
	GLfloat mat_emissionmonitor[] = {0,0,0, 0.0};
	GLfloat mat_emissionkilincs[] = {0.9,0.5,0.4, 0.0};
	GLfloat mat_emissionbajto[] = {0.35,0.2,0.2, 0.0};
	GLfloat mat_emissionszajto[] = {0.4,0.2,0.2, 0.0};
	GLfloat mat_emissionmatrac[] = {0.8,0.9,0.9, 0.0};
	GLfloat mat_emissionasztalagy[] = {0.3,0.2,0.2, 0.0};
	GLfloat mat_emissionkeret[] = {0.6,0.8,0.6, 0.0};

	GLfloat mat_emission_menu[] = { -0.5f, 0.3, -0.5f, 1.0 };
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission_menu);
	if (menu)help();
//pálya
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glTranslated(-2, -1, 0);
//wall
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionw);
	glColor3f(1,1,1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-3, -2, -2);
	glVertex3f(9, -2, -2);
	glVertex3f(9, 4, -2);
	glVertex3f(-3, 4, -2);

	glNormal3d(1,0,0);
	glVertex3f(-3, -2, 8);
	glVertex3f(-3, -2, -2);
	glVertex3f(-3, 4, -2);
	glVertex3f(-3, 4, 8);
	
	glNormal3d(0,0,-1);
	glVertex3f(9, 4, 8);
	glVertex3f(9, -2, 8);
	glVertex3f(-3, -2, 8);
	glVertex3f(-3, 4, 8);

	glNormal3d(0,-1,0);
	glVertex3f(-3, 4, 8);
	glVertex3f(-3, 4, -2);
	glVertex3f(9, 4, -2);
	glVertex3f(9, 4, 8);
//padló
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionpadlo);
	glColor3f(0.8,0.8,1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glNormal3d(0,1,0);
	glVertex3f(-3, -2, -2);
	glVertex3f(-3, -2, 8);
	glVertex3f(9, -2, 8);
	glVertex3f(9, -2, -2);

	glEnd();
//szekrények bedeszkázása
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissiondeszkaszekreny);
  //vizszintes alja
	deszka(-90,0,8.99,-1.8,-0.85);
	deszka(-90,0,8.99,-1.8,1.5);
	deszka(-90,0,8.99,-1.8,6.8);
  //vizszintes közép
	deszka(-90,0,8.99,1.6,-0.85);
	deszka(-90,0,8.99,1.6,1.5);
	deszka(-90,0,8.99,1.6,6.8);
  //vizszintes teteje
	deszka(-90,0,8.99,3.8,-0.85);
	deszka(-90,0,8.99,3.8,1.5);
	deszka(-90,0,8.99,3.8,6.8);
  //ajtó deszka
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glVertex3f(8.99, 4, 3);
	glVertex3f(8.99, 2.9, 3);
	glVertex3f(8.99, 2.9, 5.5);
	glVertex3f(8.99, 4, 5.5);
	glEnd();

  //függőleges balszél
	fdeszka(-90,90,8.99,3,-1.9);
	fdeszka(-90,90,8.99,0,-1.9);
  //függőleges bal
	fdeszka(-90,90,8.99,3,0.3);
	fdeszka(-90,90,8.99,0,0.3);
  //függőleges balközép
	fdeszka(-90,90,8.99,3,2.7);
	fdeszka(-90,90,8.99,0,2.7);
  //függőleges jobbközép
	fdeszka(-90,90,8.99,3,5.6);
	fdeszka(-90,90,8.99,-0.1,5.6);
  //függőleges jobbszél
	fdeszka(-90,90,8.99,3,8);
	fdeszka(-90,90,8.99,-0.1,8);

//ajtók
	nagyszekreny(-90,8.99,0.5,-0.85);
	nagyszekreny(-90,8.99,0.5,1.5);
	nagyszekreny(-90,8.99,0.5,6.8);
	
	kisszekreny(-90,8.99,2.7,-0.85);
	kisszekreny(-90,8.99,2.7,1.5);
	kisszekreny(-90,8.99,2.7,6.8);
	
//-------------------------------------------------------------------
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionszajto);

	ajto(-90-ajtof1,8.99,2.7,-1.7);
	ajto(-90,8.99,2.7,0.5);
	ajto(-90-ajtof4,8.99,2.7,5.8);
	
	ajto2(-90-ajtof3,8.99,0.5,-1.7);
	ajto2(-90-ajtof2,8.99,0.5,0.5);
	ajto2(-90,8.99,0.5,5.8);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionkilincs);

	kilincs(-90-ajtof3,0,8.99,1.5,-1.7);
	kilincs(-90-ajtof2,0,8.99,1.5,0.5);
	kilincs(-90,0,8.99,1.5,5.8);

	kilincs(-90-ajtof1,0,8.99,2.7,-1.7);
	kilincs(-90,0,8.99,2.7,0.5);
	kilincs(-90-ajtof4,0,8.99,2.7,5.8);
//-------------------------------------------------------------------
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_emissionbajto);
	bejaratiajto(90+ajtof5,8.89,1,5.4,mat_emissionkilincs);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionw);
	ajtobuki(-90,8.99,1,4.15,1+(-fer/3),mat_emissionw,mat_emissionwajtokeret);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionasztalagy);
//asztalok
	asztal(0,0,0,0);
  //a.labak
	a_lab(0,1.5,0,0);
	a_lab(0,1.5,0,-1.5);
	a_lab(0,-1.5,0,0);
	a_lab(0,-1.5,0,-1.5);
//-------------------------------------------------------------------
	asztal(0,4.5,0,0);
  //a.labak
	a_lab(0,6,0,0);
	a_lab(0,6,0,-1.5);
	a_lab(0,3,0,0);
	a_lab(0,3,0,-1.5);
//ágyak
	agy(180,-1.5,-1,7.9,mat_emissionasztalagy,mat_emissionmatrac);
	agy(90,1,-1,6.7,mat_emissionasztalagy,mat_emissionmatrac);
//monitor talp
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionmonitor);
  //talpfront
	glColor3f(0.1,0.1,0.1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-0.3,0.05,-1);
	glVertex3f(0.3,0.05,-1);
	glVertex3f(0.2,0.05,-1.8);
	glVertex3f(-0.2,0.05,-1.8);
	glEnd();
  //talptop
	glBegin(GL_QUADS);
	glNormal3d(0,1,0);
	glVertex3f(-0.3,0.05,-1);
	glVertex3f(-0.3,0.03,-1);
	glVertex3f(0.3,0.03,-1);
	glVertex3f(0.3,0.05,-1);
	glEnd();
  //talptarto
	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,1);
	glVertex3f(-0.15,0.05,-1.4);
	glVertex3f(0.15,0.05,-1.4);
	glVertex3f(-0.1,0.2,-1.5);
	glVertex3f(0.1,0.2,-1.5);
	glNormal3d(0,0,1);
	glVertex3f(-0.1,0.4,-1.5);
	glVertex3f(0.1,0.4,-1.5);
	glEnd();

  //monitor
	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,0,1);
	glVertex3f(0.55,0.25,-1.4);
	glVertex3f(0.95,0.25,-1.4);//
	glVertex3f(0.5,0.3,-1.4);
	glVertex3f(1,0.3,-1.4);//
	glVertex3f(-1,0.3,-1.4);
	glVertex3f(1,1.5,-1.4);
	glVertex3f(-1,1.5,-1.4);
	glVertex3f(-1,1.5,-1.4);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3d(1,0,0);
	glVertex3f(1,1.5,-1.4);
	glVertex3f(1,0.3,-1.4);
	glVertex3f(1,0.3,-1.45);
	glVertex3f(1,1.5,-1.45);

	glNormal3d(1,-1,0);
	glVertex3f(1,0.3,-1.4);
	glVertex3f(0.95,0.25,-1.4);
	glVertex3f(0.95,0.25,-1.45);
	glVertex3f(1,0.3,-1.45);
	glEnd();
//fény ki
	glDisable(GL_LIGHTING);
//képernyő
	glColor3f(mf,mf,mf);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glBegin(GL_QUADS);
	glNormal3d(0,0,1);
	glVertex3f(-0.9,0.4,-1.39);
	glVertex3f(0.9,0.4,-1.39);
	glVertex3f(0.9,1.4,-1.39);
	glVertex3f(-0.9,1.4,-1.39);
	glEnd();
//kepernyokimelo
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emission);
	glColor3f(1,1,1);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glTranslated(0, 0.9 ,-1.38);
	glRotated(alpha,0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4,0,0);
	glVertex3f(-0.3,-0.3,0);
	glVertex3f(0,-0.4,0);
	glVertex3f(0.3,-0.3,0);
	glVertex3f(0.4,0,0);
	glVertex3f(0.3,0.3,0);
	glVertex3f(0,0.4,0);
	glVertex3f(-0.3,0.3,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.9 ,-1.38);
	glRotated(-alpha,0,0,1);
	glBegin(GL_POLYGON);
	glVertex3f(-0.02,0,0);
	glVertex3f(-0.05,-0.05,0);
	glVertex3f(0,-0.02,0);
	glVertex3f(0.05,-0.05,0);
	glVertex3f(0.02,0,0);
	glVertex3f(0.05,0.05,0);
	glVertex3f(0,0.02,0);
	glVertex3f(-0.05,0.05,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.9 ,-1.38);
	glRotated(-alpha,0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25,0.15,0);
	glVertex3f(-0.25,-0.15,0);
	glVertex3f(0,-0.3,0);
	glVertex3f(0.25,-0.15,0);
	glVertex3f(0.25,0.15,0);
	glVertex3f(0,0.3,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1,1,1);
	glTranslated(0, 0.9 ,-1.38);
	glRotated(alpha,0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.12,-0.12,0);
	glVertex3f(0.12,-0.12,0);
	glVertex3f(0.12,0.12,0);
	glVertex3f(-0.12,0.12,0);
	glEnd();
	glPopMatrix();
//fény be
	glEnable(GL_LIGHTING);
//óra
	ora(90,-alpha/5,-2.99,2.5,3,mat_emissionkeret,mat_emission,mat_emissionmonitor);
//polcok
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emissionpolc);

	polc(0,0,0,0);
	polc(0,4.5,0,0);
	polc(180,3.5,0,6);
//cetlik
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_emission);

	cetli(-10,-1.55);
	cetli(15,-1.3);
	cetli(-20,-1);

   glutSwapBuffers();
}

void timer(int value) {
	alpha += 1;
	if (alpha > 360) {
		//alpha -= 360;
	}

	
	glutPostRedisplay(); 
	glutTimerFunc(25, timer, 0);
}

void specialkey(int key, int x, int y){
	switch(key){
		case GLUT_KEY_F1:
			menu = !menu;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1280,1000);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

    glutCreateWindow("Szoba");
	initRendering();

	Camera.Move( F3dVector(0.0, 0.0, 20 ));
	Camera.MoveForwards( 1.0 );

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
	glutSpecialFunc(specialkey);
	glutTimerFunc(25,timer,0);
	
	glClearColor(0.0,0.0,0.0,1); 

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

    glutMainLoop();

    return 0;
}
