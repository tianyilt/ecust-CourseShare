`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:30:07 05/24/2023 
// Design Name: 
// Module Name:    sram 
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
module sram(Address,Data,SRG,SRE,SRW);
input[10:0] Address;
input SRG,								//Output enable
		SRE,								//Chip enable
		SRW;								//Write enable
inout[7:0] Data;						//Bus

wire[10:0] Addr=Address;
reg[7:0] RdData;
reg[7:0] SramMem[0:'h7ff];
reg RdSramDly,RdFlip;
wire[7:0] FlpData,Data;
reg WR_flag;							//To judge the signals according to the specification of HM-65162
integer i;
wire RdSram=~SRG&~SRE;
wire WrSram=~SRW&~SRE;
reg[10:0] DelayAddr;
reg[7:0] DelayData;
reg WrSramDly;
integer file;

assign FlpData = (RdFlip)?~RdData:RdData;
assign Data = (RdSramDly)?FlpData:'hz;

parameter TAVQV=90,					//2	(max)		Address access time
			 TELQV=90,					//3	(max)		Chip enable access time
			 TELQX=5,					//4	(min)		Chip enable output enable time
			 TGLQV=65,					//5	(max)		Output enable access time
			 TGLQX=5,					//6	(min)		Output enable output enable time
			 TEHQZ=50,					//7	(max)		Chip enable output disable time
			 TGHQZ=40,					//8	(max)		Output enable output disable time
			 TAVQX=5;					//9	(min)		Output hold from address change
			 
parameter TAVWL=10,					//12	(min)		Address setup time
			 TWLWH=55,					//13	(min)		Chip enable pulse setup time
			 TWHAX=15,					//14	(min10)	Write enable read setup time
			 TWLQZ=50,					//16	(max)		Write enable output disable time
			 TDVWH=30,					//17	(min)		Data setup time
			 TWHDX=20,					//18	(min15)	Data hold time
			 TWHQX=20,					//19	(min0)	Write enable output enable time
			 TWLEH=55,					//20	(min)		Write enable pulse setup time
			 TDVEH=30,					//21	(min)		Chip enable data setup time
			 TAVWH=70;					//22	(min65)	Address valid to end of write
			 
initial
	begin
		file=$fopen("ramlow.txt");
		if(!file)
			begin
				$display("Could not open the file.");
				$stop;
			end
	end

initial
	begin
		for(i=0;i<'h7ff;i=i+1)
			SramMem[i]=i;
			$monitor($time,"DelayAddr=%h,DelayData=%h",DelayAddr,DelayData);
	end

initial RdSramDly=0;
initial WR_flag=1;

always@(posedge RdSram) #TGLQX RdSramDly=RdSram;
always@(posedge SRW)		#TWHQX RdSramDly=RdSram;

always@(Addr)
	begin
		#TAVQX;
		RdFlip=1;
		#(TGLQV-TAVQX)
		if(RdSram)
			RdFlip=0;
	end

always@(posedge RdSram)
	begin
		RdFlip=1;
		#TAVQV;
		if(RdSram)
			RdFlip=0;
	end

always@(Addr)				#TAVQX RdFlip=1;
always@(posedge SRG)		#TEHQZ RdSramDly=RdSram;
always@(posedge SRE)		#TGHQZ RdSramDly=RdSram;
always@(negedge SRW)		#TWLQZ RdSramDly=0;

always@(negedge WrSramDly or posedge RdSramDly) RdData=SramMem[Addr];

always@(Addr)				#TAVWL DelayAddr=Addr;
always@(Data)				#TDVWH DelayData=Data;
always@(WrSram)			#5 	 WrSramDly=WrSram;
always@(Addr or Data or WrSram) WR_flag=1;

always@(negedge SRW)
	begin
		#TWLWH;
		if(SRW)
			begin
				WR_flag=0;
				$display("ERROR!Can't write!Write enable time(W) is too short!");
			end
	end

always@(posedge SRW)
	begin
		#TWHAX;
		if(DelayAddr!==Addr)
			begin
				WR_flag=0;
				$display("ERROR!Can't write!Write enable read setup time is too short!");
			end
	end
	
always@(Data)
	if(WrSram)
		begin
			#TDVEH;
			if(SRE)
				begin
					WR_flag=0;
					$display("ERROR!Can't write!Chip enable data setup time is too short!");
				end
		end
		
always@(Data)
	if(WrSram)
		begin
			#TDVEH;
			if(SRW)
				begin
					WR_flag=0;
					$display("ERROR!Can't write!Chip enable data setup time is too short!");
				end
		end
		
always@(posedge SRW)
	begin
		#TWHDX
		if(DelayData!==Data)
			$display("Warning!Data hold time is too short!");
	end
	
always@(DelayAddr or DelayData or WrSramDly)
	if(WrSram&&WR_flag)
		begin
			if(!Addr[5])
				begin
					#15 SramMem[Addr]=Data;
					$display("mem[%h]=%h",Addr,Data);
					$fwrite(file,"mem[%h]=%h",Addr,Data);
					if(Addr[0]&&Addr[1])
						$fwrite(file,"\n");
				end
			else
				begin
					$fclose(file);
					$display("Please check the txt.");
					$stop;
				end
		end

endmodule
