use <case.scad>
include <case_parameters.scad>

$fn = 90;
pcb_thickness = 1.6;

#difference(){
	case();
	//debug
	translate([0, 0, case_height/2]){
		cube([case_length+1, case_width+1, case_height], center = true);
	}
	//debug
}

translate([0, 0, -case_height/2 + case_wallThickness + 1.5]){
	rotate([0, 0, -90])
		import ("../electronics/mainboard/mainboard.stl");
}