-------------------------------------------------------------------------------
-- 
-- Quadrature Encoder
-- ESL 2021
-- Version: 1.0
-- Creator: Stijn Slebos, Tijmen Smit
-- Date: 12th May 2021
--
-------------------------------------------------------------------------------
--
-- Keeps track of position of an quadrature encoder with two
-- input signals. 
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity QuadratureEncoder is
	generic (
		RESOLUTION : positive := 8
	);
	port (
	  clk : in std_logic;
	  rst : in std_logic;
	  A : in std_logic;
	  B : in std_logic;
	
	  output : out signed(RESOLUTION-1 downto 0) := (others => '0')
	);
end entity;

architecture behaviour of QuadratureEncoder is
	signal Aold : std_logic;
	signal Bold : std_logic;
	signal Pold : signed(RESOLUTION-1 downto 0) := (others => '0');
begin	
	position_calculation: process(clk, rst) is
	  variable pos : signed(RESOLUTION-1 downto 0);
	begin
	  if (rst = '1') then
	    output <= (others => '0');
	    Pold := (others => '0');
	  elsif rising_edge(clk) then
	  pos := Pold;
		if A /= Aold then
			if A = B then	
				pos := pos - 1;
			else 
				pos := pos + 1;
			end if;
		elsif B /= Bold then
			if B = A then
				pos := pos + 1;
			else
				pos := pos - 1;
			end if;
		end if;
		output <= pos;
		Pold <= pos;
		Aold <= A;
		Bold <= B;
		end if;
	end process;
end architecture;
