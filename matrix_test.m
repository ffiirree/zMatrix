m1 = [
		5,7,9,1,5;
		3,6,7,1,98;
		4,2,96,4,3;
		5,4,9,56,3;
		5,1,5,7,61
	]
	core = [
		1,1,1,1,1;
        1,1,1,1,1;
		1,1,-1,1,1;
		1,1,1,1,1;
        1,1,1,1,1
	]

conv2(m1, core, 'same')
