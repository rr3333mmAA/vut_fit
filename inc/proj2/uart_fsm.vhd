-- uart_fsm.vhd: UART controller - finite state machine
-- Author(s): Abayev Amirkhan (xabaye00)
--
library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------
entity UART_FSM is
port(
   CLK        : in std_logic;
   RST        : in std_logic;
   DIN        : in std_logic;
   CNT        : in std_logic_vector(4 downto 0);
   CNTBITS    : in std_logic_vector(3 downto 0);
   CNTSTOP    : in std_logic_vector(3 downto 0);
   DOUT_VLD   : out std_logic;
   READ_DATA  : out std_logic;
   CNTR       : out std_logic
   );
end entity UART_FSM;

-------------------------------------------------
architecture behavioral of UART_FSM is
type FSM_State is (
	wait_for_start,
	wait_first_bit,
	read_data_s,
	wait_stop_bit,
	output
);
signal state : FSM_State := wait_for_start;
begin 
  READ_DATA <= '1' when state = read_data_s 
  else '0';
  DOUT_VLD <= '1' when state = output
  else '0';
  CNTR <= '1' when state = wait_first_bit or state = read_data_s 
  else '0';

  process (CLK) begin 
    if rising_edge(CLK) then
      if RST = '1' then
        state <= wait_for_start;
      else
          case state is
          when wait_for_start => if DIN = '0' then
                                    state <= wait_first_bit;
                                  end if;
          when wait_first_bit => if CNT = "10110" then
                                    state <= read_data_s;
                                  end if;
          when read_data_s => if CNTBITS = "1000" then
                                    state <= wait_stop_bit;
                                  end if;
          when wait_stop_bit  => if CNTSTOP = "1000" then
                                  state <= output; 
                                  end if;
          when output => state <= wait_for_start;
          when others          => null;
          end case; 
      end if;
    end if;
  end process;
end behavioral;
