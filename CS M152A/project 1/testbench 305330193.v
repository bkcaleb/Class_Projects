`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:04:01 04/18/2021
// Design Name:   proj1
// Module Name:   /home/ise/xilinx/Proj1/proj1_tb.v
// Project Name:  Proj1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: proj1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module FPCVT_tb;
	reg [12:0] D;
	wire S;
	wire [2:0] E;
	wire [4:0] F;
	FPCVT uut(.D(D),.S(S),.E(E),.F(F));


	initial begin
		// Initialize Inputs
		D=0;
		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		D = 13'b1_0000_0000_0000;
		#10;
		D = 13'b0_0000_0110_1100;
		#10;
		D = 13'b0_0000_0110_1101;
		#10;
		D = 13'b0_0000_0110_1110;
		#10;
		D = 13'b0_0000_0110_1111;
		#10;
		D = 13'b0_1111_1111_1111;
		#10;
		D = 13'b1_1111_1111_1111;
		#10;
		D = 13'b0_0011_1111_0000;
		#10;
		D = 13'b0_0000_0000_0000;
		#10;
		D = 13'b0_0000_0000_0001;
		#10;
	end
      
endmodule

