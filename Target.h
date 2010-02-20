#ifndef _TARGET_H
#define _TARGET_H

#include <vector>
#include "Vision/ColorImage.h"

#define THRESHOLD 5

bool angleWithinThreshold(double horAngle);

class Target
{
public:
    double m_majorRadius;
    double m_minorRadius;
    double m_rawScore;
    double m_xPos;
    double m_yPos;
    double m_score;
    double m_rotation;
    double m_xMax;
    double m_horAngle;
    bool m_bothFound;
    
    static vector<Target> FindCircularTargets(ColorImage *image);
    double GetHorizontalAngle();
    void Print();
};

#endif
