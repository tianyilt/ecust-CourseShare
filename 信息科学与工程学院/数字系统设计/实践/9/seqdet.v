`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:06:50 05/06/2023 
// Design Name: 
// Module Name:    seqdet 
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
module seqdet(
input x,clk,rst,
output wire z,
output reg [2:0] state
    );
	 parameter IDLE = 'd0,A='d1,B='d2,C='d3,D='d4,E='d5,F='d6,G='d7;
	 assign z = (state==E && x == 0) ? 1 : 0;
	 always@(posedge clk)
		if(!rst)
			state <= IDLE;
		else casex(state)
			IDLE: if(x == 1) state <= A;
			A: if(x == 0) state <= B;
			B: if(x == 0) state <= C;
				else 		  state <= F;
			C: if(x == 1) state <= D;
				else       state <= G;
			D: if(x == 0) state <= E;
				else       state <= A;
			E: if(x == 0) state <= C;
				else       state <= A;
			F: if(x == 1) state <= A;
				else       state <= B;
			G: if(x == 1) state <= F;
			default:      state <= IDLE;
		endcase
endmodule
