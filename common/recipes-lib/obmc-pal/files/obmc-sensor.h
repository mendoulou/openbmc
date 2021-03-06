/*
 *
 * Copyright 2017-present Facebook. All Rights Reserved.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __OBMC_SENSOR_H__
#define __OBMC_SENSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* Error codes returned */
#define ERR_UNKNOWN_FRU -1
#define ERR_SENSOR_NA   -2
#define ERR_FAILURE     -3

/* Range for sensor num for various sensors */
#define PHYSICAL_SENSOR_START   0
#define PHYSICAL_SENSOR_END     0xff
#define AGGREGATE_SENSOR_START  0x100

/* FRU used for aggregate sensors */
#define AGGREGATE_SENSOR_FRU_ID   0xff
#define AGGREGATE_SENSOR_FRU_NAME "aggregate"

/* Functions */

/* Read a cached value of the given sensor */
int sensor_cache_read(uint8_t fru, uint8_t sensor_num, float *value);

/* Writes the cache explicitly */
int sensor_cache_write(uint8_t fru, uint8_t sensor_num, bool available, float value);

/* Read the sensor history */
int sensor_read_history(uint8_t fru, uint8_t sensor_num, float *min,
               float *average, float *max, int start_time);

/* Clear the sensor history */
int sensor_clear_history(uint8_t fru, uint8_t sensor_num);

/* Read sensor directly from the hardware. Note, this function does not
 * protect the caller from other readers. The caller should ensure 
 * exclusivity. The simplest method being limiting all calls to this
 * function to a single daemon. */
int sensor_raw_read(uint8_t fru, uint8_t sensor_num, float *value);
#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __OBMC_SENSOR_H__ */
