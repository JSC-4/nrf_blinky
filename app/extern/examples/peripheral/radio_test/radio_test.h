/**
 * Copyright (c) 2012-2020 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef RADIO_TEST_H
#define RADIO_TEST_H

#include <stdint.h>

#include "nrf_radio.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Indicates devices that support BLE LR and 802.15.4 radio modes. */
#if defined(NRF52840_XXAA) || defined(NRF52833_XXAA)
    #define USE_MORE_RADIO_MODES 1
#else
    #define USE_MORE_RADIO_MODES 0
#endif

#define RADIO_MAX_PAYLOAD_LEN     256   /**< Maximum radio RX or TX payload. */
#define IEEE_MAX_PAYLOAD_LEN      127   /**< IEEE 802.15.4 maximum payload length. */
#define IEEE_MIN_CHANNEL          11    /**< IEEE 802.15.4 minimum channel. */
#define IEEE_MAX_CHANNEL          26    /**< IEEE 802.15.4 maximum channel. */

/**@brief Radio transmit and address pattern.
 */
typedef enum
{
    TRANSMIT_PATTERN_RANDOM,   /**< Random pattern generated by RNG. */
    TRANSMIT_PATTERN_11110000, /**< Pattern 11110000(F0). */
    TRANSMIT_PATTERN_11001100, /**< Pattern 11001100(CC). */
} transmit_pattern_t;

/**@brief Radio test mode. */
typedef enum  {
    UNMODULATED_TX,          /**< TX carrier. */
    MODULATED_TX,            /**< Modulated TX carrier. */
    RX,                      /**< RX carrier. */
    TX_SWEEP,                /**< TX carrier sweep. */
    RX_SWEEP,                /**< RX carrier sweep. */
    MODULATED_TX_DUTY_CYCLE, /**< Duty-cycled modulated TX carrier. */
} radio_test_mode_t;

/**@brief Radio test configuration. */
typedef struct {
    radio_test_mode_t type; /**< Radio test type. */
    nrf_radio_mode_t mode;  /**< Radio mode. Data rate and modulation. */

    union {
        struct {
            nrf_radio_txpower_t txpower; /**< Radio output power. */
            uint8_t channel;             /**< Radio channel. */
        } unmodulated_tx;                /**< TX carrier Parameters. */

        struct {
            nrf_radio_txpower_t txpower; /**< Radio output power. */
            transmit_pattern_t pattern;  /**< Radio transmission pattern. */
            uint8_t channel;             /**< Radio channel. */
            uint32_t packets_num;        /**< Number of pacets to transmit. Set to zero for continuous TX. */
            void (*cb)(void);            /**< Callback to indicate that TX is finished. */
        } modulated_tx;                  /**< Modulated TX carrier Parameters. */

        struct {
            transmit_pattern_t pattern; /**< Radio transmission pattern. */
            uint8_t channel;            /**< Radio channel. */
        } rx;                           /**< RX carrier Parameters. */

        struct {
                nrf_radio_txpower_t txpower; /**< Radio output power. */
                uint8_t channel_start;       /**< Radio start channel (frequency). */
                uint8_t channel_end;         /**< Radio end channel (frequency). */
                uint32_t delay_ms;           /**< Delay time in milliseconds. */
        } tx_sweep;                          /**< TX carrier sweep Parameters. */

        struct {
                uint8_t channel_start; /**< Radio start channel (frequency). */
                uint8_t channel_end;   /**< Radio end channel (frequency). */
                uint32_t delay_ms;     /**< Delay time in milliseconds. */
        } rx_sweep;                    /**< RX carrier sweep Parameters. */

        struct {
            nrf_radio_txpower_t txpower; /**< Radio output power. */
            transmit_pattern_t pattern;  /**< Radio transmission pattern. */
            uint8_t channel;             /**< Radio channel. */
            uint32_t duty_cycle;         /**< Duty cycle. */
        } modulated_tx_duty_cycle;       /**< Duty-cycled modulated TX carrier Parameters. */
    } params; /**< Test Parameters. */

} radio_test_config_t;

/**@brief Radio RX statistics. */
typedef struct {
        struct {
                uint8_t *buf; /**< Content of the last packet. */
                size_t len;   /**< Length of the last packet. */
        } last_packet;        /**< The last packet descriptor. */

        uint32_t packet_cnt; /**< Number of received packets with valid CRC. */
} radio_rx_stats_t;

/**
 * @brief Function for initializing the Radio Test module.
 *
 * @param[in] p_config  Radio test configuration.
 */
void radio_test_init(radio_test_config_t * p_config);

/**
 * @brief Function for starting radio test.
 *
 * @param[in] p_config  Radio test configuration.
 */
void radio_test_start(radio_test_config_t * p_config);

/**
 * @brief Function for stopping ongoing test (Radio and Timer operations).
 */
void radio_test_cancel(void);

/**
 * @brief Function for get RX statistics.
 *
 * @param[out] p_rx_stats RX statistics.
 */
void radio_rx_stats_get(radio_rx_stats_t * p_rx_stats);

/**
 * @brief Function for toggling the DC/DC converter state.
 *
 * @param[in] dcdc_state  DC/DC converter state.
 */
void toggle_dcdc_state(uint8_t dcdc_state);


#ifdef __cplusplus
}
#endif

#endif
