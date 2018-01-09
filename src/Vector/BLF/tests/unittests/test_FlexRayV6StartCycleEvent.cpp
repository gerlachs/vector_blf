#define BOOST_TEST_MODULE FlexRayV6StartCycleEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* FLEXRAY_CYCLE = 40 */
BOOST_AUTO_TEST_CASE(FlexRayV6StartCycleEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_FlexRayV6StartCycleEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_CYCLE);
    Vector::BLF::FlexRayV6StartCycleEvent * obj = static_cast<Vector::BLF::FlexRayV6StartCycleEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::FLEXRAY_CYCLE);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* FlexRayV6StartCycleEvent */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->lowTime, 0x33);
    BOOST_CHECK_EQUAL(obj->fpgaTick, 0x44444444);
    BOOST_CHECK_EQUAL(obj->fpgaTickOverflow, 0x55555555);
    BOOST_CHECK_EQUAL(obj->clientIndexFlexRayV6StartCycleEvent, 0x66666666);
    BOOST_CHECK_EQUAL(obj->clusterTime, 0x77777777);
    BOOST_CHECK_EQUAL(obj->dataBytes[0], 0x88);
    BOOST_CHECK_EQUAL(obj->dataBytes[1], 0x99);
    BOOST_CHECK_EQUAL(obj->reservedFlexRayV6StartCycleEvent, 0xAAAA);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::FLEXRAY_CYCLE);

    delete ohb;

    /* read last */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::Unknown115);

    delete ohb;

    /* read eof */
    BOOST_REQUIRE(!file.eof());
    ohb = file.read();
    BOOST_REQUIRE(ohb == nullptr);
    BOOST_CHECK(file.eof());
    file.close();
}
