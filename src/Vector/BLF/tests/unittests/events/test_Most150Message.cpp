#define BOOST_TEST_MODULE Most150Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_150_MESSAGE = 76 */
BOOST_AUTO_TEST_CASE(Most150Message)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_Most150Message.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);
    Vector::BLF::Most150Message * obj = static_cast<Vector::BLF::Most150Message *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 5708800000); // ns
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* Most150Message */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->dir, 1); // Tx
    // reserved
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x0172);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x03C8);
    BOOST_CHECK_EQUAL(obj->transferType, 1); // Node
    BOOST_CHECK_EQUAL(obj->state, 0x02);
    BOOST_CHECK_EQUAL(obj->ackNack, 0x11); // Ack
    // reserved
    BOOST_CHECK_EQUAL(obj->crc, 0xAABB);
    BOOST_CHECK_EQUAL(obj->pAck, 0x22);
    BOOST_CHECK_EQUAL(obj->cAck, 0x44);
    BOOST_CHECK_EQUAL(obj->priority, 1);
    BOOST_CHECK_EQUAL(obj->pIndex, 0x33);
    BOOST_CHECK_EQUAL(obj->msgLen, 8);
    // reserved
    BOOST_CHECK_EQUAL(obj->msg[0], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[1], 0x22);
    BOOST_CHECK_EQUAL(obj->msg[2], 0x33);
    BOOST_CHECK_EQUAL(obj->msg[3], 0x34);
    BOOST_CHECK_EQUAL(obj->msg[4], 0x00);
    BOOST_CHECK_EQUAL(obj->msg[5], 0x02);
    BOOST_CHECK_EQUAL(obj->msg[6], 0x11);
    BOOST_CHECK_EQUAL(obj->msg[7], 0x22);

    delete obj;

    file.close();
}