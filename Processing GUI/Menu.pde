
class Menu {
  String name;
  ArrayList<RenderGroup> renderGroups = new ArrayList();
  Textlabel label;
  
  Menu(ControlP5 p5, String name) {
    this.name = name;
    PFont pfont = createFont("Arial", 25, true);
    this.label = p5.addTextlabel(name, name, 450, 20).setFont(pfont);
  }
  
  String getName() {
    return name;
  }

  void setVisible(boolean visible) {
    for(RenderGroup g : renderGroups) {
      g.setVisible(visible);    
    }
    if(visible) {
      label.show();
    } else {
      label.hide();
    }
  }
  
  void addGroup(RenderGroup g) {
    renderGroups.add(g);
  }

}
