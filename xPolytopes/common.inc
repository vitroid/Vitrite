global_settings { max_trace_level 100 }

// White background
sky_sphere {pigment {gradient y color_map {
//        [0 color rgb<0,0,0>][1 color rgb<1,1,1>]}}
//        [0 color rgb<0,0,0>][0.45 color rgb<0,0,0>][0.55 color rgb<1,1,1>][1 color rgb<1,1,1>]}}
        [0 color rgb<0,0,0>][0.95 color rgb<1,1,1>][1 color rgb<1,1,1>]}}

}

//background{rgb 1}
// Two lights with slightly different colors
light_source{<-300,-2000,-80> color rgb 0.7 shadowless}
light_source{<1200,-1200,0> color rgb 0.7 shadowless}
//light_source{<0,-70,0> color rgb <0.43,0.45,0.45> }




#declare Normal=finish{specular 0.5 ambient 0.0 diffuse 0.8};
#declare Polygon=finish{specular 0.0 ambient 0.6 diffuse 0.4};
#declare R2 = 0.02;
#declare R3 = R2;
#declare R4 = R2;
#declare R5 = R2;
#declare R6 = R2;
#declare R7 = R2;
#declare R8 = R2;
#declare R9 = R2;
#declare R10 = R2;
#declare R11 = R2;
#declare R12 = R2;
#declare R13 = R2;
#declare R14 = R2;
#declare R15 = R2;
#declare R16 = R2;
#declare R17 = R2;
#declare R18 = R2;
#declare R19 = R2;

//#declare C1=<1.0, 0.9, 0.2, 0.0>;
//#declare C2=<0.9, 0.2, 1.0, 0.0>;
#declare C0=<1.0, 1.0, 1.0, 0.0>;
#declare C1=<1.0, 0.2, 0.2, 0.0>;
#declare C2=<0.2, 0.2, 1.0, 0.0>;

#declare TEX0=texture { finish { Normal } pigment { color rgbt <0/8 0/8 0/8 0/8> }}
#declare TEX1C=texture { finish { Normal } pigment { color rgbt <3/8 8/8 1/8 5/8> }}
#declare TEX1H=texture { finish { Normal } pigment { color rgbt <0/8 8/8 5/8 5/8> }}

#declare TEXv4=texture { finish { Polygon } pigment { color rgb <236/255, 153/255, 21/255> }}
#declare TEXv8=texture { finish { Polygon } pigment { color rgb <255/255, 0/255, 0/255> }}
#declare TEXv46=texture { finish { Polygon } pigment { color rgb <0,0.5,1> }}
#declare TEXv39=texture { finish { Polygon } pigment { color rgb <0,1,0> }}
#declare TEXv34=texture { finish { Polygon } pigment { color rgb <185/255,115/255,173/255> }}
#declare TEXv874=texture { finish { Polygon } pigment { color rgb <185/255*0.8,0.2,0.2> }}


#declare TEX3=texture { finish { Polygon } pigment { color rgbt (C0* 0+C1*8)/8 + <0,0,0,0/8> }}
#declare TEX4=texture { finish { Polygon } pigment { color rgbt (C0* 1+C1*7)/8 + <0,0,0,0/8> }}
#declare TEX5=texture { finish { Polygon } pigment { color rgbt (C0* 2+C1*6)/8 + <0,0,0,0/8> }}
#declare TEX6=texture { finish { Polygon } pigment { color rgbt (C0* 3+C1*5)/8 + <0,0,0,0/8> }}
#declare TEX7=texture { finish { Polygon } pigment { color rgbt (C0* 4+C1* 4)/8 + <0,0,0,8/8> }}
#declare TEX8=texture { finish { Polygon } pigment { color rgbt (C0* 5+C1* 3)/8 + <0,0,0,8/8> }}
#declare TEX9=texture { finish { Polygon } pigment { color rgbt (C0* 6+C1* 2)/8 + <0,0,0,8/8> }}
#declare TEX10=texture { finish { Polygon } pigment { color rgbt (C0* 7+C1* 1)/8 + <0,0,0,8/8> }}
#declare TEX11=texture { finish { Polygon } pigment { color rgbt (C0* 8+C2* 0)/8 + <0,0,0,8/8> }}
#declare TEX12=texture { finish { Polygon } pigment { color rgbt (C0* 7+C2* 1)/8 + <0,0,0,8/8> }}
#declare TEX13=texture { finish { Polygon } pigment { color rgbt (C0* 6+C2* 2)/8 + <0,0,0,8/8> }}
#declare TEX14=texture { finish { Polygon } pigment { color rgbt (C0* 5+C2* 3)/8 + <0,0,0,8/8> }}
#declare TEX15=texture { finish { Polygon } pigment { color rgbt (C0* 4+C2* 4)/8 + <0,0,0,8/8> }}
#declare TEX16=texture { finish { Polygon } pigment { color rgbt (C0* 3+C2* 5)/8 + <0,0,0,0/8> }}
#declare TEX17=texture { finish { Polygon } pigment { color rgbt (C0* 2+C2* 6)/8 + <0,0,0,0/8> }}
#declare TEX18=texture { finish { Polygon } pigment { color rgbt (C0* 1+C2* 7)/8 + <0,0,0,0/8> }}
#declare TEX19=texture { finish { Polygon } pigment { color rgbt (C0* 0+C2* 8)/8 + <0,0,0,0/8> }}


