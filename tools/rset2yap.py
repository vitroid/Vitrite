#!/usr/bin/env python3
# coding: utf-8
#
import sys
import math
import string
import fileloaders as fl
import rsetadjacency as ra
import numpy as np
import itertools as it
import wrap as wr
import ringposition as rp
import importlib as il






def usage(cmd):
    print("""
usage: cat ringlist.rngs coord.ar3a ringsets.rset [vertexmarks.vmrk] | {0} [-s x]
    -s x       Shrink each fragment. [x=1.0]
    -X x       Explode each fragment. [x=1.0]
    -v a,b,c   Show specific fragment types only. Type of fragments are given in VMRK format.
    -a         Show adjacency graph.
    -r         Show edges instead of polygons.
    -O         OpenSCAD.
    -R         Show both edges and polygons.
    -n         Show the network.
    -G file    Read color from file in @VMRK format.
""".format(cmd))
    sys.exit(1)




cmd = sys.argv.pop(0)

kinds = []
adjacency = False
shrink = 1.0
showrims = False
showpoly = True
shownet = False
explode = 1.0
openscad = False
palette = []
while 0 < len(sys.argv):
    item = sys.argv.pop(0)
    #print "ITEM:",item
    if item == "-a":
        adjacency = True
    elif item == "-n":
        shownet = True
    elif item == "-O":
        openscad = True
    elif item == "-r":
        showrims = True
        showpoly = False
    elif item == "-R":
        showrims = True
        showpoly = True
    elif item == "-s":
        shrink = float(sys.argv.pop(0))
    elif item == "-X":
        explode = float(sys.argv.pop(0))
    elif item == "-v":
        #usage: -v kinds
        item = sys.argv.pop(0)
        kinds = [int(x) for x in item.split(",")]
        #print "KINDS:",kinds
        # When fragment types are specified, colors and layers are set based on the types;
        # Otherwise, they are set based on the size.
    elif item == "-G":
        file = open(sys.argv.pop(0))
        while True:
            line = file.readline()
            if len(line) == 0:
                break
            columns = line.split()
            if 0 < len(columns) and columns[0] == "@VMRK":
                palette = fl.LoadVMRK(file)

if openscad:
    yp = il.import_module("openscadlib.py")
else:
    yp = il.import_module("yaplotlib")

file = sys.stdin
graph = None
while True:
    line = file.readline()
    if line == "":
        break
    #process @RSET
    columns = [x for x in line.split()]
    if 0 < len(columns):
        if columns[0] == "@RSET":
            nring_,ringsets = fl.LoadRNGS(file)
        elif columns[0] == "@RNGS":
            nnode_,rings = fl.LoadRNGS(file)
        elif columns[0] == "@BOX3":
            box = fl.LoadBOX3(file)
        elif columns[0] in ("@AR3A", "@NX3A", "@NX4A"):
            coord = fl.LoadAR3A(file)
        elif columns[0] == "@VMRK":
            idlist = fl.LoadVMRK(file)
            members = set()
            for i in range(len(idlist)):
                if idlist[i] in kinds:
                    members.add(i)
            #print members



if graph == None and shownet:
    #graph is auto generated from rset
    graph = set()
    for ringset in ringsets:
        for ringid in ringset:
            vertices = rings[ringid]
            for i in range(len(vertices)):
                x,y = vertices[i-1],vertices[i]
                graph.add(frozenset([x,y]))

#output string
s = ""

ringpositions = rp.RingPositions(rings, coord, box)
ringsetpositions = rp.RingPositions(ringsets, ringpositions, box)
            

#network
if shownet:
    s += yp.Color(0)
    s += yp.Layer(1)
    for edge in graph:
        i,j = edge
        ci = wr.wrap(coord[i],box)
        cj = wr.wrap(coord[j]-ci,box) + ci
        s += yp.Line(ci,cj)


#Adjacency Graph
if adjacency:
    #First layer is reserved for adjacency graph
    s += yp.Color(0) #black
    s += yp.Layer(1)
    #in case kinds are specified, prepare the layer order
    order = 0
    orderdict = dict()
    for i in kinds:
        if not orderdict.has_key((i,i)):
            orderdict[(i,i)] = order
            order += 1
    for i in kinds:
        for j in kinds:
            if not orderdict.has_key((i,j)):
                orderdict[(i,j)] = order
                orderdict[(j,i)] = order
                order += 1
    adjacencygraph = ra.AdjacencyGraph(nring_, ringsets)
    for edge in adjacencygraph:
        if 0 < len(kinds) and not edge.intersection(members) == edge:
            continue
        #edge is a set of vertices, not list
        #p is the tuple of ringsets 
        p = tuple([x for x in edge])
        ids = tuple([idlist[x] for x in p])
        #determine the layer
        if 0 < len(kinds):
            layer = len(kinds) + orderdict[ids]
            s += yp.Layer(2+layer)
            s += yp.Color(3+layer)
        v = [ringsetpositions[x] for x in p]
        d = wr.wrap(v[1]-v[0],box)
        s += yp.Line(v[0], v[0]+d)


#Fragment shapes
for i in range(len(ringsets)):
    #draw polyhedron
    if 0 < len(kinds) and not i in members:
        continue
    if 0 < len(palette):
        col = palette[i]
        s += yp.Color(col)
    elif 0 < len(kinds):
        order = kinds.index(idlist[i])
        s += yp.Color(order+3)
    else:
        size = len(ringsets[i])
        s += yp.Color(size + 0)
    if 0 < len(kinds):
        order = kinds.index(idlist[i])
        s += yp.Layer(order+2)
    else:
        size = len(ringsets[i])
        s += yp.Layer(size - 1)
    center = ringsetpositions[i]
    for ring in ringsets[i]:
        pos = ringpositions[ring]
        dr  = wr.wrap(pos - center, box)
        vpos = []
        for vertex in rings[ring]:
            dv = wr.wrap(coord[vertex] - center, box) * shrink
            vpos.append(center*explode + dv)
        if showrims:
            for i in range(len(vpos)):
                s += yp.Line(vpos[i-1],vpos[i])
        if showpoly:
            s += yp.Polygon( vpos )
            
    
    
#a new line is followed.
print(s)
