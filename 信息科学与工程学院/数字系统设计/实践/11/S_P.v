`timescale 1ns/1ns
`define YES 1
`define NO 0
module S_P(input Dbit_in,
           input Dbit_ena,
           input clk,
           output [7:0] data);
    reg [7:0] data_buf;
    reg [3:0] state;
    reg p_out_link;
    assign data = (p_out_link == `YES) ? data_buf : 8'bz;
    always@ (negedge clk)
        if (Dbit_ena)
            case(state)
                0: begin
                    p_out_link  <= `NO;
                    data_buf[7] <= Dbit_in;
                    state       <= 1;
                end
                1: begin
                    data_buf[6] <= Dbit_in;
                    state       <= 2;
                end
                2: begin
                    data_buf[5] <= Dbit_in;
                    state       <= 3;
                end
                3: begin
                    data_buf[4] <= Dbit_in;
                    state       <= 4;
                end
                4: begin
                    data_buf[3] <= Dbit_in;
                    state       <= 5;
                end
                5: begin
                    data_buf[2] <= Dbit_in;
                    state       <= 6;
                end
                6: begin
                    data_buf[1] <= Dbit_in;
                    state       <= 7;
                end
                7: begin
                    data_buf[0] <= Dbit_in;
                    state       <= 8;
                end
                8: begin
                    p_out_link <= `YES;
                    state      <= 4'b1111;
                end
                default: state <= 0;
            endcase
        else begin
            p_out_link <= `YES;
            state      <= 0;
        end
endmodule
