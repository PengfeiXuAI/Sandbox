/***********************************************************************
GestureUtility - Functions to process and judge the user gestures.
Copyright (c) 2016 Pengfei Xu

Input pixel set:

------------- x -- size[0] --horizontal----------------
|
|
y
|
size[1]
|
vertical
|
|
-------------------------------------------------------

***********************************************************************/
#include "GestureUtility.h"

template <class PixelParam,class PixelPropertyParam>
void GestureUtility::IntializePixelmap(const unsigned int size[2],
	const PixelParam* frame,
	const PixelPropertyParam& property)
{
    m_gestureRegion = new Region(size);

    for(unsigned int x = 0; x < size[0]; ++x)
    {
        Segment seg(size[1], x);
        m_horizontalSegments.push_back(seg);
    }

    for(unsigned int y = 0; y < size[1]; ++y)
    {
        Segment seg(size[0], y);
        m_verticalSegements.push_back(seg);
    }

    const PixelParam* frameRowPtr=frame;
    for(unsigned int y = 0;y < size[1]; ++y,frameRowPtr+=size[0])
    {
        const PixelParam* framePtr=frameRowPtr;
        std::vector<unsigned int> row;
        for(unsigned int x = 0; x < x<size[0]; ++x)
        {
            if(property(x,y,*framePtr))
            {
                m_gestureRegion.Update(x, y);
                row.push_back(1);

                m_horizontalSegments[x].Update(y);
                m_verticalSegements[y].Update(x);
            }
            else
            {
                row.push_back(0);
            }
        }

        m_pixelmap.push_back(row);
    }

    std::cout<< "Region Top and Bottom with size: " << size[1] << ", " << m_gestureRegion.top << " " << m_gestureRegion.bottom << std::endl;
    std::cout<< "Region Left and Right with size: " << size[0] << ", " << m_gestureRegion.left << " " << m_gestureRegion.right << std::endl;
}

float GestureUtility::GetMinWidth()
{
    float averageWidth = 0.0;
    float averageheight = 0.0;

    for(unsigned int x = m_gestureRegion.left; x <= m_gestureRegion.right; ++x)
    {
        averageWidth += m_horizontalSegments[x].GetLength();
    }

    averageWidth /= m_gestureRegion.right - m_gestureRegion.left + 1;


    for(unsigned int y = m_gestureRegion.top; y <= m_gestureRegion.bottom; ++y)
    {
        averageheight += m_verticalSegements[y].GetLength();
    }

    averageheight /= m_gestureRegion.bottom - m_gestureRegion.top + 1;

    return averageWidth > averageheight ? averageheight : averageWidth;
}

Region GestureUtility::GetEndRegion(unsigned int size[2], float minAverageSegmentLength)
{
    Region endRegion(size);

    // Get the end region
    if(m_gestureRegion.top == 0)
    {
        endRegion.Update(m_gestureRegion.bottom, m_gestureRegion.left);
        endRegion.Update(m_gestureRegion.bottom - (unsigned int)(2 * minAverageSegmentLength), m_gestureRegion.right);
    }

    if(m_gestureRegion.bottom == size[1] - 1)
    {
        endRegion.Update(m_gestureRegion.top, m_gestureRegion.left);
        endRegion.Update(m_gestureRegion.top + (unsigned int)(2 * minAverageSegmentLength), m_gestureRegion.right);
    }

    if(m_gestureRegion.left == 0)
    {
        endRegion.Update(m_gestureRegion.top, m_gestureRegion.left);
        endRegion.Update(m_gestureRegion.bottom, m_gestureRegion.left + (unsigned int)(2 * minAverageSegmentLength));
    }

    if(m_gestureRegion.right == size[0] - 1)
    {
        endRegion.Update(m_gestureRegion.top, m_gestureRegion.right);
        endRegion.Update(m_gestureRegion.bottom, m_gestureRegion.left + (unsigned int)(2 * minAverageSegmentLength));
    }

    return endRegion;
}

bool GestureUtility::IsBoundary(unsigned int y, unsigned int x)
{
    return m_pixelmap[y-1][x] == 0 || m_pixelmap[y + 1][x] == 0
            || m_pixelmap[y][x-1] == 0 || m_pixelmap[y][x+1] == 0;
}

template <class PixelParam,class PixelPropertyParam>
bool GestureUtility::IsFist(const unsigned int size[2],
	const PixelParam* frame,
	const PixelPropertyParam& property)
{
    IntializePixelmap(size, frame, property);

    //TODO: if need, we can use height and width ratio to judge the gesture is slope, vertical or horizontal
    float minAverageSegmentLength = GetMinWidth();
    Region endRegion = GetEndRegion(size, minAverageSegmentLength);

    float endRegionArea = 0.0;
    float endRegionPerimeter = 0.0;

    for(unsigned int y = endRegion.top; y <= endRegion.bottom; ++y)
    {
        if(m_pixelmap[y][m_gestureRegion.left] == 1)
        {
            ++endRegionArea;
            ++endRegionPerimeter;
        }

        if(m_pixelmap[y][m_gestureRegion.right] == 1)
        {
            ++endRegionArea;
            ++endRegionPerimeter;
        }
    }

    for(unsigned int x = endRegion.left; x <= endRegion.right; ++x)
    {
        if(m_pixelmap[m_gestureRegion.top][x] == 1)
        {
            ++endRegionArea;
            ++endRegionPerimeter;
        }

        if(m_pixelmap[m_gestureRegion.bottom][x] == 1)
        {
            ++endRegionArea;
            ++endRegionPerimeter;
        }
    }

    for(unsigned int y = endRegion.top + 1; y <= endRegion.bottom - 1; ++y)
    {
        for(unsigned int x = endRegion.left + 1; x <= endRegion.right - 1; ++x)
        {
            if(m_pixelmap[y][x] == 1)
            {
                ++endRegionArea;

                if(IsBoundary(y, x))
                {
                    ++endRegionPerimeter;
                }
            }
        }
    }

    float areaPerimeterRatio = sqrt(endRegionArea)/endRegionPerimeter; // sqrt(pi * r * r) / (2 * pi * r) = 0.28, sqrt(a * a) / (4 * a) = 0.25

    std::cout<< "areaPerimeterRatio: " << areaPerimeterRatio << std::endl;

    return areaPerimeterRatio >= 0.2;
}
