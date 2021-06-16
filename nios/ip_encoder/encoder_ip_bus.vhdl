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
-- Adapted from ESL demo by Rene Moll (2012)
--
-- Straight forward initialization and mapping of an IP to the avalon bus.
-- The communication part is kept simple, since only register is of interest.
--
-- Communication signals use the prefix slave_
-- User signals use the prefix user_
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity encoder_ip_bus is
	generic (
		DATA_WIDTH : natural := 8;	-- word size of each input and output register
	);
	port (
		-- signals to connect to an Avalon clock source interface
		clk			  : in  std_logic;
		reset			: in  std_logic;

		-- signals to connect to an Avalon-MM slave interface
		slave_address		  : in  std_logic_vector(7 downto 0);
		slave_read		    : in  std_logic;
		slave_write		    : in  std_logic;
		slave_readdata		: out std_logic_vector(DATA_WIDTH-1 downto 0);
		slave_writedata		: in  std_logic_vector(DATA_WIDTH-1 downto 0);
		
		-- signals to connect encoder
		user_A	: in std_logic;
		user_B	: in std_logic;
	);
end entity;

architecture behavior of encoder_ip_bus is
	-- Internal memory for the system and a subset for the IP
	signal mem_short : std_logic_vector(DATA_WIDTH-1 downto 0);
	signal mem_long  : std_logic_vector(31 downto 0) <= (others => '0');

	-- Definition of the encoder
	component QuadratureEncoder
		generic (
			RESOLUTION : positive := 8
		);
		port (
			clk : in std_logic;
			rst: in std_logic;
			A : in std_logic;
			B : in std_logic;
			output : out signed(7 downto 0)
		);
	end component;
begin
	-- Initialization and portmape of the encoder
	encoder : QuadratureEncoder
	generic map(
		RESOLUTION => DATA_WIDTH
	)
	port map(
		clk   => clk,
		rst   => reset,
		A     => user_A;
		B     => user_B
		output => mem_short
	);

	-- Communication with the bus
	p_avalon : process(clk, reset)
	begin
		if (reset = '1') then
			mem_long <= (others => '0');
		elsif (rising_edge(clk)) then
			if (slave_read = '1') then
				slave_readdata <= mem_long;
			end if;
			if (slave_write = '1') then
				mem_long <= slave_writedata;
			end if;
		end if;
	end process;
	
	-- Enlarge memory length to correspond to the Avalon memory
	mem_long(31 downto 31-DATA_WIDTH) <= mem_short;
end architecture;
