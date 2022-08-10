/**
 * Copyright (C) 2021 Xilinx, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
 /* This header file is shared between the DMA Proxy test application and the DMA Proxy device driver. It defines the
 * shared interface to allow DMA transfers to be done from user space.
 *
 * A set of channel buffers are created by the driver for the transmit and receive channel. The application may choose
 * to use only a subset of the channel buffers to allow prioritization of transmit vs receive.
 *
 * Note: the buffer in the data structure should be 1st in the channel interface so that the buffer is cached aligned,
 * otherwise there may be issues when using cached memory.
 */

#define BUFFER_SIZE 1024                    /* must match driver exactly */
#define BUFFER_COUNT 1						/* driver only */

#define TX_BUFFER_COUNT 	1
#define RX_BUFFER_COUNT 	8
#define BUFFER_INCREMENT	1				/* normally 1, but skipping buffers (2) defeats prefetching in the CPU */

#define START_CYCLIC 			_IOW('a','a',int32_t*)
#define STOP_CYCLIC 			_IOW('a','b',int32_t*)
#define PROXY_DMA_SET_SIGNAL	_IOW('a','c',int32_t*)
#define FINISH_XFER 			_IOW('a','d',int32_t*)
#define START_XFER 				_IOW('a','e',int32_t*)
#define XFER 					_IOR('a','f',int32_t*)

#define DT unsigned short
typedef struct d_buffer{
    DT x;
    DT y;
}d_buffer_t;

typedef struct signal_parameters{
    unsigned int on;
    unsigned int data;
    unsigned int period;
} signal_parameters;

struct dma_proxy_channel_interface {
    d_buffer_t buffer[BUFFER_SIZE*RX_BUFFER_COUNT];
    enum proxy_status { PROXY_NO_ERROR = 0, PROXY_BUSY = 1, PROXY_TIMEOUT = 2, PROXY_ERROR = 3 } status;
    unsigned int length;
} __attribute__ ((aligned (1024)));		/* 64 byte alignment required for DMA, but 1024 handy for viewing memory */



