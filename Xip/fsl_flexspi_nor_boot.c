/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_flexspi_nor_boot.h"

#if (defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1))
	#if defined(__CC_ARM) || defined(__GNUC__)
    	__attribute__((section(".boot_hdr.ivt")))
	#elif defined(__ICCARM__)
		#pragma location=".boot_hdr.ivt"
#endif
/************************************* 
 *  IVT Data 
 *************************************/
const ivt image_vector_table = {
  IVT_HEADER,                         /* IVT Header */
  IMAGE_ENTRY_ADDRESS,                /* Image Entry Function */
  IVT_RSVD,                           /* Reserved = 0 */
  (uint32_t)DCD_ADDRESS,              /* Address where DCD information is stored */
  (uint32_t)BOOT_DATA_ADDRESS,        /* Address where BOOT Data Structure is stored */
  (uint32_t)&image_vector_table,      /* Pointer to IVT Self (absolute address */
  (uint32_t)CSF_ADDRESS,              /* Address where CSF file is stored */
  IVT_RSVD                            /* Reserved = 0 */
};

#if defined(__CC_ARM) || defined(__GNUC__)
    __attribute__((section(".boot_hdr.boot_data")))
#elif defined(__ICCARM__)
	#pragma location=".boot_hdr.boot_data"
#endif
/************************************* 
 *  Boot Data 
 *************************************/
const BOOT_DATA_T boot_data = {
  FLASH_BASE,                 /* boot start location */
  FLASH_SIZE,                 /* size */
  PLUGIN_FLAG,                /* Plugin flag*/
  0xFFFFFFFF  				  /* empty - extra data word */
};

