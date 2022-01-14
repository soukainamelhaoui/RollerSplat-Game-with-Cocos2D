
#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class Segment
{
public:
    Vec2 start;
    Vec2 stop;
    float size;
    Segment();
    Segment(Vec2 sr, Vec2 sp);

    //defining positions
     float posx1 ;
     float posx3 ;
     float posx4 ;
     float posy1 ;
     float posy3 ;
     float posy4 ;

    static float coverdDistance;

    // Tracknig Segments

    static std::vector<Segment> segmentsList;
    static std::vector<Segment> ::iterator segmentIterator;


};

#endif 