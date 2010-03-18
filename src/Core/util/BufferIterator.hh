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
// Author(s): Cengiz Alaettinoglu <cengiz@isi.edu>

#ifndef BUFFER_ITERATOR_HH
#define BUFFER_ITERATOR_HH

#include "config.h"
#include "util/Buffer.hh"

class BufferIterator {
   Buffer &buf;
   char    seperator;
   Buffer  current;
public:
   BufferIterator(Buffer &b, char sep) 
      : buf(b), seperator(sep), current() {
      current.callerAllocated = true;
      first();
   }
   ~BufferIterator() {}
   Buffer *first() {
      current.size = 0;
      current.contents = (char *) NULL;
      if (!buf.contents || !buf.size)
	 return (Buffer *) NULL;
      current.contents = buf.contents;
      char *next = (char *) memchr(current.contents, seperator, buf.size);
      if (next)
	 current.size = next - current.contents;
      else
	 current.size = buf.size;
      return &current;
   }

   Buffer *next() {
      if (!current.contents)
	 return (Buffer *) NULL;
      
      current.contents += current.size + 1;
      if (current.contents >= buf.contents + buf.size) {
	 current.contents = (char *) NULL;
	 current.size = 0;
	 return (Buffer *) NULL;
      }

      char *next = (char *) memchr(current.contents, seperator, 
				   buf.size - (current.contents-buf.contents));
      if (next)
	 current.size = next - current.contents;
      else
	 current.size = buf.size - (current.contents - buf.contents);
      return &current;
   }
   BufferIterator &operator++(int) {
      next();
      return *this;
   }
   operator Buffer*() { 
      return current.contents ? &current : (Buffer *) NULL; 
   }
   Buffer* operator()(void) { 
      return current.contents ? &current : (Buffer *) NULL; 
   }
};

#endif // BUFFER_ITERATOR_HH


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
