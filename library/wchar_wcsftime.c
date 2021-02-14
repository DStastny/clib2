/*
 * Copyright 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Imported and modified 2021/01/25
 */

#ifndef _WCHAR_HEADERS_H
#include "wchar_headers.h"
#endif /* _WCHAR_HEADERS_H */

/****************************************************************************/

size_t
wcsftime(wchar_t *s, size_t n, const wchar_t *f, const struct tm *tm)
{
	size_t l, k;
	char buf[100];
	wchar_t wbuf[100];
	wchar_t *p;
	const char *t_mb;
	const wchar_t *t;
	int plus;
	unsigned long width;
	for (l=0; l<n; f++) {
		if (!*f) {
			s[l] = 0;
			return l;
		}
		if (*f != '%') {
			s[l++] = *f;
			continue;
		}
		f++;
		if (*f == '-' || *f == '_' || *f == '0') f++;
		if ((plus = (*f == '+'))) f++;
		width = wcstoul(f, &p, 10);
		if (*p == 'C' || *p == 'F' || *p == 'G' || *p == 'Y') {
			if (!width && p!=f) width = 1;
		} else {
			width = 0;
		}
		f = p;
		if (*f == 'E' || *f == 'O') f++;
		t_mb = strftime(&buf, &k, *f, tm);
		if (!t_mb) break;
		k = mbstowcs(wbuf, t_mb, sizeof wbuf / sizeof *wbuf);
		if (k == (size_t)-1) return 0;
		t = wbuf;
		if (width) {
			for (; *t=='+' || *t=='-' || (*t=='0'&&t[1]); t++, k--);
			width--;
			if (plus && tm->tm_year >= 10000-1900)
				s[l++] = '+';
			else if (tm->tm_year < -1900)
				s[l++] = '-';
			else
				width++;
			for (; width > k && l < n; width--)
				s[l++] = '0';
		}
		if (k >= n-l) k = n-l;
		wmemcpy(s+l, t, k);
		l += k;
	}
	if (n) {
		if (l==n) l=n-1;
		s[l] = 0;
	}
	return 0;
}
