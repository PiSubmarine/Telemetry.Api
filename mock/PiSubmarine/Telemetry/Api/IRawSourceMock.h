#pragma once

#include <gmock/gmock.h>

#include "PiSubmarine/Telemetry/Api/IRawSource.h"

namespace PiSubmarine::Telemetry::Api
{
    class IRawSourceMock : public IRawSource
    {
    public:
        MOCK_METHOD((Error::Api::Result<std::vector<std::byte>>), GetRaw, (), (const, override));
    };
}
