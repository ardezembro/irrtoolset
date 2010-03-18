//
// Copyright (c) 2001,2002                        RIPE NCC
//
// All Rights Reserved
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose and without fee is hereby granted,
// provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in
// supporting documentation, and that the name of the author not be
// used in advertising or publicity pertaining to distribution of the
// software without specific, written prior permission.
//
// THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
// ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS; IN NO EVENT SHALL
// AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
// AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// $Id$
//
// Time.hh
// Author(s): Ramesh Govindan

#ifndef _Time_hh
#define _Time_hh

#include "util/Types.hh"

// Forward definitions
class TimeLong;
class TimeShort;

// We use the NTP format for representing time.
//
// Time differences are usually represented 
// in a "short" format, with a 16 bit integral part and a
// 16 bit fractional part.
//
// Absolute time is usually represented in a "long" format
// using 32 bits for the integer part and 32 for the fractional part.
//

template <class T>
class Time {
  public:
    void
    operator=(const Time<T> y) {
        time = y.time;
    };

    Boolean
    operator==(const Time<T> y) const {
        return (time == y.time);
    };

    Boolean
    operator!=(const Time<T> y) const {
        return (time != y.time);
    };

    Boolean
    operator>(const Time<T> y) const {
        return (time > y.time);
    };

    Boolean
    operator<(const Time<T> y) const {
        return (time < y.time);
    };

    void
    operator>>=(int i) {
        time >>= i;
    }

    void
    operator<<=(int i) {
        time <<= i;
    }

    void
    operator+=(Time<T> y) {
        time += y.time;
    }

    void
    operator-=(Time<T> y) {
        time = (time > y.time) ? (time - y.time) : 0;
    }

    void
    operator*=(float x) {
        time = (T) (time * x);
    }

    T	time;
};

class TimeShort : public Time<U32> {
    friend class TimeLong;
    
  public:
    // Create empty time instance
    TimeShort();

    // Create time instance given a 32-bit value
    TimeShort(U32);

    // Create time instance given seconds and fraction
    TimeShort(U16 i,
              U16 f);

    // Convert to long format
    TimeLong
    lengthen();
    
    // Multiply by a uniform random real number in 0..1
    void
    randomize();
    
    // Extract the seconds part
    U16
    seconds();

    // Extract the fractional part
    U16
    fraction();

    // Return the number of microseconds
    U32
    usecs();

    // Return the NTP representation
    U32
    get() const;
    
    // Set the integer and fractional part
    void
    set(U16, U16);
    
    // Set our value to the number of microseconds in the argument
    void
    set(U32 usecs);
};

class TimeLong : public Time<U64> {
    friend class TimeShort;
    
  public:
    // Create an empty time instance
    TimeLong();

    // Create an instance given the fixed point representation
    TimeLong(U64 t);

    // Create an instance given the components
    TimeLong(U32 i, U32 f);

    // Subtract a smaller time
    TimeShort
    operator-(TimeLong y);

    // Add a smaller time
    TimeLong
    operator+(TimeShort y);
    
    // Synchronize with operating system clock
    void
    sync();
    
    // Extract the seconds part
    U32
    seconds();

    // Extract the fractional part
    U32
    fraction();

    // Return the fixed point representation
    U64
    get() const;
    
    // Set the components
    void
    set(U32 secs, U32 frac);

    // Convert to operating system time representation
    void
    systemTime(struct timeval* tv);
};

// Constants
static const TimeShort	ZeroInterval(0, 0);
static const TimeShort 	InfiniteInterval(0xffff, 0xffff);
static const TimeLong	ZeroTime(0, 0);
static const TimeLong	InfiniteTime(0xffffffff, 0xffffffff);

extern TimeLong& sysClock;

// 
//  Copyright (c) 1994 by the University of Southern California.
//  All rights reserved.
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in
//    all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//    THE SOFTWARE.
//
//  Questions concerning this software should be directed to 
//  irrtoolset@cs.usc.edu.
//
//  Author(s): Ramesh Govindan <govindan@isi.edu>

#endif // _system_hh