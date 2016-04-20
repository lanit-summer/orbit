#Generic for script.cel file
script = [
'{\n',
	'time{utc "2015-01-01T00:01:24.0000"}\n',
	'select{object "Orbit-test-spacecraft"}\n',
	'center {time 5.0}\n',
	'goto { time 5.0 }\n',
	'follow{}\n',
	'lock{}\n',
'}'
]

#Generic for orbit.ssc file
scriptSSC = [
'"Orbit-test-spacecraft" "Sol"\n',
'{\n',
'\tClass "spacecraft"\n',
'\tMesh "orbit.3ds"\n',
'\tRadius 0.011\n',
'\tOrientation [ 180 1 0 0 ]\n',
'\tTimeline [\n',
'\t# Phase 3: Solstice mission\n',
'\t{\n',
'\tBeginning "2015 01 01 00:00:00"\n',       
'\tEnding    "2020  9 15 17:02:00"\n',
'\tOrbitFrame { EclipticJ2000 { Center "Sol/Earth" } }\n',
'\tSampledTrajectory { Source "orbit.xyzv" }\n',
'\t}\n',
'\t]\n',
'}\n',
]


def makeScript(beginDate,shipName):
	#set new begin date
	script[1] = 'time{utc "' + str(beginDate) + '"}\n'
	#set new ship object
	script[2] = 'select{object "' + str(shipName) + '"}\n'
	
	f = open("script.cel","w")	
	for line in script:
		f.write(line)

def makeSSCScript(beginDate, endDate, shipName):
	#set new ship name
	scriptSSC[0] = '"'+str(shipName)+'" "Sol"\n'
	#set new begin/end date
	scriptSSC[9] = '\tBeginning "' +str(beginDate)+'"\n'
	scriptSSC[10] = '\tEnding "' +str(endDate)+'"\n'

	f = open("orbit.ssc","w")	
	for line in scriptSSC:
		f.write(line)

if __name__ == '__main__':
	makeScript("2015 01 01 00:00:00","ORBIT")
	makeSSCScript("2015 01 01 00:00:00","2016 01 01 00:00:00","ORBIT")
