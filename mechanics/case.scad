$fn = 90;

wallThickness = 2;
length = 140;
width = 60;
height = 20;
difference(){
	baseShape(length, width, height);
	translate([0, 0, wallThickness/2])
		#baseShape(length-2*wallThickness, width-2*wallThickness, height-wallThickness);
}

module baseShape(length, width, height){
	hull(){
		radius = 10 - (60-width)/2;
		xAbs = length/2 - radius;
		yAbs = width/2 - radius;
		for(x = [-xAbs, xAbs]){
			for(y = [-yAbs, yAbs]){
				translate([x, y, 0]){
					sphere(r=radius);
					translate([0, 0, radius/2])
						cylinder(r=radius, h=height-radius, center=true);
				}
			}
		}
	}
}
