//
//  Explorer.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#include "Explorer.h"





void Explorer::draw(){
    if (isVisible) {
        glPushMatrix();
            glTranslated(x+.5,y+.5,0);
            glRotated(directionAngle,0,1,0);
            //dibujar el muñeco
            //glutWireTeapot(.4);
            //copy paste del monito explorer
            drawExplorer();
        
            //termina el copy paste
        

        glPopMatrix();
    }
    
    
}

void Explorer::drawExplorer(){
   
    
    
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    glColor3f(0.925, 0.705, 0.42);
    torso();
    glPushMatrix();
    
    //glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glTranslatef(0.0, TORSO_HEIGHT + HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    glColor3f(0.78,0.55,0.25);
    head();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[3], 1.0, 0.0, 0.0);
    glColor3f(0.0,0.0,0.0);
    left_upper_arm();
    
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    glColor3f(0.78,0.55,0.25);
    left_lower_arm();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    glColor3f(0.0,0.0,0.0);
    right_upper_arm();
    
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    glColor3f(0.78,0.55,0.25);
    right_lower_arm();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS-UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], 1.0, 0.0, 0.0);
    glColor3f(0.03,0.29,0.02);
    left_upper_leg();
    
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    glColor3f(0.03,0.29,0.02);
    left_lower_leg();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS -UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], 1.0, 0.0, 0.0);
    glColor3f(0.03,0.29,0.02);
    right_upper_leg();
    
    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    glColor3f(0.03,0.29,0.02);
    right_lower_leg();
    
    glPopMatrix();
    
    glutSwapBuffers();
}



void Explorer::setDirectionAngle(int directionAngleIn){
    directionAngle=directionAngleIn;
}
int Explorer::getX(){
    return x;
}
int Explorer::getY(){
    return y;
}
int Explorer::getDirectionAngle(){
    return directionAngle;
}
void Explorer::setMoveAngles(std::vector<int> moveAnglesIn){
    moveAngles=moveAnglesIn;
}
std::vector<int> Explorer::getMoveAngles(){
    std::vector<int> lista;
    return lista;
}
void Explorer::throwArrow(){
    hasArrow=false;
}
void Explorer::setVisible(bool valIn){
    isVisible=valIn;
}
bool Explorer::getArrow(){
    
    return hasArrow;
    
}
void Explorer::init(){
    std::vector<int> initialMoveAngles={0,0,0,0};
    setPosition(0, 0);
    setDirectionAngle(0);
    setArrow();
    setMoveAngles(initialMoveAngles);
    setVisible(true);
    //lamo a init quadric para inicializar todo los quadrics
    initQuadrics();
    
}
void Explorer::setArrow(){
    hasArrow=true;
}
void Explorer::setPosition(float xIn,float yIn){
    x=xIn;
    y=yIn;
}



//esta funciones son para dibujar el explorador

void Explorer::torso() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,15,15);
    glPopMatrix();
}

void Explorer::head() {
    glPushMatrix();
    glTranslatef(0.0, 0.5*HEAD_HEIGHT,0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}

void Explorer::left_upper_arm() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::left_lower_arm() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::right_upper_arm() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::right_lower_arm() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::left_upper_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::left_lower_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::right_upper_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::right_lower_leg() {
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void Explorer::initQuadrics() {
    GLint estilo=GLU_FILL;
    
    /* allocate quadrics with filled drawing style */
    h=gluNewQuadric();
    gluQuadricDrawStyle(h, estilo);
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, estilo);
    lua=gluNewQuadric();
    gluQuadricDrawStyle(lua, estilo);
    lla=gluNewQuadric();
    gluQuadricDrawStyle(lla, estilo);
    rua=gluNewQuadric();
    gluQuadricDrawStyle(rua, estilo);
    rla=gluNewQuadric();
    gluQuadricDrawStyle(rla, estilo);
    lul=gluNewQuadric();
    gluQuadricDrawStyle(lul, estilo);
    lll=gluNewQuadric();
    gluQuadricDrawStyle(lll, estilo);
    rul=gluNewQuadric();
    gluQuadricDrawStyle(rul, estilo);
    rll=gluNewQuadric();
    gluQuadricDrawStyle(rll, estilo);
}


