package exokit;

import processing.serial.Serial;

public class Exokit {
	public enum ArmSide {
		LEFT("left"), RIGHT("right");
		
		final String serialName;
		private ArmSide(String serialName) {
			this.serialName = serialName;
		}
	}
	
	public enum JointType {
		ELBOW("elbow"), SHOULDER_SIDE("shoulderside"), SHOULDER_BACK("shoulderback");
		
		final String serialName;
		private JointType(String serialName) {
			this.serialName = serialName;
		}
	}
	
	public enum JointMovementDirection {
		ABDUCTION_OR_FLEXION("abduction"), ADDUCTION_EXTENSION("adduction"), BOTH("both");
		
		final String serialName;
		private JointMovementDirection(String serialName) {
			this.serialName = serialName;
		}
	}
	
	public enum Gesture {
		WAVE("wave");
		
		final String serialName;
		private Gesture(String serialName) {
			this.serialName = serialName;
		}
	}
	
	public enum MoveToTargetType {
		ABSOLUTE("absolute"), RELATIVE("relative");
		
		final String serialName;
		private MoveToTargetType(String serialName) {
			this.serialName = serialName;
		}
	}
	
	private Serial serial;
	
	Exokit(Serial serial) {
		this.serial = serial;
	}
	
	public void armAmplify(int exoId, ArmSide side, float torquePercentage) {
		armAmplify(exoId, side, torquePercentage, JointMovementDirection.BOTH, 30, 0);
	}
	
	public void armAmplify(int exoId, ArmSide side, float torquePercentage, JointMovementDirection amplifyDirection) {
		armAmplify(exoId, side, torquePercentage, amplifyDirection, 30, 0);
	}
	
	public void armAmplify(int exoId, ArmSide side, float torquePercentage, JointMovementDirection amplifyDirection, int startingVelocity) {
		armAmplify(exoId, side, torquePercentage, amplifyDirection, startingVelocity, 0);
	}
	
	public void armAmplify(int exoId, ArmSide side, float torquePercentage, JointMovementDirection amplifyDirection, int startingVelocity, int maxVelocity) {
		serial.write("armamplify " + exoId + " " + side.serialName + " " + torquePercentage + " " + amplifyDirection.serialName + " " + startingVelocity+ " " + maxVelocity + "\n");
	}
	
	public void armConstrainTo(int exoId, ArmSide side, ExoArmAngles angles, float radius) {
		serial.write("armconstrainto " + exoId + " " + side.serialName + " " + angles.toSerialString() + " " + radius + "\n");
	}
	
	public void armFilterSpeed(int exoId, ArmSide side, float minVelocity, float maxVelocity, JointMovementDirection onDirection) {
		armFilterSpeed(exoId, side, minVelocity, maxVelocity, onDirection, 0.05f, 0.05f, 0.05f, 0.05f);
	}
	
	public void armFilterSpeed(int exoId, ArmSide side, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage) {
		armFilterSpeed(exoId, side, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 0.05f, 0.05f, 0.05f);
	}
	
	public void armFilterSpeed(int exoId, ArmSide side, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage) {
		armFilterSpeed(exoId, side, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 
				resistFlexTorquePercentage, 0.05f, 0.05f);
	}
	
	public void armFilterSpeed(int exoId, ArmSide side, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage, float amplifyExtensionTorquePercentage) {
		armFilterSpeed(exoId, side, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 
				resistFlexTorquePercentage, amplifyExtensionTorquePercentage, 0.05f);
	}
	
	public void armFilterSpeed(int exoId, ArmSide side, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage, float amplifyExtensionTorquePercentage, float  resistExtensionTorquePercentage) {
		serial.write("armfilterspeed " + exoId + " " + side.serialName + " " + minVelocity + " " + maxVelocity + " " + onDirection.serialName + " " + amplifyFlexTorquePercentage
				+ " " + resistFlexTorquePercentage + " " + amplifyExtensionTorquePercentage + " " + resistExtensionTorquePercentage + "\n");
	}
	
	public void armGesture(int exoId, ArmSide side) {
		armGesture(exoId, side, Gesture.WAVE);
	}
	
	public void armGesture(int exoId, ArmSide side, Gesture gesture) {
		serial.write("armgesture " + exoId + " " + side.serialName + " " + gesture.serialName + "\n");
	}
	
