import os, glob

data = [] 	# Holds all bytes across all files
data_max = []	# Holds max value for each byte position across all files

# LOAD ALL FILES INTO DATA ARRAY
for filename in glob.glob(os.path.join(os.getcwd(),'M*.TD*')):
	filedata = open(filename,'rb')
	byte_index=0
	for line in filedata:
		for byte in line:
			try: data[byte_index].append(byte)
			except: data.append([byte])
			byte_index+=1
	filedata.close()

# CALCULATE DATA_MAX VALUE ARRAY
for bytearray in data: data_max.append(max(bytearray))

# CONVENIENT DISPLAY OF MAX DATA VALUES
def show_data(minlines=0,maxlines=21000):
	offset=0
	for item in data_max:
		if offset >= minlines: print(hex(offset),": ", item)
		offset+=1
		if offset > maxlines: break

# SHOW ALL BREAKS
def show_breaks():
	last_break=0
	this_break=0
	size=0
	for i in range(len(data_max)):
		if data_max[i-1]==0:
			if data_max[i] > 0:
				this_break = i
				size = this_break-last_break-1
				print(hex(this_break), "-- Size:", size)
		last_break = int(this_break)