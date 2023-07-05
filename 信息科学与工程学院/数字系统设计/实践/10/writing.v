`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:05:18 05/08/2023 
// Design Name: 
// Module Name:    writing 
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
module writing(
input reset,clk,
input [7:0] data,address,
output reg ack,
inout sda
    );
reg [3:0] state;
reg [4:0] sh8out_state;
reg [7:0] sh8out_buf;
reg link_write,finish_F;

parameter idle = 0,addr_write = 1,data_write = 2,stop_back = 3;
parameter bit0 = 1,bit1 = 2,bit2 = 3,bit3 = 4,bit4 = 5,bit5 = 6,bit6 = 7,bit7 = 8;
assign sda = link_write ? sh8out_buf[7] : 1'bz;
always@(posedge clk) begin
	if(!reset) begin
		link_write <= 0;
		state <= idle;
		finish_F <= 0;
		sh8out_state <= idle;
		ack <= 0;
		sh8out_buf <= 0;
	end
	else case(state)
		idle: begin
			link_write <= 0;
			finish_F <= 0;
			sh8out_state <= idle;
			ack <= 0;
			sh8out_buf <= address;
			state <= addr_write;
		end
		addr_write: begin
			if(finish_F == 0) shift8_out;
			else begin
				sh8out_state <= idle;
				sh8out_buf <= data;
				state <= data_write;
				finish_F <= 0;
			end
		end
		data_write: begin
			if(finish_F == 0) shift8_out;
			else begin
				link_write <= 0;
				state <= stop_back;
				finish_F <= 0;
				ack <= 1;
			end
		end
		stop_back:begin
			ack <= 0;
			state <= idle;
		end
	endcase
end
task shift8_out; begin
	case(sh8out_state)
		idle:begin
			link_write <= 1;
			sh8out_state <= bit7;
		end
		bit7: begin
			link_write <= 1;
			sh8out_state <= bit6;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit6: begin
			sh8out_state <= bit5;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit5:begin
			sh8out_state <= bit4;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit4:begin
			sh8out_state <= bit3;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit3:begin
			sh8out_state <= bit2;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit2:begin
			sh8out_state <= bit1;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit1:begin
			sh8out_state <= bit0;
			sh8out_buf <= sh8out_buf << 1;
		end
		bit0:begin
			link_write <= 0;
			finish_F <= 1;
		end
	endcase
end
endtask
endmodule
