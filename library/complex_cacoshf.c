/*
 * Experimental: Not a part of clib2 from Olaf Barthel
 */

#ifndef _COMPLEX_HEADERS_H
#include "complex_headers.h"
#endif /* _COMPLEX_HEADERS_H */

/****************************************************************************/

#if defined(COMPLEX_SUPPORT)

/****************************************************************************/

extern float complex
cacoshf(float complex z)
{
    float complex zp = cacosf(z);
    return signbit(cimagf(z)) ? CMPLXF(cimagf(zp), -crealf(zp))
                              : CMPLXF(-cimagf(zp), crealf(zp));
}

/****************************************************************************/

#endif /* COMPLEX_SUPPORT */
