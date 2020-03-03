#include "gtest/gtest.h"

#include "data/user.h"
#include "core/entitydatabank.h"
#include "core/datasource.h"

class DummyFetcher : public SUCore::AbstractDatafetcher
{
public:
    virtual void cancel() {}

protected:
    virtual void doFetch(const std::vector<SUCore::DataSource_I *>& sources) {
        Q_UNUSED(sources)
    }
};

TEST(topk, firstUnique)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::User_C user(dataBank, 1, "test", "testUser", "test@test.com");
    ASSERT_EQ(user.id(), 1);
    ASSERT_EQ(user.name(), "test");
    ASSERT_EQ(user.userName(), "testUser");
    ASSERT_EQ(user.email(), "test@test.com");
}
