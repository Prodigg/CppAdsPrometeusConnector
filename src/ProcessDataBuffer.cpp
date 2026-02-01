//
// Created by prodigg on 01.02.26.
//
#include "ProcessDataBuffer.h"

#include <stdexcept>

void ProcessDataBuffer_t::setSymbolValue(const std::string &value, const std::string &symbolName) {
    std::scoped_lock lock (dataAccess);
    if (symbolsValues.contains(symbolName))
        symbolsValues.at(symbolName) = value;
    else
        symbolsValues.emplace(symbolName, value);
}

void ProcessDataBuffer_t::getSymbolValue(const std::string &symbolName, std::string &value) {
    std::scoped_lock lock (dataAccess);
    try {
        value = symbolsValues.at(symbolName);
    } catch (std::out_of_range &ex) {
        value = "NaN";
    }
}