	public void armGuideAway(int exoId, ArmSide side, ExoArmAngles armAngles, float radius) {
		armGuideAway(exoId, side, armAngles, radius, 0.05f, 0.05f);
	}
	
	public void armGuideAway(int exoId, ArmSide side, ExoArmAngles armAngles, float radius, float amplifyTorquePercentage) {
		armGuideAway(exoId, side, armAngles, radius, amplifyTorquePercentage, 0.05f);
	}
	
	
	public void armGuideAway(int exoId, ArmSide side, ExoArmAngles armAngles, float radius, float amplifyTorquePercentage, float resistTorquePercentage) {
		serial.write("armguideaway " + exoId + " " + side.serialName + " " + armAngles.toString() + " " + radius + " " + amplifyTorquePercentage + " " + resistTorquePercentage + "\n");
	}
	
	public void armGuideTowards(int exoId, ArmSide side, ExoArmAngles armAngles, float radius) {
		armGuideTowards(exoId, side, armAngles, radius, 0.05f, 0.05f);
	}
	
	public void armGuideTowards(int exoId, ArmSide side, ExoArmAngles armAngles, float radius, float amplifyTorquePercentage) {
		armGuideTowards(exoId, side, armAngles, radius, amplifyTorquePercentage, 0.05f);
	}
	
	
	public void armGuideTowards(int exoId, ArmSide side, ExoArmAngles armAngles, float radius, float amplifyTorquePercentage, float resistTorquePercentage) {
		serial.write("armguidetowards " + exoId + " " + side.serialName + " " + armAngles.toString() + " " + radius + " " + amplifyTorquePercentage + " " + resistTorquePercentage + "\n");
	}
	
	public void armJerk(int exoId, ArmSide side, float minJerkAngle, float maxJerkAngle, int minJerkIntervalMs, int maxJerkIntervalMs, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight) {
		serial.write("armjerk " + exoId + " " + side.serialName + " " + minJerkAngle + " " + maxJerkAngle + " " + minJerkIntervalMs
				+ " " + maxJerkIntervalMs + " " + maxAccumulatedMovementsLeft + " " + maxAccumulatedMovementsRight + "\n");
	}
	
	public void armLock(int exoId, ArmSide side) {
		serial.write("armlock " + exoId + " " + side.serialName + "\n");
	}
	
	public void armMirror(int sourceExoId, ArmSide sourceArmSide, int targetExoId, ArmSide targetArmSide, boolean mirrorElbow, boolean mirrorShoulderSide,
			boolean mirrorShoulderBack) {
		armMirror(sourceExoId, sourceArmSide, targetExoId, targetArmSide, mirrorElbow, mirrorShoulderSide,
				mirrorShoulderBack, 1.0f, 1.0f, 1.0f);
	}
	
	public void armMirror(int sourceExoId, ArmSide sourceArmSide, int targetExoId, ArmSide targetArmSide, boolean mirrorElbow, boolean mirrorShoulderSide,
			boolean mirrorShoulderBack, float scaleFactorElbow) {
		armMirror(sourceExoId, sourceArmSide, targetExoId, targetArmSide, mirrorElbow, mirrorShoulderSide,
				mirrorShoulderBack, scaleFactorElbow, 1.0f, 1.0f);
	}
	
	public void armMirror(int sourceExoId, ArmSide sourceArmSide, int targetExoId, ArmSide targetArmSide, boolean mirrorElbow, boolean mirrorShoulderSide,
			boolean mirrorShoulderBack, float scaleFactorElbow, float scaleFactorShoulderSide) {
		armMirror(sourceExoId, sourceArmSide, targetExoId, targetArmSide, mirrorElbow, mirrorShoulderSide,
				mirrorShoulderBack, scaleFactorElbow, scaleFactorShoulderSide, 1.0f);
	}
	
	public void armMirror(int sourceExoId, ArmSide sourceArmSide, int targetExoId, ArmSide targetArmSide, boolean mirrorElbow, boolean mirrorShoulderSide,
			boolean mirrorShoulderBack, float scaleFactorElbow, float scaleFactorShoulderSide, float scaleFactorShoulderBack) {
		serial.write("armmirror " + sourceExoId + " " + sourceArmSide.serialName + " " + targetExoId + " " + targetArmSide + " " + mirrorElbow + 
				mirrorShoulderSide + " " + mirrorShoulderBack + " " + scaleFactorElbow + " " + scaleFactorShoulderSide + " " + scaleFactorShoulderBack + "\n");
	}
	
