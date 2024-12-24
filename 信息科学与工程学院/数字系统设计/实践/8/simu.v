`timescale 1ns / 100ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:20:17 04/26/2023
// Design Name:   fdivision
// Module Name:   F:/exp7_3/simu.v
// Project Name:  exp7_3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: fdivision
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
module simu;
	reg F10M;
	reg RESET;
	wire F500KB;
	fdivision uut (
		.F10M(F10M), 
		.RESET(RESET), 
		.F500KB(F500KB)
	);
	always #5 F10M = ~F10M;
	initial begin
		F10M = 0;
		RESET = 1;
		#10 RESET = 0;
		#10 RESET = 1;
	end
endmodule

