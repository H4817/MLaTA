#include "Field.h"

CField::CField(const Parameters &parameters)
{

}

void CField::WriteOnField()
{

}

const std::string &CField::GetLocalMessage() const
{
    return localMessage;
}

void CField::SetLocalMessage(const std::string &localMessage)
{
    CField::localMessage = localMessage;
}