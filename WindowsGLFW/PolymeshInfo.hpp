//
//  PolymeshInfo.h
//  PolymeshScene
//
//  Created by David Reed on 11/23/13.
//  Copyright (c) 2013 David Reed. All rights reserved.
//

#ifndef __PolymeshScene__PolymeshInfo__
#define __PolymeshScene__PolymeshInfo__

#include <iostream>
#include <string>

#include "Angel.h"

class PolymeshInfo {
public:
    std::string filename;
    vec3 scale;
    vec3 rotate;
    vec3 translate;
    vec4 color;
};

inline std::istream& operator>>(std::istream &is, PolymeshInfo &p)
{
    getline(is, p.filename);
    // in case file pointer was at end of previous line then we get a blank line
    if (p.filename == "") {
        // so reread to get next line that contains the actual filename
        getline(is, p.filename);
    }
    is >> p.color;
    is >> p.scale;
    is >> p.rotate;
    is >> p.translate;

    return is;
}

#endif /* defined(__PolymeshScene__PolymeshInfo__) */
