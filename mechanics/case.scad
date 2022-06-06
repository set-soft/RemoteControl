include <parameters.scad>

$fn = $preview ? 60: 360;

case_upper();
translate([0, 0, -50])
	case_lower();


module case_upper(){
	difference(){
		case();
		translate([0, 0, -case_height/2])
			cube([case_length+1, case_width+1, case_height], center=true);
	}
	case_mountingLevers();
}

module case_lower(){
	difference(){
		case();
		translate([0, 0, case_height/2])
			cube([case_length+1, case_width+1, case_height], center=true);
		case_mountingPits();
	}
}

module case(){
	difference(){
		case_base();
		case_inner();
		led_hole();
		button_holes();
	}
	pcb_bottomSupport();
	pcb_positionPole();
}

module case_base(){
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
			translate([x+30.2, y, case_height/2]){
				cylinder(d=8, h=3*case_wallThickness, center=true);
			}
		}
	}
}

module case_mountingPits(){
	angleAbs = 12;
	diameter = 2;
	length = 8;
	for(angle = [-angleAbs, angleAbs]){
		rotate([90, 0, angle])
			translate([case_length/2-4.7, -3, 0])
				cylinder(d=diameter, h=length, center=true);
	}

	rotate([90, 0, 0])
		translate([-case_length/2+3.7, -3, 0])
			cylinder(d=diameter, h=length, center=true);

	yAbs = case_width/2-1.7;
	for(y = [-yAbs, yAbs]){
		translate([0, y, -3])
			rotate([90, 0, 90])
				cylinder(d=diameter, h=length, center=true);
	}
}

module case_mountingLevers(){
	angleAbs = 12;
	diameter = 2;
	length = 7;
	for(angle = [-angleAbs, angleAbs]){
		rotate([90, 0, angle])
			translate([case_length/2-4.7, -3, 0]){
				cylinder(d=diameter, h=length, center=true);
				translate([-diameter/8, 6, 0])
					cube([diameter/4*3, 12, length], center=true);
			}
	}

	rotate([90, 0, 0])
		translate([-case_length/2+3.7, -3, 0]){
			cylinder(d=diameter, h=length, center=true);
			translate([diameter/8, 6, 0])
				cube([diameter/4*3, 12, length], center=true);
		}

	yAbs = case_width/2-1.7;
	for(y = [-yAbs, yAbs]){
		translate([0, y, -3])
			rotate([90, 0, 90]){
				cylinder(d=diameter, h=length, center=true);
				translate([-sign(y)*diameter/8, 5.5, 0])
					cube([diameter/4*3, 11, length], center=true);
			}
	}
}
