$fn = 90;
height = 11;

buttons();

module buttons(){
	for(x = [-24, -12, 0, 12, 24], y = [-12, 0, 12]){
		translate([x, y, 0])
			cylinder(d=7.5, h=height, center=true);
	}
	grid(thickness=0.5);
	translate([0, 0, 6.5]){
		grid(thickness=2);
	}
}


module grid(thickness=0.5){
	for(x = [-24, -12, 0, 12, 24]){
		translate([x, 0, -height/2+thickness/2])
		cube([3, 24, thickness], center=true);
	}
	
	for(y = [-12, 0, 12]){
		translate([0, y, -height/2+thickness/2])
			cube([48, 3, thickness], center=true);
	}
}
