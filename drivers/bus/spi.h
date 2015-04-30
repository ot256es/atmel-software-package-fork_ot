/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \file
 *
 * Interface for Serial Peripheral Interface (SPI) controller.
 *
 */

#ifndef _SPI_
#define _SPI_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/**
 *
 * Here are several macros which should be used when configuring a SPI
 * peripheral.
 *
 * \section spi_configuration_macros SPI Configuration Macros
 * - \ref SPI_PCS
 * - \ref SPI_SCBR
 * - \ref SPI_DLYBS
 * - \ref SPI_DLYBCT
 */

/** Calculate the PCS field value given the chip select NPCS value */
#define SPI_PCS(npcs)       SPI_MR_PCS((~(1 << npcs) & 0xF))

/** Calculates the value of the CSR SCBR field given the baudrate and MCK. */
#define SPI_SCBR(baudrate, masterClock) SPI_CSR_SCBR((uint32_t)(masterClock / baudrate))

/** Calculates the value of the CSR DLYBS field given the desired delay (in ns) */
#define SPI_DLYBS(delay, masterClock)  SPI_CSR_DLYBS((uint32_t) (((masterClock / 1000000) * delay) / 1000)+1)

/** Calculates the value of the CSR DLYBCT field given the desired delay (in ns) */
#define SPI_DLYBCT(delay, masterClock) SPI_CSR_DLYBCT ((uint32_t) (((masterClock / 1000000) * delay) / 32000)+1)

/*------------------------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void spi_enable(Spi * spi);
extern void spi_disable(Spi * spi);

extern void spi_enable_it(Spi * spi, uint32_t dwSources);
extern void spi_disable_it(Spi * spi, uint32_t dwSources);

extern void spi_configure(Spi * spi, uint32_t dwId,
			  uint32_t dwConfiguration);
extern void spi_set_mode(Spi * spi, uint32_t dwConfiguration);

extern void spi_chip_select(Spi * spi, uint8_t cS);
extern void spi_release_cs(Spi * spi);

extern void spi_configure_npcs(Spi * spi, uint32_t dwNpcs,
			      uint32_t dwConfiguration);
extern void spi_configure_cs_mode(Spi * spi, uint32_t dwNpcs,
				uint32_t bReleaseOnLast);

extern uint32_t spi_read(Spi * spi);
extern void spi_write(Spi * spi, uint32_t dwNpcs, uint16_t wData);
extern void spi_write_last(Spi * spi, uint32_t dwNpcs, uint16_t wData);

extern uint32_t spi_get_status(Spi * spi);
extern uint32_t spi_is_finished(Spi * pSpi);

#ifdef __cplusplus
}
#endif
#endif  /* #ifndef _SPI_ */
