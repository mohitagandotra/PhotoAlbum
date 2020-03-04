#include "gtest/gtest.h"
#include <memory>
#include "core/entitydatabank.h"
#include "data/entitydatapool.h"
#include "data/user.h"

class DummyFetcher : public SUCore::AbstractDatafetcher
{
public:
    virtual void cancel() {}

protected:
    virtual void doFetch(const std::vector<SUCore::DataSource_I *>& sources) {
        Q_UNUSED(sources)
    }
};

TEST(TestUserDataPool, userdatapool)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::EntityDataPool_C dataPool;
    ASSERT_TRUE(dataPool.count() == 0);
    ASSERT_TRUE(dataPool.entityAtIndex(0) == nullptr);

    std::unique_ptr<SUData::User_C> user1 = std::make_unique<SUData::User_C>(dataBank, 1, "test", "testUser", "test@test.com");
    dataPool.addEntity(std::move(user1));

    std::unique_ptr<SUData::User_C> user2 = std::make_unique<SUData::User_C>(dataBank, 2, "test2", "testUser2", "test2@test2.com");
    dataPool.addEntity(std::move(user2));

    ASSERT_EQ(dataPool.count(), 2);
    ASSERT_EQ(dataPool.entityAtIndex(1)->id(), 2);
    ASSERT_EQ(static_cast<const SUData::User_C*>(dataPool.entityAtIndex(1))->name(), "test2");
    ASSERT_EQ(static_cast<const SUData::User_C*>(dataPool.entityAtIndex(1))->userName(), "testUser2");
    ASSERT_EQ(static_cast<const SUData::User_C*>(dataPool.entityAtIndex(1))->email(), "test2@test2.com");

}

