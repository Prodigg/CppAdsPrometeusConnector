//
// Created by prodigg on 24.02.26.
//

#include "Configuration.h"

#include <fstream>

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

void config_t::readConfig(std::string fileName) {
    if (fileName.empty()) {
        std::cerr<<"ERROR: Configuration file name is empty"<<std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr<<"ERROR: Could not open configuration file "<<fileName<<std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;


    // i know it isnt a nice solution but it works
    bool inGlobalNamespace = false;
    while (std::getline(file, line)) {

    }
}

void config_t::configureADSProvidor(AdsProvidor_t& AdsProvidor) const {
    for (const variable_t & variable: variables) {
        AdsProvidor.addSymbol(variable.symbolADSName, variable.ADSType, variable.scrapingDuration);
    }
}

void config_t::configurePrometheusEndpoint(PrometheusEndpoint_t& Endpoint) const {
    for (const variable_t & variable: variables) {
        Endpoint.addSymbol({variable.metricType, variable.symbolADSName, variable.description, variable.alias, variable.labels});
    }
}