	public void armMoveTo(int exoId, ArmSide armSide, ExoArmAngles angles, float velocity) {
		serial.write("armmoveto " + exoId + " " + armSide.serialName + " " + angles.toSerialString() + " " + velocity + "\n");
	}
	
	public void armResist(int exoId, ArmSide side, float torquePercentage) {
		armResist(exoId, side, torquePercentage, JointMovementDirection.BOTH, 0);
	}
	
	public void armResist(int exoId, ArmSide side, float torquePercentage, JointMovementDirection amplifyDirection) {
		armResist(exoId, side, torquePercentage, amplifyDirection, 0);
	}
	
	public void armResist(int exoId, ArmSide side, float torquePercentage, JointMovementDirection resistDirection, int minVelocity) {
		serial.write("armresist " + exoId + " " + side.serialName + " " + torquePercentage + " " + resistDirection.serialName + " " + minVelocity + "\n");
	}
	
	public void armVibrate(int exoId, ArmSide side, int frequency, float amplitude) {
		serial.write("armvibrate " + exoId + " " + side.serialName + " " + frequency + " " + amplitude + "\n");
	}
	
	public void cancelRunningAction() {
		serial.write("cancel" + "\n");
	}
	
	public void jointAmplify(int exoId, ArmSide side, JointType joint, float torquePercentage) {
		jointAmplify(exoId, side, joint, torquePercentage, JointMovementDirection.BOTH, 30, 0);
	}
	
	public void jointAmplify(int exoId, ArmSide side, JointType joint, float torquePercentage, JointMovementDirection amplifyDirection) {
		jointAmplify(exoId, side, joint, torquePercentage, amplifyDirection, 30, 0);
	}
	
	public void jointAmplify(int exoId, ArmSide side, JointType joint, float torquePercentage, JointMovementDirection amplifyDirection, int startingVelocity) {
		jointAmplify(exoId, side, joint, torquePercentage, amplifyDirection, startingVelocity, 0);
	}
	
	public void jointAmplify(int exoId, ArmSide side, JointType joint, float torquePercentage, JointMovementDirection amplifyDirection, int startingVelocity, int maxVelocity) {
		serial.write("jointamplify " + exoId + " " + side.serialName + " " + joint.serialName + " " + torquePercentage + " " 
				+ amplifyDirection.serialName + " " + startingVelocity + " " + maxVelocity + "\n");
	}
	
	public void jointConstrainTo(int exoId, ArmSide side, JointType joint, float angle, float radius) {
		serial.write("jointconstrainto " + exoId + " " + side.serialName + " " + joint.serialName + " " + angle + " " + radius + "\n");
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity) {
		jointFilterSpeed(exoId, side, joint, minVelocity, maxVelocity, JointMovementDirection.BOTH);
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity, JointMovementDirection onDirection) {
		jointFilterSpeed(exoId, side, joint, minVelocity, maxVelocity, onDirection, 0.05f);
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage) {
		jointFilterSpeed(exoId, side, joint, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 0.05f);
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage) {
		jointFilterSpeed(exoId, side, joint, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 
				resistFlexTorquePercentage, 0.05f);
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage, float amplifyExtensionTorquePercentage) {
		jointFilterSpeed(exoId, side, joint, minVelocity, maxVelocity, onDirection, amplifyFlexTorquePercentage, 
				resistFlexTorquePercentage, amplifyExtensionTorquePercentage, 0.05f);
	}
	
	public void jointFilterSpeed(int exoId, ArmSide side, JointType joint, float minVelocity, float maxVelocity, JointMovementDirection onDirection, float amplifyFlexTorquePercentage, 
			float resistFlexTorquePercentage, float amplifyExtensionTorquePercentage, float  resistExtensionTorquePercentage) {
		serial.write("jointfilterspeed " + exoId + " " + side.serialName + " " + joint.serialName + " " + minVelocity + " " + maxVelocity + " " + onDirection.serialName + " " + amplifyFlexTorquePercentage
				+ " " + resistFlexTorquePercentage + " " + amplifyExtensionTorquePercentage + " " + resistExtensionTorquePercentage + "\n");
	}
	
	public void jointGuideAway(int exoId, ArmSide side, JointType joint, float angle, float radius) {
		jointGuideAway(exoId, side, joint, angle, radius, 0.05f);
	}
	
