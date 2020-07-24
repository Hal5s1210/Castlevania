#include "Sound.h"
#include <cstdlib>


Sound* Sound::_instance = NULL;

Sound::Sound()
{
	_dSound = 0;
	_primaryBuffer = 0;
}

Sound::~Sound()
{
	if (_primaryBuffer) _primaryBuffer->Release();
	if (_dSound) _dSound->Release();
}

Sound* Sound::GetInstance()
{
	if (!_instance) _instance = new Sound;
	return _instance;
}

bool Sound::Init(HWND hwnd)
{
	HRESULT hr;
	hr = DirectSoundCreate8(NULL, &_dSound, NULL);
	if (FAILED(hr))
		return false;

	hr = _dSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(hr))
		return false;

	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	hr = _dSound->CreateSoundBuffer(&bufferDesc, &_primaryBuffer, NULL);
	if (FAILED(hr))
		return false;

	OutputDebugString(L"[INFO] InitSound done;\n");
	return true;
}

void Sound::Load(int id, LPCWSTR  dir)
{
	LPDIRECTSOUNDBUFFER8 buffer;

	if (!LoadWaveFile(dir, &buffer))
	{
		OutputDebugString(L"[INFO] Sound loaded Failed");
		return;
	}
	OutputDebugString(L"[INFO] Sound loaded OK");

	_secondaryBuffers[id] = buffer;
}


bool Sound::LoadWaveFile(LPCWSTR dir, LPDIRECTSOUNDBUFFER8* buffer)
{
	LPDIRECTSOUNDBUFFER tmpBuffer;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	WaveHeaderType waveHeader;
	HRESULT hr;
	FILE* file;

	size_t   i;
	char* d = (char*)malloc(BUFFER_SIZE);

	wcstombs_s(&i, d, (size_t)BUFFER_SIZE, dir, (size_t)BUFFER_SIZE);

	if (fopen_s(&file, d, "rb") != 0)
	{
		return false;
	}

	// Read in the wave file header.
	if (fread(&waveHeader, sizeof(waveHeader), 1, file) != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveHeader.chunkId[0] != 'R') || 
		(waveHeader.chunkId[1] != 'I') ||
		(waveHeader.chunkId[2] != 'F') || 
		(waveHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveHeader.format[0] != 'W') ||
		(waveHeader.format[1] != 'A') ||
		(waveHeader.format[2] != 'V') ||
		(waveHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveHeader.subChunkId[0] != 'f') || 
		(waveHeader.subChunkId[1] != 'm') ||
		(waveHeader.subChunkId[2] != 't') || 
		(waveHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveHeader.dataChunkId[0] != 'd') || 
		(waveHeader.dataChunkId[1] != 'a') ||
		(waveHeader.dataChunkId[2] != 't') || 
		(waveHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	waveFormat.wFormatTag = waveHeader.audioFormat;
	waveFormat.nSamplesPerSec = waveHeader.sampleRate;
	waveFormat.wBitsPerSample = waveHeader.bitsPerSample;
	waveFormat.nChannels = waveHeader.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	hr = _dSound->CreateSoundBuffer(&bufferDesc, &tmpBuffer, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	hr = tmpBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*buffer);
	if (FAILED(hr))
	{
		return false;
	}

	// Release the temporary buffer.
	tmpBuffer->Release();
	tmpBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(file, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	// Read in the wave file data into the newly created buffer.
	unsigned char* waveData = new unsigned char[waveHeader.dataSize];
	if (fread(waveData, 1, waveHeader.dataSize, file) != waveHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	if (fclose(file) != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	unsigned char* bufferPtr;
	unsigned long bufferSize;
	hr = (*buffer)->Lock(0, waveHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(hr))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	hr = (*buffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(hr))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	return true;
}

void Sound::Remove(int id)
{
	_secondaryBuffers[id]->Release();
	_secondaryBuffers.erase(id);
}


bool Sound::Play(int id, bool loop)
{
	HRESULT hr;
	LPDIRECTSOUNDBUFFER8 buffer = 0;
	buffer = _secondaryBuffers[id];
	if (!buffer)
		return false;

	hr = buffer->SetCurrentPosition(0);
	if (FAILED(hr))
		return false;

	hr = buffer->SetVolume(DSBVOLUME_MAX);
	if (FAILED(hr))
		return false;

	hr = buffer->Play(0, 0, loop);
	if (FAILED(hr))
		return false;

	return true;
}

bool Sound::Stop(int id)
{
	HRESULT hr;
	LPDIRECTSOUNDBUFFER8 buffer = 0;
	buffer = _secondaryBuffers[id];
	if (!buffer)
		return false;

	hr = buffer->Stop(); 
	if (FAILED(hr))
		return false;

	return true;
}

void Sound::StopAll()
{
	for (std::unordered_map<int, LPDIRECTSOUNDBUFFER8>::iterator itr = _secondaryBuffers.begin(); itr != _secondaryBuffers.end(); itr++)
	{
		itr->second->Stop();
	}
}

void Sound::Clear()
{
	for (std::unordered_map<int, LPDIRECTSOUNDBUFFER8>::iterator itr = _secondaryBuffers.begin(); itr != _secondaryBuffers.end(); itr++)
	{
		if (itr->second) itr->second->Release();
	}
	_secondaryBuffers.clear();
}
