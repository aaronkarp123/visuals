import threading
import multiprocessing
import time
import logging
import numpy as np
import matplotlib.pyplot as plt
from record import *

def record_function(buffer_lock):
	init()
	global buffer
	while True:
		data = read_stream()  # READ INTO ARRAY THEN WRITE TO GLOBALS
		with buffer_lock:
			buffer.append(data)
	close_stream()

def visual_function(buffer_lock):
	global buffer
	plt.axis([0, 10, 0, 1])
	plt.ion()
	plt.scatter(0, 1)
	plt.plot()
	plt.show()
	i = 0
	while i < 50:
		if len(buffer) > 0:
			numpy_array = np.fromstring(buffer[0], dtype=np.int16)
			print(numpy_array)
			plt.scatter(i, np.average(numpy_array))
			buffer = []
			plt.plot()
			i += 1

if __name__ == '__main__':
    threads = []

    buffer_lock = threading.Lock()

    event = threading.Event()

    rec_thread = threading.Thread(name='recording_thread', target=record_function, args = (buffer_lock, ))
    rec_thread.setDaemon(True)
    threads.append(rec_thread)

    visual_thread = threading.Thread(name='visual_thread', target=visual_function, args = (buffer_lock, ))
    visual_thread.setDaemon(True)
    threads.append(visual_thread)

    buffer = []

    for t in threads:
        t.start()
    visual_thread.join()