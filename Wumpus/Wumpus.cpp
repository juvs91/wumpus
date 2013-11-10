//
//  Wumpus.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//
#include <iostream>
#include "Wumpus.h"
void Wumpus::draw(Texture texture){
    GLUquadricObj *qobj;
    
    glColor4f(1.0, 1.0, 1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    if (isAlive) {
        glBindTexture(GL_TEXTURE_2D, texture.getTexName(0));
    }
    else{
        glBindTexture(GL_TEXTURE_2D, texture.getTexName(1));
    }
    qobj=gluNewQuadric();
    glTranslated(x+.5,y+.5,0);
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluSphere(qobj, .4, 20, 20);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
}
void Wumpus::init(int gridSize){
    generateNewRandomPosition(gridSize);
    setAlive();
    
}
bool Wumpus::getAlive(){
    return isAlive;
}
int Wumpus::getX(){
    return x;
}
int Wumpus::getY(){
    return y;
}
void Wumpus::yell(){
    
    char buf[1024];
    snprintf(buf, 1024, "afplay /Users/usuario/Desktop/graficas/Wumpus/Wumpus/wav/grito.wav");
    system(buf);
    std::cout<<"grita";
    
}
void Wumpus::generateNewRandomPosition(int gridSize){
    x=rand()%gridSize;
    y=rand()%gridSize;
    if (x==0 && y==0) {
        generateNewRandomPosition(gridSize);
    }
}
void Wumpus::setAlive(){
    isAlive=true;
}
void Wumpus::killWumpus(){
    isAlive=false;
    yell();
}
