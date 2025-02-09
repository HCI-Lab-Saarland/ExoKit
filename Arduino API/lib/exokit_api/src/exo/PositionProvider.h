#ifndef CHI25_EXOSKELETON_API_POSITIONPROVIDER_H
#define CHI25_EXOSKELETON_API_POSITIONPROVIDER_H


class PositionProvider {
public:
    ~PositionProvider() = default;
    virtual float getPosition() = 0;
};


#endif //CHI25_EXOSKELETON_API_POSITIONPROVIDER_H
