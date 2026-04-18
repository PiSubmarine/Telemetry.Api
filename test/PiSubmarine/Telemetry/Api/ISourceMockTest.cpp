#include <gtest/gtest.h>

#include "PiSubmarine/Telemetry/Api/ISourceMock.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(ISourceMockTest, GetSnapshotReturnsConfiguredTelemetry)
    {
        ISourceMock sourceMock;
        const Snapshot expectedSnapshot{
            .Depth = 8.0_m,
            .DistanceToSeaFloor = 0.4_m,
            .BatteryState = Battery::Telemetry::Api::State{
                .PackCurrent = Amperes{-1.5},
                .StateOfCharge = NormalizedFraction(0.65)},
            .Thrusters = std::array<Motor::Telemetry::Api::State, 4>{
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{},
                Motor::Telemetry::Api::State{}},
            .BallastPosition = std::nullopt};

        EXPECT_CALL(sourceMock, GetSnapshot())
            .WillOnce(testing::Return(expectedSnapshot));

        const auto snapshot = sourceMock.GetSnapshot();

        EXPECT_EQ(snapshot, expectedSnapshot);
    }
}
