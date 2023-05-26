/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2019 Barefoot Networks, Inc.

 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of
 * Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Barefoot Networks,
 * Inc.
 * and its suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material is
 * strictly forbidden unless prior written permission is obtained from
 * Barefoot Networks, Inc.
 *
 * No warranty, explicit or implicit is provided, unless granted under a
 * written agreement with Barefoot Networks, Inc.
 *
 * $Id: $
 *
 ******************************************************************************/
/* bf_rmon.h
*
* This file contains the Comira UMAC RMON counters in a
* metadata form. Use this file to create whatever
* data/structures are most convenient for your
* application.
*
* The RMON counters are all 64-bit values. The
* number represents the ordinal value of a given
* counter. The DMA buffer returned in the completion
* callback after calling lld_port_update_mac_rmon_stats()
* contains 89  64-bit values representing the counters
* defined below.
*
* So, for example, you could create an enum for the counters
* to use as an index into a uint64_t array by doing the
* following,
*
* #define MAC_RMON_CTR( index, name ) \
*   name = index \
*
* typedef enum {
*     #include "bf_rmon.h"
*     NUM_UMAC_RMON_COUNTERS,
* } umac_rmon_counter_e;
*
*/
MAC_RMON_CTR(0, FramesReceivedOK)
MAC_RMON_CTR(1, FramesReceivedAll)
MAC_RMON_CTR(2, FramesReceivedwithFCSError)
MAC_RMON_CTR(3, FrameswithanyError)
MAC_RMON_CTR(4, OctetsReceivedinGoodFrames)
MAC_RMON_CTR(5, OctetsReceived)
MAC_RMON_CTR(6, FramesReceivedwithUnicastAddresses)
MAC_RMON_CTR(7, FramesReceivedwithMulticastAddresses)
MAC_RMON_CTR(8, FramesReceivedwithBroadcastAddresses)
MAC_RMON_CTR(9, FramesReceivedoftypePAUSE)
MAC_RMON_CTR(10, FramesReceivedwithLengthError)
MAC_RMON_CTR(11, FramesReceivedUndersized)
MAC_RMON_CTR(12, FramesReceivedOversized)
MAC_RMON_CTR(13, FragmentsReceived)
MAC_RMON_CTR(14, JabberReceived)
MAC_RMON_CTR(15, PriorityPauseFrames)
MAC_RMON_CTR(16, CRCErrorStomped)
MAC_RMON_CTR(17, FrameTooLong)
MAC_RMON_CTR(18, RxVLANFramesGood)
MAC_RMON_CTR(19, FramesDroppedBufferFull)
MAC_RMON_CTR(20, FramesReceivedLength_lt_64)
MAC_RMON_CTR(21, FramesReceivedLength_eq_64)
MAC_RMON_CTR(22, FramesReceivedLength_65_127)
MAC_RMON_CTR(23, FramesReceivedLength_128_255)
MAC_RMON_CTR(24, FramesReceivedLength_256_511)
MAC_RMON_CTR(25, FramesReceivedLength_512_1023)
MAC_RMON_CTR(26, FramesReceivedLength_1024_1518)
MAC_RMON_CTR(27, FramesReceivedLength_1519_2047)
MAC_RMON_CTR(28, FramesReceivedLength_2048_4095)
MAC_RMON_CTR(29, FramesReceivedLength_4096_8191)
MAC_RMON_CTR(30, FramesReceivedLength_8192_9215)
MAC_RMON_CTR(31, FramesReceivedLength_9216)
MAC_RMON_CTR(32, FramesTransmittedOK)
MAC_RMON_CTR(33, FramesTransmittedAll)
MAC_RMON_CTR(34, FramesTransmittedwithError)
MAC_RMON_CTR(35, OctetsTransmittedwithouterror)
MAC_RMON_CTR(36, OctetsTransmittedTotal)
MAC_RMON_CTR(37, FramesTransmittedUnicast)
MAC_RMON_CTR(38, FramesTransmittedMulticast)
MAC_RMON_CTR(39, FramesTransmittedBroadcast)
MAC_RMON_CTR(40, FramesTransmittedPause)
MAC_RMON_CTR(41, FramesTransmittedPriPause)
MAC_RMON_CTR(42, FramesTransmittedVLAN)
MAC_RMON_CTR(43, FramesTransmittedLength_lt_64)
MAC_RMON_CTR(44, FramesTransmittedLength_eq_64)
MAC_RMON_CTR(45, FramesTransmittedLength_65_127)
MAC_RMON_CTR(46, FramesTransmittedLength_128_255)
MAC_RMON_CTR(47, FramesTransmittedLength_256_511)
MAC_RMON_CTR(48, FramesTransmittedLength_512_1023)
MAC_RMON_CTR(49, FramesTransmittedLength_1024_1518)
MAC_RMON_CTR(50, FramesTransmittedLength_1519_2047)
MAC_RMON_CTR(51, FramesTransmittedLength_2048_4095)
MAC_RMON_CTR(52, FramesTransmittedLength_4096_8191)
MAC_RMON_CTR(53, FramesTransmittedLength_8192_9215)
MAC_RMON_CTR(54, FramesTransmittedLength_9216)
MAC_RMON_CTR(55, Pri0FramesTransmitted)
MAC_RMON_CTR(56, Pri1FramesTransmitted)
MAC_RMON_CTR(57, Pri2FramesTransmitted)
MAC_RMON_CTR(58, Pri3FramesTransmitted)
MAC_RMON_CTR(59, Pri4FramesTransmitted)
MAC_RMON_CTR(60, Pri5FramesTransmitted)
MAC_RMON_CTR(61, Pri6FramesTransmitted)
MAC_RMON_CTR(62, Pri7FramesTransmitted)
MAC_RMON_CTR(63, Pri0FramesReceived)
MAC_RMON_CTR(64, Pri1FramesReceived)
MAC_RMON_CTR(65, Pri2FramesReceived)
MAC_RMON_CTR(66, Pri3FramesReceived)
MAC_RMON_CTR(67, Pri4FramesReceived)
MAC_RMON_CTR(68, Pri5FramesReceived)
MAC_RMON_CTR(69, Pri6FramesReceived)
MAC_RMON_CTR(70, Pri7FramesReceived)
MAC_RMON_CTR(71, TransmitPri0Pause1USCount)
MAC_RMON_CTR(72, TransmitPri1Pause1USCount)
MAC_RMON_CTR(73, TransmitPri2Pause1USCount)
MAC_RMON_CTR(74, TransmitPri3Pause1USCount)
MAC_RMON_CTR(75, TransmitPri4Pause1USCount)
MAC_RMON_CTR(76, TransmitPri5Pause1USCount)
MAC_RMON_CTR(77, TransmitPri6Pause1USCount)
MAC_RMON_CTR(78, TransmitPri7Pause1USCount)
MAC_RMON_CTR(79, ReceivePri0Pause1USCount)
MAC_RMON_CTR(80, ReceivePri1Pause1USCount)
MAC_RMON_CTR(81, ReceivePri2Pause1USCount)
MAC_RMON_CTR(82, ReceivePri3Pause1USCount)
MAC_RMON_CTR(83, ReceivePri4Pause1USCount)
MAC_RMON_CTR(84, ReceivePri5Pause1USCount)
MAC_RMON_CTR(85, ReceivePri6Pause1USCount)
MAC_RMON_CTR(86, ReceivePri7Pause1USCount)
MAC_RMON_CTR(87, ReceiveStandardPause1USCount)
MAC_RMON_CTR(88, FramesTruncated)
