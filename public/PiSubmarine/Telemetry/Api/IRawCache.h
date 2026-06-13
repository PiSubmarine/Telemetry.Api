#pragma once

#include <cstddef>
#include <vector>

#include "PiSubmarine/Error/Api/Result.h"
#include "PiSubmarine/Telemetry/Api/ChannelId.h"

namespace PiSubmarine::Telemetry::Api
{
    class IRawCache
    {
    public:
        virtual ~IRawCache() = default;

        [[nodiscard]] virtual Error::Api::Result<std::vector<std::byte>> GetRaw(
            const ChannelId& channel) const = 0;
    };
}
