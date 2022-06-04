use <case.scad>
include <parameters.scad>

case_lower();
pcb();
/*
translate([0, 0, 100]){
	case_upper();
	pcb();
}*/



module pcb(){
	#translate([-0.5, 0, -case_height/2 + case_wallThickness + pcb_bottomClearance]){
		rotate([0, 0, -90])
			import ("../electronics/mainboard/mainboard.stl");
	}
}

//debug
//use <mainboard_outline.scad>
//mainboard_outline();
