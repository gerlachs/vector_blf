#define BOOST_TEST_MODULE FlexRayStatusEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FLEXRAY_STATUS = 45 */
BOOST_AUTO_TEST_CASE(FlexRayStatusEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_FlexRayStatusEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_STATUS);
    Vector::BLF::FlexRayStatusEvent * obj = static_cast<Vector::BLF::FlexRayStatusEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FLEXRAY_STATUS);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayStatusEvent */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->version, 0x2222);
    BOOST_CHECK_EQUAL(obj->statusType, 0x3333);
    BOOST_CHECK_EQUAL(obj->infoMask1, 0x4444);
    BOOST_CHECK_EQUAL(obj->infoMask2, 0x5555);
    BOOST_CHECK_EQUAL(obj->infoMask3, 0x6666);
    for (uint16_t i = 0; i < 16; i++) {
        BOOST_CHECK_EQUAL(obj->reservedFlexRayStatusEvent[i], i);
    }
    BOOST_CHECK_EQUAL(obj->reservedFlexRayStatusEvent[16], 0);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayStatusEvent[17], 0);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_STATUS);

    delete ohb;

    file.close();
}
