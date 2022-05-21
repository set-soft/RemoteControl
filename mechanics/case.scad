include <case_parameters.scad>

$fn = 90;
pcb_thickness = 1.6;

case();

module case(){
	difference(){
		case_base();
		translate([-1.5, 0, 0]){
			resize([case_length-3-2*case_wallThickness, case_width-2*case_wallThickness, case_height-2*case_wallThickness]){
				case_base();
			}
		}
		translate([case_length/2, 0, 0])
			rotate([0, -90, 0])
				cylinder(d=5, h=20);
		translate([case_length/2+3, 0, 0])
			rotate([90, 0, 0])
				cylinder(d=12, h=case_width, center=true);
	}
}


module case_base(){
	radius = 1;
	minkowski(){
		resize([case_length-2*radius, case_width-2*radius, case_height-2*radius]){
			intersection(){
				cube([case_length, case_width, case_height], center=true);

				resize([2*case_length, case_width, 3*case_height])
					translate([0, 0, 0])
						rotate([0, 90, 0])
							cylinder(center=true);
				
				resize([case_length, 3*case_width, 3*case_height])
					translate([0, 0, 0])
						cylinder(center=true);
			}
		}
		sphere(r=radius);
	}
}
