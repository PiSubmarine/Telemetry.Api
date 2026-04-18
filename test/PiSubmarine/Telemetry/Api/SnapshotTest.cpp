#include <gtest/gtest.h>

#include "PiSubmarine/Telemetry/Api/Snapshot.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(SnapshotTest, StoresConfiguredTelemetryValues)
    {
        const Snapshot snapshot{
            .Depth = 12.5_m,
            .DistanceToSeaFloor = 0.7_m,
            .BatteryState = Battery::Telemetry::Api::State{
                .PackCurrent = Amperes{-3.2},
                .StateOfCharge = NormalizedFraction(0.85)},
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{
                    .Operational = Motor::Telemetry::Api::OperationalState::Operational,
                    .ActiveFaults = Motor::Telemetry::Api::Faults{},
                    .ActiveWarnings = Motor::Telemetry::Api::Warnings{}},
                Motor::Telemetry::Api::State{
                    .Operational = Motor::Telemetry::Api::OperationalState::Operational,
                    .ActiveFaults = Motor::Telemetry::Api::Faults{},
                    .ActiveWarnings = Motor::Telemetry::Api::Warnings{}},
                Motor::Telemetry::Api::State{
                    .Operational = Motor::Telemetry::Api::OperationalState::Degraded,
                    .ActiveFaults = Motor::Telemetry::Api::Faults::Overtemperature,
                    .ActiveWarnings = Motor::Telemetry::Api::Warnings::Temperature},
                Motor::Telemetry::Api::State{
                    .Operational = Motor::Telemetry::Api::OperationalState::Operational,
                    .ActiveFaults = Motor::Telemetry::Api::Faults{},
                    .ActiveWarnings = Motor::Telemetry::Api::Warnings{}}},
            .BallastPosition = NormalizedFraction(0.35)};

        ASSERT_TRUE(snapshot.Depth.has_value());
        EXPECT_EQ(snapshot.Depth->Value, 12.5);
        ASSERT_TRUE(snapshot.DistanceToSeaFloor.has_value());
        EXPECT_EQ(snapshot.DistanceToSeaFloor->Value, 0.7);
        ASSERT_TRUE(snapshot.BatteryState.has_value());
        EXPECT_EQ(snapshot.BatteryState->PackCurrent.Value, -3.2);
        EXPECT_EQ(static_cast<double>(snapshot.BatteryState->StateOfCharge), 0.85);
        EXPECT_EQ(snapshot.Thrusters[2].Operational, Motor::Telemetry::Api::OperationalState::Degraded);
        ASSERT_TRUE(snapshot.BallastPosition.has_value());
        EXPECT_EQ(static_cast<double>(*snapshot.BallastPosition), 0.35);
    }

    TEST(SnapshotTest, EqualityComparesOptionalTelemetryFieldsByValue)
    {
        const Snapshot left{
            .Depth = 5.0_m,
            .DistanceToSeaFloor = std::nullopt,
            .BatteryState = Battery::Telemetry::Api::State{
                .StateOfCharge = NormalizedFraction(0.50)},
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{}},
            .BallastPosition = NormalizedFraction(0.20)};

        const Snapshot right{
            .Depth = 5.0_m,
            .DistanceToSeaFloor = std::nullopt,
            .BatteryState = Battery::Telemetry::Api::State{
                .StateOfCharge = NormalizedFraction(0.50)},
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{}},
            .BallastPosition = NormalizedFraction(0.20)};

        EXPECT_EQ(left, right);
    }
}
