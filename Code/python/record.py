from __future__ import print_function
import pyaudio
import wave
import numpy as np

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
RECORD_SECONDS = 5
WAVE_BUFFER = []
p = ''
stream = ''

def init():
	global p
	global stream

	p = pyaudio.PyAudio()

	stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

	print("initialized recorder")

def read_stream():
	#global WAVE_BUFFER
	data = stream.read(CHUNK)
	#WAVE_BUFFER.append(data)
	return data

def close_stream():
	print("closing recorder")
	global p, stream
	# numpy_array = np.fromstring(WAVE_BUFFER, dtype=np.int16)
	stream.stop_stream()
	stream.close()
	p.terminate()
