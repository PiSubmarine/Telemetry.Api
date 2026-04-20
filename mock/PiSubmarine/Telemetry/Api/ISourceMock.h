#pragma once

#include <gmock/gmock.h>

#include "PiSubmarine/Telemetry/Api/ISource.h"

namespace PiSubmarine::Telemetry::Api
{
    class ISourceMock : public ISource
    {
    public:
        MOCK_METHOD((Error::Api::Result<Snapshot>), GetSnapshot, (), (const, override));
    };
}
