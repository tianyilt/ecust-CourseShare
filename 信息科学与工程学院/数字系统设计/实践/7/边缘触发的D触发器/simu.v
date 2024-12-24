`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:44:29 04/26/2023
// Design Name:   edged
// Module Name:   F:/exp7_1/simu.v
// Project Name:  exp7_1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: edged
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module simu;
	reg d, clk;
	wire q, qn;
	edged uut (
		.d(d), 
		.clk(clk), 
		.q(q), 
		.qn(qn)
	);
	always #50 clk = $random;
	always #40 d = ~d;
	initial begin
		d = 0;
		clk = 0;
	end
endmodule

