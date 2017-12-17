#define BOOST_TEST_MODULE Most150Message
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <Vector/BLF.h>

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
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedObjectHeader2, 0x33);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x4444444444444444);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0x5555555555555555);

    /* Most150Message */
    BOOST_CHECK_EQUAL(obj->channel, 0x1111);
    BOOST_CHECK_EQUAL(obj->dir, 0x22);
    BOOST_CHECK_EQUAL(obj->reservedMost150Message1, 0x33);
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x44444444);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x55555555);
    BOOST_CHECK_EQUAL(obj->transferType, 0x66);
    BOOST_CHECK_EQUAL(obj->state, 0x77);
    BOOST_CHECK_EQUAL(obj->ackNack, 0x88);
    BOOST_CHECK_EQUAL(obj->reservedMost150Message2, 0x99);
    BOOST_CHECK_EQUAL(obj->crc, 0xAAAA);
    BOOST_CHECK_EQUAL(obj->pAck, 0xBB);
    BOOST_CHECK_EQUAL(obj->cAck, 0xCC);
    BOOST_CHECK_EQUAL(obj->priority, 0xDD);
    BOOST_CHECK_EQUAL(obj->pIndex, 0xEE);
    BOOST_CHECK_EQUAL(obj->msgLen, 3);
    BOOST_CHECK_EQUAL(obj->msg[0], 4);
    BOOST_CHECK_EQUAL(obj->msg[1], 5);
    BOOST_CHECK_EQUAL(obj->msg[2], 6);

    delete ohb;

    /* read next */
    ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_150_MESSAGE);

    delete ohb;

    file.close();
}
