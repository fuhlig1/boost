#ifndef BOOST_PREPROCESSOR_WHILE_HPP
#define BOOST_PREPROCESSOR_WHILE_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

/** <P>Iterates F(D,X) while C(D,X) is true.</P>

<P>In other words, expands to:</P>

<PRE>
  F(D, ... F(D, F(D,X) ) ... )
</PRE>

<P>The depth of iteration is determined by C(D,X).</P>

<H3>Legend</H3>
<UL>
  <LI><B>X</B> is the current state of iteration. The state is usually a tuple.
  <LI><B>C</B> is the condition for iteration. It must expand to a decimal
      integer literal.
  <LI><B>F</B> is the iterated macro. Note that if the state is a tuple, then
      F(D,X) usually expands to a tuple of the same number of elements.
  <LI><B>D</B> is the recursion depth and should only be used as a parameter
      to other macros using BOOST_PP_WHILE(). Such macros include
      BOOST_PP_ADD() and other arithmetic operations. For each macro using
      BOOST_PP_WHILE(), there is a version of the macro, distinguished by the
      D suffix (e.g. BOOST_PP_ADD_D()), that accepts an additional recursion
      depth as the first parameter. This technique is necessary to avoid
      recursively expanding the same macro again, which is not permitted by the
      C++ preprocessor.
</UL>

<P>NOTE: The value of the D parameter may exceed BOOST_PP_LIMIT_MAG.</P>

<H3>Caveat</H3>

<P>Using BOOST_PP_WHILE() is a bit tricky. This is due to the C++ preprocessor
limitations. It is recommended to take a look at the implementations of the
various PREPROCESSOR library primitives such as BOOST_PP_ADD() for additional
examples.</P>

<H3>Example</H3>
<UL>
  <LI><a href="../../example/count_down.c">count_down.c</a>
</UL>

<P>For a more complex example, let's take a look at an implementation of
BOOST_PP_MUL().</P>

<PRE>
  #define BOOST_PP_MUL(X,Y) BOOST_PP_MUL_D(0,X,Y)
  // Since the macro is implemented using WHILE, the actual implementation
  // takes a depth as a parameter so that it can be called inside a WHILE.
  // The above easy-to-use version simply uses 0 as the depth and can not be
  // called inside a WHILE.

  #define BOOST_PP_MUL_D(D,X,Y)\
    BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_WHILE##D(BOOST_PP_MUL_C,BOOST_PP_MUL_F,(0,X,Y)))
  //                    ^^^               ^^^             ^^             ^^ ^^^^^^^
  //                    #1                #2              #3             #3 #1
  //
  // #1) The state is a 3-tuple. After the iteration is finished, the first
  // element of the tuple is the result.
  //
  // #2) The WHILE primitive is "invoked" directly. BOOST_PP_WHILE(D,...)
  // can't be used because it would not be expanded by the C++ preprocessor.
  //
  // #3) ???_C is the condition and ???_F is the iteration macro.

  #define BOOST_PP_MUL_C(D,P)\
    BOOST_PP_TUPLE_ELEM(3,2,P)
  // Iteration is finished when the counter reaches 0.

  #define BOOST_PP_MUL_F(D,P)\
    ( BOOST_PP_ADD_D(D,BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE_ELEM(3,1,P))\
    , BOOST_PP_TUPLE_ELEM(3,1,P)\
    , BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(3,2,P))\
    )
  // ( The result is increased by the multiplier.
  // , The multiplier is retained without change.
  // , The counter is decreased.
  // )
</PRE>

<H3>Implementation rationale</H3>
<UL>
  <LI>The maximum iteration depth is greater than 2*BOOST_PP_LIMIT_MAG to make
      it possible to compute N*N functions.
</UL>
*/
#define BOOST_PP_WHILE(C,F,X) BOOST_PP_WHILE_C(C(1,X),0,X)(C,F,F(1,X))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_WHILE_C(C,D,X) BOOST_PP_IF(C,BOOST_PP_WHILE##D,X BOOST_PP_TUPLE3_EAT)
#define BOOST_PP_WHILE0(C,F,X) BOOST_PP_WHILE_C(C(2,X),1,X)(C,F,F(2,X))
#define BOOST_PP_WHILE1(C,F,X) BOOST_PP_WHILE_C(C(3,X),2,X)(C,F,F(3,X))
#define BOOST_PP_WHILE2(C,F,X) BOOST_PP_WHILE_C(C(4,X),3,X)(C,F,F(4,X))
#define BOOST_PP_WHILE3(C,F,X) BOOST_PP_WHILE_C(C(5,X),4,X)(C,F,F(5,X))
#define BOOST_PP_WHILE4(C,F,X) BOOST_PP_WHILE_C(C(6,X),5,X)(C,F,F(6,X))
#define BOOST_PP_WHILE5(C,F,X) BOOST_PP_WHILE_C(C(7,X),6,X)(C,F,F(7,X))
#define BOOST_PP_WHILE6(C,F,X) BOOST_PP_WHILE_C(C(8,X),7,X)(C,F,F(8,X))
#define BOOST_PP_WHILE7(C,F,X) BOOST_PP_WHILE_C(C(9,X),8,X)(C,F,F(9,X))
#define BOOST_PP_WHILE8(C,F,X) BOOST_PP_WHILE_C(C(10,X),9,X)(C,F,F(10,X))
#define BOOST_PP_WHILE9(C,F,X) BOOST_PP_WHILE_C(C(11,X),10,X)(C,F,F(11,X))
#define BOOST_PP_WHILE10(C,F,X) BOOST_PP_WHILE_C(C(12,X),11,X)(C,F,F(12,X))
#define BOOST_PP_WHILE11(C,F,X) BOOST_PP_WHILE_C(C(13,X),12,X)(C,F,F(13,X))
#define BOOST_PP_WHILE12(C,F,X) BOOST_PP_WHILE_C(C(14,X),13,X)(C,F,F(14,X))
#define BOOST_PP_WHILE13(C,F,X) BOOST_PP_WHILE_C(C(15,X),14,X)(C,F,F(15,X))
#define BOOST_PP_WHILE14(C,F,X) BOOST_PP_WHILE_C(C(16,X),15,X)(C,F,F(16,X))
#define BOOST_PP_WHILE15(C,F,X) BOOST_PP_WHILE_C(C(17,X),16,X)(C,F,F(17,X))
#define BOOST_PP_WHILE16(C,F,X) BOOST_PP_WHILE_C(C(18,X),17,X)(C,F,F(18,X))
#define BOOST_PP_WHILE17(C,F,X) BOOST_PP_WHILE_C(C(19,X),18,X)(C,F,F(19,X))
#define BOOST_PP_WHILE18(C,F,X) BOOST_PP_WHILE_C(C(20,X),19,X)(C,F,F(20,X))
#define BOOST_PP_WHILE19(C,F,X) BOOST_PP_WHILE_C(C(21,X),20,X)(C,F,F(21,X))
#define BOOST_PP_WHILE20(C,F,X) BOOST_PP_WHILE_C(C(22,X),21,X)(C,F,F(22,X))
#define BOOST_PP_WHILE21(C,F,X) BOOST_PP_WHILE_C(C(23,X),22,X)(C,F,F(23,X))
#define BOOST_PP_WHILE22(C,F,X) BOOST_PP_WHILE_C(C(24,X),23,X)(C,F,F(24,X))
#define BOOST_PP_WHILE23(C,F,X) BOOST_PP_WHILE_C(C(25,X),24,X)(C,F,F(25,X))
#define BOOST_PP_WHILE24(C,F,X) BOOST_PP_WHILE_C(C(26,X),25,X)(C,F,F(26,X))
#define BOOST_PP_WHILE25(C,F,X) BOOST_PP_WHILE_C(C(27,X),26,X)(C,F,F(27,X))
#define BOOST_PP_WHILE26(C,F,X) BOOST_PP_WHILE_C(C(28,X),27,X)(C,F,F(28,X))
#define BOOST_PP_WHILE27(C,F,X) BOOST_PP_WHILE_C(C(29,X),28,X)(C,F,F(29,X))
#define BOOST_PP_WHILE28(C,F,X) BOOST_PP_WHILE_C(C(30,X),29,X)(C,F,F(30,X))
#define BOOST_PP_WHILE29(C,F,X) BOOST_PP_WHILE_C(C(31,X),30,X)(C,F,F(31,X))
#define BOOST_PP_WHILE30(C,F,X) BOOST_PP_WHILE_C(C(32,X),31,X)(C,F,F(32,X))
#define BOOST_PP_WHILE31(C,F,X) BOOST_PP_WHILE_C(C(33,X),32,X)(C,F,F(33,X))
#define BOOST_PP_WHILE32(C,F,X) BOOST_PP_WHILE_C(C(34,X),33,X)(C,F,F(34,X))
#define BOOST_PP_WHILE33(C,F,X) BOOST_PP_WHILE_C(C(35,X),34,X)(C,F,F(35,X))
#define BOOST_PP_WHILE34(C,F,X) BOOST_PP_WHILE_C(C(36,X),35,X)(C,F,F(36,X))
#define BOOST_PP_WHILE35(C,F,X) BOOST_PP_WHILE_C(C(37,X),36,X)(C,F,F(37,X))
#define BOOST_PP_WHILE36(C,F,X) BOOST_PP_WHILE_C(C(38,X),37,X)(C,F,F(38,X))
#define BOOST_PP_WHILE37(C,F,X) BOOST_PP_WHILE_C(C(39,X),38,X)(C,F,F(39,X))
#define BOOST_PP_WHILE38(C,F,X) BOOST_PP_WHILE_C(C(40,X),39,X)(C,F,F(40,X))
#define BOOST_PP_WHILE39(C,F,X) BOOST_PP_WHILE_C(C(41,X),40,X)(C,F,F(41,X))
#define BOOST_PP_WHILE40(C,F,X) BOOST_PP_WHILE_C(C(42,X),41,X)(C,F,F(42,X))
#define BOOST_PP_WHILE41(C,F,X) BOOST_PP_WHILE_C(C(43,X),42,X)(C,F,F(43,X))
#define BOOST_PP_WHILE42(C,F,X) BOOST_PP_WHILE_C(C(44,X),43,X)(C,F,F(44,X))
#define BOOST_PP_WHILE43(C,F,X) BOOST_PP_WHILE_C(C(45,X),44,X)(C,F,F(45,X))
#define BOOST_PP_WHILE44(C,F,X) BOOST_PP_WHILE_C(C(46,X),45,X)(C,F,F(46,X))
#define BOOST_PP_WHILE45(C,F,X) BOOST_PP_WHILE_C(C(47,X),46,X)(C,F,F(47,X))
#define BOOST_PP_WHILE46(C,F,X) BOOST_PP_WHILE_C(C(48,X),47,X)(C,F,F(48,X))
#define BOOST_PP_WHILE47(C,F,X) BOOST_PP_WHILE_C(C(49,X),48,X)(C,F,F(49,X))
#define BOOST_PP_WHILE48(C,F,X) BOOST_PP_WHILE_C(C(50,X),49,X)(C,F,F(50,X))
#define BOOST_PP_WHILE49(C,F,X) BOOST_PP_WHILE_C(C(51,X),50,X)(C,F,F(51,X))
#define BOOST_PP_WHILE50(C,F,X) BOOST_PP_WHILE_C(C(52,X),51,X)(C,F,F(52,X))
#define BOOST_PP_WHILE51(C,F,X) BOOST_PP_WHILE_C(C(53,X),52,X)(C,F,F(53,X))
#define BOOST_PP_WHILE52(C,F,X) BOOST_PP_WHILE_C(C(54,X),53,X)(C,F,F(54,X))
#define BOOST_PP_WHILE53(C,F,X) BOOST_PP_WHILE_C(C(55,X),54,X)(C,F,F(55,X))
#define BOOST_PP_WHILE54(C,F,X) BOOST_PP_WHILE_C(C(56,X),55,X)(C,F,F(56,X))
#define BOOST_PP_WHILE55(C,F,X) BOOST_PP_WHILE_C(C(57,X),56,X)(C,F,F(57,X))
#define BOOST_PP_WHILE56(C,F,X) BOOST_PP_WHILE_C(C(58,X),57,X)(C,F,F(58,X))
#define BOOST_PP_WHILE57(C,F,X) BOOST_PP_WHILE_C(C(59,X),58,X)(C,F,F(59,X))
#define BOOST_PP_WHILE58(C,F,X) BOOST_PP_WHILE_C(C(60,X),59,X)(C,F,F(60,X))
#define BOOST_PP_WHILE59(C,F,X) BOOST_PP_WHILE_C(C(61,X),60,X)(C,F,F(61,X))
#define BOOST_PP_WHILE60(C,F,X) BOOST_PP_WHILE_C(C(62,X),61,X)(C,F,F(62,X))
#define BOOST_PP_WHILE61(C,F,X) BOOST_PP_WHILE_C(C(63,X),62,X)(C,F,F(63,X))
#define BOOST_PP_WHILE62(C,F,X) BOOST_PP_WHILE_C(C(64,X),63,X)(C,F,F(64,X))
#define BOOST_PP_WHILE63(C,F,X) BOOST_PP_WHILE_C(C(65,X),64,X)(C,F,F(65,X))
#define BOOST_PP_WHILE64(C,F,X) BOOST_PP_WHILE_C(C(66,X),65,X)(C,F,F(66,X))
#define BOOST_PP_WHILE65(C,F,X) BOOST_PP_WHILE_C(C(67,X),66,X)(C,F,F(67,X))
#define BOOST_PP_WHILE66(C,F,X) BOOST_PP_WHILE_C(C(68,X),67,X)(C,F,F(68,X))
#define BOOST_PP_WHILE67(C,F,X) BOOST_PP_WHILE_C(C(69,X),68,X)(C,F,F(69,X))
#define BOOST_PP_WHILE68(C,F,X) BOOST_PP_WHILE_C(C(70,X),69,X)(C,F,F(70,X))
#define BOOST_PP_WHILE69(C,F,X) BOOST_PP_WHILE_C(C(71,X),70,X)(C,F,F(71,X))
#define BOOST_PP_WHILE70(C,F,X) BOOST_PP_WHILE_C(C(72,X),71,X)(C,F,F(72,X))
#define BOOST_PP_WHILE71(C,F,X) BOOST_PP_WHILE_C(C(73,X),72,X)(C,F,F(73,X))
#define BOOST_PP_WHILE72(C,F,X) BOOST_PP_WHILE_C(C(74,X),73,X)(C,F,F(74,X))
#define BOOST_PP_WHILE73(C,F,X) BOOST_PP_WHILE_C(C(75,X),74,X)(C,F,F(75,X))
#define BOOST_PP_WHILE74(C,F,X) BOOST_PP_WHILE_C(C(76,X),75,X)(C,F,F(76,X))
#define BOOST_PP_WHILE75(C,F,X) BOOST_PP_WHILE_C(C(77,X),76,X)(C,F,F(77,X))
#define BOOST_PP_WHILE76(C,F,X) BOOST_PP_WHILE_C(C(78,X),77,X)(C,F,F(78,X))
#define BOOST_PP_WHILE77(C,F,X) BOOST_PP_WHILE_C(C(79,X),78,X)(C,F,F(79,X))
#define BOOST_PP_WHILE78(C,F,X) BOOST_PP_WHILE_C(C(80,X),79,X)(C,F,F(80,X))
#define BOOST_PP_WHILE79(C,F,X) BOOST_PP_WHILE_C(C(81,X),80,X)(C,F,F(81,X))
#define BOOST_PP_WHILE80(C,F,X) BOOST_PP_WHILE_C(C(82,X),81,X)(C,F,F(82,X))
#define BOOST_PP_WHILE81(C,F,X) BOOST_PP_WHILE_C(C(83,X),82,X)(C,F,F(83,X))
#define BOOST_PP_WHILE82(C,F,X) BOOST_PP_WHILE_C(C(84,X),83,X)(C,F,F(84,X))
#define BOOST_PP_WHILE83(C,F,X) BOOST_PP_WHILE_C(C(85,X),84,X)(C,F,F(85,X))
#define BOOST_PP_WHILE84(C,F,X) BOOST_PP_WHILE_C(C(86,X),85,X)(C,F,F(86,X))
#define BOOST_PP_WHILE85(C,F,X) BOOST_PP_WHILE_C(C(87,X),86,X)(C,F,F(87,X))
#define BOOST_PP_WHILE86(C,F,X) BOOST_PP_WHILE_C(C(88,X),87,X)(C,F,F(88,X))
#define BOOST_PP_WHILE87(C,F,X) BOOST_PP_WHILE_C(C(89,X),88,X)(C,F,F(89,X))
#define BOOST_PP_WHILE88(C,F,X) BOOST_PP_WHILE_C(C(90,X),89,X)(C,F,F(90,X))
#define BOOST_PP_WHILE89(C,F,X) BOOST_PP_WHILE_C(C(91,X),90,X)(C,F,F(91,X))
#define BOOST_PP_WHILE90(C,F,X) BOOST_PP_WHILE_C(C(92,X),91,X)(C,F,F(92,X))
#define BOOST_PP_WHILE91(C,F,X) BOOST_PP_WHILE_C(C(93,X),92,X)(C,F,F(93,X))
#define BOOST_PP_WHILE92(C,F,X) BOOST_PP_WHILE_C(C(94,X),93,X)(C,F,F(94,X))
#define BOOST_PP_WHILE93(C,F,X) BOOST_PP_WHILE_C(C(95,X),94,X)(C,F,F(95,X))
#define BOOST_PP_WHILE94(C,F,X) BOOST_PP_WHILE_C(C(96,X),95,X)(C,F,F(96,X))
#define BOOST_PP_WHILE95(C,F,X) BOOST_PP_WHILE_C(C(97,X),96,X)(C,F,F(97,X))
#define BOOST_PP_WHILE96(C,F,X) BOOST_PP_WHILE_C(C(98,X),97,X)(C,F,F(98,X))
#define BOOST_PP_WHILE97(C,F,X) BOOST_PP_WHILE_C(C(99,X),98,X)(C,F,F(99,X))
#define BOOST_PP_WHILE98(C,F,X) BOOST_PP_WHILE_C(C(100,X),99,X)(C,F,F(100,X))
#define BOOST_PP_WHILE99(C,F,X) BOOST_PP_WHILE_C(C(101,X),100,X)(C,F,F(101,X))
#define BOOST_PP_WHILE100(C,F,X) BOOST_PP_WHILE_C(C(102,X),101,X)(C,F,F(102,X))
#define BOOST_PP_WHILE101(C,F,X) BOOST_PP_WHILE_C(C(103,X),102,X)(C,F,F(103,X))
#define BOOST_PP_WHILE102(C,F,X) BOOST_PP_WHILE_C(C(104,X),103,X)(C,F,F(104,X))
#define BOOST_PP_WHILE103(C,F,X) BOOST_PP_WHILE_C(C(105,X),104,X)(C,F,F(105,X))
#define BOOST_PP_WHILE104(C,F,X) BOOST_PP_WHILE_C(C(106,X),105,X)(C,F,F(106,X))
#define BOOST_PP_WHILE105(C,F,X) BOOST_PP_WHILE_C(C(107,X),106,X)(C,F,F(107,X))
#define BOOST_PP_WHILE106(C,F,X) BOOST_PP_WHILE_C(C(108,X),107,X)(C,F,F(108,X))
#define BOOST_PP_WHILE107(C,F,X) BOOST_PP_WHILE_C(C(109,X),108,X)(C,F,F(109,X))
#define BOOST_PP_WHILE108(C,F,X) BOOST_PP_WHILE_C(C(110,X),109,X)(C,F,F(110,X))
#define BOOST_PP_WHILE109(C,F,X) BOOST_PP_WHILE_C(C(111,X),110,X)(C,F,F(111,X))
#define BOOST_PP_WHILE110(C,F,X) BOOST_PP_WHILE_C(C(112,X),111,X)(C,F,F(112,X))
#define BOOST_PP_WHILE111(C,F,X) BOOST_PP_WHILE_C(C(113,X),112,X)(C,F,F(113,X))
#define BOOST_PP_WHILE112(C,F,X) BOOST_PP_WHILE_C(C(114,X),113,X)(C,F,F(114,X))
#define BOOST_PP_WHILE113(C,F,X) BOOST_PP_WHILE_C(C(115,X),114,X)(C,F,F(115,X))
#define BOOST_PP_WHILE114(C,F,X) BOOST_PP_WHILE_C(C(116,X),115,X)(C,F,F(116,X))
#define BOOST_PP_WHILE115(C,F,X) BOOST_PP_WHILE_C(C(117,X),116,X)(C,F,F(117,X))
#define BOOST_PP_WHILE116(C,F,X) BOOST_PP_WHILE_C(C(118,X),117,X)(C,F,F(118,X))
#define BOOST_PP_WHILE117(C,F,X) BOOST_PP_WHILE_C(C(119,X),118,X)(C,F,F(119,X))
#define BOOST_PP_WHILE118(C,F,X) BOOST_PP_WHILE_C(C(120,X),119,X)(C,F,F(120,X))
#define BOOST_PP_WHILE119(C,F,X) BOOST_PP_WHILE_C(C(121,X),120,X)(C,F,F(121,X))
#define BOOST_PP_WHILE120(C,F,X) BOOST_PP_WHILE_C(C(122,X),121,X)(C,F,F(122,X))
#define BOOST_PP_WHILE121(C,F,X) BOOST_PP_WHILE_C(C(123,X),122,X)(C,F,F(123,X))
#define BOOST_PP_WHILE122(C,F,X) BOOST_PP_WHILE_C(C(124,X),123,X)(C,F,F(124,X))
#define BOOST_PP_WHILE123(C,F,X) BOOST_PP_WHILE_C(C(125,X),124,X)(C,F,F(125,X))
#define BOOST_PP_WHILE124(C,F,X) BOOST_PP_WHILE_C(C(126,X),125,X)(C,F,F(126,X))
#define BOOST_PP_WHILE125(C,F,X) BOOST_PP_WHILE_C(C(127,X),126,X)(C,F,F(127,X))
#define BOOST_PP_WHILE126(C,F,X) BOOST_PP_WHILE_C(C(128,X),127,X)(C,F,F(128,X))
#define BOOST_PP_WHILE127(C,F,X) BOOST_PP_WHILE_C(C(129,X),128,X)(C,F,F(129,X))
#define BOOST_PP_WHILE128(C,F,X) BOOST_PP_WHILE_C(C(130,X),129,X)(C,F,F(130,X))
#define BOOST_PP_WHILE129(C,F,X) BOOST_PP_WHILE_C(C(131,X),130,X)(C,F,F(131,X))
#define BOOST_PP_WHILE130(C,F,X) BOOST_PP_WHILE_C(C(132,X),131,X)(C,F,F(132,X))
#define BOOST_PP_WHILE131(C,F,X) BOOST_PP_WHILE_C(C(133,X),132,X)(C,F,F(133,X))
#define BOOST_PP_WHILE132(C,F,X) BOOST_PP_WHILE_C(C(134,X),133,X)(C,F,F(134,X))
#define BOOST_PP_WHILE133(C,F,X) BOOST_PP_WHILE_C(C(135,X),134,X)(C,F,F(135,X))
#define BOOST_PP_WHILE134(C,F,X) BOOST_PP_WHILE_C(C(136,X),135,X)(C,F,F(136,X))
#define BOOST_PP_WHILE135(C,F,X) BOOST_PP_WHILE_C(C(137,X),136,X)(C,F,F(137,X))
#define BOOST_PP_WHILE136(C,F,X) BOOST_PP_WHILE_C(C(138,X),137,X)(C,F,F(138,X))
#define BOOST_PP_WHILE137(C,F,X) BOOST_PP_WHILE_C(C(139,X),138,X)(C,F,F(139,X))
#define BOOST_PP_WHILE138(C,F,X) BOOST_PP_WHILE_C(C(140,X),139,X)(C,F,F(140,X))
#define BOOST_PP_WHILE139(C,F,X) BOOST_PP_WHILE_C(C(141,X),140,X)(C,F,F(141,X))
#define BOOST_PP_WHILE140(C,F,X) BOOST_PP_WHILE_C(C(142,X),141,X)(C,F,F(142,X))
#define BOOST_PP_WHILE141(C,F,X) BOOST_PP_WHILE_C(C(143,X),142,X)(C,F,F(143,X))
#define BOOST_PP_WHILE142(C,F,X) BOOST_PP_WHILE_C(C(144,X),143,X)(C,F,F(144,X))
#define BOOST_PP_WHILE143(C,F,X) BOOST_PP_WHILE_C(C(145,X),144,X)(C,F,F(145,X))
#define BOOST_PP_WHILE144(C,F,X) BOOST_PP_WHILE_C(C(146,X),145,X)(C,F,F(146,X))
#define BOOST_PP_WHILE145(C,F,X) BOOST_PP_WHILE_C(C(147,X),146,X)(C,F,F(147,X))
#define BOOST_PP_WHILE146(C,F,X) BOOST_PP_WHILE_C(C(148,X),147,X)(C,F,F(148,X))
#define BOOST_PP_WHILE147(C,F,X) BOOST_PP_WHILE_C(C(149,X),148,X)(C,F,F(149,X))
#define BOOST_PP_WHILE148(C,F,X) BOOST_PP_WHILE_C(C(150,X),149,X)(C,F,F(150,X))
#define BOOST_PP_WHILE149(C,F,X) BOOST_PP_WHILE_C(C(151,X),150,X)(C,F,F(151,X))
#define BOOST_PP_WHILE150(C,F,X) BOOST_PP_WHILE_C(C(152,X),151,X)(C,F,F(152,X))
#define BOOST_PP_WHILE151(C,F,X) BOOST_PP_WHILE_C(C(153,X),152,X)(C,F,F(153,X))
#define BOOST_PP_WHILE152(C,F,X) BOOST_PP_WHILE_C(C(154,X),153,X)(C,F,F(154,X))
#define BOOST_PP_WHILE153(C,F,X) BOOST_PP_WHILE_C(C(155,X),154,X)(C,F,F(155,X))
#define BOOST_PP_WHILE154(C,F,X) BOOST_PP_WHILE_C(C(156,X),155,X)(C,F,F(156,X))
#define BOOST_PP_WHILE155(C,F,X) BOOST_PP_WHILE_C(C(157,X),156,X)(C,F,F(157,X))
#define BOOST_PP_WHILE156(C,F,X) BOOST_PP_WHILE_C(C(158,X),157,X)(C,F,F(158,X))
#define BOOST_PP_WHILE157(C,F,X) BOOST_PP_WHILE_C(C(159,X),158,X)(C,F,F(159,X))
#define BOOST_PP_WHILE158(C,F,X) BOOST_PP_WHILE_C(C(160,X),159,X)(C,F,F(160,X))
#define BOOST_PP_WHILE159(C,F,X) BOOST_PP_WHILE_C(C(161,X),160,X)(C,F,F(161,X))
#define BOOST_PP_WHILE160(C,F,X) BOOST_PP_WHILE_C(C(162,X),161,X)(C,F,F(162,X))
#define BOOST_PP_WHILE161(C,F,X) BOOST_PP_WHILE_C(C(163,X),162,X)(C,F,F(163,X))
#define BOOST_PP_WHILE162(C,F,X) BOOST_PP_WHILE_C(C(164,X),163,X)(C,F,F(164,X))
#define BOOST_PP_WHILE163(C,F,X) BOOST_PP_WHILE_C(C(165,X),164,X)(C,F,F(165,X))
#define BOOST_PP_WHILE164(C,F,X) BOOST_PP_WHILE_C(C(166,X),165,X)(C,F,F(166,X))
#define BOOST_PP_WHILE165(C,F,X) BOOST_PP_WHILE_C(C(167,X),166,X)(C,F,F(167,X))
#define BOOST_PP_WHILE166(C,F,X) BOOST_PP_WHILE_C(C(168,X),167,X)(C,F,F(168,X))
#define BOOST_PP_WHILE167(C,F,X) BOOST_PP_WHILE_C(C(169,X),168,X)(C,F,F(169,X))
#define BOOST_PP_WHILE168(C,F,X) BOOST_PP_WHILE_C(C(170,X),169,X)(C,F,F(170,X))
#define BOOST_PP_WHILE169(C,F,X) BOOST_PP_WHILE_C(C(171,X),170,X)(C,F,F(171,X))
#define BOOST_PP_WHILE170(C,F,X) BOOST_PP_WHILE_C(C(172,X),171,X)(C,F,F(172,X))
#define BOOST_PP_WHILE171(C,F,X) BOOST_PP_WHILE_C(C(173,X),172,X)(C,F,F(173,X))
#define BOOST_PP_WHILE172(C,F,X) BOOST_PP_WHILE_C(C(174,X),173,X)(C,F,F(174,X))
#define BOOST_PP_WHILE173(C,F,X) BOOST_PP_WHILE_C(C(175,X),174,X)(C,F,F(175,X))
#define BOOST_PP_WHILE174(C,F,X) BOOST_PP_WHILE_C(C(176,X),175,X)(C,F,F(176,X))
#define BOOST_PP_WHILE175(C,F,X) BOOST_PP_WHILE_C(C(177,X),176,X)(C,F,F(177,X))
#define BOOST_PP_WHILE176(C,F,X) BOOST_PP_WHILE_C(C(178,X),177,X)(C,F,F(178,X))
#define BOOST_PP_WHILE177(C,F,X) BOOST_PP_WHILE_C(C(179,X),178,X)(C,F,F(179,X))
#define BOOST_PP_WHILE178(C,F,X) BOOST_PP_WHILE_C(C(180,X),179,X)(C,F,F(180,X))
#define BOOST_PP_WHILE179(C,F,X) BOOST_PP_WHILE_C(C(181,X),180,X)(C,F,F(181,X))
#define BOOST_PP_WHILE180(C,F,X) BOOST_PP_WHILE_C(C(182,X),181,X)(C,F,F(182,X))
#define BOOST_PP_WHILE181(C,F,X) BOOST_PP_WHILE_C(C(183,X),182,X)(C,F,F(183,X))
#define BOOST_PP_WHILE182(C,F,X) BOOST_PP_WHILE_C(C(184,X),183,X)(C,F,F(184,X))
#define BOOST_PP_WHILE183(C,F,X) BOOST_PP_WHILE_C(C(185,X),184,X)(C,F,F(185,X))
#define BOOST_PP_WHILE184(C,F,X) BOOST_PP_WHILE_C(C(186,X),185,X)(C,F,F(186,X))
#define BOOST_PP_WHILE185(C,F,X) BOOST_PP_WHILE_C(C(187,X),186,X)(C,F,F(187,X))
#define BOOST_PP_WHILE186(C,F,X) BOOST_PP_WHILE_C(C(188,X),187,X)(C,F,F(188,X))
#define BOOST_PP_WHILE187(C,F,X) BOOST_PP_WHILE_C(C(189,X),188,X)(C,F,F(189,X))
#define BOOST_PP_WHILE188(C,F,X) BOOST_PP_WHILE_C(C(190,X),189,X)(C,F,F(190,X))
#define BOOST_PP_WHILE189(C,F,X) BOOST_PP_WHILE_C(C(191,X),190,X)(C,F,F(191,X))
#define BOOST_PP_WHILE190(C,F,X) BOOST_PP_WHILE_C(C(192,X),191,X)(C,F,F(192,X))
#define BOOST_PP_WHILE191(C,F,X) BOOST_PP_WHILE_C(C(193,X),192,X)(C,F,F(193,X))
#define BOOST_PP_WHILE192(C,F,X) BOOST_PP_WHILE_C(C(194,X),193,X)(C,F,F(194,X))
#define BOOST_PP_WHILE193(C,F,X) BOOST_PP_WHILE_C(C(195,X),194,X)(C,F,F(195,X))
#define BOOST_PP_WHILE194(C,F,X) BOOST_PP_WHILE_C(C(196,X),195,X)(C,F,F(196,X))
#define BOOST_PP_WHILE195(C,F,X) BOOST_PP_WHILE_C(C(197,X),196,X)(C,F,F(197,X))
#define BOOST_PP_WHILE196(C,F,X) BOOST_PP_WHILE_C(C(198,X),197,X)(C,F,F(198,X))
#define BOOST_PP_WHILE197(C,F,X) BOOST_PP_WHILE_C(C(199,X),198,X)(C,F,F(199,X))
#define BOOST_PP_WHILE198(C,F,X) BOOST_PP_WHILE_C(C(200,X),199,X)(C,F,F(200,X))
#define BOOST_PP_WHILE199(C,F,X) BOOST_PP_WHILE_C(C(201,X),200,X)(C,F,F(201,X))
#define BOOST_PP_WHILE200(C,F,X) BOOST_PP_WHILE_C(C(202,X),201,X)(C,F,F(202,X))
#define BOOST_PP_WHILE201(C,F,X) BOOST_PP_WHILE_C(C(203,X),202,X)(C,F,F(203,X))
#define BOOST_PP_WHILE202(C,F,X) BOOST_PP_WHILE_C(C(204,X),203,X)(C,F,F(204,X))
#define BOOST_PP_WHILE203(C,F,X) BOOST_PP_WHILE_C(C(205,X),204,X)(C,F,F(205,X))
#define BOOST_PP_WHILE204(C,F,X) BOOST_PP_WHILE_C(C(206,X),205,X)(C,F,F(206,X))
#define BOOST_PP_WHILE205(C,F,X) BOOST_PP_WHILE_C(C(207,X),206,X)(C,F,F(207,X))
#define BOOST_PP_WHILE206(C,F,X) BOOST_PP_WHILE_C(C(208,X),207,X)(C,F,F(208,X))
#define BOOST_PP_WHILE207(C,F,X) BOOST_PP_WHILE_C(C(209,X),208,X)(C,F,F(209,X))
#define BOOST_PP_WHILE208(C,F,X) BOOST_PP_WHILE_C(C(210,X),209,X)(C,F,F(210,X))
#define BOOST_PP_WHILE209(C,F,X) BOOST_PP_WHILE_C(C(211,X),210,X)(C,F,F(211,X))
#define BOOST_PP_WHILE210(C,F,X) BOOST_PP_WHILE_C(C(212,X),211,X)(C,F,F(212,X))
#define BOOST_PP_WHILE211(C,F,X) BOOST_PP_WHILE_C(C(213,X),212,X)(C,F,F(213,X))
#define BOOST_PP_WHILE212(C,F,X) BOOST_PP_WHILE_C(C(214,X),213,X)(C,F,F(214,X))
#define BOOST_PP_WHILE213(C,F,X) BOOST_PP_WHILE_C(C(215,X),214,X)(C,F,F(215,X))
#define BOOST_PP_WHILE214(C,F,X) BOOST_PP_WHILE_C(C(216,X),215,X)(C,F,F(216,X))
#define BOOST_PP_WHILE215(C,F,X) BOOST_PP_WHILE_C(C(217,X),216,X)(C,F,F(217,X))
#define BOOST_PP_WHILE216(C,F,X) BOOST_PP_WHILE_C(C(218,X),217,X)(C,F,F(218,X))
#define BOOST_PP_WHILE217(C,F,X) BOOST_PP_WHILE_C(C(219,X),218,X)(C,F,F(219,X))
#define BOOST_PP_WHILE218(C,F,X) BOOST_PP_WHILE_C(C(220,X),219,X)(C,F,F(220,X))
#define BOOST_PP_WHILE219(C,F,X) BOOST_PP_WHILE_C(C(221,X),220,X)(C,F,F(221,X))
#define BOOST_PP_WHILE220(C,F,X) BOOST_PP_WHILE_C(C(222,X),221,X)(C,F,F(222,X))
#define BOOST_PP_WHILE221(C,F,X) BOOST_PP_WHILE_C(C(223,X),222,X)(C,F,F(223,X))
#define BOOST_PP_WHILE222(C,F,X) BOOST_PP_WHILE_C(C(224,X),223,X)(C,F,F(224,X))
#define BOOST_PP_WHILE223(C,F,X) BOOST_PP_WHILE_C(C(225,X),224,X)(C,F,F(225,X))
#define BOOST_PP_WHILE224(C,F,X) BOOST_PP_WHILE_C(C(226,X),225,X)(C,F,F(226,X))
#define BOOST_PP_WHILE225(C,F,X) BOOST_PP_WHILE_C(C(227,X),226,X)(C,F,F(227,X))
#define BOOST_PP_WHILE226(C,F,X) BOOST_PP_WHILE_C(C(228,X),227,X)(C,F,F(228,X))
#define BOOST_PP_WHILE227(C,F,X) BOOST_PP_WHILE_C(C(229,X),228,X)(C,F,F(229,X))
#define BOOST_PP_WHILE228(C,F,X) BOOST_PP_WHILE_C(C(230,X),229,X)(C,F,F(230,X))
#define BOOST_PP_WHILE229(C,F,X) BOOST_PP_WHILE_C(C(231,X),230,X)(C,F,F(231,X))
#define BOOST_PP_WHILE230(C,F,X) BOOST_PP_WHILE_C(C(232,X),231,X)(C,F,F(232,X))
#define BOOST_PP_WHILE231(C,F,X) BOOST_PP_WHILE_C(C(233,X),232,X)(C,F,F(233,X))
#define BOOST_PP_WHILE232(C,F,X) BOOST_PP_WHILE_C(C(234,X),233,X)(C,F,F(234,X))
#define BOOST_PP_WHILE233(C,F,X) BOOST_PP_WHILE_C(C(235,X),234,X)(C,F,F(235,X))
#define BOOST_PP_WHILE234(C,F,X) BOOST_PP_WHILE_C(C(236,X),235,X)(C,F,F(236,X))
#define BOOST_PP_WHILE235(C,F,X) BOOST_PP_WHILE_C(C(237,X),236,X)(C,F,F(237,X))
#define BOOST_PP_WHILE236(C,F,X) BOOST_PP_WHILE_C(C(238,X),237,X)(C,F,F(238,X))
#define BOOST_PP_WHILE237(C,F,X) BOOST_PP_WHILE_C(C(239,X),238,X)(C,F,F(239,X))
#define BOOST_PP_WHILE238(C,F,X) BOOST_PP_WHILE_C(C(240,X),239,X)(C,F,F(240,X))
#define BOOST_PP_WHILE239(C,F,X) BOOST_PP_WHILE_C(C(241,X),240,X)(C,F,F(241,X))
#define BOOST_PP_WHILE240(C,F,X) BOOST_PP_WHILE_C(C(242,X),241,X)(C,F,F(242,X))
#define BOOST_PP_WHILE241(C,F,X) BOOST_PP_WHILE_C(C(243,X),242,X)(C,F,F(243,X))
#define BOOST_PP_WHILE242(C,F,X) BOOST_PP_WHILE_C(C(244,X),243,X)(C,F,F(244,X))
#define BOOST_PP_WHILE243(C,F,X) BOOST_PP_WHILE_C(C(245,X),244,X)(C,F,F(245,X))
#define BOOST_PP_WHILE244(C,F,X) BOOST_PP_WHILE_C(C(246,X),245,X)(C,F,F(246,X))
#define BOOST_PP_WHILE245(C,F,X) BOOST_PP_WHILE_C(C(247,X),246,X)(C,F,F(247,X))
#define BOOST_PP_WHILE246(C,F,X) BOOST_PP_WHILE_C(C(248,X),247,X)(C,F,F(248,X))
#define BOOST_PP_WHILE247(C,F,X) BOOST_PP_WHILE_C(C(249,X),248,X)(C,F,F(249,X))
#define BOOST_PP_WHILE248(C,F,X) BOOST_PP_WHILE_C(C(250,X),249,X)(C,F,F(250,X))
#define BOOST_PP_WHILE249(C,F,X) BOOST_PP_WHILE_C(C(251,X),250,X)(C,F,F(251,X))
#define BOOST_PP_WHILE250(C,F,X) BOOST_PP_WHILE_C(C(252,X),251,X)(C,F,F(252,X))
#define BOOST_PP_WHILE251(C,F,X) BOOST_PP_WHILE_C(C(253,X),252,X)(C,F,F(253,X))
#define BOOST_PP_WHILE252(C,F,X) BOOST_PP_WHILE_C(C(254,X),253,X)(C,F,F(254,X))
#define BOOST_PP_WHILE253(C,F,X) BOOST_PP_WHILE_C(C(255,X),254,X)(C,F,F(255,X))
#define BOOST_PP_WHILE254(C,F,X) BOOST_PP_WHILE_C(C(256,X),255,X)(C,F,F(256,X))
#define BOOST_PP_WHILE255(C,F,X) BOOST_PP_WHILE_C(C(257,X),256,X)(C,F,F(257,X))
#define BOOST_PP_WHILE256(C,F,X) BOOST_PP_WHILE_C(C(258,X),257,X)(C,F,F(258,X))
#define BOOST_PP_WHILE257(C,F,X) BOOST_PP_WHILE_C(C(259,X),258,X)(C,F,F(259,X))
#define BOOST_PP_WHILE258(C,F,X) RECURSION DEPTH EXCEEDED!
#define BOOST_PP_WHILE259(C,F,X) RECURSION DEPTH EXCEEDED!
#endif
#endif
