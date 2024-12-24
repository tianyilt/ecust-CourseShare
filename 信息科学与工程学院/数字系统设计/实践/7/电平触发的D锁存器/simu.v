`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:08:49 04/26/2023
// Design Name:   latch
// Module Name:   F:/exp7_2/simu.v
// Project Name:  exp7_2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: latch
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module simu;

	// Inputs
	reg d;
	reg clk;

	// Outputs
	wire q;
	wire qn;

	// Instantiate the Unit Under Test (UUT)
	latch uut (
		.d(d), 
		.clk(clk), 
		.q(q), 
		.qn(qn)
	);
	always #50 clk = $random;
	always #40 d = ~d;
	initial begin
		// Initialize Inputs
		d = 0;
		clk = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

