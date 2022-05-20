include <case_parameters.scad>
use <case.scad>

pcb_thickness = 1.6;

mainboard_outline();

module mainboard_outline(){
	color("DarkGreen"){
		projection(){
			delta = 2*case_wallThickness+3;
			resize([case_length-delta, case_width-delta, 0]){
				difference(){
					translate([0, 0, case_height/2])
						case_base();
					bottomCutHeight = case_wallThickness + 1.5;
					translate([0, 0, -case_height/2+bottomCutHeight])
						cube([case_length, case_width, case_height], center=true);
					translate([0, 0, case_height/2+bottomCutHeight+pcb_thickness])
						cube([case_length, case_width, case_height], center=true);
				}
			}
		}
	}
}
