#define BOOST_TEST_MODULE LinWakeupEvent
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Vector/BLF.h"

/* LIN_WAKEUP = 21 */
BOOST_AUTO_TEST_CASE(LinWakeupEvent)
{
    Vector::BLF::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/test_LinWakeupEvent.blf");
    BOOST_REQUIRE(file.is_open());

    Vector::BLF::ObjectHeaderBase * ohb = file.read();
    BOOST_REQUIRE(ohb != nullptr);
    BOOST_REQUIRE(ohb->objectType == Vector::BLF::ObjectType::LIN_WAKEUP);
    Vector::BLF::LinWakeupEvent * obj = static_cast<Vector::BLF::LinWakeupEvent *>(ohb);

    /* ObjectHeaderBase */
    BOOST_CHECK_EQUAL(obj->signature, Vector::BLF::ObjectSignature);
    BOOST_CHECK_EQUAL(obj->headerSize, obj->calculateHeaderSize());
    BOOST_CHECK_EQUAL(obj->headerVersion, 1);
    BOOST_CHECK_EQUAL(obj->objectSize, obj->calculateObjectSize());
    BOOST_CHECK(obj->objectType == Vector::BLF::ObjectType::LIN_WAKEUP);

    /* ObjectHeader */
    BOOST_CHECK(obj->objectFlags == Vector::BLF::ObjectHeader::ObjectFlags::TimeOneNans);
    BOOST_CHECK_EQUAL(obj->clientIndex, 0x2222);
    BOOST_CHECK_EQUAL(obj->objectVersion, 0);
    BOOST_CHECK_EQUAL(obj->objectTimeStamp, 0x3333333333333333);

    /* LinWakeupEvent */
    // @todo LinWakeupEvent

    delete obj;

    file.close();
}