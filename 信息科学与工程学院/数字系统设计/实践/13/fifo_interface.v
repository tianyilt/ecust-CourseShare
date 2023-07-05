`define SRAM_SIZE 8
`timescale 1ns/1ns

module fifo_interface(
    input [7:0] in_data,
    input fiford,fifowr,clk,rst,
    inout sram_data,
    output [7:0] out_data,
    output reg nempty,nfull,
    output rd,wr,
    output reg [10:0] address
);

reg[10:0] fifo_wp,fifo_rp;
reg[10:0] fifo_wp_next,fifo_rp_next;
reg near_full, near_empty;
reg[3:0] state;
reg[7:0] in_data_buf,out_data_buf;

parameter idle= 'b0000,
read_ready= 'b0100,
read= 'b0101,
read_over= 'b0111,
write_ready = 'b1000,
write= 'b1001,
write_over='b1011;

always @(posedge clk or negedge rst)
    if (~rst)
        state <= idle;
    else
        case(state)
            idle:
                if (fifowr==0 && nfull)
                    state <= write_ready;
                else if(fiford==0 && nempty)
                    state<= read_ready;
                else
                    state<= idle;
            read_ready:
                state <= read;
            read:
                if (fiford == 1)
                    state <= read_over;
                else
                    state <= read;
            read_over:
                state <= idle;
            write_ready:
                state <= write;
            write:
                if (fifowr == 1)
                    state <= write_over;
                else
                    state <= write;
            write_over:
                state <= idle;
            default: 
                state <= idle;
        endcase

assign rd = ~state[2];
assign wr = (state == write) ? fifowr : 1'b1;

always @ (posedge clk)
    if (~fifowr)
        in_data_buf <= in_data;

assign sram_data = (state[3]) ? in_data_buf : 8'hzz;

always @ (state or fiford or fifowr or fifo_wp or fifo_rp)
    if (state[2] || ~fiford)
        address = fifo_rp;
    else if (state[3] || ~fifowr)
        address = fifo_wp;
    else
        address = 'bz;

assign out_data = (state[2]) ? sram_data : 8'bz;

always @ (posedge clk)
    if (state == read)
        out_data_buf <= sram_data;

always @ ( posedge clk or negedge rst)
    if (~rst)
        fifo_rp <= 0;
    else if (state == read_over)
        fifo_rp <= fifo_rp_next;

always @ (fifo_rp)
    if (fifo_rp == `SRAM_SIZE - 1)
        fifo_rp_next = 0;
    else
        fifo_rp_next = fifo_rp + 1;

always @ (posedge clk or negedge rst)
    if (~rst)
        fifo_wp <= 0;
    else if (state == write_over)
        fifo_wp <= fifo_wp_next;

always @ (fifo_wp)
    if (fifo_wp == `SRAM_SIZE-1)
        fifo_wp_next = 0;
    else
        fifo_wp_next = fifo_wp + 1;

always @(posedge clk or negedge rst)
    if (~rst)
        near_empty <= 1'b0;
    else if (fifo_wp == fifo_rp_next)
        near_empty <= 1'b1;
    else
        near_empty <= 1'b0;

always @ (posedge clk or negedge rst)

if (~rst)
nempty <= 1'b0;
else if (near_empty && state == read)
nempty <= 1'b0;
else if (state == write)
nempty <= 1'b1;

always @(posedge clk or negedge rst)
if (~rst)
near_full <= 1'b0;
else if (fifo_rp == fifo_wp_next)
near_full <= 1'b1;
else
near_full <= 1'b0;

always @(posedge clk or negedge rst)
if (~rst)
	nfull <= 1'b1;
else if (near_full && state == write)
	nfull <= 1'b0;
else if (state == read)
	nfull <= 1'b1;

endmodule

