-------------------------------------------------------------------------------
-- 
-- PWM driver
-- ESL 2021
-- Version: 1.0
-- Creator: Stijn Slebos, Tijmen Smit
-- Date: 20th May 2021
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

entity pwm_bus is
  generic (
    DATA_WIDTH : integer := 12;
    clockfrequency : integer := 50; --Mhz
    pwmfrequency : integer := 20 --Mhz
  );
	port (
		-- signals to connect to an Avalon clock source interface
		clk			: in  std_logic;
		reset			: in  std_logic;
		
		duty_cycle : in unsigned(DATA_WIDTH-1 downto 0);
    dir : in std_logic; --direction; 1 is clockwise

		-- signals to connect to an Avalon-MM slave interface
		slave_address		: in  std_logic_vector(7 downto 0);
		slave_read			: in  std_logic;
		slave_write			: in  std_logic;
		slave_readdata		: out std_logic_vector(DATA_WIDTH-1 downto 0);
		slave_writedata		: in  std_logic_vector(DATA_WIDTH-1 downto 0);

		-- signals to connect to custom user logic
		user_pwm		: out std_logic;
		user_A      : out std_logic;
		user_B      : out std_logic
	);
end entity;

architecture behavior of pwm_bus is
	-- Internal memory for the system and a subset for the IP
	signal enable     : std_logic;
	signal mem        : std_logic_vector(31 downto 0);
	signal mem_masked : std_logic_vector(DATA_WIDTH-1 downto 0);

	-- Definition of the counter
	component pwm_entity
	  generic (
      N : integer := 12;
      clockfrequency : integer := 50; --Mhz
      pwmfrequency : integer := 20 --Mhz
    );
    port (
      clk : in std_logic;
      rst : in std_logic;
      duty_cycle : in unsigned(N-1 downto 0);
      dir : in std_logic; --direction; 1 is clockwise
      
      pwm_sig : out std_logic;
      a_in : out std_logic;
      b_in : out std_logic
    );
	end component;
begin
	-- Initialization of the example
	my_pwm : pwm_entity
	generic map(
		N => DATA_WIDTH
	)
	port map(
		clk => clk,
		rst => reset,
		
		duty_cycle  => mem_masked,
		dir => enable,
		
		pwm_sig => user_output,
		a_in => user_A,
		b_in => user_B
	);

	-- Communication with the bus
	p_avalon : process(clk, reset)
	begin
		if (reset = '1') then
			mem <= (others => '0');
		elsif (rising_edge(clk)) then
			if (slave_read = '1') then
				slave_readdata <= mem;
			end if;
			
			if (slave_write = '1') then
				mem <= slave_writedata;
			end if;
		end if;
	end process;
	
	-- Only select the amount bits that the logic can handle
	mem_masked <= mem(DATA_WIDTH-1 downto 0);
	enable <= mem(DATA_WIDTH);
end architecture;
