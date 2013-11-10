//
//  Gold.cpp
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#include "Gold.h"
void Gold::draw(Texture texture){
    glPushMatrix();
        glTranslated(x+.5,y+.5,0);
        //dibujar el cofre
        glColor4f(1, 1, 0,1);
        glutSolidTeapot(.2);
    glPopMatrix();
}

void Gold::init(int gridSize){
    generateNewRandomPosition(gridSize);
}
void Gold::generateNewRandomPosition(int gridSize){
    x=rand()%gridSize;
    y=rand()%gridSize;
    if (x==0 && y==0) {
        generateNewRandomPosition(gridSize);
    }
}
int Gold::getX(){
    return x;
}
int Gold::getY(){
    return y;
}

