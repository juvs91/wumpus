//
//  Cell.h
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef Cell_H
#define Cell_H

#include "GlutHeader.h"
#include "Texture.h"

#include <stdlib.h>
#include <math.h>
class Cell{
public:
    bool getVisited();
    void draw(Texture texture);
    void setVisited(bool val);
    void setBreeze(bool val);
    void setStench(bool val);
    void init(const float pitProbability,int xIn,int yIn);
    bool getPit();
    void setPosition(int xIn,int yIn);
    void noPit();
    void setGlitter(bool val);
private:
    int x;
    int y;
    bool isVisited;
    bool hasBreeze;
    bool hasStench;
    bool hasGlitter;
    bool hasPit;
    void setPit(const float pitProbability);
    void drawCircle(float radio);
};


#endif /* defined(__Wumpus__Cell__) */
