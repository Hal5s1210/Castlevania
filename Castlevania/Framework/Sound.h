#pragma once

#include <dsound.h>
#include <unordered_map>

class Sound
{
	static Sound* _instance;

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	LPDIRECTSOUND8 _dSound;
	LPDIRECTSOUNDBUFFER _primaryBuffer;
	std::unordered_map<int, LPDIRECTSOUNDBUFFER8> _secondaryBuffers;

	bool LoadWaveFile(const wchar_t*, LPDIRECTSOUNDBUFFER8*);

public:
	Sound();
	~Sound();

	static Sound* GetInstance();

	bool Init(HWND);

	void Load(int id, const wchar_t* dir);
	bool Play(int id, bool = false);
	void Remove(int id);
};
typedef Sound* LPSOUND;

/*
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
#include <XAudio2.h>

class XSound
{
private:
	static XSound* _instance;

	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
	std::unordered_map<int, IXAudio2SourceVoice*> pSourceVoices;

	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

public:
	XSound();
	~XSound();

	static XSound* GetInstance();

	bool Init(HWND);

	HRESULT Load(int id, LPCWSTR dir);
	HRESULT Play(int id, bool = false);
	void Remove(int id);
};
*/