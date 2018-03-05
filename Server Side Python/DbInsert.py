import datetime
import time
import MySQLdb


def read_file(l): 
   f=open('log.txt',"r")
   lineList=f.readlines()
   f.close()
   k=str(lineList[-l])
   parts=k.split(" ")
   device=parts[0]
   attribute=parts[1]
   value=parts[2]
   return (device,attribute,value)




def time_stamp():
    ts = time.time()
    st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
    return st

def inser(a,b,c,d):
    db=MySQLdb.connect(host="localhost",user="<dbusername>",passwd="<dbpassword>",db="<dbname>")
    cursor=db.cursor()
    query = "INSERT INTO data (device,attribute,value,timestamp) VALUES(%s,%s,%s,%s)"
    args = (a,b,c,d)
    cursor.execute(query, args)
    db.commit()
    db.close()
    return

