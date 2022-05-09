-- uart.vhd: UART controller - receiving part
-- Author(s): Abayev Amirkhan (xabaye00)
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

-------------------------------------------------
entity UART_RX is
port(	
        CLK      : in std_logic;
	RST      : in std_logic;
	DIN      : in std_logic;
	DOUT     : out std_logic_vector(7 downto 0);
	DOUT_VLD : out std_logic
);
end UART_RX;   

-------------------------------------------------
architecture behavioral of UART_RX is
signal CNT        : std_logic_vector(4 downto 0):= "00001" ;
signal CNTBITS    : std_logic_vector(3 downto 0):= "0000" ;
signal CNTSTOP    : std_logic_vector(3 downto 0):= "0000" ;
signal VLD        : std_logic := '0';
signal READ_DATA  : std_logic := '0';
signal CNTR       : std_logic := '0';
signal ZERO       : std_logic := '0';
begin
  
  FSM: entity work.UART_FSM(behavioral)
    port map (
        CLK 	         => CLK,
        RST 	         => RST, 
        DIN 	         => DIN,
        CNT              => CNT, 
        CNTBITS          => CNTBITS,
        CNTSTOP          => CNTSTOP,
        DOUT_VLD         => VLD,
        READ_DATA        => READ_DATA, 
        CNTR             => CNTR
    );
    process(CLK) begin
      if rising_edge(CLK) then
        DOUT_VLD <= ZERO;
        if CNTR = '1' then 
          CNT <= CNT + "1";  
        else
          CNT <= "00001";  
        end if;
        if RST = '1' then
          DOUT <= "00000000"; 
        end if;
         if VLD = '0' then
          VLD <= '1'; 
        end if;
        if CNTBITS = "1000" then
           CNTSTOP <= CNTSTOP + "1";
        end if;
        if CNTSTOP = "1000" then
            DOUT_VLD <= '1';
            CNTBITS <= "0000";
            CNTSTOP <= "0000";
        end if;
        if READ_DATA = '1' then
          if CNT(4) = '1' then
            CNT <= "00001"; 
            case CNTBITS is
              when "0000" => DOUT(0) <= DIN; 
              when "0001" => DOUT(1) <= DIN; 
              when "0010" => DOUT(2) <= DIN; 
              when "0011" => DOUT(3) <= DIN; 
              when "0100" => DOUT(4) <= DIN; 
              when "0101" => DOUT(5) <= DIN;  
              when "0110" => DOUT(6) <= DIN; 
              when "0111" => DOUT(7) <= DIN;  
              when others => null;
            end case;
            CNTBITS <= CNTBITS + "1";   
          end if;    
      end if;
  end if;
end process;
end behavioral;