// The radius of the cylinders to be used when drawing the Voronoi cells
#declare r=0.08;

#declare Gauss = function(x,y,z,s) {exp(-(pow(x,2) + pow(y,2) + pow(z,2))/pow(s,2))}


#declare RBubble = 7;
#declare RGi = 1.0;
//frame
#declare RFrame = 0.05;
#declare RHB = 0.2;

#declare Bubble =
finish {
    ambient 0.1
    diffuse 0.1
    //reflection .1
    reflection .02 //physical value
    specular 0.9
    roughness 0.015
    //phong_size 200
    //phong 0.9
}
#declare Polyhed =
finish {
    ambient 0.6
    diffuse 0.4
    ambient 0.1
    diffuse 0.1
    reflection .25
    specular 0.6
    roughness 0.02
}
#declare Methane =
finish {
    ambient 0.0
    diffuse 1.0
    reflection .25
    specular 0
    //phong_size 200
    //phong 0.9
}
#declare Frame =
finish {
    ambient 0.8
    diffuse 0.2
    reflection 0
    specular 0
    //phong_size 200
    //phong 0.9
    roughness 0.1
}
#declare TEXGi=
texture {
    finish { Methane }
    pigment { color rgb <0.2 0.1 0.8> }
}
#declare TEXBubble=
texture {
    finish { Bubble }
    pigment { Clear }
}

#declare TEXFrame=
texture {
    finish { Frame }
    pigment { color rgb <0.2, 0.2, 0.2> }
//    pigment { color rgb <0.8, 0.8, 0.8> }
//    pigment { color rgb <0.2 0.8 1> }
}
//polyhed
#declare TEXPoly=
texture {
    finish { Polyhed }
    pigment { color rgbt <0 1 0.7 0.8> }
}


#declare TEXR=
texture {
    finish { Methane }
    pigment { color rgb <1 0 0> }
}

#declare TEXG=
texture {
    finish { Methane }
    pigment { color rgb <0 1 0> }
}

#declare TEXB=
texture {
    finish { Methane }
    pigment { color rgb <0 0 1> }
}



#declare TEXHB = texture{TEXFrame};



