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
    ss << getPrometheusMetricName(metric) << " " << value << "\n";
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

bool PrometheusEndpoint_t::addSymbol(const prometheusMetric_t& metric) {
    if (metric.symbolName.empty())
        return false;
    _metrics.push_back(metric);
    return true;
}

PrometheusEndpoint_t::PrometheusEndpoint_t(ProcessDataBuffer_t& dataBuffer, const uint16_t port) :
    _dataBuffer(dataBuffer),
    addr(Pistache::Ipv4::any(), Pistache::Port(port)),
    endpoint(addr) {
    Pistache::Rest::Routes::Get(router, "/metrics", Pistache::Rest::Routes::bind(&PrometheusEndpoint_t::getData, this));

    endpoint.init(opts);
    endpoint.setHandler(router.handler());
    _thread.emplace(std::jthread(&PrometheusEndpoint_t::threadLoop, this));
}

void PrometheusEndpoint_t::getData(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, generateEndpointData());
}

void PrometheusEndpoint_t::threadLoop(std::stop_token stoken) {
    endpoint.serve();
}