#define BOOST_TEST_MODULE MostPkt2
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* MOST_PKT2 = 33 */
BOOST_AUTO_TEST_CASE(MostPkt2)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_MostPkt2.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::MOST_PKT2);
    Vector::BLF::MostPkt2 * obj = static_cast<Vector::BLF::MostPkt2 *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1); // Vector bug: This should be 2 for ObjectHeader2
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::MOST_PKT2);

    /* ObjectHeader2 */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader2::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->timeStampStatus, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 4445080000);
    BOOST_CHECK_EQUAL(obj->originalTimeStamp, 0);

    /* MostPkt2 */
    BOOST_CHECK_EQUAL(obj->channel, 1);
    BOOST_CHECK_EQUAL(obj->dir, 0); // Rx
    // reserved
    BOOST_CHECK_EQUAL(obj->sourceAdr, 0x0101);
    BOOST_CHECK_EQUAL(obj->destAdr, 0x0100);
    BOOST_CHECK_EQUAL(obj->arbitration, 0x03);
    BOOST_CHECK_EQUAL(obj->timeRes, 0);
    BOOST_CHECK_EQUAL(obj->quadsToFollow, 0);
    // reserved
    BOOST_CHECK_EQUAL(obj->crc, 0x0000);
    BOOST_CHECK_EQUAL(obj->priority, 0);
    BOOST_CHECK_EQUAL(obj->transferType, 1); // Node
    BOOST_CHECK_EQUAL(obj->state, 0); // Rx
    // reserved
    BOOST_CHECK_EQUAL(obj->pktDataLength, 0x0A);
    // reserved
    BOOST_CHECK_EQUAL(obj->pktData[0], 0x52);
    BOOST_CHECK_EQUAL(obj->pktData[1], 0x01);
    BOOST_CHECK_EQUAL(obj->pktData[2], 0xE0);
    BOOST_CHECK_EQUAL(obj->pktData[3], 0x3C);
    BOOST_CHECK_EQUAL(obj->pktData[4], 0x90);
    BOOST_CHECK_EQUAL(obj->pktData[5], 0x01);
    BOOST_CHECK_EQUAL(obj->pktData[6], 0xFD);
    BOOST_CHECK_EQUAL(obj->pktData[7], 0x00);
    BOOST_CHECK_EQUAL(obj->pktData[8], 0x00);
    BOOST_CHECK_EQUAL(obj->pktData[9], 0x00);

    delete obj;

    file.close();
}