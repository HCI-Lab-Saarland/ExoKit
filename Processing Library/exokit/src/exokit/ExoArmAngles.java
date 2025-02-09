package exokit;

public class ExoArmAngles {
	
    private boolean hasShoulderBack = false;
    private float shoulderBackAngle = 0;
    private boolean hasShoulderSide = false;
    private float shoulderSideAngle = 0;
    private boolean hasElbow = false;
    private float elbowAngle = 0;

	
	void delShoulderSideAngle() {
	    hasShoulderSide = false;
	}

	void delShoulderBackAngle() {
	    hasShoulderBack = false;
	}

	void delElbowAngle() {
	    hasElbow = false;
	}

	void setElbowAngle(float angle) {
	    hasElbow = true;
	    elbowAngle = angle;
	}

	void setShoulderBackAngle(float angle) {
	    hasShoulderBack = true;
	    shoulderBackAngle = angle;
	}

	void setShoulderSideAngle(float angle) {
	    hasShoulderSide = true;
	    shoulderSideAngle = angle;
	}

	float getElbowAngle() {
	    return elbowAngle;
	}

	float getShoulderBackAngle() {
	    return shoulderBackAngle;
	}

	float getShoulderSideAngle() {
	    return shoulderSideAngle;
	}

	boolean isHasShoulderBack() {
	    return hasShoulderBack;
	}

	boolean isHasShoulderSide() {
	    return hasShoulderSide;
	}

	boolean isHasElbow() {
	    return hasElbow;
	}
	
	String toSerialString() {
		StringBuilder sb = new StringBuilder();
		if(isHasElbow()) {
			sb.append(getElbowAngle());
		} else {
			sb.append("false");
		}
		if(isHasShoulderSide()) {
			sb.append(getShoulderSideAngle());
		} else {
			sb.append("false");
		}
		if(isHasShoulderBack()) {
			sb.append(getShoulderBackAngle());
		} else {
			sb.append("false");
		}
		return sb.toString();
	}
}
