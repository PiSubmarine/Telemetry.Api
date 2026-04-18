#pragma once

#include "PiSubmarine/Telemetry/Api/Snapshot.h"

namespace PiSubmarine::Telemetry::Api
{
    class ISource
    {
    public:
        virtual ~ISource() = default;

        [[nodiscard]] virtual Snapshot GetSnapshot() const = 0;
    };
}
