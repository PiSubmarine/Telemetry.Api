#pragma once

#include <compare>
#include <string>

namespace PiSubmarine::Telemetry::Api
{
    struct ChannelId
    {
        std::string Value;

        [[nodiscard]] constexpr auto operator<=>(const ChannelId& other) const noexcept = default;
    };
}
