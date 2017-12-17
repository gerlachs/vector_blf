#define BOOST_TEST_MODULE LinReceiveError
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

/* LIN_RCV_ERROR = 14 */
BOOST_AUTO_TEST_CASE(LinReceiveError)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinReceiveError.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR);
    Vector::BLF::LinReceiveError * obj = static_cast<Vector::BLF::LinReceiveError *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x1111);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x2222222222222222);

    /* LinReceiveError */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->id, 0x22);
    BOOST_CHECK_EQUAL(obj->dlc, 0x33);
    BOOST_CHECK_EQUAL(obj->fsmId, 0x44);
    BOOST_CHECK_EQUAL(obj->fsmState, 0x55);
    BOOST_CHECK_EQUAL(obj->headerTime, 0x66);
    BOOST_CHECK_EQUAL(obj->fullTime, 0x77);
    BOOST_CHECK_EQUAL(obj->stateReason, 0x88);
    BOOST_CHECK_EQUAL(obj->offendingByte, 0x99);
    BOOST_CHECK_EQUAL(obj->shortError, 0xAA);
    BOOST_CHECK_EQUAL(obj->timeoutDuringDlcDetection, 0xBB);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_RCV_ERROR);

    delete ohb;

    file.close();
}
