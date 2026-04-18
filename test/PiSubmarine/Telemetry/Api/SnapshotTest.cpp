#include <gtest/gtest.h>

#include "PiSubmarine/Telemetry/Api/Snapshot.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(SnapshotTest, StoresConfiguredTelemetryValues)
    {
        const Snapshot snapshot{
            .Depth = 12.5_m,
            .DistanceToSeaFloor = 0.7_m,
            .BatteryStateOfCharge = NormalizedFraction(0.85),
            .BatteryCurrent = Amperes{-3.2},
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{
                    .OperationalState = Motor::Telemetry::Api::OperationalState::Operational,
                    .Faults = Motor::Telemetry::Api::Faults{},
                    .Warnings = Motor::Telemetry::Api::Warnings{}},
                Motor::Telemetry::Api::State{
                    .OperationalState = Motor::Telemetry::Api::OperationalState::Operational,
                    .Faults = Motor::Telemetry::Api::Faults{},
                    .Warnings = Motor::Telemetry::Api::Warnings{}},
                Motor::Telemetry::Api::State{
                    .OperationalState = Motor::Telemetry::Api::OperationalState::Degraded,
                    .Faults = Motor::Telemetry::Api::Faults::Overtemperature,
                    .Warnings = Motor::Telemetry::Api::Warnings::Temperature},
                Motor::Telemetry::Api::State{
                    .OperationalState = Motor::Telemetry::Api::OperationalState::Operational,
                    .Faults = Motor::Telemetry::Api::Faults{},
                    .Warnings = Motor::Telemetry::Api::Warnings{}}},
            .BallastPosition = NormalizedFraction(0.35)};

        ASSERT_TRUE(snapshot.Depth.has_value());
        EXPECT_EQ(snapshot.Depth->Value, 12.5);
        ASSERT_TRUE(snapshot.DistanceToSeaFloor.has_value());
        EXPECT_EQ(snapshot.DistanceToSeaFloor->Value, 0.7);
        ASSERT_TRUE(snapshot.BatteryStateOfCharge.has_value());
        EXPECT_EQ(static_cast<double>(*snapshot.BatteryStateOfCharge), 0.85);
        ASSERT_TRUE(snapshot.BatteryCurrent.has_value());
        EXPECT_EQ(snapshot.BatteryCurrent->Value, -3.2);
        EXPECT_EQ(snapshot.Thrusters[2].OperationalState, Motor::Telemetry::Api::OperationalState::Degraded);
        ASSERT_TRUE(snapshot.BallastPosition.has_value());
        EXPECT_EQ(static_cast<double>(*snapshot.BallastPosition), 0.35);
    }

    TEST(SnapshotTest, EqualityComparesOptionalTelemetryFieldsByValue)
    {
        const Snapshot left{
            .Depth = 5.0_m,
            .DistanceToSeaFloor = std::nullopt,
            .BatteryStateOfCharge = NormalizedFraction(0.50),
            .BatteryCurrent = std::nullopt,
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{}},
            .BallastPosition = NormalizedFraction(0.20)};

        const Snapshot right{
            .Depth = 5.0_m,
            .DistanceToSeaFloor = std::nullopt,
            .BatteryStateOfCharge = NormalizedFraction(0.50),
            .BatteryCurrent = std::nullopt,
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{}},
            .BallastPosition = NormalizedFraction(0.20)};

        EXPECT_EQ(left, right);
    }
}
