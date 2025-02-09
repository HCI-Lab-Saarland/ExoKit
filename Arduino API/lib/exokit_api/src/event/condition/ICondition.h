
#ifndef ICONDITION_H
#define ICONDITION_H


class ICondition;
class ActionBuilder;

class ICondition
{
private:
    bool c_requiresConfigure;
    bool c_isConfigured;
    ActionBuilder* objectOwner;
protected:
    void setConfigured();
    virtual bool evalCondition() = 0;
public:
    explicit ICondition(bool requiresConfigure = false);
    virtual ~ICondition() = default;
    void setObjectOwner(ActionBuilder* objectOwner);
    bool eval();
    bool isConfigured();
    virtual void restore() = 0;
    virtual bool isTimer();
    virtual unsigned long getTimeout();

    ICondition& operator&&(ICondition& other);
    ICondition& operator||(ICondition& other);
    ICondition& operator!();
};




#endif //ICONDITION_H
