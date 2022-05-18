$fn = 360;

width = 45;
length = 3*width;
height = 17;

radius = 1;
minkowski(){
	resize([length-2*radius, width-2*radius, height-2*radius]){
		intersection(){
			cube([length, width, height], center=true);

			resize([2*length, width, 3*height])
				translate([0, 0, 0])
					rotate([0, 90, 0])
						cylinder(center=true);
			
			
			resize([length, 3*width, 3*height])
				translate([0, 0, 0])
					cylinder(center=true);
		}
	}
	sphere(r=radius);
}
