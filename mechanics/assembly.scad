use <case.scad>
use <buttons.scad>
include <parameters.scad>

case_lower();
pcb();

translate([0, 0, 100]){
	case_upper();
	pcb();
	translate([30.2, 0, 5.45])
		buttons();
}



module pcb(){
	#translate([-0.5, 0, -case_height/2 + case_wallThickness + pcb_bottomClearance]){
		rotate([0, 0, -90])
			import ("../electronics/mainboard/mainboard.stl");
	}
}

//debug
//use <mainboard_outline.scad>
//mainboard_outline();
