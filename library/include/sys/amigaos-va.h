/*
 * $Id: amigaos-va.h,v 1.6 2005-11-27 10:28:16 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2005 by Olaf Barthel <olsen@sourcery.han.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************
 *
 * Documentation and source code for this library, and the most recent library
 * build are available from <http://sourceforge.net/projects/clib2>.
 *
 *****************************************************************************
 */

#ifndef _SYS_AMIGAOS_VA_H
#define _SYS_AMIGAOS_VA_H

/****************************************************************************/

/* The following is not part of the ISO 'C' (1994) standard. */

/****************************************************************************/

#ifndef _STDARG_H
#include <stdarg.h>
#endif /* _STDARG_H */

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************************************************************/

/* Define the AmigaOS specific varargs macros,
   if <stdarg.h> didn't already define them.   */

#ifndef va_startlinear
 #define va_startlinear(AP,ARG) \
	va_start(AP,ARG)
#endif

#ifndef va_getlinearva
 #if defined(__GNUC__) && defined(__PPC__)
  #define va_getlinearva(AP,TYPE) \
	((TYPE)__builtin_getlinearva(AP))
 #else
  #define va_getlinearva(AP,TYPE) \
	((TYPE)(void *)(AP))
 #endif
#endif

/****************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/****************************************************************************/

#endif /* _SYS_AMIGAOS_VA_H */
