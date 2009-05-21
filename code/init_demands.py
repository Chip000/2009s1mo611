#!/usr/bin/python
# -*- coding: utf-8 -*-
# Creates the demands for all instances

import sys
import os
import re

if (len(sys.argv) < 3):
        print ">>> Missing parameters!!!"
        exit(1)

inst_dir = sys.argv[1] 
dem_dir = sys.argv[2]
ext = ".dem"

r0 = re.compile("n ([0-9]*)")

for inst in os.listdir(inst_dir):
        f = open(inst_dir+inst, "r")
        for line in f:
                if r0.match(line):
			l0 = r0.findall(line)
			break
        
        f_out = open(dem_dir+inst+ext, "w")
        for i in range(1, int(l0[0]) + 1):
                for j in range(i + 1, int(l0[0]) + 1):
                        f_out.write("p %d %d\n" % (i, j)) 

        f_out.close()
        f.close()

# EOF
