import cx_Oracle

ip = '192.168.50.128'
port = 1521
SID = 'XE'
dsn_tns = cx_Oracle.makedsn(ip, port, SID)
print dsn_tns
db = cx_Oracle.connect('leb', 'awst_leb', dsn_tns)
curs = db.cursor()
curs.execute('select * from interval')
for row in curs:
    print row
db.close()