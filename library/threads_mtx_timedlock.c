/*
 * Copyright (c) 2021 Ola S�der
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _THREADS_HEADERS_H
#include "threads_headers.h"
#endif

/*------------------------------------------------------------------------------
 __mtx_trylock_callback

 Description: Polling mutex callback used in combination with __eclock_poll.
 Input:       void *data - callback function input data.
 Return:      int - 'thrd_success' if conditions are met in time,
              'thrd_timedout' on timeout and 'thrd_error' on error.
*/
static int __mtx_trylock_callback(void *data)
{
    ENTER();
    assert(data);

    FOG(("Attempt to lock mutex.\n"));
    int status = mtx_trylock((mtx_t *) data);

    LEAVE();
    return status;
}

int mtx_timedlock(mtx_t *restrict mutex,
                  const struct timespec *restrict time_point)
{
    ENTER();
    assert(mutex && mutex->mutex && time_point);

    if(unlikely(!(mutex->type & mtx_timed)))
    {
        LEAVE();
        return thrd_error;
    }

    FOG(("Attempt to lock mutex.\n"));
    int lock = mtx_trylock(mutex);

    if(lock != thrd_busy)
    {
        LEAVE();
        return lock;
    }

    FOG(("Poll mutex with timeout.\n"));
    int status = __eclock_poll(__mtx_trylock_callback, mutex,
        __eclock_future(time_point), POLL_STRIDE);

    LEAVE();
    return status;
}
