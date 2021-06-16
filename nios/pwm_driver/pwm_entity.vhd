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
-- Creates a PWM signal based to drive a motor h-bridge
-- based on a direction and duty cycle input. 
--
-------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

entity pwm_entity is
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
    end pwm;

architecture behaviour of pwm_entity is

    --signal duty_count : unsigned(7 downto 0);
    --constant pwm_period : unsigned(N-1 downto 0) := (others => '1'); --in terms of clockfrequency
    constant period : unsigned(N-1 downto 0) := to_unsigned(2500,N); -- := clockfrequency*1000/pwmfrequency; -- should be 2500 ( := "2500"; )
begin
    pwm_cycle : process(clk, rst)
    variable cycle_count : unsigned(N-1 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            if rst = '1' then
                pwm_sig <= '0';
                cycle_count := (others => '0');
                a_in <= '0';
                b_in <= '0';
            else
                if (cycle_count >= period-1) then -- if we are out of period
                    cycle_count := (others => '0');
                    if (duty_cycle /= 0) then
                    	pwm_sig <= '1';  -- one clockcycle backlash
                    end if;
                else
                    cycle_count := cycle_count + 1;
                    if (cycle_count >= duty_cycle) then
                        pwm_sig <= '0';
                    else
                        pwm_sig <= '1';
                    end if;
                end if;
                if duty_cycle = 0 then
                    a_in <= '0';
                    b_in <= '0'; --goto brake-gnd
                else
                    a_in <= dir; --clockwise/cntrclockwise
                    b_in <= '1' xor dir;
                end if;
            end if;
        end if;
    end process;
end behaviour;
