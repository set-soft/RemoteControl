include <parameters.scad>

$fn = 90;

//debug
difference(){
	case();
	translate([0, 0, case_height/2]){
		cube([case_length+1, case_width+1, case_height], center = true);
	}
}
//debug

module case(){
	difference(){
		case_base();
		case_inner();
		led_hole();
	}
	pcb_bottomSupport();
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


module case_inner(){
	translate([-1.5, 0, 0]){
		resize([case_innerLength, case_innerWidth, case_innerHeight]){
			case_base();
		}
	}
}

module led_hole(){
	translate([case_length/2, 0, 0])
		rotate([0, -90, 0])
			cylinder(d=5, h=20);
	translate([case_length/2+3, 0, 0])
		rotate([90, 0, 0])
			cylinder(d=12, h=case_width, center=true);
}

module pcb_bottomSupport(){
	for(y = [-18, -6, 6, 18]){
		translate([33, y, -case_height/2+case_wallThickness+pcb_bottomClearance/2])
			cube([70, 1, pcb_bottomClearance], center=true);
	}
	
	translate([-34, 10, -case_height/2+case_wallThickness+pcb_bottomClearance/2])
		cube([65, 25, pcb_bottomClearance], center=true);
	
	translate([-34, -12, -case_height/2+case_wallThickness+pcb_bottomClearance/2])
		cube([65, 10, pcb_bottomClearance], center=true);
}
