#define BOOST_TEST_MODULE MostCtrl
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_CTRL = 23 */
BOOST_AUTO_TEST_CASE(MostCtrl)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostCtrl.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_CTRL);
    Vector::BLF::MostCtrl * obj = static_cast<Vector::BLF::MostCtrl *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_CTRL);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 111757000); // ns

    /* MostCtrl */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->dir, 1); // Tx
    // reserved
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x0100);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x0401);
    BOOST_CHECK_EQUAL(obj->msg[ 0], 0x01);
    BOOST_CHECK_EQUAL(obj->msg[ 1], 0x01);
    BOOST_CHECK_EQUAL(obj->msg[ 2], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 3], 0x01);
    BOOST_CHECK_EQUAL(obj->msg[ 4], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 5], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 6], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 7], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 8], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[ 9], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[10], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[11], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[12], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[13], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[14], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[15], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[16], 0x00);
    // reserved
    BOOST_CHECK_EQUAL(obj->rTyp, 0); // Normal
    BOOST_CHECK_EQUAL(obj->rTypAdr, 0); // Device
    BOOST_CHECK_EQUAL(obj->state, 0x50); // TxF|Ack
    // reserved
    BOOST_CHECK_EQUAL(obj->ackNack, 0x12); // NoResp|NAck
    // reserved

    delete obj;

    file.close();
}