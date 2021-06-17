/**
 * @file example.cpp
 * @brief cpp example file.
 * @uathor Jan Jaap Kempenaar, University of Twente.
 */

#include <iostream>
#include "gpmc_driver_cpp.h"

int main(int argc, char* argv[])
{
  if (2 != argc)
  {
    std::cout << "Usage: " << argv[0] << " <device_name>" << std::endl;
    return 1;
  }
  
  std::cout << "GPMC driver cpp-example" << std::endl;
  // Create GPMC device driver object
  std::cout << "Opening gpmc_fpga..." << std::endl;
  gpmc_driver Device(argv[1]);
  
  if (!Device.isValid())
  {
    std::cerr << "Error opening gpmc_fpga device: %s" << std::endl;
    return 1;
  }
  // define the (16-bit) variable to send/receive
  unsigned short value = 100;
  
  // write the value to idx 2
  int idx = 2;
  Device.setValue(value, idx);
  printf("Set value of %i to idx %d.\n", value, idx);  

  // read the value back from idx 0
  idx = 2;
  value = Device.getValue(idx);;
  printf("read back : %i from idx %d\n", value, idx);
  
  std::cout << "Exiting..." << std::endl;
  return 0;
}
