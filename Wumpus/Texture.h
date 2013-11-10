//
//  texture.h
//  Wumpus
//
//  Created by juvs on 4/30/13.
//  Copyright (c) 2013 juvs. All rights reserved.
//

#ifndef texture_H
#define texture_H



#include <iostream>
#include "GlutHeader.h"
#include "Image.h"

class Texture{
    public:
     GLuint getTexName(int k);
     void loadTexture(Image* image,int k);
     void init();
     
    private:
    GLuint texName[10];
    
    
    
};

#endif /* defined(__Wumpus__texture__) */