#if (defined(USE_EXTERNAL_SDRAM) && (USE_EXTERNAL_SDRAM == 1)) && \
	(defined(XIP_BOOT_HEADER_DCD_ENABLE) && (XIP_BOOT_HEADER_DCD_ENABLE == 1))
	#if defined(__CC_ARM) || defined(__GNUC__)
		__attribute__((section(".boot_hdr.dcd_data")))
	#elif defined(__ICCARM__)
		#pragma location=".boot_hdr.dcd_data"
	#endif
	/************************************* 
	*  DCD Data 
	 *************************************/
	const uint8_t dcd_sdram[1044] = {
		/*0000*/ 0xD2, 0x04, 0x14, 0x41, 0xCC, 0x02, 0xF4, 0x04, 0x40, 0x0F, 0xC0, 0x68, 0xFF, 0xFF, 0xFF, 0xFF, 
		/*0010*/ 0x40, 0x0F, 0xC0, 0x6C, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x0F, 0xC0, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 
		/*0020*/ 0x40, 0x0F, 0xC0, 0x74, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x0F, 0xC0, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 
		/*0030*/ 0x40, 0x0F, 0xC0, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x0F, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 
		/*0040*/ 0x40, 0x0D, 0x80, 0x30, 0x00, 0x00, 0x20, 0x01, 0x40, 0x0D, 0x81, 0x00, 0x00, 0x1D, 0x00, 0x00, 
		/*0050*/ 0x40, 0x0F, 0xC0, 0x14, 0x00, 0x09, 0x83, 0x40, 0x40, 0x1F, 0x80, 0x14, 0x00, 0x00, 0x00, 0x00, 
		/*0060*/ 0x40, 0x1F, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x1C, 0x00, 0x00, 0x00, 0x00, 
		/*0070*/ 0x40, 0x1F, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x24, 0x00, 0x00, 0x00, 0x00, 
		/*0080*/ 0x40, 0x1F, 0x80, 0x28, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x2C, 0x00, 0x00, 0x00, 0x00, 
		/*0090*/ 0x40, 0x1F, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x34, 0x00, 0x00, 0x00, 0x00, 
		/*00a0*/ 0x40, 0x1F, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x3C, 0x00, 0x00, 0x00, 0x00, 
		/*00b0*/ 0x40, 0x1F, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x44, 0x00, 0x00, 0x00, 0x00, 
		/*00c0*/ 0x40, 0x1F, 0x80, 0x48, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x4C, 0x00, 0x00, 0x00, 0x00, 
		/*00d0*/ 0x40, 0x1F, 0x80, 0x50, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x54, 0x00, 0x00, 0x00, 0x00, 
		/*00e0*/ 0x40, 0x1F, 0x80, 0x58, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x5C, 0x00, 0x00, 0x00, 0x00, 
		/*00f0*/ 0x40, 0x1F, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x64, 0x00, 0x00, 0x00, 0x00, 
		/*0100*/ 0x40, 0x1F, 0x80, 0x68, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x6C, 0x00, 0x00, 0x00, 0x00, 
		/*0110*/ 0x40, 0x1F, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x74, 0x00, 0x00, 0x00, 0x00, 
		/*0120*/ 0x40, 0x1F, 0x80, 0x78, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x7C, 0x00, 0x00, 0x00, 0x00, 
		/*0130*/ 0x40, 0x1F, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x84, 0x00, 0x00, 0x00, 0x00, 
		/*0140*/ 0x40, 0x1F, 0x80, 0x88, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x8C, 0x00, 0x00, 0x00, 0x00, 
		/*0150*/ 0x40, 0x1F, 0x80, 0x90, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x94, 0x00, 0x00, 0x00, 0x00, 
		/*0160*/ 0x40, 0x1F, 0x80, 0x98, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0x9C, 0x00, 0x00, 0x00, 0x00, 
		/*0170*/ 0x40, 0x1F, 0x80, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0xA4, 0x00, 0x00, 0x00, 0x00, 
		/*0180*/ 0x40, 0x1F, 0x80, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x80, 0xAC, 0x00, 0x00, 0x00, 0x00, 
		/*0190*/ 0x40, 0x1F, 0x80, 0xB0, 0x00, 0x00, 0x00, 0x10, 0x40, 0x1F, 0x80, 0xB4, 0x00, 0x00, 0x00, 0x00, 
		/*01a0*/ 0x40, 0x1F, 0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1F, 0x82, 0x04, 0x00, 0x00, 0x00, 0xF1, 
		/*01b0*/ 0x40, 0x1F, 0x82, 0x08, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x0C, 0x00, 0x00, 0x00, 0xF1, 
		/*01c0*/ 0x40, 0x1F, 0x82, 0x10, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x14, 0x00, 0x00, 0x00, 0xF1, 
		/*01d0*/ 0x40, 0x1F, 0x82, 0x18, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x1C, 0x00, 0x00, 0x00, 0xF1, 
		/*01e0*/ 0x40, 0x1F, 0x82, 0x20, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x24, 0x00, 0x00, 0x00, 0xF1, 
		/*01f0*/ 0x40, 0x1F, 0x82, 0x28, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x2C, 0x00, 0x00, 0x00, 0xF1, 
		/*0200*/ 0x40, 0x1F, 0x82, 0x30, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x34, 0x00, 0x00, 0x00, 0xF1, 
		/*0210*/ 0x40, 0x1F, 0x82, 0x38, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x3C, 0x00, 0x00, 0x00, 0xF1, 
		/*0220*/ 0x40, 0x1F, 0x82, 0x40, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x44, 0x00, 0x00, 0x00, 0xF1, 
		/*0230*/ 0x40, 0x1F, 0x82, 0x48, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x4C, 0x00, 0x00, 0x00, 0xF1, 
		/*0240*/ 0x40, 0x1F, 0x82, 0x50, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x54, 0x00, 0x00, 0x00, 0xF1, 
		/*0250*/ 0x40, 0x1F, 0x82, 0x58, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x5C, 0x00, 0x00, 0x00, 0xF1, 
		/*0260*/ 0x40, 0x1F, 0x82, 0x60, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x64, 0x00, 0x00, 0x00, 0xF1, 
		/*0270*/ 0x40, 0x1F, 0x82, 0x68, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x6C, 0x00, 0x00, 0x00, 0xF1, 
		/*0280*/ 0x40, 0x1F, 0x82, 0x70, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x74, 0x00, 0x00, 0x00, 0xF1, 
		/*0290*/ 0x40, 0x1F, 0x82, 0x78, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x7C, 0x00, 0x00, 0x00, 0xF1, 
		/*02a0*/ 0x40, 0x1F, 0x82, 0x80, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x84, 0x00, 0x00, 0x00, 0xF1, 
		/*02b0*/ 0x40, 0x1F, 0x82, 0x88, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x8C, 0x00, 0x00, 0x00, 0xF1, 
		/*02c0*/ 0x40, 0x1F, 0x82, 0x90, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x94, 0x00, 0x00, 0x00, 0xF1, 
		/*02d0*/ 0x40, 0x1F, 0x82, 0x98, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0x9C, 0x00, 0x00, 0x00, 0xF1, 
		/*02e0*/ 0x40, 0x1F, 0x82, 0xA0, 0x00, 0x00, 0x00, 0xF1, 0x40, 0x1F, 0x82, 0xA4, 0x00, 0x00, 0x00, 0xF1, 
		/*02f0*/ 0x40, 0x1F, 0x82, 0xA8, 0x00, 0x00, 0x00, 0xF1, 0xCC, 0x00, 0x0C, 0x14, 0x40, 0x2F, 0x00, 0x00, 
		/*0300*/ 0x00, 0x00, 0x00, 0x02, 0xCC, 0x00, 0x9C, 0x04, 0x40, 0x2F, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 
		/*0310*/ 0x40, 0x2F, 0x00, 0x08, 0x00, 0x03, 0x05, 0x24, 0x40, 0x2F, 0x00, 0x0C, 0x06, 0x03, 0x05, 0x24, 
		/*0320*/ 0x40, 0x2F, 0x00, 0x10, 0x80, 0x00, 0x00, 0x21, 0x40, 0x2F, 0x00, 0x14, 0x90, 0x00, 0x00, 0x21, 
		/*0330*/ 0x40, 0x2F, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x40, 0x2F, 0x00, 0x40, 0x00, 0x00, 0x0B, 0x27, 
		/*0340*/ 0x40, 0x2F, 0x00, 0x44, 0x00, 0x10, 0x01, 0x00, 0x40, 0x2F, 0x00, 0x48, 0x00, 0x02, 0x02, 0x01, 
		/*0350*/ 0x40, 0x2F, 0x00, 0x4C, 0x08, 0x19, 0x3D, 0x0E, 0x40, 0x2F, 0x00, 0x74, 0x00, 0x65, 0x29, 0x22, 
		/*0360*/ 0x40, 0x2F, 0x00, 0x78, 0x00, 0x01, 0x09, 0x20, 0x40, 0x2F, 0x00, 0x7C, 0x50, 0x21, 0x0A, 0x08, 
		/*0370*/ 0x40, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x21, 0x40, 0x2F, 0x00, 0x84, 0x00, 0x88, 0x88, 0x88, 
		/*0380*/ 0x40, 0x2F, 0x00, 0x94, 0x00, 0x00, 0x00, 0x02, 0x40, 0x2F, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 
		/*0390*/ 0x40, 0x2F, 0x00, 0x90, 0x80, 0x00, 0x00, 0x00, 0x40, 0x2F, 0x00, 0x9C, 0xA5, 0x5A, 0x00, 0x0F, 
		/*03a0*/ 0xCF, 0x00, 0x0C, 0x1C, 0x40, 0x2F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0xCC, 0x00, 0x14, 0x04, 
		/*03b0*/ 0x40, 0x2F, 0x00, 0x90, 0x80, 0x00, 0x00, 0x00, 0x40, 0x2F, 0x00, 0x9C, 0xA5, 0x5A, 0x00, 0x0C, 
		/*03c0*/ 0xCF, 0x00, 0x0C, 0x1C, 0x40, 0x2F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0xCC, 0x00, 0x14, 0x04, 
		/*03d0*/ 0x40, 0x2F, 0x00, 0x90, 0x80, 0x00, 0x00, 0x00, 0x40, 0x2F, 0x00, 0x9C, 0xA5, 0x5A, 0x00, 0x0C, 
		/*03e0*/ 0xCF, 0x00, 0x0C, 0x1C, 0x40, 0x2F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0xCC, 0x00, 0x1C, 0x04, 
		/*03f0*/ 0x40, 0x2F, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x22, 0x40, 0x2F, 0x00, 0x90, 0x80, 0x00, 0x00, 0x00, 
		/*0400*/ 0x40, 0x2F, 0x00, 0x9C, 0xA5, 0x5A, 0x00, 0x0A, 0xCF, 0x00, 0x0C, 0x1C, 0x40, 0x2F, 0x00, 0x3C, 
		/*0410*/ 0x00, 0x00, 0x00, 0x01, 
	};
#else
	const uint8_t dcd_data[] = {0x00, 0x00};
#endif

#endif

