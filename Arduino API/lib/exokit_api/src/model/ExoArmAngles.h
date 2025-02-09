#ifndef CHI25_EXOSKELETON_API_EXOARMANGLES_H
#define CHI25_EXOSKELETON_API_EXOARMANGLES_H
/**
 * A class representing the angles of an exoskeleton arm.
 * 
 * This class manages the angular positions of the three possible active joints in an exoskeleton arm:
 * - Shoulder side (flexion-extension)
 * - Shoulder back (abduction-adduction)
 * - Elbow (flexion-extension)
 * 
 * It provides methods to set, get, and delete angles for these joints, as well as
 * boolean flags to indicate whether an angle has been set.
 */

class ExoArmAngles {
private:
    bool hasShoulderBack{false};
    float shoulderBackAngle{0};
    bool hasShoulderSide{false};
    float shoulderSideAngle{0};
    bool hasElbow{false};
    float elbowAngle{0};
public:
     /**
     * Sets the elbow/shoulder side/shoulder back joint angle.
     * @param angle The new angle of the elbow/shoulder side/shoulder back in degrees.
     */
    void setElbowAngle(float angle);
    void setShoulderBackAngle(float angle);
    void setShoulderSideAngle(float angle);

     /**
     * Gets the previously set elbow/shoulder side/shoulder back joint angle.
     * @return The set angle of the elbow joint/shoulder side/shoulder back in degrees.
     */
    float getElbowAngle();
    float getShoulderBackAngle();
    float getShoulderSideAngle();

    /**
     * Deletes the previously set elbow/shoulder side/shoulder back joint angle.
     */
    void delElbowAngle();
    void delShoulderBackAngle();
    void delShoulderSideAngle();

     /**
     * Checks if an elbow/shoulder side/shoulder back angle has been set.
     * @return True if an elbow/shoulder side/shoulder back has been assigned, false otherwise.
     */
    bool isHasShoulderBack();
    bool isHasShoulderSide();
    bool isHasElbow();
};


#endif //CHI25_EXOSKELETON_API_EXOARMANGLES_H
