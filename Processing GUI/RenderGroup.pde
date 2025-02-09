class RenderGroup {
  public class Component {
    Controller<?> component;
    CallbackListener listener;
    boolean isArgumentPart;

    Component(Controller<?> component, CallbackListener listener, boolean isArgumentPart) {
      this.component = component;
      this.listener = listener;
      this.isArgumentPart = isArgumentPart;
    }
  }

  ArrayList<Component> controllers = new ArrayList();
  ControlP5 cp5;
  int nrXAxisControllers;
  int componentheight;
  int padding = 0;
  int startX;
  int endX;
  int startY;

  RenderGroup(ControlP5 cp5, int startX, int endX, int startY, int nrXAxisControllers, int componentheight) {
    this.startX = startX;
    this.endX = endX;
    this.startY = startY;
    this.nrXAxisControllers = nrXAxisControllers;
    this.componentheight = componentheight;
    this.cp5 = cp5;
  }

  void setVisible(boolean visible) {
    if (visible) {
      reposition();
    }
    for (Component c : controllers) {
      if (visible) {
        c.component.show();
        //cp5.show(c.component);
        if(c.listener != null) {
          c.component.onClick(c.listener);
        }
      } else {
        c.component.hide();
        if(c.listener != null) {
          c.component.removeListenerFor(ControlP5Constants.ACTION_CLICK, c.listener);
        }
      }
    }
  }

  void setNrXAxisControllers(int val) {
    this.nrXAxisControllers = val;
  }

  void setComponentheight(int val) {
    this.componentheight = val;
  }

  void setPadding(int val) {
    this.padding = val;
  }

  void addComponent(String identifier, CallbackListener listener) {
    addComponent(identifier, listener, true);
  }

  void addComponent(String identifier, CallbackListener listener, boolean isArgumentPart) {
    Controller<?> component = cp5.get(Controller.class, identifier);
    controllers.add(new Component(component, listener, isArgumentPart));
  }

  void reposition() {
    int width = endX - startX;
    int widthComponents = width - (nrXAxisControllers * padding);
    int widthComponent = widthComponents / nrXAxisControllers;
    for (int i = 0; i < controllers.size(); i++) {
      Controller<?> c = controllers.get(i).component;
           int row = i / nrXAxisControllers;
      int col = i % nrXAxisControllers;

      //int col = i < (controllers.size()/nrXAxisControllers)? 0 : 1;
      //int row = i < floor((float(controllers.size())/float(nrXAxisControllers)))? i : (i % floor((float(controllers.size())/float(nrXAxisControllers))));
      //int col = i / ceil(float(controllers.size())/float(nrXAxisControllers));

      c.setPosition(startX + col * (widthComponent + padding), startY + row * (componentheight + padding));
      c.setSize(widthComponent, componentheight);
    }
  }
}
