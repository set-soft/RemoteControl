include <parameters.scad>

$fn = $preview ? 45 : 180;

case_upper();
translate([0, 0, -50])
	case_lower();

translate([-40, 0, 0])
case_backRing();


module case_upper(){
	difference(){
		case();
		translate([0, 0, -case_height/2])
			cube([case_length+1, case_width+1, case_height], center=true);
	}
}

module case_lower(){
	difference(){
		case();
		translate([0, 0, case_height/2])
			cube([case_length+1, case_width+1, case_height], center=true);
	}
}

module case(){
	difference(){
		case_base();
		case_inner();
		led_hole();
		button_holes();
		scale([1.001,1.001,1.001]) //workaround to make the groove visible
			case_backRing();
		case_positioningSlits();
	}
	pcb_bottomSupport();
	pcb_positionPole();
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
	translate([-0.5, 0, 0]){
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
			cube([60, 1, pcb_bottomClearance], center=true);
	}
	
	translate([-33, 10, -case_height/2+case_wallThickness+pcb_bottomClearance/2])
		cube([65, 24, pcb_bottomClearance], center=true);
	
	translate([-33, -12, -case_height/2+case_wallThickness+pcb_bottomClearance/2])
		cube([65, 10, pcb_bottomClearance], center=true);
}

module pcb_positionPole(){
	translate([-9, -12, -case_height/2+case_wallThickness+pcb_bottomClearance])
		cylinder(d1=3, d2=2.5, h=3*pcb_thickness);
}

module button_holes(){
	for(x = [-24, -12, 0, 12, 24]){
		for(y = [-12, 0, 12]){
			translate([x+29.3, y, case_height/2]){
				cylinder(d=8, h=3*case_wallThickness, center=true);
			}
		}
	}
}

module case_backRing(){
	intersection(){
		difference(){
			case_base();
			resize([case_length, case_width-case_wallThickness, case_height-case_wallThickness]){
				case_base();
			}
		}
		translate([-50, 0, 0]){
			cube([15, case_width+1, case_height+1], center=true);
		}
	}
}

module case_positioningSlits(){
	angleAbs = 15;
	for(angle = [-angleAbs, angleAbs]){
		//front
		rotate([0, 0, angle])
			translate([case_length/2-3, 0, 0])
				cube([1, 9, case_height-4*case_wallThickness], center=true);
		//back
		rotate([0, 0, angle])
			translate([-case_length/2+2, 0, 0])
				cube([1, 9, case_height-4*case_wallThickness], center=true);
	}
}
