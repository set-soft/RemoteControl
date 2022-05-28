use <case.scad>

case_upper();

translate([0, 55, 0])
	rotate([180, 0, 0])
		case_lower();
