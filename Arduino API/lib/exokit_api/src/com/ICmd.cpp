#include "ICmd.h"

String ICmd::getIdentifier() {
    String usage = getUsage();
    int endIdentifier = usage.indexOf(' ');
    if(endIdentifier < 0) {
        return usage;
    }
    return usage.substring(0, endIdentifier);
}

