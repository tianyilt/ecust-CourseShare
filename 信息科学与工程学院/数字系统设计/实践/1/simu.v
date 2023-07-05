`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:43:18 04/10/2023
// Design Name:   test1
// Module Name:   E:/test/simu.v
// Project Name:  test
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: test1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
include"test1.v";
module simu;
	// Inputs
	reg a;
	reg b;
	reg sl,clock;
	// Outputs
	wire out;
	// Instantiate the Unit Under Test (UUT)
	test1 uut (
		.out(out), 
		.a(a), 
		.b(b), 
		.sl(sl)
	);
	initial begin
		// Initialize Inputs
		a = 0;
		b = 0;
		sl = 0;
		clock = 0;
		// Wait 100 ns for global reset to finish
		#100;
		// Add stimulus here
	end
	always #50 clock = ~clock;
	always @(posedge clock)
	 begin
	  #1a={$random}%2;
	  #3b={$random}%2;
    end
	 always#10000 sl=!sl;
	 
endmodule

