#pragma once

#include <gmock/gmock.h>

#include "PiSubmarine/Telemetry/Api/IRawCache.h"

namespace PiSubmarine::Telemetry::Api
{
    class IRawCacheMock : public IRawCache
    {
    public:
        MOCK_METHOD((Error::Api::Result<std::vector<std::byte>>), GetRaw, (const ChannelId& channel), (const, override));
    };
}
