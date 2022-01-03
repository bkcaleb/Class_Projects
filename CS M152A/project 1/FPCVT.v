`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:00:39 04/18/2021 
// Design Name: 
// Module Name:    proj1 
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
module FPCVT( input[12:0] D, output S, output[2:0] E, output[4:0] F);
	//declaring some variable
	integer lead_zero, i, sixth;
	reg[12:0] tempD;
	reg tempS;
	reg [2:0] tempE;
	reg [4:0] tempF;
	//check if the binary is UMIN
	always @* begin
		tempD = D;
		if (tempD[12:0] == 13'b1_0000_0000_0000) begin
			tempS = 1;
			tempE = 3'b111;
			tempF = 5'b11111;
		end else begin
			tempS= tempD[12];
			
			//convert negative
			if (tempS == 1)
				tempD = ~tempD + 1;
			//get lead zeros
			lead_zero = 13;
			for(i=12; i>=0 && lead_zero == 13; i=i-1) begin
				if(tempD[i] == 1)
					lead_zero = 12-i;
			end
			//exponent
			case(lead_zero) 
				4'b0001: tempE = 3'b111;
				4'b0010: tempE = 3'b110;
				4'b0011: tempE = 3'b101;
				4'b0100: tempE = 3'b100;
				4'b0101: tempE = 3'b011;
				4'b0110: tempE = 3'b010;
				4'b0111: tempE = 3'b001;
				default: tempE = 3'b000;
			endcase
			
			//get significand
			if(lead_zero > 8)
				lead_zero = 8;
			tempD = tempD << lead_zero;
			tempF = tempD[12:8];
			sixth = tempD[7];
			if (sixth == 1) begin
				tempF = tempF + 1;
				if(tempF[4:0] == 5'b00000) begin
					tempE = tempE + 1;
					tempF = 5'b10000;
					if(tempE[2:0] == 3'b000)begin
						tempE = 3'b111;
						tempF = 5'b11111;
					end
				end
			end
		end
	end
	assign E = tempE;
	assign F = tempF;
	assign S = tempS;
endmodule
