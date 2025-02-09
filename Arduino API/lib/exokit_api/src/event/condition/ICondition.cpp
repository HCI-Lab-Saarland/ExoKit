
#include "ICondition.h"
#include "OrCondition.h"
#include "AndCondition.h"
#include "NotCondition.h"
#include "event/simpleactionbuilder/ActionBuilder.h"

ICondition::ICondition(bool requiresConfigure):
    c_requiresConfigure{false}, c_isConfigured{false} {}

bool ICondition::isConfigured() {
    return c_isConfigured || !c_requiresConfigure;
}

bool ICondition::eval() {
    if(!isConfigured()) {
        return false;
    }
    return evalCondition();
}

void ICondition::setConfigured() {
    c_isConfigured = true;
}

bool ICondition::isTimer()
{
    return false;
}

unsigned long ICondition::getTimeout()
{
    return 0;
}

ICondition& ICondition::operator&&(ICondition &other) {
    auto* andCondition = new AndCondition();
    andCondition->configure(*this, other);
    if(this->objectOwner) {
        andCondition->setObjectOwner(this->objectOwner);
    }
    return *andCondition;
}

ICondition& ICondition::operator||(ICondition &other) {
    auto* orCondition = new OrCondition();
    orCondition->configure(*this, other);
    if(this->objectOwner) {
        orCondition->setObjectOwner(this->objectOwner);
    }
    return *orCondition;
}

ICondition& ICondition::operator!() {
    auto* notCondition = new NotCondition();
    notCondition->configure(*this);
    if(this->objectOwner) {
        notCondition->setObjectOwner(this->objectOwner);
    }
    return *notCondition;
}

void ICondition::setObjectOwner(ActionBuilder *objectOwner) {
    if(this->objectOwner) {
        this->objectOwner->unbindOwnerShip(*this);
    }
    if(objectOwner) {
        this->objectOwner = objectOwner;
        this->objectOwner->bindOwnership(*this);
    }
}




