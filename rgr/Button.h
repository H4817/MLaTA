#include "AbstractBox.h"

class CButton : public IAbstractBox
{
public:
    CButton(const Parameters &parameters);

    void operator()(const std::string &msg);

private:
    enum ButtonState
    {
        PRESSED,
        RELEASED
    };
};


