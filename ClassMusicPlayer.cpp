#include "Classes.h"

int ClassMusicPlayer::getFriquencySummery() {
	float fft[512];
	int friq = 0;

	BASS_ChannelGetData(chan, fft, BASS_DATA_FFT1024);

	for (int i = 0; i < 512; i++) {
		if (int(fft[i] * 1000) > 5) {
			friq = friq + int(fft[i] * 1000);
		}
	}

	return friq;
}

void ClassMusicPlayer::playMusic(const char* fileName) {
	BASS_Init(-1, 44100, 0, 0, NULL);
	BASS_SetVolume(0.5);
	if (!(chan = BASS_StreamCreateFile(FALSE, fileName, 0, 0, BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT))
		&& !(chan = BASS_MusicLoad(FALSE, fileName, 0, 0, BASS_MUSIC_RAMPS | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT, 1))) {

	}
	BASS_ChannelPlay(chan, FALSE);
}

void ClassMusicPlayer::stopMusic() {
	BASS_ChannelPause(chan);
}

int ClassMusicPlayer::getMusicLength() {
	QWORD len = BASS_ChannelGetLength(chan, BASS_POS_BYTE);
	double val = BASS_ChannelBytes2Seconds(chan, len);
	return int(val);
}

void ClassMusicPlayer::resumeMusic() {
	BASS_ChannelPlay(chan, false);
}

void ClassMusicPlayer::setMusicPosition(int secondsAmount) {
	BASS_ChannelSetPosition(chan, BASS_ChannelSeconds2Bytes(chan, secondsAmount), BASS_POS_BYTE);
}

int ClassMusicPlayer::getMusicPosition() {
	return BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan, BASS_POS_BYTE));
}

bool ClassMusicPlayer::endOfMusic() {
	if (BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan, BASS_POS_BYTE)) >= BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetLength(chan, BASS_POS_BYTE)) - 1) {
		this->stopMusic();
		return true;
	}
	else {
		return false;
	}
}