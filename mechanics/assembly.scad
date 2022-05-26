use <case.scad>
include <parameters.scad>

$fn = 90;
pcb_thickness = 1.6;


case_lower();

#translate([-1.5, 0, -case_height/2 + case_wallThickness + pcb_bottomClearance]){
	rotate([0, 0, -90])
		import ("../electronics/mainboard/mainboard.stl");
}

//debug
//use <mainboard_outline.scad>
//mainboard_outline();
