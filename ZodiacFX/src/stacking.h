/**
 * @file
 * command.c
 *
 * This file contains the command line functions
 *
 */

/*
 * This file is part of the Zodiac FX firmware.
 * Copyright (c) 2016 Northbound Networks.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Paul Zanna <paul@northboundnetworks.com>
 *
 *
 */


#ifndef STACKING_H_
#define STACKING_H_

#define SPI_Handler     SPI_Handler
#define SPI_IRQn        SPI_IRQn

#define SPI_SEND_READY	0
#define SPI_SEND_STATS	1
#define SPI_SEND_PKT	2
#define SPI_RECEIVE		3
#define SPI_RCV_PREAMBLE	4
#define SPI_STATS_PREAMBLE		0xABAB
#define SPI_PACKET_PREAMBLE		0xBCBC
#define SPI_SEND_WAIT		0
#define SPI_HEADER_SIZE	14

struct spi_port_stats {
	uint16_t preamble;
	uint16_t spi_size;
	uint8_t port_status[4];
	uint8_t last_port_status[4];
	uint64_t rx_bytes[4];
    uint64_t tx_bytes[4];
    uint64_t rx_dropped[4];
    uint64_t tx_dropped[4];
};

struct spi_packet {
	uint16_t preamble;		// Transmission preamble
	uint16_t spi_size;		// SPI transmission size
	uint32_t ul_rcv_size;	// Actual packet size
	uint32_t spi_crc;		// Calculated CRC of packet
	uint8_t tag;			// Port number (1-8, or 255)
	uint8_t pad;			// Pad to 14 bytes
	uint8_t pkt_buffer[GMAC_FRAME_LENTGH_MAX];
};

struct spi_debug_stats {
	uint32_t master_tx_count;
	uint32_t master_rx_count;
	uint32_t master_rx_error_bad_preamble;
	uint32_t master_rx_error_bad_size;
	uint32_t master_rx_error_bad_crc;
};
	
void stacking_init(bool master);
void MasterReady(void);
void MasterStackSend(uint8_t *p_uc_data, uint16_t ul_size, uint32_t port);
void MasterStackRcv(void);
void Slave_timer(void);

// ***** Stacking Test Functions *****
uint8_t masterslave_test(void);		// Send pattern from master -> slave
uint8_t slavemaster_test(void);		// Send pattern from slave -> master

#endif /* STACKING_H_ */