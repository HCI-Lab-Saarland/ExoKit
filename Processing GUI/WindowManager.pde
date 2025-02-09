class WindowManager {
  ArrayList<Menu> menus = new ArrayList();
  boolean updated = false;
  String activeMenu;

  WindowManager(String initialMenu) {
    this.activeMenu = initialMenu;
  }
  
  void setActive(String menuName) {
    this.activeMenu = menuName;
    this.updated = false;
  }
  
  void addMenu(Menu m) {
    menus.add(m);
  }
  
  void update() {
    if(updated) {
      return;
    }
    for(Menu m : menus) {
      m.setVisible(false);
    }
    
    for(Menu m : menus) {
      if(m.getName().equalsIgnoreCase(activeMenu)) {
        m.setVisible(true);
      }
    }
    
    updated = true;
  }
  
  Menu getCurrentMenu() {
    for(Menu m : menus) {
      if(m.getName().equalsIgnoreCase(activeMenu)) {
        return m;
      }
    }
    return null;
  }
  
  void clickCommandRun() {
    Menu m = getCurrentMenu();
    if(m == null || !(m instanceof CommandMenu)) {
      return;
    }
    ((CommandMenu) m).onRun();
  }
}
