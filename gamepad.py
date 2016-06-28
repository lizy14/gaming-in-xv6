import virtkey
import time

v=virtkey.virtkey()

def send_key(char):
		v.press_unicode(ord(char)) 
		v.release_unicode(ord(char)) 

def simulate(): 
	f = open("/tmp/xbox_log")
	w,s,a,d=0,0,0,0
	while(True):
		k = f.readline()
		char=" "
		if len(k)<130:
			time.sleep(.01);
			continue;
		print(k)
		if k[45]=="1":
			if(w==0):
				send_key("w")
			w=1
		else:
			w=0
		if k[50]=="1":
			if s==0:
				send_key("s")
			s=1
		else:
			s=0
		if k[55]=="1":
			if a==0:
				send_key("a")
			a=1
		else:
			a=0
		if k[60]=="1":
			if d==0:
				send_key("d")
			d=1
		else:
			d=0
		if char==" ":
			continue;



simulate()
