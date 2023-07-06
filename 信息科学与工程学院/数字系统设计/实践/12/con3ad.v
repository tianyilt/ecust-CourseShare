`timescale 1ns/100 ps

module con3ad(
    input wire[7:0] indata,
    input wire CLK,
    input wire reset,
    input wire start,
    input wire nbusy1,
    input wire nbusy2,
    input wire nbusy3,
    output reg[10:0] address,
    output reg[7:0] outdata,
    output reg nconvst1,
    output reg nconvst2,
    output reg nconvst3,
    output reg wr,
    output reg enout1,
    output reg enout2
);

reg[6:0] state;
reg[5:0] i;
reg[1:0] j;
reg[11:0] counter;
reg[23:0] line;
reg[15:0] result;
reg high,k, EOC1 ,EOC2,EOC3;

parameter hl = 1,h2 = 2,h3 = 3;
parameter IDLE = 7'b0000001, READ_PRE = 7'b0000010,
READ = 7'b0000100, CALCU = 7'b0001000,
WRREADY = 7'b0010000, WR = 7'b0100000,
WREND = 7'b1000000;

always @ (posedge CLK) begin
    if (! reset) begin
        state <= IDLE;
        counter <= 12'b0;
        wr <= 1;
        enout1 <= 1;
        enout2 <= 1;
        outdata <= 8'bz;
        address <= 11'bz;
        line <= 24'b0;
        result <= 16'b0;
        high <= 0;
    end
    else begin
        case(state)
            IDLE:
                if (start) begin
                    counter <= 0;
                    state <= READ_PRE;
                end
                else state <= IDLE;

            READ_PRE:
                if (EOC1||EOC2||EOC3)
                    state <= READ;
                else
                    state <= READ_PRE;

            READ:
                begin
                    high <= 0;
                    enout2 <= 1;
                    wr <= 1;

                    if (j == 1)begin
                        if (EOC1)begin
                            line <= {line[15:0],indata};
                            state <= CALCU;
                        end
                        else state <= READ_PRE;
                    end

                    else if (j == 2 && counter != 0) begin
                        if (EOC2)begin
                            line <= {line[15:0],indata};
                            state <= CALCU;
                        end
                        else state <= READ_PRE;
                    end

                    else if (j == 3 && counter != 0) begin
                        if (EOC3)begin
                            line <= {line[15:0],indata};
                            state <= CALCU;
                        end
                        else state <= READ_PRE;
                    end

                    else state <= READ;

                end

            CALCU:
                begin
                    result <= line[7:0] * hl + line[15:8] * h2 + line[23:16] * h3;
                    state <= WRREADY;
                end

            WRREADY:
                begin
                    wr <= 1;
                    address <= counter;

                    if (k == 1)
                        state <= WR;

                    else state <= WRREADY;

                end

            WR:
                begin
                    if (!high)
                        enout1 <= 0;

                    else enout2 <= 0;

                    wr <= 0;

                    if (!high)
                        outdata <= result[7:0];

                    else outdata <= result[15:8];

                    if (k == 1)
                        state <= WREND;

                    else state <= WR;

                end

            WREND:
                begin
                    wr <= 1;
                    enout1 <= 1;
                    enout2 <= 1;

                    if (k == 1) begin
                        if (!high) begin
                            high <= 1;
                            state <= WRREADY;
                        end

                        else begin
                            counter <= counter + 1;

                            if (counter[11] && counter[0])
                                state <= IDLE;

                            else state<= READ_PRE;

                        end

                    end

                    else state<= WREND;

                end

            default:
                state<= IDLE;

        endcase

    end

end


always @ (posedge CLK)begin
    if (! reset)
        i<= 0;

    else begin
        if (i==44)
            i<= 0;

        else i<= i+1;

    end

end


always @(posedge CLK) begin
    case(i)
        4:
            j<=2;

        10:
            j<=0;

        19:
            j<=3;

        25:
            j<=0;

        34:
            j<=1;

        40:
            j<=0;

    endcase

end


always @(posedge CLK) begin
    if (state==WRREADY || state==WR || state==WREND)begin
        if (k==1)
            k<=0;

        else k<=1;

    end

    else k<=0;

end


always @ (posedge CLK) begin
    if (!reset)
        nconvst1<=1;

    else if (i==0)
        nconvst1<=0;

    else if (i==3)
        nconvst1<=1;

end


always @ (posedge CLK) begin
    if (! reset)
        nconvst2<=1;

    else if (i==15)
        nconvst2<=0;

    else if (i==18)
        nconvst2<=1;

end


always @(posedge CLK) begin
    if (! reset)
        nconvst3<=1;

    else if (i==30)
        nconvst3<=0;

    else if (i==33)
        nconvst3<=1; 

end


always @ (negedge CLK) begin 
   EOC1<=nbusy1; 
   EOC2<=nbusy2; 
   EOC3<=nbusy3; 
end 

endmodule 
