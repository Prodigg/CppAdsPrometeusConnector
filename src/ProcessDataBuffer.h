//
// Created by prodigg on 22.01.26.
//

// ReSharper disable once CppMissingIncludeGuard not needed due to using modules
export module ProcessDataBuffer;

import <mutex>;
import <string>;
import <unordered_map>;

/*!
 * @brief this class is a storage container between ADS receiver and REST endpoint
 * @details it has a mutex to limit the access of the object, the mutex is blocking.
 */
export class ProcessDataBuffer_t {
public:
    /*!
     * @param value the value that is inserted in the symbol name
     * @param symbolName the symbol name
     */
    void setSymbolValue(std::string_view value, std::string_view symbolName);

    /*!
     * @param symbolName the name of the symbol to get
     * @param value [OUT] the value that is at the symbol name
     */
    void getSymbolValue(std::string_view symbolName, std::string& value);
private:
    std::mutex dataAccess;
    std::unordered_map<std::string, std::string> symbolsValues;
};
