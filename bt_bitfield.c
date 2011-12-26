
/**
 * @file
 * @author  Willem Thiart himself@willemthiart.com
 * @version 0.1
 *
 * @section LICENSE
 * Copyright (c) 2011, Willem-Hendrik Thiart
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The names of its contributors may not be used to endorse or promote
      products derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL WILLEM-HENDRIK THIART BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdbool.h>
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>

#include "bt.h"
#include "bt_local.h"

void bt_bitfield_init(
    bt_bitfield_t * bf,
    const int nbits
)
{
//    assert(0 < nbits);
    bf->bits = calloc(nbits, sizeof(uint32_t));
    bf->size = nbits;
//    bf->bits = realloc(bf->bits, sizeof(uint32_t) * nbits);
}

void bt_bitfield_mark(
    bt_bitfield_t * bf,
    const int bit
)
{
    int cint;

    assert(bf->bits);
    assert(0 <= bit);
    assert(bit < bf->size);

    cint = bit / 32;
    bf->bits[cint] |= 1 << (31 - bit % 32);
}

void bt_bitfield_unmark(
    bt_bitfield_t * bf,
    const int bit
)
{
    assert(bf->bits);
    assert(0 <= bit);
    assert(bit < bf->size);


}

int bt_bitfield_is_marked(
    bt_bitfield_t * bf,
    const int bit
)
{
    assert(bf->bits);
    assert(0 <= bit);
    assert(bit < bf->size);

    int cint;

    cint = bit / 32;
    return 0 != (bf->bits[cint] & (1 << (31 - bit % 32)));
}

int bt_bitfield_get_length(
    bt_bitfield_t * bf
)
{
    return bf->size;
}

char *bt_bitfield_str(
    bt_bitfield_t * bf
)
{
    char *str;

    int ii;

    str = malloc(bf->size + 1);

    for (ii = 0; ii < bf->size; ii++)
    {
        str[ii] = bt_bitfield_is_marked(bf, ii) ? '1' : '0';
    }

    str[bf->size] = '\0';
    return str;
}