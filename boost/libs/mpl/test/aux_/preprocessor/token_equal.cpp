
// + file: libs/mpl/test/aux_/token_eqaul.cpp
// + last modified: 03/may/03

// Copyright (c) 2003
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/preprocessor/token_equal.hpp"

#include "boost/preprocessor/logical/not.hpp"
#include "boost/preprocessor/debug/assert.hpp"

#define AUX_ASSERT_EQUAL(x, y) \
    BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(x, y) ) \
/**/

#define AUX_ASSERT_NOT_EQUAL(x, y) \
    BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(x, y) ) ) \
/**/

int main()
{
    #define BOOST_MPL_PP_TOKEN_EQUAL_apple(x) x
    #define BOOST_MPL_PP_TOKEN_EQUAL_orange(x) x

    AUX_ASSERT_NOT_EQUAL( apple, abc )
    AUX_ASSERT_NOT_EQUAL( abc, apple )
    AUX_ASSERT_NOT_EQUAL( apple, orange )
    AUX_ASSERT_NOT_EQUAL( orange, apple )

    AUX_ASSERT_EQUAL( apple, apple )
    AUX_ASSERT_EQUAL( orange, orange )

    return 0;
}
