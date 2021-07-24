#include <stdio.h>
#include <stdlib.h>
#include <complex>

#include "meep.hpp"

#include "ctl-math.h"
#include "ctlgeom.h"

#include "meep/meepgeom.hpp"

using namespace meep;

//typedef std::complex<double> cdouble;

vector3 v3(double x, double y = 0.0, double z = 0.0) {
  vector3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

double eps(const vec &p){
  return 1.0;
  }
  
int main(int argc, char *argv[]){
initialize mpi(argc, argv);
double resolution = 20;
grid_volume v = vol2d(10, 10, resolution);
structure s(v, eps, pml(1.0));

meep_geom::material_type dielectric = meep_geom::make_dielectric(12.0);
vector3 vertices[4];
vertices[0] = v3(0,0,0);
vertices[1] = v3(4,0,0);
vertices[2] = v3(4,4,0);
vertices[3] = v3(0,4,0);
double height = 0.0;
vector3 axis = v3(0.0,0.0,1.0);

GEOMETRIC_OBJECT objects[1];
object[0] = make_prism(dielectric, vertices, 4, height, axis);
geometric_object_list g = {1, objects};
meep_geom::set_materials_from_geometry(&the_structure, g);
  
fields f(&s);
f.output.hdf5(Dielectric, v.surroundings());
  
return 0;
}
