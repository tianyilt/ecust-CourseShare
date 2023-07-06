`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:04:37 04/24/2023 
// Design Name: 
// Module Name:    flowled 
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
module flowled(
input start,
input reset,
input clk,
output [7:0] cled
    );
reg flag = 0;
reg [20:0] count;
reg [7:0] led;
assign cled = led;

always@(posedge clk)
begin
	if(count[20] == 1) count <= 0;
	else count <= count + 1;
end

always@(posedge clk)
begin
	if(count[20])
		if(reset) begin
			led <= 8'b0000_0111;
			flag <= 1;
		end
		else if(start)
			if(flag) begin
				led <= {led[6:0],led[7]};
				if(led == 8'b0111_0000)
					flag <= 0;
				else ;
			end
			else begin
				led <= {led[0],led[7:1]};
				if(led == 8'b0000_1110)
					flag <= 1;
				else ;
			end
		else led <= led;
end

endmodule
