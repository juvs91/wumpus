//
//  Gold.h
//  Wumpus
//
//  Created by juvs on 3/27/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef Gold_H
#define Gold_H

#include "GlutHeader.h"
#include "Texture.h"

#include <stdlib.h>

class Gold{
public:
    void draw(Texture texture);
    void init(int gridSize);
    int getX();
    int getY();
    
private:
    int x;
    int y;
    void generateNewRandomPosition(int gridSize);
    
};
#endif /* defined(__Wumpus__Gold__) */
