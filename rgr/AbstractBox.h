#include <SFML/Graphics.hpp>
#include <iostream>

class CAbstractBox {
public:
    virtual ~CAbstractBox() = default;

    bool IsCollide();

    bool IsSelected();

protected:
    bool m_isSelected;

};

