/***********************************************************************
GestureUtility - Functions to process and judge the user gestures.
Copyright (c) 2016 Pengfei Xu
***********************************************************************/
#include <cmath>
#include <vector>
#include <iostream>

class Segment
{
public:
    unsigned int min,max, coordinate;
    Segment(unsigned int maxSize, unsigned int c)
    {
        min = maxSize;
        max = 0;
        coordinate = c;
    }

    void Update(unsigned int value)
    {
        if(min > value)
        {
            min = value;
        }

        if(max < value)
        {
            max = value;
        }
    }

    unsigned int GetLength()
    {
        return max - min;
    }
};

class Region
{
public:
    unsigned int top, bottom, left, right;

    Region(unsigned int size[2])
    {
        top = size[1] - 1;
        bottom = 0;

        left = size[0] - 1;
        right = 0;
    }

    void Update(unsigned int x, unsigned int y)
    {
        if(top > y)
        {
            top = y;
        }

        if(bottom < y)
        {
            bottom = y;
        }

        if(left > x)
        {
            left = x;
        }

        if(right < x)
        {
            right = x;
        }
    }
};


class GestureUtility
{
public:
    GestureUtility();
    ~GestureUtility();

    template <class PixelParam,class PixelPropertyParam>
    bool IsFist(const unsigned int size[2], const PixelParam* frame, const PixelPropertyParam& property);

private:
    std::vector<std::vector<unsigned int> > m_pixelmap;
    Region m_gestureRegion;
    std::vector<Segment> m_verticalSegements;
    std::vector<Segment> m_horizontalSegments;

    template <class PixelParam,class PixelPropertyParam>
    void IntializePixelmap(const unsigned int size[2], const PixelParam* frame, const PixelPropertyParam& property);
    bool IsBoundary(unsigned int y, unsigned int x);
    float GetMinWidth();
    Region GetEndRegion(unsigned int size[2], float minAverageSegmentLength);
};
