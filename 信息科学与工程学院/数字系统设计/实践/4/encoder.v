`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:19:11 04/19/2023 
// Design Name: 
// Module Name:    encoder 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module encoder(in,yn);
	input [7:0] in;
	output [3:0] yn;
	reg [3:0]yn;
	reg [3:0]y;
	always@ (in)
		begin
		     if( in[7] == 1'b0) y=4'b1000;
		else if( in[6] == 1'b0) y=4'b1001;
		else if( in[5] == 1'b0) y=4'b1010;
		else if( in[4] == 1'b0) y=4'b1011;
		else if( in[3] == 1'b0) y=4'b1100;
		else if( in[2] == 1'b0) y=4'b1110;
		else if( in[1] == 1'b0) y=4'b1111;
		else if( in[0] == 1'b0) y=4'b0001;
		else y=4'b0000;
		yn = y;
		end
endmodule
