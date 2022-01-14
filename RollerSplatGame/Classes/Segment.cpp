#include "Segment.h"


Segment::Segment() {
    start = Vec2(0,0);
    stop = Vec2(0,0);
    size = 0;
    //positions
    posx1 = 376.875000;
    posx3 = 499.901886;
    posx4 = 561.662720;
    posy1 = 276.875000;
    posy3 = 399.899902;
    posy4 = 461.662628;

}

Segment::Segment(Vec2 sr, Vec2 sp) {
    start = sr;
    stop = sp;
    if (sr.x != sp.x) {
        size = abs(sr.x - sp.x);
    }
    else {
        size = abs(sr.y - sp.y);
    }
    //positions
    posx1 = 376.875000;
    posx3 = 499.901886;
    posx4 = 561.662720;
    posy1 = 276.875000;
    posy3 = 399.899902;
    posy4 = 461.662628;

}

float Segment::coverdDistance = 0;
std::vector<Segment> Segment::segmentsList;

std::vector<Segment> ::iterator Segment::segmentIterator;

