include <case_parameters.scad>
use <mainboard_outline.scad>

$fn = 90;
pcb_thickness = 1.6;

#difference(){
	case_base();
	resize([case_length-2*case_wallThickness, case_width-2*case_wallThickness, case_height-2*case_wallThickness]){
		case_base();
	}
	//debug
	translate([0, 0, case_height/2]){
		cube([case_length+1, case_width+1, case_height], center = true);
	}
	//debug
}

translate([0, 0, -case_height/2 + case_wallThickness + 1.5]){
	mainboard_outline();
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
