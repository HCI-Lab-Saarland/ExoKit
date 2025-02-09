The 3d models were designed with Autodesk Fusion 360. We fabricated the 3D-printed parts with an Ultimaker S5 printer, using ABS filament. We used 100% infill with an octet infill pattern, a normal support structure and 2 mm wall thickness. 

To build the back construction, print:
	2x back_rail
	1x lower_back_rail

To build a 3 DoF actuated left arm (right arm analogous), print:
	Joints: 1x joint_elbow_l, 1x joint_shoulder_back_l, 1x joint_shoulder_side_l, 3x rotor
	Cuffs: 2x arm_cuff_upper_arm, 1x forearm_cuff (the cuff for the forearm is smaller than the upper arm cuff)
	Links: 1x arm_rail, 2x joint_rod_long, 1x forearm_chain_adapter, multiple chain_mf and chain_mm (we recommend at least two chain segments of each type)

If passive joint modules are needed, print:
	1x servo_dummy_outer
	1x servo_dummy_rotor
	1x rotor

If a load cell should be deployed at the upper arm, also print:
	1x loadcell_adapter_joint 
	1x loadcell_adapter_rail 


For more fabrication and assembly information, please refer to the user manual (Chapter 2 & 3).
