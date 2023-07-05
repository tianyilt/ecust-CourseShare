`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:09:57 04/17/2023
// Design Name:   mux_4to1
// Module Name:   E:/mux_4to1/simu.v
// Project Name:  mux_4to1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mux_4to1
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
	reg a;
	reg b;
	reg c;
	reg d;
	reg [1:0] sel;

	// Outputs
	wire y;

	// Instantiate the Unit Under Test (UUT)
	mux_4to1 uut (
		.y(y), 
		.a(a), 
		.b(b), 
		.c(c), 
		.d(d), 
		.sel(sel)
	);

	initial begin
		// Initialize Inputs
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		sel = 2'b00;

		// Wait 100 ns for global reset to finish
		
	   #100; a=1;
	   #100; b=1;
	   #100; c=1;
	   #100; d=1;
		#100; a=0;
	   #100; b=0;
	   #100; c=0;
	   #100; d=0;
      #100; $stop;
		// Add stimulus here

	end
   always #10 sel=sel+1;
endmodule

