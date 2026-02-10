//
// Created by prodigg on 01.02.26.
//
// ReSharper disable once CppMissingIncludeGuard
export module AdsProvidor;

import ProcessDataBuffer;
import <string>;
import <vector>;
import <chrono>;
import <concepts>;
import <type_traits>;
import <thread>;

#include "AdsLib.h"
#include "AdsDevice.h"
#include "AdsVariable.h"
#include "AdsNotificationOOI.h"

export enum class symbolDataType_t {
    e_uint8_t = 0,
    e_uint16_t,
    e_uint32_t,
    e_uint64_t,
    e_int8_t,
    e_int16_t,
    e_int32_t,
    e_int64_t,
    e_float,
    e_double,
    e_bool,
    e_char,
    e_string
};

struct symbolDefinition_t {
    std::string symbolName;
    symbolDataType_t symbolType;

    // max time allowed to wait for value change (manual read required)
    std::chrono::high_resolution_clock::duration expirationDuration;
    std::chrono::high_resolution_clock::time_point lastRead;

    // true, if value is subscribed to
    bool subscribed = false;
    std::optional<AdsNotification> adsNotification;
};

/*! Due to constraints to the callback function, subscribing is currently not implemented
 * This may change if the performance is terrible, and significant effort on optimizations is required
*/

export class AdsProvidor_t {
public:
    explicit AdsProvidor_t(ProcessDataBuffer_t& processDataBuffer, AmsNetId remoteAmsNetId, std::string remoteIPv4, AmsNetId localAmsNetId);
    ~AdsProvidor_t();
    void addSymbol(const std::string& symbolName, symbolDataType_t symbolType, std::chrono::high_resolution_clock::duration scrapingTime);

private:

    static void subscribeSymbols();
    static void unsubscribeSymbols();

    /*!
     * @brief subscribes to symbol
     * @param symbolDefinition symbol to subscribe to
     */
    void subscribeSymbol(symbolDefinition_t& symbolDefinition);

    /*!
     * @brief get from symboltype the size
     * @param symbolType type of symbol
     * @return size of symbol
     */
    static uint32_t mapSymbolTipeToSize(const symbolDataType_t& symbolType );

    /*!
     * @brief is called every time a symbol changes
     * @param addr netId of remote
     * @param notification actual callback data
     * @param user user
     */
    void symbolChangedCallback(const AmsAddr* addr, const AdsNotificationHeader* notification, uint32_t user);

    /*!
     * @brief uses a symbol definition to set the symbol to a new value
     */
    void updateSymbolProcessDataBuffer(symbolDefinition_t& symbolDefinition, std::string value) const;
    void updateSymbolProcessDataBuffer(symbolDefinition_t &symbolDefinition, const char value) const { updateSymbolProcessDataBuffer (symbolDefinition, std::string{value});}
    void updateSymbolProcessDataBuffer(symbolDefinition_t& symbolDefinition, const bool value) const { updateSymbolProcessDataBuffer (symbolDefinition, (value ? std::string("true") : std::string("false"))); }
    template <typename T>
    void updateSymbolProcessDataBuffer(symbolDefinition_t& symbolDefinition, const T value) requires std::is_integral_v<T> || std::is_floating_point_v<T> { updateSymbolProcessDataBuffer (symbolDefinition, std::to_string(value)); }

    /*!
     * @brief this function checks time last read from symbols and reads them if necessary.
     */
    void forceReadSymbol();

    void readSymbol(symbolDefinition_t& symbolDefinition);

    /*!
     * Converts a duration to a time that is n*100ns
     * @param duration duration to convert
     * @return *100ns
     */
    static uint32_t durationToNs(std::chrono::high_resolution_clock::duration duration);

    /*!
     * @brief this is the main thread function
     */
    void threadLoop();

    //! initialize object after calling bhf::ads::SetLocalAddress in the constructor.
    //! expect this variable to ALWAYS have a device.
    std::optional<AdsDevice> _device;

    //! this object should be created in the constructor and destroyed with the destructor
    std::optional<std::jthread> _thread;


    ProcessDataBuffer_t& _processDataBuffer;

    std::mutex _symbolNamesMutex;
    std::vector<symbolDefinition_t> _symbolNames;
};