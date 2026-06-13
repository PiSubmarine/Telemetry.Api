#include <gtest/gtest.h>

#include "PiSubmarine/Error/Api/MakeError.h"
#include "PiSubmarine/Telemetry/Api/IRawSourceMock.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(IRawSourceMockTest, GetRawReturnsConfiguredPayload)
    {
        IRawSourceMock sourceMock;
        const std::vector<std::byte> expectedPayload{
            std::byte{0x10},
            std::byte{0x20},
            std::byte{0x30}};

        EXPECT_CALL(sourceMock, GetRaw())
            .WillOnce(testing::Return(Error::Api::Result<std::vector<std::byte>>(expectedPayload)));

        const auto payload = sourceMock.GetRaw();

        ASSERT_TRUE(payload.has_value());
        EXPECT_EQ(*payload, expectedPayload);
    }

    TEST(IRawSourceMockTest, GetRawCanReportConfiguredError)
    {
        IRawSourceMock sourceMock;
        const auto expectedError = Error::Api::MakeError(Error::Api::ErrorCondition::CommunicationError);

        EXPECT_CALL(sourceMock, GetRaw())
            .WillOnce(testing::Return(std::unexpected(expectedError)));

        const auto payload = sourceMock.GetRaw();

        ASSERT_FALSE(payload.has_value());
        EXPECT_EQ(payload.error(), expectedError);
    }
}
