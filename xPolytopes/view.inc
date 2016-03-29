#version 3.6;
#include "colors.inc"
#declare enable_radiosity=0;
#declare enable_focus=0;


global_settings {
  max_trace_level 100 
#if (enable_radiosity=1)
  radiosity {   }
#end
}
// Right-handed coordinate system where the z-axis points upwards
camera {
        location <0,-250,0>
        sky z
        right -y*image_width/image_height
        //up 0.15*z
        look_at <0,0,0>
        angle 20
#if (enable_focus=1)
        focal_point <0,-30,0>
        aperture 2
        blur_samples 4 
#end
}

// The radius of the cylinders to be used when drawing the Voronoi cells
#declare r=0.08;
#declare BOX=63.4085148948;
#include "common.inc"
#declare RDROP=3;
