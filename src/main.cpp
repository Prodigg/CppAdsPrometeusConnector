#include <iostream>

#include "AdsLib.h"
#include "AdsDevice.h"
#include "AdsVariable.h"

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "ADSProvidor.h"
#include "ProcessDataBuffer.h"
#include "PrometheusEndpoint.h"

using namespace Pistache;


void test(const Rest::Request& request, Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "endpoint is ok\n");
}

int main() {
    ProcessDataBuffer_t processDataBuffer;
    AdsProvidor_t adsProvidor(processDataBuffer,
        {5, 109, 7, 180, 1, 1},
        "plc-raphael.localdomain",
        {192,168,1,126,1,1});

    adsProvidor.addSymbol("NodeRed.bIsLightOn", symbolDataType_t::e_bool, std::chrono::seconds(1));

    PrometheusEndpoint_t endpoint(processDataBuffer, 9081);
    endpoint.addSymbol({prometheusMetricType::UNTYPED, "NodeRed.bIsLightOn", "is the light on\\", "", {{"yo", "h\\i\""}}});

    while (true)
        ;

    //std::string newData;
    // while (true) {
    //     processDataBuffer.getSymbolValue("NodeRed.bIsLightOn", newData);
    //     if (std::cin.get() == 'r') {
    //         std::cout << "NodeRed.bIsLightOn: " << newData << std::endl;
    //     }
    // }
/*
    static const AmsNetId remoteNetId{5, 109, 7, 180, 1, 1};
    static constexpr char remoteIpV4[] = "plc-raphael";
    bhf::ads::SetLocalAddress({192,168,1,126,1,1});

    AdsDevice route{ remoteIpV4, remoteNetId, AMSPORT_R0_PLC_TC3 };

    AdsVariable<bool> readVar{ route, "NodeRed.bIsLightOn" };

    std::cout << "NodeRed.bIsLightOn: " << (bool)readVar <<" \n";


    Address addr(Ipv4::any(), Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint endpoint(addr);
    Rest::Router router;

    Rest::Routes::Get(router, "/test", Rest::Routes::bind(&test));

    endpoint.init(opts);
    endpoint.setHandler(router.handler());
    endpoint.serve();
*/


    return 0;
}
