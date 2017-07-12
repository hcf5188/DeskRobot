/******************************************************************************
 *                                                                            *
 * This program is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE. This file and program are licensed    *
 * under the GNU Lesser General Public License Version 3, 29 June 2007.       *
 * The complete license can be accessed from the following location:          *
 * http://opensource.org/licenses/lgpl-3.0.html                               *
 *                                                                            *
 * Author: Yun Li (yunli.open@gmail.com)                                      *
 *   Date: 07/30/2010                                                         *
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
  REVISION HISTORY
  ================
  
  Date     Version  Name          Description
  -------- -------  ------------  -------------------------------------------------

  -------- -------  ------------  --------------------------------------------

 ******************************************************************************/

#ifndef __FIFO_H
#define __FIFO_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define CLEAE_CAN( A )   (*((volatile unsigned long  *)( (A) + 0x0008)) ) = 0
#define GET_CANERR( A )  (*((volatile unsigned long  *)( (A) + 0x0008)) )

#define BOOL int   
#define FIFO_BUFFER_DECLARE(_name, _element_size, _capacity)  \
    static byte_t _name [_element_size * _capacity]

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

// for size 
typedef uint32_t usize_t;

typedef uint8_t byte_t;         

typedef struct _fifo_t{
    // fifo里可以容纳多少个元素单元
    usize_t capacity_;     
    // 元素单元的buffer地址
    byte_t *buffer_addr_start_;
    byte_t *buffer_addr_end_;
    // 元素单元数
    usize_t element_size_;
    // fifo里当前有多少个元素单元
    usize_t count_;
    // 指向可以获取的下一个元素的位置
    byte_t *cursor_get_;
    // 指向可以放入的下一个元素的位置
    byte_t *cursor_put_;
} fifo_t, *fifo_handle_t;

#ifdef __cplusplus
extern "C"  {
#endif
  
void fifo_init (fifo_handle_t _handle, void *_buffer,
    usize_t _element_size, usize_t _capacity);
void fifo_element_put (fifo_handle_t _handle, const void *_p_element);
void fifo_element_get (fifo_handle_t _handle, void *_p_element);


static inline BOOL fifo_is_empty (const fifo_handle_t _handle)
{
    return (BOOL)(0 == _handle->count_);
}

static inline BOOL fifo_is_full (const fifo_handle_t _handle)
{
    return (BOOL)(_handle->count_ == _handle->capacity_);
}

static inline usize_t fifo_capacity (const fifo_handle_t _handle)
{
    return _handle->capacity_;
}
 
static inline usize_t fifo_count (const fifo_handle_t _handle)
{
    return _handle->count_;
}

static inline usize_t fifo_element_size (const fifo_handle_t _handle)
{
    return _handle->element_size_;
}

#ifdef __cplusplus
}
#endif


#endif
