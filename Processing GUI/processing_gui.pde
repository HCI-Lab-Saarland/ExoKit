import processing.serial.*;

import controlP5.*;

String serialPort = "/dev/cu.usbserial-14110";
int serialBaudRate = 115200;
Serial serial;

ControlP5 cp5;
ControlFont font;
ControlFont fontSlider;
public color myColoRect = color(88, 111, 124);
public color myColorBackground = #0d162a;
public color secondaryColor = color(88, 111, 124);
public color textColor = #E0E1DD;

public int uiSizeY = 600;
public int uiSizeX = uiSizeY * 16 / 9;
public int buttonMargin = 35;
public int buttonSizeY = 45;
public int nrButtonsX = 2;

WindowManager wManager = new WindowManager("ExoKit GUI");


void setup() {
  serial = new Serial(this, serialPort, serialBaudRate);
  size(600 * 16 / 9, 600);
  noStroke();
  textSize(64);
  
  cp5 = new ControlP5(this);
  PFont pfont = createFont("Arial", 10, true);
  font = new ControlFont(pfont, 15);
  fontSlider = new ControlFont(pfont, 13);
  fill(textColor);
  
  surface.setTitle("ExoKit GUI");
 
  genBtn("armAmplifyBtn", "Arm: Amplify");
  genBtn("armConstrainBtn", "Arm: Constrain To");
  genBtn("armFilterSpeed", "Arm: Filter Speed");
  genBtn("armGesture", "Arm: Gesture");
  genBtn("armGuideAway", "Arm: Guide Away");
  genBtn("armGuideTowards", "Arm: Guide Towards");
  genBtn("armJerk", "Arm: Add Jerks");
  genBtn("armLock", "Arm: Lock");
  genBtn("armMirror", "Arm: Mirror");
  genBtn("armMoveTo", "Arm: Move to");
  genBtn("armResist", "Arm: Resist");
  genBtn("armVibrate", "Arm: Vibrate");
  genBtn("jointAmplify", "Joint: Amplify");
  genBtn("jointConstrain", "Joint: Constrain To");
  genBtn("jointFilterSpeed", "Joint: Filter Speed");
  genBtn("jointGuideAway", "Joint: Guide Away");
  genBtn("jointGuideTowards", "Joint: Guide Towards");
  genBtn("jointJerk", "Joint: Add Jerks");
  genBtn("jointLock", "Joint: Lock");
  genBtn("jointMirror", "Joint: Mirror");
  genBtn("jointMoveTo", "Joint: Move to");
  genBtn("jointResist", "Joint: Resist");
  genBtn("jointVibrate", "Joint: Vibrate");
  genBtn("goBack", "Go Back");
  genBtn("run", "Run");
  genBtn("cancel", "Cancel").onClick((x) -> {
    System.out.println("cancel");
    serial.write("cancel\n");
  }).setColorBackground(0xFFFF0000);
  
  cp5.addTextfield("exoId")
      .setFont(font)
      .setInputFilter(ControlP5.INTEGER)
      .setCaptionLabel("Exoskeleton ID");
  cp5.addButtonBar("armSide")
      .setFont(font)
      .addItem("Arm side: Left", "left")
      .addItem("Right", "right");
  genSlider("amplifyPercentage", "Amplifying torque (%)", 0, 1, 0.1, 100);
  genSlider("resistPercentage", "Resisting torque (%)", 0, 1, 0.1, 100);
  genSlider("amplifyFlexPercentage", "Amplifying torque (%) during abduction/flexion", 0, 1, 0.1, 100);
  genSlider("resistFlexPercentage", "Resisting torque (%) during abduction/flexion", 0, 1, 0.1, 100);
  genSlider("amplifyExtensionPercentage", "Amplifying torque (%) during adduction/extension", 0, 1, 0.1, 100);
  genSlider("resistExtensionPercentage", "Resisting torque (%) during adduction/extension", 0, 1, 0.1, 100);
  cp5.addButtonBar("jointMoveDirection")
      .setFont(font)
      .addItem("Direction: Both", "both")
      .addItem("Abd./Flex.", "abduction")
      .addItem("Add./Ext.", "adduction")
      .setCaptionLabel("jointMoveDirection")
      .setLabel("jointMoveDirection")
      .changeItem("Direction: Both",  "selected" , true);
  cp5.addButtonBar("joint")
      .setFont(font)
      .addItem("Joint: Elbow", "elbow")
      .addItem("Shoulder side", "shoulderside")
      .addItem("Shoulder back", "shoulderback")
      .setCaptionLabel("joint")
      .setLabel("joint");
  cp5.addButtonBar("targetJoint")
      .setFont(font)
      .addItem("Target: Elbow", "elbow")
      .addItem("Shoulder side", "shoulderside")
      .addItem("Shoulder back", "shoulderback")
      .setCaptionLabel("Target Joint")
      .setLabel("Target Joint");
  cp5.addButtonBar("sourceJoint")
      .setFont(font)
      .addItem("Source: Elbow", "elbow")
      .addItem("Shoulder side", "shoulderside")
      .addItem("Shoulder back", "shoulderback")
      .setCaptionLabel("Source Joint")
      .setLabel("Source Joint");
  cp5.addButtonBar("moveToTargetType")
      .setFont(font)
      .addItem("Target Type: Absolute", "absolute")
      .addItem("Relative", "relative")
      .setCaptionLabel("Target Type")
      .setLabel("Target Type")
      .changeItem("Target Type: Absolute",  "selected" , true);
  cp5.addButtonBar("gesture")
      .setFont(font)
      .addItem("Gesture: Wave", "WAVE")
      .setCaptionLabel("Gesture")
      .setValueLabel("Gesture")
      .setLabel("Gesture")
      .changeItem("Gesture: Wave",  "selected" , true);
  genSlider("startingVelocity", "Starting velocity", 0, 180, 0, 181);
  genSlider("minSpeed", "Min. speed (deg/sec)", 0, 180, 30, 181);
  genSlider("maxSpeed", "Max. speed (deg/sec)", 0, 180, 40, 181);
  genSlider("minVelocity", "Min. velocity (deg/sec)", 0, 180, 40, 181);
  genSlider("maxVelocity", "Max. velocity (deg/sec)", 0, 180, 40, 181);
  genSlider("radius", "Radius around angle (deg)", 0, 67, 0, 68);
  genSlider("jointAngle", "Target angle (deg)", -115, 115, 0, 231);
  genSlider("armAngleElbow", "Elbow angle (deg)", 0, 115, 0, 116);
  genSlider("armAngleShoulderSide", "Shoulder side angle (deg)", -20, 115, 0, 136);
  genSlider("armAngleShoulderBack", "Shoulder back angle (deg)", 0, 90, 0, 91);
  genSlider("minJerkAngle", "Min. jerk angle (deg)", 1, 50, 10, 50);
  genSlider("maxJerkAngle", "Max. jerk angle (deg)", 1, 50, 10, 50);
  genSlider("minJerkIntervalMs", "Min. jerk interval (ms)", 1, 5000, 500, 5000);
  genSlider("maxJerkIntervalMs", "Max. jerk interval (ms)", 1, 5000, 1000, 5000);
  genSlider("maxAccumulatedMovementsLeft", "Max. accumulated movements left (deg)", 0, 140, 0, 141);
  genSlider("maxAccumulatedMovementsRight", "Max. accumulated movements right (deg)", 0, 140, 0, 141);
  genSlider("velocity", "Velocity (deg/sec)", 0, 100, 0, 101);
  genSlider("nrJerks", "Number of jerks", 0, 100, 0, 101);
  cp5.addTextfield("targetExoId")
      .setFont(font)
      .setInputFilter(ControlP5.INTEGER)
      .setCaptionLabel("Target exoskeleton ID");
  cp5.addButtonBar("targetArmSide")
      .setFont(font)
      .addItem("Target arm side: left", "left")
      .addItem("right", "right");
  cp5.addTextfield("sourceExoId")
      .setFont(font)
      .setInputFilter(ControlP5.INTEGER)
      .setCaptionLabel("Source exoskeleton ID");
  cp5.addButtonBar("sourceArmSide")
      .setFont(font)
      .addItem("Source arm side: left", "left")
      .addItem("right", "right");
  cp5.addButtonBar("mirrorElbow")
      .setFont(font)
      .addItem("Mirror elbow: true", "true")
      .addItem("false", "false")
      .setCaptionLabel("mirrorElbow")
      .setLabel("mirrorElbow");
  cp5.addButtonBar("mirrorSoulderSide")
      .setFont(font)
      .addItem("Mirror shoulder side: true", "true")
      .addItem("false", "false")
      .setCaptionLabel("mirrorSoulderSide")
      .setLabel("mirrorSoulderSide");
  cp5.addButtonBar("mirrorSoulderBack")
      .setFont(font)
      .addItem("Mirror shoulder back: true", "true")
      .addItem("false", "false")
      .setCaptionLabel("mirrorSoulderBack")
      .setLabel("mirrorSoulderBack");
  genSlider("scaleFactorElbow", "Scale factor elbow", 0, 5, 1, 501);
  genSlider("scaleFactorShoulderSide", "Scale factor shoulder side", 0, 5, 1, 501);
  genSlider("scaleFactorShoulderBack", "Scale factor shoulder back", 0, 5, 1, 501);
  genSlider("scaleFactor", "Scale factor", 0, 5, 1, 501);
  genSlider("frequency", "Frequency (Hz)", 0, 70, 10, 71);
  genSlider("amplitude", "Amplitude (deg)", 0, 20, 2, 21);
        
       
  RenderGroup runAndBack = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 525, 3, buttonSizeY);
  runAndBack.setPadding(buttonMargin);
  runAndBack.addComponent("goBack", (x) -> wManager.setActive("ExoKit GUI"), false);
  runAndBack.addComponent("cancel", null, false);
  runAndBack.addComponent("run", (c) -> wManager.clickCommandRun(), false);
  
  
  Menu mainMenu = new Menu(cp5, "ExoKit GUI");
  wManager.addMenu(mainMenu);
  
  RenderGroup mmGroupArm = new RenderGroup(cp5, buttonMargin, uiSizeX / 2 - buttonMargin, 50, nrButtonsX, buttonSizeY);
  mmGroupArm.setPadding(buttonMargin);
  mainMenu.addGroup(mmGroupArm);
  mmGroupArm.addComponent("armAmplifyBtn", (x) -> wManager.setActive("Amplify (Arm)"));
  mmGroupArm.addComponent("armConstrainBtn", (x) -> wManager.setActive("Constrain To (Arm)"));
  mmGroupArm.addComponent("armFilterSpeed", (x) -> wManager.setActive("Filter Speed (Arm)"));
  mmGroupArm.addComponent("armGesture", (x) -> wManager.setActive("Gesture (Arm)"));
  mmGroupArm.addComponent("armGuideAway", (x) -> wManager.setActive("Guide Away (Arm)"));
  mmGroupArm.addComponent("armGuideTowards", (x) -> wManager.setActive("Guide Towards (Arm)"));
  mmGroupArm.addComponent("armJerk", (x) -> wManager.setActive("Add Jerks (Arm)"));
  mmGroupArm.addComponent("armLock", (x) -> wManager.setActive("Lock (Arm)"));
  mmGroupArm.addComponent("armMirror", (x) -> wManager.setActive("Mirror (Arm)"));
  mmGroupArm.addComponent("armMoveTo", (x) -> wManager.setActive("Move To (Arm)"));
  mmGroupArm.addComponent("armResist", (x) -> wManager.setActive("Resist (Arm)"));
  mmGroupArm.addComponent("armVibrate", (x) -> wManager.setActive("Vibrate (Arm)"));

  RenderGroup mmGroupJoint = new RenderGroup(cp5, uiSizeX / 2 + buttonMargin, uiSizeX - buttonMargin, 50, nrButtonsX, buttonSizeY);
  mmGroupJoint.setPadding(buttonMargin);
  mainMenu.addGroup(mmGroupJoint);
  mmGroupJoint.addComponent("jointAmplify", (x) -> wManager.setActive("Amplify (Joint)"));
  mmGroupJoint.addComponent("jointConstrain", (x) -> wManager.setActive("Constrain To (Joint)"));
  mmGroupJoint.addComponent("jointFilterSpeed", (x) -> wManager.setActive("Filter Speed (Joint)"));
  mmGroupJoint.addComponent("jointGuideAway", (x) -> wManager.setActive("Guide Away (Joint)"));
  mmGroupJoint.addComponent("jointGuideTowards", (x) -> wManager.setActive("Guide Towards (Joint)"));
  mmGroupJoint.addComponent("jointJerk", (x) -> wManager.setActive("Add Jerks (Joint)"));
  mmGroupJoint.addComponent("jointLock", (x) -> wManager.setActive("Lock (Joint)"));
  mmGroupJoint.addComponent("jointMirror", (x) -> wManager.setActive("Mirror (Joint)"));
  mmGroupJoint.addComponent("jointMoveTo", (x) -> wManager.setActive("Move To (Joint)"));
  mmGroupJoint.addComponent("jointResist", (x) -> wManager.setActive("Resist (Joint)"));
  mmGroupJoint.addComponent("jointVibrate", (x) -> wManager.setActive("Vibrate (Joint)"));
  
  RenderGroup mmCancel = new RenderGroup(cp5, uiSizeX / 2 - 175, uiSizeX / 2 + 175, 525, 1, buttonSizeY);
  mmCancel.addComponent("cancel", null);
  mainMenu.addGroup(mmCancel);
    
    
  CommandMenu armAmplifyMenu = new CommandMenu(cp5, "Amplify (Arm)", "armamplify", serial);
  armAmplifyMenu.addGroup(runAndBack);
  wManager.addMenu(armAmplifyMenu);
  
  RenderGroup armAmplifyGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 2, buttonSizeY);
  armAmplifyMenu.addGroup(armAmplifyGroup);
  armAmplifyGroup.setPadding(buttonMargin);
  armAmplifyGroup.addComponent("exoId", null);
  armAmplifyGroup.addComponent("armSide", null);
  armAmplifyGroup.addComponent("amplifyPercentage", null);
  armAmplifyGroup.addComponent("jointMoveDirection", null);
  armAmplifyGroup.addComponent("startingVelocity", null);
  armAmplifyGroup.addComponent("maxVelocity", null);
  
  
  CommandMenu armConstrainMenu = new CommandMenu(cp5, "Constrain To (Arm)", "armconstrainto", serial);
  armConstrainMenu.addGroup(runAndBack);
  wManager.addMenu(armConstrainMenu);
  RenderGroup armConstrainGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armConstrainMenu.addGroup(armConstrainGroup);
  armConstrainGroup.setPadding(buttonMargin);
  armConstrainGroup.addComponent("exoId", null);
  armConstrainGroup.addComponent("armSide", null);
  armConstrainGroup.addComponent("armAngleElbow", null);
  armConstrainGroup.addComponent("armAngleShoulderBack", null);
  armConstrainGroup.addComponent("armAngleShoulderSide", null);
  armConstrainGroup.addComponent("radius", null);
  
  
  CommandMenu armFilterSpeedMenu = new CommandMenu(cp5, "Filter Speed (Arm)", "armfilterspeed", serial);
  armFilterSpeedMenu.addGroup(runAndBack);
  wManager.addMenu(armFilterSpeedMenu);
  RenderGroup armFilterSpeedGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armFilterSpeedGroup.setPadding(buttonMargin);
  armFilterSpeedGroup.addComponent("exoId", null);
  armFilterSpeedGroup.addComponent("armSide", null);
  armFilterSpeedGroup.addComponent("minSpeed", null);
  armFilterSpeedGroup.addComponent("maxSpeed", null);
  armFilterSpeedGroup.addComponent("jointMoveDirection", null);
  armFilterSpeedGroup.addComponent("amplifyFlexPercentage", null);
  armFilterSpeedGroup.addComponent("resistFlexPercentage", null);
  armFilterSpeedGroup.addComponent("amplifyExtensionPercentage", null);
  armFilterSpeedGroup.addComponent("resistExtensionPercentage", null);
  armFilterSpeedMenu.addGroup(armFilterSpeedGroup);
  
  CommandMenu armGestureMenu = new CommandMenu(cp5, "Gesture (Arm)", "armgesture", serial);
  armGestureMenu.addGroup(runAndBack);
  wManager.addMenu(armGestureMenu);
  RenderGroup armGestureGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 1, buttonSizeY);
  armGestureGroup.setPadding(buttonMargin);
  armGestureGroup.addComponent("exoId", null);
  armGestureGroup.addComponent("armSide", null);
  armGestureGroup.addComponent("gesture", null);
  armGestureMenu.addGroup(armGestureGroup);
  
  CommandMenu armGuideAwayMenu = new CommandMenu(cp5, "Guide Away (Arm)", "armguideaway", serial);
  armGuideAwayMenu.addGroup(runAndBack);
  wManager.addMenu(armGuideAwayMenu);
  RenderGroup armGuideAwayGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armGuideAwayGroup.setPadding(buttonMargin);
  armGuideAwayGroup.addComponent("exoId", null);
  armGuideAwayGroup.addComponent("armSide", null);
  armGuideAwayGroup.addComponent("armAngleElbow", null);
  armGuideAwayGroup.addComponent("armAngleShoulderBack", null);
  armGuideAwayGroup.addComponent("armAngleShoulderSide", null);
  armGuideAwayGroup.addComponent("radius", null);
  armGuideAwayGroup.addComponent("amplifyPercentage", null);
  armGuideAwayGroup.addComponent("resistPercentage", null);
  armGuideAwayMenu.addGroup(armGuideAwayGroup);
  
  CommandMenu armGuideTowardsMenu = new CommandMenu(cp5, "Guide Towards (Arm)", "armguidetowards", serial);
  armGuideTowardsMenu.addGroup(runAndBack);
  wManager.addMenu(armGuideTowardsMenu);
  RenderGroup armGuideTowardsGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armGuideTowardsGroup.setPadding(buttonMargin);
  armGuideTowardsGroup.addComponent("exoId", null);
  armGuideTowardsGroup.addComponent("armSide", null);
  armGuideTowardsGroup.addComponent("armAngleElbow", null);
  armGuideTowardsGroup.addComponent("armAngleShoulderBack", null);
  armGuideTowardsGroup.addComponent("armAngleShoulderSide", null);
  armGuideTowardsGroup.addComponent("radius", null);
  armGuideTowardsGroup.addComponent("amplifyPercentage", null);
  armGuideTowardsGroup.addComponent("resistPercentage", null);
  armGuideTowardsMenu.addGroup(armGuideTowardsGroup);
  
  CommandMenu armJerkMenu = new CommandMenu(cp5, "Add Jerks (Arm)", "armjerk", serial);
  armJerkMenu.addGroup(runAndBack);
  wManager.addMenu(armJerkMenu);
  RenderGroup armJerkGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armJerkGroup.setPadding(buttonMargin);
  armJerkGroup.addComponent("exoId", null);
  armJerkGroup.addComponent("armSide", null);
  armJerkGroup.addComponent("minJerkAngle", null);
  armJerkGroup.addComponent("maxJerkAngle", null);
  armJerkGroup.addComponent("minJerkIntervalMs", null);
  armJerkGroup.addComponent("maxJerkIntervalMs", null);
  armJerkGroup.addComponent("maxAccumulatedMovementsLeft", null);
  armJerkGroup.addComponent("maxAccumulatedMovementsRight", null);
  armJerkGroup.addComponent("velocity", null);
  armJerkGroup.addComponent("nrJerks", null);
  armJerkMenu.addGroup(armJerkGroup);
  
  CommandMenu armLockMenu = new CommandMenu(cp5, "Lock (Arm)", "armlock", serial);
  armLockMenu.addGroup(runAndBack);
  wManager.addMenu(armLockMenu);
  RenderGroup armLockGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 1, buttonSizeY);
  armLockGroup.setPadding(buttonMargin);
  armLockGroup.addComponent("exoId", null);
  armLockGroup.addComponent("armSide", null);
  armLockMenu.addGroup(armLockGroup);
  
  CommandMenu armMirrorMenu = new CommandMenu(cp5, "Mirror (Arm)", "armmirror", serial);
  armMirrorMenu.addGroup(runAndBack);
  wManager.addMenu(armMirrorMenu);
  RenderGroup armMirrorGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armMirrorGroup.setPadding(buttonMargin);
  armMirrorGroup.addComponent("targetExoId", null);
  armMirrorGroup.addComponent("targetArmSide", null);
  armMirrorGroup.addComponent("sourceExoId", null);
  armMirrorGroup.addComponent("sourceArmSide", null);
  armMirrorGroup.addComponent("mirrorElbow", null);
  armMirrorGroup.addComponent("mirrorSoulderSide", null);
  armMirrorGroup.addComponent("mirrorSoulderBack", null);
  armMirrorGroup.addComponent("scaleFactorElbow", null);
  armMirrorGroup.addComponent("scaleFactorShoulderSide", null);
  armMirrorGroup.addComponent("scaleFactorShoulderBack", null);
  armMirrorMenu.addGroup(armMirrorGroup);
  
  CommandMenu armMoveToMenu = new CommandMenu(cp5, "Move To (Arm)", "armmoveto", serial);
  armMoveToMenu.addGroup(runAndBack);
  wManager.addMenu(armMoveToMenu);
  RenderGroup armMoveToGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armMoveToGroup.setPadding(buttonMargin);
  armMoveToGroup.addComponent("exoId", null);
  armMoveToGroup.addComponent("armSide", null);
  armMoveToGroup.addComponent("armAngleElbow", null);
  armMoveToGroup.addComponent("armAngleShoulderSide", null);
  armMoveToGroup.addComponent("armAngleShoulderBack", null);
  armMoveToGroup.addComponent("velocity", null);
  armMoveToMenu.addGroup(armMoveToGroup);
  
  CommandMenu armResistMenu = new CommandMenu(cp5, "Resist (Arm)", "armresist", serial);
  armResistMenu.addGroup(runAndBack);
  wManager.addMenu(armResistMenu);
  RenderGroup armResistGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armResistGroup.setPadding(buttonMargin);
  armResistGroup.addComponent("exoId", null);
  armResistGroup.addComponent("armSide", null);
  armResistGroup.addComponent("resistPercentage", null);
  armResistGroup.addComponent("jointMoveDirection", null);
  armResistGroup.addComponent("minVelocity", null);
  armResistMenu.addGroup(armResistGroup);
  
  CommandMenu armVibrateMenu = new CommandMenu(cp5, "Vibrate (Arm)", "armvibrate", serial);
  armVibrateMenu.addGroup(runAndBack);
  wManager.addMenu(armVibrateMenu);
  RenderGroup armVibrateGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  armVibrateGroup.setPadding(buttonMargin);
  armVibrateGroup.addComponent("exoId", null);
  armVibrateGroup.addComponent("armSide", null);
  armVibrateGroup.addComponent("frequency", null);
  armVibrateGroup.addComponent("amplitude", null);
  armVibrateMenu.addGroup(armVibrateGroup);
  
  CommandMenu jointamplifyMenu = new CommandMenu(cp5, "Amplify (Joint)", "jointamplify", serial);
  jointamplifyMenu.addGroup(runAndBack);
  wManager.addMenu(jointamplifyMenu);
  RenderGroup jointamplifyGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointamplifyGroup.setPadding(buttonMargin);
  jointamplifyGroup.addComponent("exoId", null);
  jointamplifyGroup.addComponent("armSide", null);
  jointamplifyGroup.addComponent("joint", null);
  jointamplifyGroup.addComponent("amplifyPercentage", null);
  jointamplifyGroup.addComponent("jointMoveDirection", null);
  jointamplifyGroup.addComponent("startingVelocity", null);
  jointamplifyGroup.addComponent("maxVelocity", null);
  jointamplifyMenu.addGroup(jointamplifyGroup);
  
  CommandMenu jointConstrainMenu = new CommandMenu(cp5, "Constrain To (Joint)", "jointconstrainto", serial);
  jointConstrainMenu.addGroup(runAndBack);
  wManager.addMenu(jointConstrainMenu);
  RenderGroup jointConstrainGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointConstrainMenu.addGroup(jointConstrainGroup);
  jointConstrainGroup.setPadding(buttonMargin);
  jointConstrainGroup.addComponent("exoId", null);
  jointConstrainGroup.addComponent("armSide", null);
  jointConstrainGroup.addComponent("joint", null);
  jointConstrainGroup.addComponent("jointAngle", null);
  jointConstrainGroup.addComponent("radius", null);
  jointConstrainMenu.addGroup(jointConstrainGroup);
  
  CommandMenu jointFilterSpeedMenu = new CommandMenu(cp5, "Filter Speed (Joint)", "jointfilterspeed", serial);
  jointFilterSpeedMenu.addGroup(runAndBack);
  wManager.addMenu(jointFilterSpeedMenu);
  RenderGroup jointFilterSpeedGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointFilterSpeedGroup.setPadding(buttonMargin);
  jointFilterSpeedGroup.addComponent("exoId", null);
  jointFilterSpeedGroup.addComponent("armSide", null);
  jointFilterSpeedGroup.addComponent("joint", null);
  jointFilterSpeedGroup.addComponent("minSpeed", null);
  jointFilterSpeedGroup.addComponent("maxSpeed", null);
  jointFilterSpeedGroup.addComponent("jointMoveDirection", null);
  jointFilterSpeedGroup.addComponent("amplifyFlexPercentage", null);
  jointFilterSpeedGroup.addComponent("resistFlexPercentage", null);
  jointFilterSpeedGroup.addComponent("amplifyExtensionPercentage", null);
  jointFilterSpeedGroup.addComponent("resistExtensionPercentage", null);
  jointFilterSpeedMenu.addGroup(jointFilterSpeedGroup);
  
  CommandMenu jointGuideAwayMenu = new CommandMenu(cp5, "Guide Away (Joint)", "jointguideaway", serial);
  jointGuideAwayMenu.addGroup(runAndBack);
  wManager.addMenu(jointGuideAwayMenu);
  RenderGroup jointGuideAwayGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointGuideAwayGroup.setPadding(buttonMargin);
  jointGuideAwayGroup.addComponent("exoId", null);
  jointGuideAwayGroup.addComponent("armSide", null);
  jointGuideAwayGroup.addComponent("joint", null);
  jointGuideAwayGroup.addComponent("jointAngle", null);
  jointGuideAwayGroup.addComponent("radius", null);
  jointGuideAwayGroup.addComponent("amplifyPercentage", null);
  jointGuideAwayGroup.addComponent("resistPercentage", null);
  jointGuideAwayMenu.addGroup(jointGuideAwayGroup);
  
  CommandMenu jointGuideTowardsMenu = new CommandMenu(cp5, "Guide Towards (Joint)", "jointguidetowards", serial);
  jointGuideTowardsMenu.addGroup(runAndBack);
  wManager.addMenu(jointGuideTowardsMenu);
  RenderGroup jointGuideTowardsGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointGuideTowardsGroup.setPadding(buttonMargin);
  jointGuideTowardsGroup.addComponent("exoId", null);
  jointGuideTowardsGroup.addComponent("armSide", null);
  jointGuideTowardsGroup.addComponent("joint", null);
  jointGuideTowardsGroup.addComponent("jointAngle", null);
  jointGuideTowardsGroup.addComponent("radius", null);
  jointGuideTowardsGroup.addComponent("amplifyPercentage", null);
  jointGuideTowardsGroup.addComponent("resistPercentage", null);
  jointGuideTowardsMenu.addGroup(jointGuideTowardsGroup);
  
  CommandMenu jointJerkMenu = new CommandMenu(cp5, "Add Jerks (Joint)", "jointjerk", serial);
  jointJerkMenu.addGroup(runAndBack);
  wManager.addMenu(jointJerkMenu);
  RenderGroup jointJerkGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 50, nrButtonsX, buttonSizeY);
  jointJerkGroup.setPadding(buttonMargin);
  jointJerkGroup.addComponent("exoId", null);
  jointJerkGroup.addComponent("armSide", null);
  jointJerkGroup.addComponent("joint", null);
  jointJerkGroup.addComponent("minJerkAngle", null);
  jointJerkGroup.addComponent("maxJerkAngle", null);
  jointJerkGroup.addComponent("minJerkIntervalMs", null);
  jointJerkGroup.addComponent("maxJerkIntervalMs", null);
  jointJerkGroup.addComponent("maxAccumulatedMovementsLeft", null);
  jointJerkGroup.addComponent("maxAccumulatedMovementsRight", null);
  jointJerkGroup.addComponent("velocity", null);
  jointJerkGroup.addComponent("nrJerks", null);
  jointJerkMenu.addGroup(jointJerkGroup);
  
  CommandMenu jointLockMenu = new CommandMenu(cp5, "Lock (Joint)", "jointlock", serial);
  jointLockMenu.addGroup(runAndBack);
  wManager.addMenu(jointLockMenu);
  RenderGroup jointLockGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 1, buttonSizeY);
  jointLockGroup.setPadding(buttonMargin);
  jointLockGroup.addComponent("exoId", null);
  jointLockGroup.addComponent("armSide", null);
  jointLockGroup.addComponent("joint", null);
  jointLockMenu.addGroup(jointLockGroup);
  
  CommandMenu jointMirrorMenu = new CommandMenu(cp5, "Mirror (Joint)", "jointmirror", serial);
  jointMirrorMenu.addGroup(runAndBack);
  wManager.addMenu(jointMirrorMenu);
  RenderGroup jointMirrorGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointMirrorGroup.setPadding(buttonMargin);
  jointMirrorGroup.addComponent("targetExoId", null);
  jointMirrorGroup.addComponent("targetArmSide", null);
  jointMirrorGroup.addComponent("targetJoint", null);
  jointMirrorGroup.addComponent("sourceExoId", null);
  jointMirrorGroup.addComponent("sourceArmSide", null);
  jointMirrorGroup.addComponent("sourceJoint", null);
  jointMirrorGroup.addComponent("scaleFactor", null);
  jointMirrorMenu.addGroup(jointMirrorGroup);
    
  CommandMenu jointMoveToMenu = new CommandMenu(cp5, "Move To (Joint)", "jointmoveto", serial);
  jointMoveToMenu.addGroup(runAndBack);
  wManager.addMenu(jointMoveToMenu);
  RenderGroup jointMoveToGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, nrButtonsX, buttonSizeY);
  jointMoveToGroup.setPadding(buttonMargin);
  jointMoveToGroup.addComponent("exoId", null);
  jointMoveToGroup.addComponent("armSide", null);
  jointMoveToGroup.addComponent("joint", null);
  jointMoveToGroup.addComponent("jointAngle", null);
  jointMoveToGroup.addComponent("velocity", null);
  jointMoveToGroup.addComponent("moveToTargetType", null);
  jointMoveToMenu.addGroup(jointMoveToGroup);
  
  CommandMenu jointResistMenu = new CommandMenu(cp5, "Resist (Joint)", "jointresist", serial);
  jointResistMenu.addGroup(runAndBack);
  wManager.addMenu(jointResistMenu);
  RenderGroup jointResistGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 2, buttonSizeY);
  jointResistGroup.setPadding(buttonMargin);
  jointResistGroup.addComponent("exoId", null);
  jointResistGroup.addComponent("armSide", null);
  jointResistGroup.addComponent("joint", null);
  jointResistGroup.addComponent("resistPercentage", null);
  jointResistGroup.addComponent("jointMoveDirection", null);
  jointResistGroup.addComponent("minVelocity", null);
  jointResistMenu.addGroup(jointResistGroup);
  
  CommandMenu jointVibrateMenu = new CommandMenu(cp5, "Vibrate (Joint)", "jointvibrate", serial);
  jointVibrateMenu.addGroup(runAndBack);
  wManager.addMenu(jointVibrateMenu);
  RenderGroup jointVibrateGroup = new RenderGroup(cp5, buttonMargin, uiSizeX - buttonMargin, 75, 2, buttonSizeY);
  jointVibrateGroup.setPadding(buttonMargin);
  jointVibrateGroup.addComponent("exoId", null);
  jointVibrateGroup.addComponent("armSide", null);
  jointVibrateGroup.addComponent("joint", null);
  jointVibrateGroup.addComponent("frequency", null);
  jointVibrateGroup.addComponent("amplitude", null);
  jointVibrateMenu.addGroup(jointVibrateGroup);
  
}


Button genBtn(String handle, String label) {
  return cp5.addButton(handle)
    .setFont(font)
    .setCaptionLabel(label)
    .hide();
}

Slider genSlider(String handle, String label, float min, float max, float defaultValue, int nrTickMarks) {
  Slider slider = cp5.addSlider(handle)
    .setCaptionLabel(label)
    .setFont(fontSlider)
    .setValue(defaultValue)
    .setRange(min, max)
    .setNumberOfTickMarks(nrTickMarks)
    .setTriggerEvent(Slider.RELEASE);
    slider.getCaptionLabel().getStyle().marginTop = 40;
    slider.getCaptionLabel().getStyle().marginLeft = -465;    
  return slider;
}


void draw() {
  background(myColorBackground);
  wManager.update();
  //text("Arm", 410, 200);
  //text("Joint", 1450, 200);
}
