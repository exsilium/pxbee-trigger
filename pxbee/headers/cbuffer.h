/****************************************************************************
 * Copyright (C) 2011 - 2015 Digi International Inc, All Rights Reserved.
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

#ifndef __CBUFFER_H_
#define __CBUFFER_H_

#include <types.h>

struct cbuf {
	uint8_t head;
	uint8_t tail;
	uint8_t blen;
	uint8_t *buf;
};

void cbuf_init(struct cbuf *cb, void *buffer, uint8_t buflen);
uint8_t cbuf_data_in_buf(struct cbuf *cb);
uint8_t cbuf_space_in_buf(struct cbuf *cb);
bool_t is_cbuf_emtpy(struct cbuf *cb);
bool_t is_cbuf_full(struct cbuf *cb);
void cbuf_flush(struct cbuf *cb);
void cbuf_append(struct cbuf *cb, uint8_t data);
int cbuf_get(struct cbuf *cb);
uint8_t cbuf_get_nocheck(struct cbuf *cb);

#endif /* __CBUFFER_H_ */
