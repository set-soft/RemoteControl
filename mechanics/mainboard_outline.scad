include <parameters.scad>
use <case.scad>

mainboard_outline();

module mainboard_outline(){
	color("DarkGreen"){
		projection(){
			resize([case_innerLength-2, case_innerWidth-3, 0]){
				intersection(){
					case_inner();
					translate([0, 0, -case_height/2+pcb_bottomClearance+pcb_thickness/2])
						cube([case_length, case_width, pcb_thickness], center=true);
				}
			}
		}
	}
}
