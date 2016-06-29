#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

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
    Parameters m_parameters;
};

