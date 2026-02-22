//
// Created by prodigg on 23.02.26.
//
#include "PrometheusEndpoint.h"

std::string_view PrometheusEndpoint_t::getPrometheusMetricName(const prometheusMetric_t& metric) {
    return (metric.alias.empty() ? metric.symbolName : metric.alias);
}

std::string PrometheusEndpoint_t::generateHelp(const prometheusMetric_t& metric) {
    if (metric.description.empty())
        return "";
    std::stringstream ss;
    ss << "# HELP " << getPrometheusMetricName(metric) << " " << metric.description << "\n";
    return ss.str();
}

std::string PrometheusEndpoint_t::generateType(const prometheusMetric_t& metric) {
    if (metric.metricType == prometheusMetricType::UNTYPED)
        return "";
    std::stringstream ss;
    ss << "# TYPE " << getPrometheusMetricName(metric) << " ";
    if (metric.metricType == prometheusMetricType::COUNTER)
        ss << "counter";
    else if (metric.metricType == prometheusMetricType::GAUGE)
        ss << "gauge";
    ss << "\n";
    return ss.str();
}

std::string PrometheusEndpoint_t::generateDataLine(const prometheusMetric_t& metric) const {
    std::stringstream ss;
    std::string value;
    _dataBuffer.getSymbolValue(metric.symbolName, value);
    ss << getPrometheusMetricName(metric) << value << "\n";
    return ss.str();
}

std::string PrometheusEndpoint_t::generateEndpointData() const {
    std::stringstream ss;
    for (const prometheusMetric_t & metric: _metrics) {
        ss << generateHelp(metric);
        ss << generateType(metric);
        ss << generateDataLine(metric);
    }
    return ss.str();
}
