file=open('TD.MAP','rb').read()   # DANGLING FILE DESCRIPTOR
mission=open('M1.TD1','rb').read()  # SECOND PHASE

map=[]

#LOAD UP MAP
for mapx in range(201):
	map.append([])
	for mapy in range(201):
		if file[mapx*201+mapy] == 0x31: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x32: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x33: map[mapx].append('.')
		#elif file[mapx*201+mapy] == 0x3B: map[mapx].append('.')
		#elif file[mapx*201+mapy] == 0x3C: map[mapx].append('.')
		#elif file[mapx*201+mapy] == 0x3D: map[mapx].append('.')
		else: map[mapx].append('O')

#LOAD UP SHIP WAYPOINTS  SECOND PHASE
for i in range(500):
	x_pos = mission[0x50+i]
	y_pos = mission[0x50+10000+i]
	map[x_pos][y_pos]='X'

#PRINT OUT MAP
for i in range(201):
	line=''
	for j in range(201):
		line+=map[j][i]
	print(line,end="")