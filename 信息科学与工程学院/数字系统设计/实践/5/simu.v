`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:25:33 04/19/2023
// Design Name:   decoder
// Module Name:   E:/exp5/simu.v
// Project Name:  exp5
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: decoder
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
	reg [2:0] a;
	reg en;

	// Outputs
	wire [7:0] y;

	// Instantiate the Unit Under Test (UUT)
	decoder uut (
		.a(a), 
		.en(en), 
		.y(y)
	);

	initial begin
		// Initialize Inputs
		a = 3'b000;
		en = 0;

		// Wait 100 ns for global reset to finish
		#100 en = 1;
		#100 a = 3'b000;
		#100 a = 3'b001;
		#100 a = 3'b010;
		#100 a = 3'b011;
		#100 a = 3'b100;
		#100 a = 3'b101;
		#100 a = 3'b110;
		#100 a = 3'b111;
		#100 a = 3'b000;
        
		// Add stimulus here
	end
endmodule

