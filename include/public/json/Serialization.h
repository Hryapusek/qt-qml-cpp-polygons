#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "json/json.h"

namespace json
{
    template < class T >
    Json::Value toJson(T &&value)
    {
        return Json::Value(value);
    }
}

#endif
