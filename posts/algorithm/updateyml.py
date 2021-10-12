'''
Descripttion: 
version: 
Author: Stonex
Date: 2021-10-12 14:39:33
LastEditTime: 2021-10-12 17:46:13
'''
import time
import os
import sys

def updateDate(file_name):
    
    t = time.localtime(time.time())
    print(file_name)
    fd = open(file_name, 'rb')
    write_time = format("%4d-%2d-%2d"%(t.tm_year, t.tm_mon, t.tm_mday))
    lines = []
    for line in fd.readlines():
        lines.append(line)
        print(line)

    lines[3] = bytes('date: ' + write_time + '\n', encoding="utf8")
    lines[4] = bytes('lastmod: ' + write_time + '\n', encoding="utf8")
    
    fd = open(file_name, 'wb+')
    for line in lines:
        fd.write(line)
    fd.close()

def main(argc, argv):
    assert(argc >= 2)
    operator = argv[1].lower()

    if(operator == "t"):
        print("update time")
        assert(argc == 3)
        updateDate(argv[2])


if __name__ == "__main__" :
    main(len(sys.argv), sys.argv)