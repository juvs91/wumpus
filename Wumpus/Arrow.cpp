//
//  Arrow.cpp
//  Wumpus
//
//  Created by juvs on 4/7/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#include "Arrow.h"
void Arrow::init(){
    isVisible=false;
    x=0;
    y=0;
}
void Arrow::setX(int xIn){
    x=xIn;
}
int Arrow::getX(){
    return x;
}
void Arrow::setY(int yIn){
    y=yIn;
}
int Arrow::getY(){
    return y;
}
void Arrow::setVisible(bool visibleIn){
    isVisible=visibleIn;
}
bool Arrow::getVisible(){
    return isVisible;
}
void Arrow::setAngle(int angleIn){
    angleFlecha=angleIn;
}
int Arrow::getAngle(){
    return angleFlecha;
}
void Arrow::draw(){
    if (isVisible) {
        glColor3f(1, 1, 1);
        glLineWidth(5);
        glPushMatrix();
        glTranslatef(x+.5, y+.5, 0);
        glRotatef(angleFlecha, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex3f(-.25, 0, 0);
        glVertex3f(.25, .0, 0);
        glEnd();
        glPopMatrix();
        glLineWidth(1);
   
    }
}
