#include "gtest/gtest.h"
#include <memory>
#include "core/entitydatabank.h"
#include "data/entitydatapool.h"
#include "data/entitydatamodel.h"
#include "data/photo.h"

#include <QVariant>

class DummyFetcher : public SUCore::AbstractDatafetcher
{
public:
    virtual void cancel() {}

protected:
    virtual void doFetch(const std::vector<SUCore::DataSource_I *>& sources) {
        Q_UNUSED(sources)
    }
};

TEST(TestPhotoDataModel, userdatamodel)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::EntityDataPool_C dataPool;
    SUData::EntityDataModel_C dataModel(dataPool);

    ASSERT_TRUE(dataModel.rowCount() == 0);
    ASSERT_TRUE(dataModel.entityObject(0) == nullptr);

    std::unique_ptr<SUData::Photo_C> photo1 = std::make_unique<SUData::Photo_C>(dataBank, 1, 1, "testphoto", QUrl("testImageUrl"), QUrl("testThumbnailUrl"));
    dataPool.addEntity(std::move(photo1));

    std::unique_ptr<SUData::Photo_C> photo2 = std::make_unique<SUData::Photo_C>(dataBank, 2, 2, "testphoto2", QUrl("testImageUrl2"), QUrl("testThumbnailUrl2"));
    dataPool.addEntity(std::move(photo2));

    ASSERT_EQ(dataModel.rowCount(), 2);
    ASSERT_EQ(dataModel.entityObject(1)->id(), 2);
    ASSERT_EQ(dataModel.data(dataModel.index(1 , 0), static_cast<int>(SUData::EntityDataModel_C::DataRoles::IdRole)).value<ulong>(), 2);
}
