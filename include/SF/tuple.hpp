
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2011, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// Version: 1.3.1
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#ifndef INCLUDE_SF_TUPLE_HPP
#define INCLUDE_SF_TUPLE_HPP

#include <RCF/Config.hpp>

#include <boost/tuple/tuple.hpp>

#ifdef RCF_USE_TR1
#include RCF_TR1_HEADER(tuple)
#endif

namespace SF {

    class Archive;

    // boost::tuple

    template<
        typename T0>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0> &t)
    {
        ar 
            & t.template get<0>();
    }

    template<
        typename T0, 
        typename T1>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4,T5> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>() 
            & t.template get<5>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4,T5,T6> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>() 
            & t.template get<5>() 
            & t.template get<6>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4,T5,T6,T7> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>() 
            & t.template get<5>() 
            & t.template get<6>() 
            & t.template get<7>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7, 
        typename T8>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>() 
            & t.template get<5>() 
            & t.template get<6>() 
            & t.template get<7>() 
            & t.template get<8>();
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7, 
        typename T8, 
        typename T9>
    void serialize(SF::Archive &ar, boost::tuples::tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> &t)
    {
        ar 
            & t.template get<0>() 
            & t.template get<1>() 
            & t.template get<2>() 
            & t.template get<3>() 
            & t.template get<4>() 
            & t.template get<5>() 
            & t.template get<6>() 
            & t.template get<7>() 
            & t.template get<8>() 
            & t.template get<9>();
    }

#ifdef RCF_USE_TR1

    // tr1::tuple

    template<
        typename T0>
        void serialize(SF::Archive &ar, std::tr1::tuple<T0> &t)
    {
        ar 
            & std::tr1::get<0>(t);
    }

    template<
        typename T0, 
        typename T1>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4,T5> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t) 
            & std::tr1::get<5>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4,T5,T6> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t) 
            & std::tr1::get<5>(t) 
            & std::tr1::get<6>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4,T5,T6,T7> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t) 
            & std::tr1::get<5>(t) 
            & std::tr1::get<6>(t) 
            & std::tr1::get<7>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7, 
        typename T8>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t) 
            & std::tr1::get<5>(t) 
            & std::tr1::get<6>(t) 
            & std::tr1::get<7>(t) 
            & std::tr1::get<8>(t);
    }

    template<
        typename T0, 
        typename T1, 
        typename T2, 
        typename T3, 
        typename T4, 
        typename T5, 
        typename T6, 
        typename T7, 
        typename T8, 
        typename T9>
    void serialize(SF::Archive &ar, std::tr1::tuple<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9> &t)
    {
        ar 
            & std::tr1::get<0>(t) 
            & std::tr1::get<1>(t) 
            & std::tr1::get<2>(t) 
            & std::tr1::get<3>(t) 
            & std::tr1::get<4>(t) 
            & std::tr1::get<5>(t) 
            & std::tr1::get<6>(t) 
            & std::tr1::get<7>(t) 
            & std::tr1::get<8>(t) 
            & std::tr1::get<9>(t);
    }

#endif // RCF_USE_TR1

}

#endif // ! INCLUDE_SF_TUPLE_HPP
