#!/usr/bin/env python

import numpy as np

def LoadVMRK(file):
    n = int(file.readline())
    v = []
    for i in range(n):
        x = float(file.readline())
        v.append(x)
    return v




def LoadVMKX(file):
    n = int(file.readline())
    v = []
    for i in range(n):
        x = [float(a) for a in file.readline().split()][1:]
        v.append(x)
    return v




def LoadBOX3(file):
    line = file.readline()
    return np.array([float(x) for x in line.split()])



def LoadAR3A(file):
    xyz = []
    line = file.readline()
    nmol = int(line)
    for i in range(nmol):
        line = file.readline()
        columns = np.array([float(x) for x in line.split()[0:3]])
        xyz.append(columns)
    return xyz



def LoadNX4A(file):
    xyz = []
    line = file.readline()
    nmol = int(line)
    for i in range(nmol):
        line = file.readline()
        columns = np.array([float(x) for x in line.split()[0:7]])
        xyz.append(columns)
    return xyz



#format is same as @RSET
def LoadRNGS(file,debug=0):
    line = file.readline()
    n = int(line)
    rings = []
    while True:
        line=file.readline()
        if len(line) == 0:
            break
        if debug: print("#",line)
        columns = [int(x) for x in line.split()]
        if debug: print("#",line,columns,n)
        if columns[0] == 0:
            break
        nodes = columns[1:]
        rings.append(nodes)
    return n,rings





def LoadISET(file,debug=0):
    line = file.readline()
    n,ntype = [int(x) for x in line.split()]
    isets = []
    while True:
        line=file.readline()
        if len(line) == 0:
            break
        if debug: print("#",line)
        columns = [int(x) for x in line.split()]
        if debug: print("#",line,columns,n)
        if columns[0] == 0:
            break
        isets.append(columns)
    return n,ntype,isets



def LoadNGPH(file,requirenmol = False):
    line = file.readline()
    nmol = int(line)
    edges = set()
    while True:
        line = file.readline()
        x,y = [int(k) for k in line.split()[0:2]]
        if x < 0:
            break
        edges.add((x,y))
    if requirenmol:
        return nmol,edges
    else:
        return edges



def LoadBMRK(file,requirenmol = False):
    line = file.readline()
    nmol = int(line)
    edges = dict()
    while True:
        line = file.readline()
        x,y,v = [k for k in line.split()[0:3]]
        x,y,v = int(x),int(y),float(v)
        if x < 0:
            break
        edges[(x,y)] = v
    if requirenmol:
        return nmol,edges
    else:
        return edges


def LoadPAIR(file,requirenmol = False):
    line = file.readline()
    nmol = int(line)
    edges = dict()
    while True:
        line = file.readline()
        x,y,v,w = [k for k in line.split()[0:4]]
        x,y,v,w = int(x),int(y),float(v),float(w)
        if x < 0:
            break
        edges[(x,y)] = (v,w)
    if requirenmol:
        return nmol,edges
    else:
        return edges

    

def LoadBMKX(file,requirenmol = False):
    line = file.readline()
    nmol = int(line)
    edges = dict()
    while True:
        line = file.readline()
        columns = [k for k in line.split()]
        x,y = [int(v) for v in columns[0:2]]
        if x < 0:
            break
        edges[(x,y)] = columns[2:]
    if requirenmol:
        return nmol,edges
    else:
        return edges
