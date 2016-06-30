#pragma once

#include "AbstractBox.h"

class CCheckBox : public IAbstractBox
{
public:
    CCheckBox(const Parameters &parameters);

    void operator()(const std::string &msg);
};