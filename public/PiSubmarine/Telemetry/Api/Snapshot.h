#pragma once

#include <array>
#include <optional>

#include "PiSubmarine/Amperes.h"
#include "PiSubmarine/Meters.h"
#include "PiSubmarine/Motor/Telemetry/Api/State.h"
#include "PiSubmarine/NormalizedFraction.h"

namespace PiSubmarine::Telemetry::Api
{
    struct Snapshot
    {
        std::optional<Meters> Depth;
        std::optional<Meters> DistanceToSeaFloor;
        std::optional<NormalizedFraction> BatteryStateOfCharge;
        std::optional<Amperes> BatteryCurrent;
        std::array<Motor::Telemetry::Api::State, 4> Thrusters{};
        std::optional<NormalizedFraction> BallastPosition;

        [[nodiscard]] constexpr bool operator==(const Snapshot& other) const noexcept
        {
            return OptionalMetersEqual(Depth, other.Depth)
                && OptionalMetersEqual(DistanceToSeaFloor, other.DistanceToSeaFloor)
                && OptionalNormalizedFractionEqual(BatteryStateOfCharge, other.BatteryStateOfCharge)
                && OptionalAmperesEqual(BatteryCurrent, other.BatteryCurrent)
                && Thrusters == other.Thrusters
                && OptionalNormalizedFractionEqual(BallastPosition, other.BallastPosition);
        }

    private:
        [[nodiscard]] static constexpr bool OptionalMetersEqual(
            const std::optional<Meters>& left,
            const std::optional<Meters>& right) noexcept
        {
            if (left.has_value() != right.has_value())
            {
                return false;
            }

            return !left.has_value() || left->Value == right->Value;
        }

        [[nodiscard]] static constexpr bool OptionalAmperesEqual(
            const std::optional<Amperes>& left,
            const std::optional<Amperes>& right) noexcept
        {
            if (left.has_value() != right.has_value())
            {
                return false;
            }

            return !left.has_value() || left->Value == right->Value;
        }

        [[nodiscard]] static constexpr bool OptionalNormalizedFractionEqual(
            const std::optional<NormalizedFraction>& left,
            const std::optional<NormalizedFraction>& right) noexcept
        {
            if (left.has_value() != right.has_value())
            {
                return false;
            }

            return !left.has_value() || static_cast<double>(*left) == static_cast<double>(*right);
        }
    };
}
