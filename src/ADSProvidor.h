//
// Created by prodigg on 01.02.26.
//
// ReSharper disable once CppMissingIncludeGuard
export module AdsProvidor;

import ProcessDataBuffer;

export class AdsProvidor_t {
public:
AdsProvidor_t(ProcessDataBuffer_t& processDataBuffer);

private:
    ProcessDataBuffer_t& _processDataBuffer;
};