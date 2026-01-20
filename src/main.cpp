#include <iostream>

#include "AdsLib.h"
#include "AdsDevice.h"
#include "AdsVariable.h"

int main() {

    static const AmsNetId remoteNetId{5, 109, 7, 180, 1, 1};
    static constexpr char remoteIpV4[] = "192.168.1.129";
    bhf::ads::SetLocalAddress({192,168,1,126,1,1});

    AdsDevice route{ remoteIpV4, remoteNetId, AMSPORT_R0_PLC_TC3 };

    AdsVariable<bool> readVar{ route, "NodeRed.bIsLightOn" };

    std::cout << "NodeRed.bIsLightOn: " << (bool)readVar <<" \n";

    return 0;
}
