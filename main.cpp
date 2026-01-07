#include <iostream>
#include "external/beckhoffAds/beckhoffAds/BeckhoffAds.h"

int main() {
    BeckhoffAds plc;
    //plc.setSource()
    plc.connect("192.168.1.96", 851);
    if (plc.connected()) {
        std::cout << "Connected" << std::endl;
    } else
        std::cout << "Disconnected" << std::endl;

    return 0;
}