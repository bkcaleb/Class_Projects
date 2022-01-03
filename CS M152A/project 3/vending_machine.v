`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:01:30 05/14/2021 
// Design Name: 
// Module Name:    vending_machine 
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
module vending_machine(input CLK, input RESET, input RELOAD, input CARD_IN, input [2:0] ITEM_CODE, input KEY_PRESS, input VALID_TRAN,
								output reg VEND, output reg INVALID_SEL, output reg [2:0] COST, output reg FAILED_TRAN);
	//define states
	parameter reset = 4'b0000;
	parameter idle = 4'b0001;
	parameter load = 4'b0010;
	parameter transact = 4'b0011;
	parameter invalid = 4'b0100;
	parameter failed = 4'b0101;
	parameter vend = 4'b0110;
	parameter wait_ = 4'b0111;
	parameter isValid = 4'b1000;
	
	reg [3:0] current;
	reg [3:0] next;
	
	reg[2:0] tens;
	reg ten_input;
	reg[2:0] ones;
	reg [2:0] count = 3'b000;
	reg count_start = 0;
	reg [2:0] second_count = 3'b000;
	reg second_count_start = 0;
	reg [2:0] trans_count = 3'b000;
	reg trans_count_start = 0;

	
	reg [3:0] count10;
	reg [3:0] count11;
	reg [3:0] count12;
	reg [3:0] count13;
	reg [3:0] count14;
	reg [3:0] count20;
	reg [3:0] count21;
	reg [3:0] count22;
	reg [3:0] count23;
	reg [3:0] count24;
	
	
	always@(posedge CLK)
	begin
		if(RESET)
			current <= reset;
		else
			current <= next;
	end
	
	//counters
	
	always@(posedge CLK)
	begin
		if(current == reset) begin
			count10 <= 4'b0000;
			count11 <= 4'b0000;
			count12 <= 4'b0000;
			count13 <= 4'b0000;
			count14 <= 4'b0000;
			count20 <= 4'b0000;
			count21 <= 4'b0000;
			count22 <= 4'b0000;
			count23 <= 4'b0000;
			count24 <= 4'b0000;
		end
		else if(current == load) begin
			count10 <= 4'b1010;
			count11 <= 4'b1010;
			count12 <= 4'b1010;
			count13 <= 4'b1010;
			count14 <= 4'b1010;
			count20 <= 4'b1010;
			count21 <= 4'b1010;
			count22 <= 4'b1010;
			count23 <= 4'b1010;
			count24 <= 4'b1010;
		end
		else if(current == vend) begin
			if(tens == 3'b001)begin
				if(ones == 3'b000) count10 <= count10 - 3'b001;
				if(ones == 3'b001) count11 <= count11 - 3'b001;
				if(ones == 3'b010) count12 <= count12 - 3'b001;
				if(ones == 3'b011) count13 <= count13 - 3'b001;
				if(ones == 3'b100) count14 <= count14 - 3'b001;
			end
			else if(tens == 3'b010) begin
				if(ones == 3'b000) count20 <= count20 - 3'b001;
				if(ones == 3'b001) count21 <= count21 - 3'b001;
				if(ones == 3'b010) count22 <= count22 - 3'b001;
				if(ones == 3'b011) count23 <= count23 - 3'b001;
				if(ones == 3'b100) count24 <= count24 - 3'b001;
			end
		end
	end
	
	//decide next state
	
	always@(posedge CLK) begin
		if(count_start)
			count <= count + 1'b1;
		else
			count <= 0;
			
		if(trans_count_start)
			trans_count <= trans_count + 1'b1;
		else
			trans_count <= 0;
			
		if(second_count_start)
			second_count <= second_count + 1'b1;
		else
			second_count <= 0;
	end
	
	always@(*) begin
		case(current)
			reset: begin next = idle;  end
			idle: begin 
				count_start = 0;
				second_count_start = 0;
				ten_input = 0;
				trans_count_start = 0;
				if(RELOAD)
					next = load;
				else if(CARD_IN)			
					next = wait_; 
				else 
					next = idle;
				end
			load: begin next = idle; end
			vend: begin next = idle; end
			wait_: begin 
				count_start = 1;
				if(count >= 3'b100 || second_count >= 3'b100)
				begin
					next = idle;
				end
				else if(KEY_PRESS && ~ten_input) begin
					tens = ITEM_CODE;
					ten_input = 1;
					next = wait_;
					count_start = 0;
					second_count_start = 1;
				end
				else if(KEY_PRESS && ten_input) begin
					ones = ITEM_CODE;
					next = isValid;
				end
				else
					next = wait_;
			end
			isValid: begin
					if((tens == 3'b001 && ones == 3'b000 && count10 > 4'b0000) ||
							(tens == 3'b001 && ones == 3'b001 && count11 > 4'b0000) ||
							(tens == 3'b001 && ones == 3'b010 && count12 > 4'b0000) ||
							(tens == 3'b001 && ones == 3'b011 && count13 > 4'b0000) ||
							(tens == 3'b001 && ones == 3'b100 && count14 > 4'b0000) ||
							(tens == 3'b010 && ones == 3'b000 && count20 > 4'b0000) ||
							(tens == 3'b010 && ones == 3'b001 && count21 > 4'b0000) ||
							(tens == 3'b010 && ones == 3'b010 && count22 > 4'b0000) ||
							(tens == 3'b010 && ones == 3'b011 && count23 > 4'b0000) ||
							(tens == 3'b010 && ones == 3'b100 && count24 > 4'b0000))
							begin
								next = transact;
							end
						else
							next = invalid;
			end
			invalid: begin
				next = idle;
			end
			transact: begin
				trans_count_start = 1;
				if(trans_count >= 3'b100) begin
					next = failed;
					end
				else if(VALID_TRAN) begin
					next = vend;
					end
				else
					next = transact;
			end
			failed: begin next = idle; end
		endcase
	end
		//get the outputs
	always @(*) begin
		case(current)
			reset,
			idle,
			load,
			wait_,
			isValid: begin
				VEND = 0;
				INVALID_SEL = 0;
				COST = 3'b000;
				FAILED_TRAN = 0;
			end
			transact: begin
				if(tens == 3'b001)
					COST = 3'b010;
				else
					COST = 3'b101;
			end
			invalid: begin
				INVALID_SEL = 1;
			end
			failed: begin
				FAILED_TRAN = 1;
			end
			vend: begin
				VEND = 1;
			end
		endcase
	end
endmodule
