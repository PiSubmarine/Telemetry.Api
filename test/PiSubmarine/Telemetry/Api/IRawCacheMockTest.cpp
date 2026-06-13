#include <gtest/gtest.h>

#include "PiSubmarine/Error/Api/MakeError.h"
#include "PiSubmarine/Telemetry/Api/IRawCacheMock.h"

namespace PiSubmarine::Telemetry::Api
{
    TEST(IRawCacheMockTest, GetRawReturnsConfiguredPayload)
    {
        IRawCacheMock cacheMock;
        const ChannelId expectedChannel{.Value = "battery.main"};
        const std::vector<std::byte> expectedPayload{
            std::byte{0x01},
            std::byte{0x02},
            std::byte{0x03}};

        EXPECT_CALL(cacheMock, GetRaw(expectedChannel))
            .WillOnce(testing::Return(Error::Api::Result<std::vector<std::byte>>(expectedPayload)));

        const auto payload = cacheMock.GetRaw(expectedChannel);

        ASSERT_TRUE(payload.has_value());
        EXPECT_EQ(*payload, expectedPayload);
    }

    TEST(IRawCacheMockTest, GetRawCanReportConfiguredError)
    {
        IRawCacheMock cacheMock;
        const ChannelId expectedChannel{.Value = "battery.main"};
        const auto expectedError = Error::Api::MakeError(Error::Api::ErrorCondition::ContractError);

        EXPECT_CALL(cacheMock, GetRaw(expectedChannel))
            .WillOnce(testing::Return(std::unexpected(expectedError)));

        const auto payload = cacheMock.GetRaw(expectedChannel);

        ASSERT_FALSE(payload.has_value());
        EXPECT_EQ(payload.error(), expectedError);
    }
}
