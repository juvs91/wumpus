//
//  Arrow.h
//  Wumpus
//
//  Created by juvs on 4/7/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef Arrow__H
#define Arrow__H

#include "GlutHeader.h"
class Arrow{
    private:
        int x;
        int y;
        bool isVisible;
    int angleFlecha;
    public:
        void init();
        void setX(int xIn);
        int getX();
        void setY(int yIn);
        int getY();
        void setVisible(bool visibleIn);
        bool getVisible();
        void draw();
    void setAngle(int angle);
    int getAngle();
    
};




#endif /* defined(__Wumpus__Arrow__) */
