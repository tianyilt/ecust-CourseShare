// `timescale 1ns / 1ps

`define YES 1
`define NO 0
module P_S(input [7:0] data,
           input nGet_AD_data,
           input clk,
           output Dbit_out,
           output reg link_S_out);
reg [3:0] state;
reg [7:0] data_buf;
reg d_buf;
reg finish_flag;
assign Dbit_out = (link_S_out) ? d_buf : 0;
always @ (posedge clk or negedge nGet_AD_data)
    if (! nGet_AD_data)
    begin
        finish_flag <= 0;
        state      <= 9;
        link_S_out <= `NO;
        d_buf      <= 0;
        data_buf   <= 0;
    end
    else
        case(state)
            9: begin
                data_buf   <= data;
                state      <= 10;
                link_S_out <= `NO;
            end
            10: begin
                data_buf   <= data;
                state      <= 0;
                link_S_out <= `NO;
            end
            0:begin
                link_S_out <= `YES;
                d_buf      <= data_buf[7];
                state      <= 1;
            end
            1:begin
                d_buf <= data_buf[6];
                state <= 2;
            end
            2:begin
                d_buf <= data_buf[5];
                state <= 3;
            end
            3:begin
                d_buf <= data_buf[4];
                state <= 4;
            end
            4:begin
                d_buf <= data_buf[3];
                state <= 5;
            end
            5:begin
                d_buf <= data_buf[2];
                state <= 6;
            end
            6:begin
                d_buf <= data_buf[1];
                state <= 7;
            end
            7:begin
                d_buf <= data_buf[0];
                state <= 8;
            end
            8:begin
                link_S_out  <= `NO;
                state       <= 4'b1111;
                finish_flag <= 1;
            end
            default:begin
                link_S_out <= `NO;
                state      <= 4'b1111;
            end
        endcase
    endmodule
