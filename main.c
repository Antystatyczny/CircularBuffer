
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
//#include <atomic>

#define CB_RESULT_OK		0
#define CB_RESULT_ERROR		2

#define CB_DATA_TYPE		uint8_t
#define CB_BUFFER_LENGTH	64

typedef struct
{
	CB_DATA_TYPE *buffer;
	uint8_t buffer_length;
	volatile uint8_t head;
	volatile uint8_t tail;
	volatile uint8_t free;
}CB_handle_t;

uint8_t CB_init(CB_handle_t* h, CB_DATA_TYPE* buf, uint8_t len);
uint8_t CB_is_empty(CB_handle_t* h);
uint8_t CB_is_full(CB_handle_t* h);
uint8_t CB_push(CB_handle_t* h, CB_DATA_TYPE data);
uint8_t CB_pop(CB_handle_t* h, CB_DATA_TYPE* data);
uint8_t CB_flush(CB_handle_t* h);


CB_DATA_TYPE buf[CB_BUFFER_LENGTH];






int main(void)
{
	CB_handle_t uart;

	CB_init(&uart, buf, CB_BUFFER_LENGTH);
	

	return 0;
}

uint8_t  CB_init(CB_handle_t* h, CB_DATA_TYPE* buf, uint8_t len)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0 && len <= UINT8_MAX)
	{
		h->buffer = buf;
		h->buffer_length = len;
		h->head = 0;
		h->tail = 0;
		h->free = len;
	}
	else
	{
		result = CB_RESULT_ERROR;
	}

	return result;
}

uint8_t CB_is_empty(CB_handle_t* h)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0)
	{
		result = (h->free == h->buffer_length) ? 1 : 0;
	}
	else
	{
		result = CB_RESULT_ERROR;
	}
		
	return result;
}

uint8_t CB_is_full(CB_handle_t* h)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0)
	{
		result = (h->free) ? 0 : 1;
	}
	else
	{
		result = CB_RESULT_ERROR;
	}
	
	return result;
}

uint8_t CB_push(CB_handle_t* h, CB_DATA_TYPE data)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0)
	{
		if (CB_is_full(h) == 0)
		{
			/* TODO atomic access */
			h->buffer[h->head] = data;
			h->free--;
			if (++h->head == h->buffer_length) h->head = 0;
		}
	}
	else
	{
		result = CB_RESULT_ERROR;
	}

	return result;
}

uint8_t CB_pop(CB_handle_t* h, CB_DATA_TYPE* data)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0 && data != 0)
	{
		/* TODO atomic access */
		*data = h->buffer[h->tail];
		h->free++;
		if (++h->tail == h->buffer_length) h->tail = 0;
	}
	else
	{
		result = CB_RESULT_ERROR;
	}

	return result;
}

uint8_t CB_flush(CB_handle_t* h)
{
	uint8_t result = CB_RESULT_OK;

	if (h != 0)
	{
		h->head = 0;
		h->tail = 0;
		h->free = h->buffer_length;
	}
	else
	{
		result = CB_RESULT_ERROR;
	}

	return result;
}