import exokit.*;

import processing.serial.*;
int serialBaudRate = 115200;
Serial serial;
ExoArmAngles angleConfig1 = new ExoArmAngles();

void setup() {
  /* Insert you correct serial port (serial 2) */
  serial = new Serial(this, "/dev/cu.usbserial-14410", 115200);
  Exokit exo = ExokitLibrary.openConnection(serial);
  
  // lower and Straighten elbow
  exo.jointMoveTo(1, Exokit.ArmSide.RIGHT, Exokit.JointType.ELBOW, 0, 30, Exokit.MoveToTargetType.ABSOLUTE);
  delay(1000);
  exo.jointMoveTo(1, Exokit.ArmSide.RIGHT, Exokit.JointType.SHOULDER_SIDE, 0, 30, Exokit.MoveToTargetType.ABSOLUTE);

  delay(1000);
  
  
}
void draw() {

    
    
}
