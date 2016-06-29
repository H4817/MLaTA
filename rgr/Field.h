#pragma once

#include "AbstractBox.h"

class CField : public IAbstractBox
{
public:
    CField(const Parameters &parameters);

    void WriteOnField();

private:
    std::string m_str;
};


