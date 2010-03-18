//  $Id$
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
//
//  Copyright (c) 1994 by the University of Southern California
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
//  Author(s): WeeSan Lee <wlee@ISI.EDU>


#if !defined(IDENT_OFF)
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7) 
static char ident[] = 
   "@(#)$Id$";
#endif
#endif


#include "config.h"
#include <cstring>
#include <cstdlib>
#include "TclCheckButton.hh"
#include "TclApp.hh"

TclCheckButton::~TclCheckButton(void)
{
   if (pzcVariableName) delete []pzcVariableName;
}

int TclCheckButton::setOption(tdCheckButtonOption eOption) 
{
   TclApplication *pcApp = (TclApplication *)getExtraArgument();
   if (!pcApp) return 0;
   if (!pzcVariableName)
      if ((pzcVariableName = new char [strlen(getName()) + 4]) == NULL) 
	 return 0;
   strcpy(pzcVariableName, getName());
   char *p = pzcVariableName;
   while ((p = strchr(p, '.')) != NULL) strcpy(p, p + 1);
   strcat(pzcVariableName, "Var");
   // Create a Tcl global variable whose name is stored in 'pzcVariableName' 
   // with value 'eOption'.

   if (!pcApp->setVar(pzcVariableName, eOption, 
		      TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG)) return 0;
/*
   // Now, link the Tcl variable with C varible: eOption
   if (Tcl_LinkVar(pcApp->getInterp(), pzcVariableName, (char *)&eOption, 
		   TCL_LINK_BOOLEAN) != TCL_OK) return 0;
*/
   if (!pcApp->evalf("%s configure -variable %s", getName(), pzcVariableName)) 
      return 0;
   return 1;
}

// This function is really a special case
// return of -1 indicates of error
int TclCheckButton::getOption(void)
{
   TclApplication *pcApp = (TclApplication *)getExtraArgument();
   if (!pcApp) return -1;
   char *pzcBuffer;
   if ((pzcBuffer = pcApp->getVar(pzcVariableName)) == NULL) return -1;
   return atoi(pzcBuffer);
}

int TclCheckButton::enable(void)
{
   TclApplication *pcApp = (TclApplication *)getExtraArgument();
   return pcApp->evalf("%s configure -state normal", getName());
}

int TclCheckButton::disable(void)
{
   TclApplication *pcApp = (TclApplication *)getExtraArgument();
   return pcApp->evalf("%s configure -state disabled", getName());
}