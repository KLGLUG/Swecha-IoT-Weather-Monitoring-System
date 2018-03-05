import DbInsert as DB
import time

def maincall(a):
  r=DB.read_file(a)
  dev=str(r[0])
  par=str(r[1])
  val=str(r[2])
  tim=DB.time_stamp()
  i=DB.inser(dev,par,val,str(tim))
 

while True:
 print ("hi") 
 for i in range(1,3):
    maincall(i)  
 time.sleep(6)
 print ("0k done uploaded to mysql database")


