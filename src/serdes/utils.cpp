/**
 * @file src/serdes/utils.cpp
 * @brief Serialization/Deserialization utils.
 * @copyright (c) 2019 Avast Software, licensed under the MIT license
 */

#include "serdes/utils.h"

namespace retdec {
namespace serdes {

//
//=============================================================================
// Safe (check type and throw exception) JSON value loading methods
//=============================================================================
//

#define SAFE_TEMPLATE(val, name, defaultValue, isF, asF, valStr)      \
	auto x = (name.empty()) ? (val) : (val.get(name, defaultValue));  \
	if (x.isF())                                                      \
	{                                                                 \
		return x.asF();                                               \
	}                                                                 \
	else                                                              \
	{                                                                 \
		std::string n = (name.empty()) ? ("property") : (name);       \
		std::string throwMsg = n + " must be " + valStr + " value";   \
		throw InternalException(throwMsg, x.getOffsetStart());        \
	}

/**
 * If JSON value is not an object value, throw an internal exception.
 * @param val Value to check.
 * @param name Name of the value to check that will be used in a throw message.
 */
void checkJsonValueIsObject(const Json::Value& val, const std::string& name)
{
	if ( val.isNull() || !val.isObject() )
	{
		std::string throwMsg = name + " must be an object value";
		throw InternalException(throwMsg, val.getOffsetStart());
	}
}

Json::Value::Int safeGetInt(
		const Json::Value& val,
		const std::string& name,
		Json::Value::Int defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isInt, asInt, "an int");
}

Json::Value::UInt safeGetUint(
		const Json::Value& val,
		const std::string& name,
		Json::Value::UInt defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isUInt, asUInt, "an uint");
}

Json::Value::UInt64 safeGetUint64(
		const Json::Value& val,
		const std::string& name,
		Json::Value::UInt64 defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isUInt64, asUInt64, "an uint64");
}

double safeGetDouble(
		const Json::Value& val,
		const std::string& name,
		double defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isDouble, asDouble, "a double");
}

std::string safeGetString(
		const Json::Value& val,
		const std::string& name,
		const std::string& defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isString, asString, "a string");
}

bool safeGetBool(
		const Json::Value& val,
		const std::string& name,
		bool defaultValue)
{
	SAFE_TEMPLATE(val, name, defaultValue, isBool, asBool, "a bool");
}

} // namespace serdes
} // namespace retdec
