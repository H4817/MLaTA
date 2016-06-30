#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct Color
{
    Color() = default;

    Color(int r, int g, int b)
            : r(r), g(g), b(b)
    { };

    int r = 0;
    int g = 0;
    int b = 0;

    bool operator==(const Color &color)
    {
        return this->r == color.r && this->g == color.g && this->b == color.b;
    }
};

enum State
{
    OWN_MENU,
    OPEN_FILE_FOR_INPUT,
    OPEN_FILE_FOR_OUTPUT,
    GET_HELP
};

struct Parameters
{
    std::pair<int, int> upLeftCoordinates;
    std::pair<int, int> widthAndHeight;
};

class IAbstractBox
{
public:
    virtual ~IAbstractBox() = default;

    virtual void CreateBox() const = 0;

    virtual bool IsMouseOnBox() const = 0;

    virtual bool IsSelected() const = 0;

protected:
    std::string m_string;
    Parameters m_parameters;
    Color m_backgroundColor;
    Color m_lineColor;
    sf::RectangleShape m_rectangle;

};

