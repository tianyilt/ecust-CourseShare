module cargo_sorter (
    input [3:0] weight,
    output reg light,
    output reg medium_,
    output reg heavy
);

    always @(weight) begin
        light <= 0;
        medium_ <= 0;
        heavy <= 0;
        case (weight)
            4'b0001, 4'b0010, 4'b0011: begin light <= 1; medium_ <= 0; heavy <= 0;end
            4'b0100, 4'b0101, 4'b0110: begin light <= 0; medium_ <= 1; heavy <= 0;end
            default: begin light <= 0; medium_ <= 0; heavy <= 1;end
        endcase
    end

endmodule
