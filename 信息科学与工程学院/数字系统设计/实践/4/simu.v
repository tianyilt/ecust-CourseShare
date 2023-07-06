`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:29:41 04/19/2023
// Design Name:   encoder
// Module Name:   E:/exp4/simu.v
// Project Name:  exp4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: encoder
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
	reg [7:0] in;

	// Outputs
	wire [3:0] yn;

	// Instantiate the Unit Under Test (UUT)
	encoder uut (
		.in(in), 
		.yn(yn)
	);

	initial begin
		// Initialize Inputs
		in = 8'b11111111;
		// Wait 100 ns for global reset to finish
		#100 in=8'b00000000;
		#100 in=8'b10100000;
		#100 in=8'b01000001;
		#100 in=4'b0011;
		#100 in=4'b0100;
		#100 in=4'b0101;
		#100 in=4'b0110;
		#100 in=4'b0111;
		#100 in=4'b1000;
		#100 in=4'b1011;
		// Add stimulus here

	end
      
endmodule

