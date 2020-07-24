#pragma once

#include <dsound.h>
#include <unordered_map>

#define BUFFER_SIZE 100

class Sound
{
private:
	static Sound* _instance;

	struct WaveHeaderType
	{
		char			chunkId[4];
		unsigned long	chunkSize;
		char			format[4];
		char			subChunkId[4];
		unsigned long	subChunkSize;
		unsigned short	audioFormat;
		unsigned short	numChannels;
		unsigned long	sampleRate;
		unsigned long	bytesPerSecond;
		unsigned short	blockAlign;
		unsigned short	bitsPerSample;
		char			dataChunkId[4];
		unsigned long	dataSize;
	};

	LPDIRECTSOUND8 _dSound;
	LPDIRECTSOUNDBUFFER _primaryBuffer;
	std::unordered_map<int, LPDIRECTSOUNDBUFFER8> _secondaryBuffers;

	//bool LoadWaveFile(const char*, LPDIRECTSOUNDBUFFER8*);
	bool LoadWaveFile(LPCWSTR , LPDIRECTSOUNDBUFFER8*);

public:
	Sound();
	~Sound();

	static Sound* GetInstance();

	bool Init(HWND);

	void Load(int id, LPCWSTR  dir);
	bool Play(int id, bool = false);
	bool Stop(int id);
	void StopAll();
	void Remove(int id);
	void Clear();
};