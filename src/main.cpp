#include "System.h"


int main() {
    System systemObject(nullptr);
    systemObject.buildTree();
    return systemObject.execApp();
}
