#ifndef WING_MEDIA_TYPE_H
#define WING_MEDIA_TYPE_H

#include "include/icqtypes.h"

#pragma pack(1)//��1�ֽڶ���

typedef struct _rtp_packet_header
{
	uint16	v:2;												/* packet type               2 */
	uint16	p:1;												/* padding flag              0 */
	uint16	x:1;												/* header extension flag     0 */
	uint16	cc:4;												/* CSRC count                0 */		 
	uint16	m:1;												/* marker bit                0 */
	uint16	pt:7;												/* payload type              98 */
	uint16  seq;												/* sequence number           auto inc */
	uint32  timestamp;											/* timestamp                 auto inc */
	union
	{
		struct 
		{
			uint8 count;										/* �ְ��ĸ���,Ĭ��Ϊ1				*/
			uint8 curr;											/* �ڼ����ְ���Ĭ��Ϊ1              */
			uint16 len;											/* ���ݰ��ĳ���,bytes				*/
		};
		uint32  ssrc;											/* synchronization source    0 */
	};
	/* The csrc list, header extension and data follow, but can't */
	/****************************************************************************************************
	uint32_t		 ph_ccsc;	// be represented in the struct.                              
	//��ph_ccsc����Ϊ�����֣����¶���
	//ph_ccsc:0..7		�ְ��ĸ���,Ĭ��Ϊ1
	//ph_ccsc:8..15		�ڼ����ְ���Ĭ��Ϊ1 
	//ph_ccsc:16..31	���ݰ��ĳ���,bytes
	*****************************************************************************************************/
}RtpHeader;

#pragma pack()

#endif

