import java.util.Map;

class CommandMenu extends Menu {
  String baseCommand;
  Serial serial;
  
  CommandMenu(ControlP5 p5, String name, String baseCommand, Serial serial) {
    super(p5, name);
    this.baseCommand = baseCommand;
    this.serial = serial;
  }
  
  void onRun() {
    String serialCmd = baseCommand;
    boolean valid = true;
    for(RenderGroup g : renderGroups) {
      for(RenderGroup.Component c : g.controllers) {
        if(!c.isArgumentPart) {
          continue;
        }
       
        String parameterVal = getStringValue(c.component);
        if(parameterVal == null) {
          c.component.setColorBackground(0xFFFF0000);
          valid = false;
        } else {
          c.component.setColorBackground(0xFF002D5A);
        }
        serialCmd = serialCmd + " " + parameterVal;
      }
    }
    serialCmd = serialCmd + "\n";
    if(!valid) {
      return;
    }
    System.out.println(serialCmd);
    serial.write(serialCmd);
  }
  
  private String getStringValue(Controller<?> component) {
    float value = component.getValue();
    
    if(component instanceof Numberbox) {
      Numberbox nb = (Numberbox) component;
      float multiplier = nb.getMultiplier();
      if(abs(multiplier - 1.0) < 0.1) {
        return String.valueOf(round(value));
      }
    }
    if(component instanceof Slider) {
      Slider slider = (Slider) component;
      float tickmarks = slider.getTickMarks().size();
      if((abs(round(slider.getMax()) - round(slider.getMin())) + 1) == tickmarks) {
        return String.valueOf(round(value));
      }
    }
    if(component instanceof Textfield) {
      String s = ((Textfield) component).getText();
      if(s.equals("")) {
        return null;
      }
      return s;
    }
    if(component instanceof ButtonBar) {
      ButtonBar bb = (ButtonBar) component;
      for(Object l : bb.getItems()) {
        HashMap hm = (HashMap) l;
        if((boolean) hm.get("selected")) {
          return (String) hm.get("value");
        }
      }
      return null;
    }
    
    return String.valueOf(value);
  }
  
}
