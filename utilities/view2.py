file=open('TD.MAP','rb').read()
map=[]

#LOAD UP MAP
for mapx in range(201):
	map.append([])
	for mapy in range(201):
		if file[mapx*201+mapy] == 0x31: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x32: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x33: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x3B: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x3C: map[mapx].append('.')
		elif file[mapx*201+mapy] == 0x3D: map[mapx].append('.')
		else: map[mapx].append('O')

#PRINT OUT MAP
for i in range(201):
	line=''
	for j in range(201):
		line+=map[j][i]
	print(line,end="")