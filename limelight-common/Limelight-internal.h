#pragma once

#include "Limelight.h"
#include "Platform.h"
#include "PlatformSockets.h"
#include "PlatformThreads.h"
#include "Video.h"

extern int serverMajorVersion;

void fixupMissingCallbacks(PDECODER_RENDERER_CALLBACKS *drCallbacks, PAUDIO_RENDERER_CALLBACKS *arCallbacks,
	PCONNECTION_LISTENER_CALLBACKS *clCallbacks, PPLATFORM_CALLBACKS *plCallbacks);

char* getSdpPayloadForStreamConfig(PSTREAM_CONFIGURATION streamConfig, struct in_addr targetAddress,
                                   int rtspClientVersion, int *length);

int initializeControlStream(IP_ADDRESS host, PSTREAM_CONFIGURATION streamConfig, PCONNECTION_LISTENER_CALLBACKS clCallbacks);
int startControlStream(void);
int stopControlStream(void);
void destroyControlStream(void);
void resyncOnDemand(void);
void connectionSinkTooSlow(int startFrame, int endFrame);
void connectionDetectedFrameLoss(int startFrame, int endFrame);
void connectionReceivedFrame(int frameIndex);
void connectionLostPackets(int lastReceivedPacket, int nextReceivedPacket);

int performRtspHandshake(IP_ADDRESS addr, PSTREAM_CONFIGURATION streamConfigPtr);
void terminateRtspHandshake(void);

void initializeVideoDepacketizer(int pktSize);
void destroyVideoDepacketizer(void);
void processRtpPayload(PNV_VIDEO_PACKET videoPacket, int length);
int getNextDecodeUnit(PDECODE_UNIT *du);
void freeDecodeUnit(PDECODE_UNIT decodeUnit);
void queueRtpPacket(PRTP_PACKET rtpPacket, int length);

void initializeVideoStream(IP_ADDRESS host, PSTREAM_CONFIGURATION streamConfig, PDECODER_RENDERER_CALLBACKS drCallbacks, PCONNECTION_LISTENER_CALLBACKS clCallbacks);
void destroyVideoStream(void);
int startVideoStream(void* rendererContext, int drFlags);
void stopVideoStream(void);

void initializeAudioStream(IP_ADDRESS host, PAUDIO_RENDERER_CALLBACKS arCallbacks, PCONNECTION_LISTENER_CALLBACKS clCallbacks);
void destroyAudioStream(void);
int startAudioStream(void);
void stopAudioStream(void);

int initializeInputStream(IP_ADDRESS addr, PCONNECTION_LISTENER_CALLBACKS clCallbacks,
	char* aesKeyData, int aesKeyDataLength, char* aesIv, int aesIvLength);
void destroyInputStream(void);
int startInputStream(void);
int stopInputStream(void);
