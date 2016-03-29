#!/usr/bin/env python3

# define more general chirality of the dihedral angles.
# 2015-3-18


import fileloaders as fl
import ringposition as rp
import wrap as wr
import numpy as np
import itertools as it
import math

def ChiralityInDihedralAngle_general2(a,b, nei,coord, box):
    #if len(nei[a]) != 4 or len(nei[b]) != 4:
    #    # not target
    #    return 0.0
    #1. make vertices list
    pivots = (a,b)
    center = coord[a]
    vertices = set(nei[a]) | set(nei[b])
    #2. calculate the direction vectors
    localcoord = dict()
    for vertex in vertices:
        localcoord[vertex] = wr.wrap(coord[vertex] - center, box)
    vertices -= set(pivots)
    pivot = localcoord[b] - localcoord[a]
    pivot /= np.linalg.norm(pivot)
    #direction vectors, perpendicular to the pivot vector
    vectors = dict()
    for vertex in vertices:
        v = localcoord[vertex] - np.dot(pivot,localcoord[vertex])*pivot
        vectors[vertex] = v / np.linalg.norm(v)
    va = list(set(nei[a]) - set(pivots))
    vb = list(set(nei[b]) - set(pivots))
    #check
    #for i in va + vb:
    #    sine = np.dot(np.cross(vectors[i],vectors[va[0]]), pivot)
    #    cosine = np.dot(vectors[i],vectors[va[0]])
    #    angle = math.atan2(sine,cosine) * 180 / math.pi
    #    #print angle
    op = []
    for i in va:
        for j in vb:
            sine = np.dot(np.cross(vectors[i],vectors[j]), pivot)
            cosine = np.dot(vectors[i],vectors[j])
            angle = math.atan2(sine,cosine)# * 180 / math.pi
            op.append(math.sin(angle*3))
    return op


def FragmentChirality(edges,coord,box=np.array([1e10,1e10,1e10])):
    nei = [[] for i in range(len(coord))]
    for edge in edges:
        i,j = edge
        nei[i].append(j)
        nei[j].append(i)
    twist = []
    chi = []
    for edge in edges:
        i,j = edge
        chi += ChiralityInDihedralAngle_general2(i,j,nei,coord,box)
    sum = 0
    for c in chi:
        sum += c
    return sum/len(chi)

    
    


if __name__ == "__main__":
    import sys
    file = sys.stdin
    box = np.array([1e10,110,1e10])
    while True:
        line = file.readline()
        if line == "":
            break
        columns = [x for x in line.split()]
        if 0 < len(columns):
            if columns[0] == "@BOX3":
                box = fl.LoadBOX3(file)
            elif columns[0] in ("@AR3A", "@NX3A", "@NX4A"):
                coord = fl.LoadAR3A(file)
    file = open(sys.argv[1]) #ngph
    values = []
    while True:
        line = file.readline()
        if line == "":
            break
        columns = [x for x in line.split()]
        if 0 < len(columns):
            if columns[0] == "@NGPH":
                edges = fl.LoadNGPH(file)
                values.append(FragmentChirality(edges,coord,box))
    print("@VMRK")
    print(len(values))
    for v in values:
        print(v)
