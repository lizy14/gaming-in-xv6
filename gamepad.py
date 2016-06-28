import virtkey
import time
import locale

v=virtkey.virtkey()

th=10000

def send_key(char):
		v.press_unicode(ord(char)) 
		v.release_unicode(ord(char)) 
'''
X1:  1024 Y1:   256  X2:  -256 Y2:  -256  du:0 dd:0 dl:0 dr:0  back:0 guide:0 start:0  TL:0 TR:0  A:0 B:0 X:0 Y:0  LB:0 RB:0  LT:  0 RT:  0
'''

def simulate(): 
	f = open("/tmp/xbox_log")
	w,s,a,d,x,y=0,0,0,0,0,0
	while(True):
		k = f.readline()
		char=" "
		if len(k)<130:
			time.sleep(.01);
			continue;
		dx = locale.atoi(k[24:30]);
		dy = locale.atoi(k[34:40]);
		
		if k[108]=="1":
			if(x==0):
				send_key("x")
			x=1
		else:
			x=0
		if k[112]=="1":
			if(y==0):
				send_key("y")
			y=1
		else:
			y=0
		if k[45]=="1" or dy>th:
			if(w==0):
				send_key("w")
			w=1
		else:
			w=0
		if k[50]=="1" or dy<-th:
			if s==0:
				send_key("s")
			s=1
		else:
			s=0
		if k[55]=="1" or dx<-th:
			if a==0:
				send_key("a")
			a=1
		else:
			a=0
		if k[60]=="1" or dx>th:
			if d==0:
				send_key("d")
			d=1
		else:
			d=0
		if char==" ":
			continue;



simulate()
