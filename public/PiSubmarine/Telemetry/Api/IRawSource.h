#pragma once

#include <cstddef>
#include <vector>

#include "PiSubmarine/Error/Api/Result.h"

namespace PiSubmarine::Telemetry::Api
{
    class IRawSource
    {
    public:
        virtual ~IRawSource() = default;

        [[nodiscard]] virtual Error::Api::Result<std::vector<std::byte>> GetRaw() const = 0;
    };
}