#declare color52=rgb <0.7,0.7,0.7>; //purple White;//bubble
#declare color56=rgb <0,0.7,0.8>;//crystal
#declare Dense=Red;
#declare Dilute=Blue;
#declare color57=Dilute*0/30 + Dense*30/30;
#declare color58=Dilute*1/30 + Dense*29/30;
#declare color59=Dilute*2/30 + Dense*28/30;
#declare color60=Dilute*3/30 + Dense*27/30;
#declare color61=Dilute*4/30 + Dense*26/30;
#declare color62=Dilute*5/30 + Dense*25/30;
#declare color63=Dilute*6/30 + Dense*24/30;
#declare color64=Dilute*7/30 + Dense*23/30;
#declare color65=Dilute*8/30 + Dense*22/30;
#declare color66=Dilute*9/30 + Dense*21/30;
#declare color67=Dilute*10/30 + Dense*20/30;
#declare color68=Dilute*11/30 + Dense*19/30;
#declare color69=Dilute*12/30 + Dense*18/30;
#declare color70=Dilute*13/30 + Dense*17/30;
#declare color71=Dilute*14/30 + Dense*16/30;
#declare color72=Dilute*15/30 + Dense*15/30;
#declare color73=Dilute*16/30 + Dense*14/30;
#declare color74=Dilute*17/30 + Dense*13/30;
#declare color75=Dilute*18/30 + Dense*12/30;
#declare color76=Dilute*19/30 + Dense*11/30;
#declare color77=Dilute*20/30 + Dense*10/30;
#declare color78=Dilute*21/30 + Dense*9/30;
#declare color79=Dilute*22/30 + Dense*8/30;
#declare color80=Dilute*23/30 + Dense*7/30;
#declare color81=Dilute*24/30 + Dense*6/30;
#declare color82=Dilute*25/30 + Dense*5/30;
#declare color83=Dilute*26/30 + Dense*4/30;
#declare color84=Dilute*27/30 + Dense*3/30;
#declare color85=Dilute*28/30 + Dense*2/30;
#declare color86=Dilute*29/30 + Dense*1/30;
#declare color87=Dilute*30/30 + Dense*0/30;

//radius of methane
#declare R=0.75;
//#declare R=1.2; //use larger spheres

#declare TEX52=texture{pigment{color52 } finish {Normal}};
#declare TEX56=texture{pigment{color56 } finish {Normal}};
#declare TEX57=texture{pigment{color57 } finish {Normal}};
#declare TEX58=texture{pigment{color58 } finish {Normal}};
#declare TEX59=texture{pigment{color59 } finish {Normal}};
#declare TEX60=texture{pigment{color60 } finish {Normal}};
#declare TEX61=texture{pigment{color61 } finish {Normal}};
#declare TEX62=texture{pigment{color62 } finish {Normal}};
#declare TEX63=texture{pigment{color63 } finish {Normal}};
#declare TEX64=texture{pigment{color64 } finish {Normal}};
#declare TEX65=texture{pigment{color65 } finish {Normal}};
#declare TEX66=texture{pigment{color66 } finish {Normal}};
#declare TEX67=texture{pigment{color67 } finish {Normal}};
#declare TEX68=texture{pigment{color68 } finish {Normal}};
#declare TEX69=texture{pigment{color69 } finish {Normal}};
#declare TEX70=texture{pigment{color70 } finish {Normal}};
#declare TEX71=texture{pigment{color71 } finish {Normal}};
#declare TEX72=texture{pigment{color72 } finish {Normal}};
#declare TEX73=texture{pigment{color73 } finish {Normal}};
#declare TEX74=texture{pigment{color74 } finish {Normal}};
#declare TEX75=texture{pigment{color75 } finish {Normal}};
#declare TEX76=texture{pigment{color76 } finish {Normal}};
#declare TEX77=texture{pigment{color77 } finish {Normal}};
#declare TEX78=texture{pigment{color78 } finish {Normal}};
#declare TEX79=texture{pigment{color79 } finish {Normal}};
#declare TEX80=texture{pigment{color80 } finish {Normal}};
#declare TEX81=texture{pigment{color81 } finish {Normal}};
#declare TEX82=texture{pigment{color82 } finish {Normal}};
#declare TEX83=texture{pigment{color83 } finish {Normal}};
#declare TEX84=texture{pigment{color84 } finish {Normal}};
#declare TEX85=texture{pigment{color85 } finish {Normal}};
#declare TEX86=texture{pigment{color86 } finish {Normal}};
#declare TEX87=texture{pigment{color87 } finish {Normal}};

#declare RNa=2.0;
#declare RCl=2.0;
#declare ROi=0;//clathrate
#declare RHi=0;
#declare ROj=1.5;
#declare RHj=1.0;

#declare TEXNa=texture{pigment{rgb<1,0.5,0.4>} finish {Normal}};
#declare TEXCl=texture{pigment{rgb<0.5,1,0.4>} finish {Normal}};
#declare TEXHi=texture{pigment{Blue} finish {Normal}};
#declare TEXHj=texture{pigment{rgb<0.4,0.8,1>} finish {Normal}};
#declare TEXOi=texture{pigment{Blue} finish {Normal}};
#declare TEXOj=texture{pigment{White} finish {Normal}};
