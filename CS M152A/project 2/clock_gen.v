`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:30:39 05/01/2021 
// Design Name: 
// Module Name:    clock_gen 
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
module clock_gen(
	input clk_in,
	input rst,
	output clk_div_2,
	output clk_div_4,
	output clk_div_8,
	output clk_div_16,
	output clk_div_32,
	output clk_div_26,
	output clk_div_3,
	output clk_pos,
	output clk_neg,
	output clk_div_5,
	output clk_div,
	output [7:0] toggle_counter
    );

clock_div_two task1(
	.clk_in (clk_in),
	.rst (rst),
	.clk_div_2(clk_div_2),
	.clk_div_4(clk_div_4),
	.clk_div_8(clk_div_8),
	.clk_div_16(clk_div_16)
);

clock_div_thirty_two task2 (
	.clk_in(clk_in),
	.rst(rst),
	.clk_div_32(clk_div_32)
);

clock_div_twenty_six task3(
	.clk_in (clk_in),
	.rst (rst),
	.clk_div_26 (clk_div_26)
);

clock_div_three task456(
	.clk_in(clk_in),
	.rst(rst),
	.clk_div_3(clk_div_3),
	.clk_pos(clk_pos),
	.clk_neg(clk_neg)
);

clock_div_five task7(
	.clk_in (clk_in),
	.rst (rst),
	.clk_div_5 (clk_div_5)
);
clock_pulse task8(
	.clk_in(clk_in),
	.rst(rst),
	.clk_div(clk_div)
);
clock_strobe task9(
	.clk_in (clk_in),
	.rst (rst),
	.toggle_counter (toggle_counter)
);
endmodule

// task 1
module clock_div_two(clk_in, rst, clk_div_2, clk_div_4,
clk_div_8, clk_div_16);
input clk_in, rst;
output clk_div_2, clk_div_4, clk_div_8, clk_div_16;
	reg [3:0] a;
	always @ (posedge clk_in)
	begin
		if (rst)
			a <= 4'b0000;
		else
			a <= a + 1'b1;
	end
	assign clk_div_2 = a[0];
	assign clk_div_4 = a[1];
	assign clk_div_8 = a[2];
	assign clk_div_16 = a[3];
endmodule

// task 2
module clock_div_thirty_two(clk_in, rst, clk_div_32);
input clk_in, rst;
output reg clk_div_32;
reg [3:0] b;
	always @ (posedge clk_in)
	begin
		if (rst) begin
			b <= 4'b0000;
			clk_div_32 <= 1'b0;
		end
		else begin
			if(b == 4'b1111)
				clk_div_32 <= ~clk_div_32;
			b <= b + 1'b1;
		end
	end
	
endmodule


// task 3
module clock_div_twenty_six(clk_in, rst, clk_div_26);
input clk_in, rst;
output reg clk_div_26;
reg [3:0] b;
	always @ (posedge clk_in)
	begin
		if (rst) begin
			b <= 4'b0000;
			clk_div_26 <= 1'b0;
		end
		else if (b == 4'b1100) begin
			clk_div_26 <= ~clk_div_26;
			b <= 4'b0000;
		end
		else
			b <= b + 1'b1;
	end
endmodule

// task 4, 5, 6
module clock_div_three(clk_in, rst, clk_div_3, clk_pos,
clk_neg);
input clk_in, rst;
output clk_div_3;
output reg clk_pos, clk_neg;
reg[3:0] b;
	//task 4
	always @ (posedge clk_in)
	begin
		if (rst) begin
			b <= 4'b0000;
			clk_pos <= 1'b0;
		end
		else if (b == 4'b0001) begin
			b <= b + 1'b1;
			clk_pos <= ~clk_pos;
		end
		else if (b == 4'b0010) begin
			b <= 4'b0000;
			clk_pos <= ~clk_pos;
		end
		else
			b <= b + 1'b1;
	end
	
reg[3:0] a;
	//task 5
	always @ (negedge clk_in)
	begin
		if (rst) begin
			a <= 4'b0000;
			clk_neg <= 1'b0;
		end
		else if (a == 4'b0001) begin
			a <= a + 1'b1;
			clk_neg <= ~clk_neg;
		end
		else if (a == 4'b0010) begin
			a <= 4'b0000;
			clk_neg <= ~clk_neg;
		end
		else
			a <= a + 1'b1;
	end
	
	//task 6
	assign clk_div_3 = clk_neg || clk_pos;
endmodule

// task 7
module clock_div_five(clk_in, rst, clk_div_5);
input clk_in, rst;
output clk_div_5;
reg clk_pos,clk_neg;
reg[3:0] b;
	//right
	always @ (posedge clk_in)
	begin
		if (rst) begin
			b <= 4'b0000;
			clk_pos <= 1'b0;
		end
		else if (b == 4'b0010) begin
			b <= b + 1'b1;
			clk_pos <= ~clk_pos;
		end
		else if (b == 4'b0100) begin
			b <= 4'b0000;
			clk_pos <= ~clk_pos;
		end
		else
			b <= b + 1'b1;
	end
	
reg[3:0] a;
	//left
	always @ (negedge clk_in)
	begin
		if (rst) begin
			a <= 4'b0000;
			clk_neg <= 1'b0;
		end
		else if (a == 4'b0010) begin
			a <= a + 1'b1;
			clk_neg <= ~clk_neg;
		end
		else if (a == 4'b0100) begin
			a <= 4'b0000;
			clk_neg <= ~clk_neg;
		end
		else
			a <= a + 1'b1;
	end
	
	//div 5
	assign clk_div_5 = clk_neg || clk_pos;
endmodule

// task 8
module clock_pulse(clk_in, rst, clk_div);
input clk_in, rst;
output reg clk_div;
reg [6:0] b;
always @ (posedge clk_in)
begin
	if (rst) begin
		b <= 7'b110_0001;
	end
	else if (b == 7'b110_0011) begin
		b <= 7'b000_0000;
	end
	else
		b <= b + 1'b1;
end
always @ (posedge clk_in)
begin
	if (rst)
		clk_div <= 0;
	if(b == 7'b110_0011)
		clk_div <= ~clk_div;
end
endmodule

// task 9
module clock_strobe(clk_in, rst, toggle_counter);
input clk_in, rst;
output reg [7:0] toggle_counter;
reg [3:0] b;
	always @ (posedge clk_in)
	begin
		if (rst) begin
			b <= 4'b0000;
			toggle_counter <= 8'b0000_0000;
		end
		else if (b == 4'b0011) begin
			toggle_counter <= toggle_counter - 8'b0000_0101;
			b <= 4'b0000;
		end
		else begin
			b <= b + 1'b1;
			toggle_counter <= toggle_counter + 8'b0000_0011;
		end
	end
endmodule
