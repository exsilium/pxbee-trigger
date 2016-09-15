/****************************************************************************
 * Copyright (C) 2010 - 2015 Digi International Inc, All Rights Reserved.
 *
 * This software is provided as instructional material without charge 
 * by Digi International for use by its employees and customers
 * subject to the following terms.
 *
 * PERMISSION
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software, to deal with it without restriction, 
 * including without limitation the rights to use, copy,  modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of it, and to permit persons to 
 * whom it is furnished to do so, provided the above copyright notice 
 * and this permission notice are included in all derived works
 * and the use of this software is restricted to Digi products.
 *
 * WARRANTY
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.  
 *
 * LIABILITY
 * IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES, 
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, 
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE 
 * OR OTHER DEALINGS WITH THE SOFTWARE.
 *
 ****************************************************************************/

#include <system.h>
#include <types.h>
#include <cbuffer.h>

void cbuf_init(struct cbuf *cb, void *buffer, uint8_t buflen)
{
	cb->head = 0;
	cb->tail = 0;
	cb->buf = (uint8_t *)buffer;
	cb->blen = buflen;
}

uint8_t cbuf_data_in_buf(struct cbuf *cb)
{
	return (uint8_t)((cb->blen + cb->head - cb->tail) % cb->blen);	
}

uint8_t cbuf_space_in_buf(struct cbuf *cb)
{
	return (uint8_t)(cb->blen - cbuf_data_in_buf(cb) - 1);
}

bool_t is_cbuf_emtpy(struct cbuf *cb)
{
	return cb->head == cb->tail;
}

void cbuf_flush(struct cbuf *cb)
{
	cb->head = cb->tail;
}

bool_t is_cbuf_full(struct cbuf *cb)
{
	return ((cb->head + 1) % cb->blen) == cb->tail;
}

void cbuf_append(struct cbuf *cb, uint8_t data)
{
	uint8_t nhead = (uint8_t)((cb->head + 1) % cb->blen);
	
	if (nhead != cb->tail) {
		cb->buf[cb->head] = data;
		cb->head = nhead;
	}
}

int cbuf_get(struct cbuf *cb)
{
	uint8_t data;
	
	if (is_cbuf_emtpy(cb))
		return -ENOENT;
	
	data = cb->buf[cb->tail];
	cb->tail = (uint8_t)((cb->tail + 1) % cb->blen);
	
	return (int)data;
}

uint8_t cbuf_get_nocheck(struct cbuf *cb)
{
	uint8_t data;
	
	data = cb->buf[cb->tail];
	cb->tail = (uint8_t)((cb->tail + 1) % cb->blen);
	
	return data;
}

