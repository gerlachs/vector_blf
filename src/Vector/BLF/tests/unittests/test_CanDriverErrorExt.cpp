#define BOOST_TEST_MODULE CanDriverErrorExt
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* CAN_DRIVER_ERROR_EXT = 74 */
BOOST_AUTO_TEST_CASE(CanDriverErrorExt)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events_from_binlog/test_CanDriverErrorExt.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);
    Vector::BLF::CanDriverErrorExt * obj = static_cast<Vector::BLF::CanDriverErrorExt *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);

    /* ObjectHeader */
    BOOST_CHECK_EQUAL(obj->objectFlags, Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* CanDriverErrorExt */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->txErrors, 0x22);
    BOOST_CHECK_EQUAL(obj->rxErrors, 0x33);
    BOOST_CHECK_EQUAL(obj->errorCode, 0x44444444);
    BOOST_CHECK_EQUAL(obj->flags, 0x55555555);
    BOOST_CHECK_EQUAL(obj->state, 0x66);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt1, 0x77);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt2, 0x8888);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt3[0], 0x99999999);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt3[1], 0xAAAAAAAA);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt3[2], 0xBBBBBBBB);
    BOOST_CHECK_EQUAL(obj->reservedCanDriverErrorExt3[3], 0xCCCCCCCC);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::CAN_DRIVER_ERROR_EXT);

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
