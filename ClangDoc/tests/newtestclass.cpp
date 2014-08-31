/*
 * File:   newtestclass.cpp
 * Author: User
 *
 * Created on May 13, 2011, 10:18:23 PM
 */

#include "newtestclass.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass()
{
}

newtestclass::~newtestclass()
{
}

void newtestclass::setUp()
{
}

void newtestclass::tearDown()
{
}

void newtestclass::testMethod()
{
    CPPUNIT_ASSERT(true);
}

void newtestclass::testFailedMethod()
{
    CPPUNIT_ASSERT(false);
}

