#pragma once

#include <string>

namespace PiSubmarine::Telemetry::Api
{
    struct ChannelId
    {
        std::string Value;

        [[nodiscard]] constexpr bool operator==(const ChannelId& other) const noexcept = default;
    };
}
