#include "gtest/gtest.h"

#include "data/user.h"
#include "core/entitydatabank.h"
#include "core/datasource.h"
#include "data/album.h"
#include "data/photo.h"
class DummyFetcher : public SUCore::AbstractDatafetcher
{
public:
    virtual void cancel() {}

protected:
    virtual void doFetch(const std::vector<SUCore::DataSource_I *>& sources) {
        Q_UNUSED(sources)
    }
};

TEST(TestUserData, User)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::User_C user(dataBank, 1, "test", "testUser", "test@test.com");
    ASSERT_EQ(user.id(), 1);
    ASSERT_EQ(user.name(), "test");
    ASSERT_EQ(user.userName(), "testUser");
    ASSERT_EQ(user.email(), "test@test.com");
}

TEST(TestAlbumData, Album)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::Album_C album(dataBank, 1, 1, "testAlbum");
    ASSERT_EQ(album.id(), 1);
    ASSERT_EQ(album.userId(), 1);
    ASSERT_EQ(album.title(), "testAlbum");

}

TEST(TestPhotoData, Album)
{
    DummyFetcher fetcher;
    SUCore::EntityDataBank_C dataBank(&fetcher);
    SUData::Photo_C photo(dataBank, 1, 1, "testPhoto", QUrl("testImageUrl"), QUrl("testThumbnailUrl"));
    ASSERT_EQ(photo.id(), 1);
    ASSERT_EQ(photo.albumId(), 1);
    ASSERT_EQ(photo.title(), "testPhoto");
    ASSERT_EQ(photo.imageUrl().url(), "testImageUrl");
    ASSERT_EQ(photo.thumbnailUrl().url(), "testThumbnailUrl");

}


