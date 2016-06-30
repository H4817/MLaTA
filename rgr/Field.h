#pragma once

#include "AbstractBox.h"

class CField : public IAbstractBox
{
public:
    CField(const Parameters &parameters);

    void WriteOnField();

    const std::string &GetLocalMessage() const;

    void SetLocalMessage(const std::string &localMessage);

private:
    std::string localMessage;
};


