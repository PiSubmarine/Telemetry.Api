#pragma once

#include "PiSubmarine/Error/Api/Result.h"
#include "PiSubmarine/Telemetry/Api/Snapshot.h"

namespace PiSubmarine::Telemetry::Api
{
    class ISource
    {
    public:
        virtual ~ISource() = default;

        [[nodiscard]] virtual Error::Api::Result<Snapshot> GetSnapshot() const = 0;
    };
}
