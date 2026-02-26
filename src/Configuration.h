//
// Created by prodigg on 24.02.26.
//

#ifndef CPPADSPROMETEUSCONNECTOR_CONFIGURATION_H
#define CPPADSPROMETEUSCONNECTOR_CONFIGURATION_H
#include <cstdint>
#include <string>
#include "ADSProvidor.h"
#include "PrometheusEndpoint.h"

/*
 * Config formate:
 * global {
 *      localNetId <localNetID>
 *      remoteNetId <remoteNetID>
 *      remoteIPv4 <remoteIPv4>
 *      httpPort <httpPort>
 * }
 *
 *
 * <symbolADSName> {
 * [optional] alias <aliasName>
 * [optional] type <untyped|counter|gauge>
 * [optional] description <description>
 * ADSDatatype <datatypes>
 * scrapingTime <timeInS>
 * [optional] labels {
 *          <labelName> {
 *              value <value>
 *          }
 *          <labelName> {
 *              value <value>
 *          }
 *          ...
 *      }
 * }
 * ...
 *
*/

struct ConfigNetId {
    uint8_t _1;
    uint8_t _2;
    uint8_t _3;
    uint8_t _4;
    uint8_t _5;
    uint8_t _6;
};

/*!
 * @brief this class is for reading the configuration and applying it to the classes.
 */
class config_t {
public:
    void readConfig(std::string fileName);
    [[nodiscard]] inline ConfigNetId getLocalNetId() const {return localNetId;}
    [[nodiscard]] inline ConfigNetId getRemoteNetId() const {return remoteNetId;}
    [[nodiscard]] inline std::string getRemoteIp() const {return remoteIp;};
    [[nodiscard]] inline uint16_t getHttpPort() const {return httpPort;};

    void configureADSProvidor(AdsProvidor_t& AdsProvidor) const;
    void configurePrometheusEndpoint(PrometheusEndpoint_t& Endpoint) const;

private:
    ConfigNetId localNetId = {};
    ConfigNetId remoteNetId = {};
    std::string remoteIp;
    uint16_t httpPort = 0;

    struct variable_t {
        std::string symbolADSName;
        std::string alias;
        prometheusMetricType metricType = prometheusMetricType::UNTYPED;
        std::string description;
        symbolDataType_t ADSType;
        std::chrono::high_resolution_clock::duration scrapingDuration;
        std::vector<label_t> labels;
    };
    std::vector<variable_t> variables;

};


#endif //CPPADSPROMETEUSCONNECTOR_CONFIGURATION_H