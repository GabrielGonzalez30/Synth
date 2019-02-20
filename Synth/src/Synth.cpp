#include "RtAudio.h"
#include "Stk.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

// Pass-through function.
int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *data)
{
	
	stk::FLOAT64 * in = (stk::FLOAT64 *) inputBuffer;
	stk::FLOAT64 * out = (stk::FLOAT64 *) outputBuffer;
	// Since the number of input and output channels is equal, we can do
	// a simple buffer copy operation here.
	if (status) std::cout << "Stream over/underflow detected." << std::endl;
	unsigned long *bytes = (unsigned long *)data;
	for (int i = 0; i < nBufferFrames; i++)
	{
		out[i] = in[i];
	}
	return 0;


}

void duplexMode()
{
	RtAudio adac;
	if (adac.getDeviceCount() < 1) {
		std::cout << "\nNo audio devices found!\n";
		exit(0);
	}
	// Set the same number of channels for both input and output.
	unsigned int bufferBytes, bufferFrames = 512;
	RtAudio::StreamParameters iParams, oParams;
	iParams.deviceId = adac.getDefaultInputDevice(); // first available device
	iParams.nChannels = 1;
	oParams.deviceId = adac.getDefaultOutputDevice(); // first available device
	oParams.nChannels = 1;
	try {
		adac.openStream(&oParams, &iParams, RTAUDIO_FLOAT64, 48000, &bufferFrames, &inout, (void *)&bufferBytes);
	}
	catch (RtAudioError& e) {
		e.printMessage();
		exit(0);
	}
	bufferBytes = bufferFrames * 2 * 4;
	try {
		adac.startStream();
		char input;
		//std::cout <<  << std::endl;
		std::cin.get(input);
		// Stop the stream.
		adac.stopStream();
	}
	catch (RtAudioError& e) {
		e.printMessage();
		goto cleanup;
	}
cleanup:
	if (adac.isStreamOpen()) adac.closeStream();
}

void config()
{
	RtAudio a;
	std::cout << a.getDeviceInfo(a.getDefaultInputDevice()).preferredSampleRate << std::endl;
	std::cin.get();
}

int main()
{
	duplexMode();
}