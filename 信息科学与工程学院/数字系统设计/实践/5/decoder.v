`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:12:45 04/19/2023 
// Design Name: 
// Module Name:    decoder 
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
module decoder(
	input [2:0] a,
	input en,
	output reg [7:0] y
    );
	 always @ (a,en)
		begin
			if (en == 1)
			begin
				case (a)
				3'b000 : y= 8'b00000001;
				3'b001 : y= 8'b00000010;
				3'b010 : y= 8'b00000100;
				3'b011 : y= 8'b00001000;
				3'b100 : y= 8'b00010001;
				3'b101 : y= 8'b00100001;
				3'b110 : y= 8'b01000001;
				3'b111 : y= 8'b10000001;
				default: y= 8'b00000000;
				endcase
			end
			else y= 8'b00000000;
		end
endmodule
