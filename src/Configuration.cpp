//
// Created by prodigg on 24.02.26.
//

#include "Configuration.h"

void config_t::readConfig(std::string fileName) {
    ;
}

void config_t::configureADSProvidor(AdsProvidor_t& AdsProvidor) const {
    for (const variable_t & variable: variables) {
        AdsProvidor.addSymbol(variable.symbolADSName, variable.ADSType, variable.scrapingDuration);
    }
}

void config_t::configurePrometheusEndpoint(PrometheusEndpoint_t& Endpoint) {
    for (const variable_t & variable: variables) {
        Endpoint.addSymbol({variable.metricType, variable.symbolADSName, variable.description, variable.alias, variable.labels});
    }
}