	public void jointGuideAway(int exoId, ArmSide side, JointType joint, float angle, float radius, float amplifyTorquePercentage) {
		jointGuideAway(exoId, side, joint, angle, radius, amplifyTorquePercentage, 0.05f);
	}
	
	public void jointGuideAway(int exoId, ArmSide side, JointType joint, float angle, float radius, float amplifyTorquePercentage, float resistTorquePercentage) {
		serial.write("jointguideaway " + exoId + " " + side.serialName + " " + joint.serialName + " " + angle + " " + radius + " " + amplifyTorquePercentage + " " + resistTorquePercentage + "\n");
	}
	
	public void jointGuideTowards(int exoId, ArmSide side, JointType joint, float angle, float radius) {
		jointGuideTowards(exoId, side, joint, angle, radius, 0.05f);
	}
	
	public void jointGuideTowards(int exoId, ArmSide side, JointType joint, float angle, float radius, float amplifyTorquePercentage) {
		jointGuideTowards(exoId, side, joint, angle, radius, amplifyTorquePercentage, 0.05f);
	}
	
	public void jointGuideTowards(int exoId, ArmSide side, JointType joint, float angle, float radius, float amplifyTorquePercentage, float resistTorquePercentage) {
		serial.write("jointguidetowards " + exoId + " " + side.serialName + " " + joint.serialName + " " + angle + " " + radius + " " + amplifyTorquePercentage + " " + resistTorquePercentage + "\n");
	}
	
	public void jointJerk(int exoId, ArmSide side, JointType joint, float minJerkAngle, float maxJerkAngle, int minJerkIntervalMs, int maxJerkIntervalMs, float maxAccumulatedMovementsLeft, float maxAccumulatedMovementsRight) {
		serial.write("jointjerk " + exoId + " " + side.serialName + " " + joint.serialName + " " + minJerkAngle + " " + maxJerkAngle + " " + minJerkIntervalMs
				+ " " + maxJerkIntervalMs + " " + maxAccumulatedMovementsLeft + " " + maxAccumulatedMovementsRight + "\n");
	}
	
	public void jointLock(int exoId, ArmSide side, JointType joint) {
		serial.write("jointlock " + exoId + " " + side.serialName + " " + joint.serialName + "\n");
	}
	
	public void jointMirror(int sourceExoId, ArmSide sourceSide, JointType sourceJoint, int targetExoId, ArmSide targetSide, JointType targetJoint, float velocity) {
		jointMirror(sourceExoId, sourceSide, sourceJoint, targetExoId, targetSide, targetJoint, velocity, 1.0f);
	}
	
	public void jointMirror(int sourceExoId, ArmSide sourceSide, JointType sourceJoint, int targetExoId, ArmSide targetSide, JointType targetJoint, float velocity, float scaleFactor) {
		serial.write("jointmirror " + sourceExoId + " " + sourceSide.serialName + " " + sourceJoint.serialName + " " + targetExoId + " " + targetSide.serialName + " " + targetJoint.serialName + " " + velocity + " " + scaleFactor + "\n");
	}
	
	public void jointMoveTo(int exoId, ArmSide side, JointType joint, float angle, float velocity, MoveToTargetType targetType) {
		serial.write("jointmoveto " + exoId + " " + side.serialName + " " + joint.serialName + " " + angle + " " + velocity + " " + targetType + "\n");
	}
	
	public void jointResist(int exoId, ArmSide side, JointType joint, float torquePercentage) {
		jointResist(exoId, side, joint, torquePercentage, JointMovementDirection.BOTH);
	}
	
	public void jointResist(int exoId, ArmSide side, JointType joint, float torquePercentage, JointMovementDirection resistDirection) {
		jointResist(exoId, side, joint, torquePercentage, resistDirection, 0.f);
	}
	
	public void jointResist(int exoId, ArmSide side, JointType joint, float torquePercentage, JointMovementDirection resistDirection, float minVelocity) {
		serial.write("jointresist " + exoId + " " + side.serialName + " " + joint.serialName + " " + torquePercentage + " " + resistDirection.serialName + " " + minVelocity + "\n");
	}
	
	public void jointVibrate(int exoId, ArmSide side, JointType joint, int frequence, float amplitude) {
		serial.write("jointvibrate " + exoId + " " + side.serialName + " " + joint.serialName + " " + frequence + " " + amplitude + "\n");
	}

}
